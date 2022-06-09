`clk.h`

```c++
#pragma once

#include <cassert>

class clk {
		unsigned long time_ { 0ul } ;
	public:
		clk &operator++() { ++time_; return *this; }
		unsigned long time() const { return time_; }
};

inline unsigned long elapsed(const clk &since, const clk &now) {
	assert(since.time() <= now.time());
	return now.time() - since.time();
}
```

`bus.h`

```c++
#pragma once

#include "clk.h"

#include <memory>
#include <vector>

class device {
		int begin_, end_;
	protected:
		device(int begin, int end): begin_ { begin }, end_ { end } { }
	public:
		int begin() const { return begin_; }
		int end() const { return end_; }
		virtual ~device() { }
		virtual void put8(int addr, int value) = 0;
		virtual int get8(int addr) = 0;
};

class bus {
		clk &clk_;
		std::vector<std::unique_ptr<device>> devices_;
	public:
		bus(clk &clk): clk_ { clk } { }
		clk &clock() { return clk_; };
		void put8(int addr, int value);
		void put16(int addr, int value);
		int get8(int addr);
		int get16(int addr);
		bus &add(std::unique_ptr<device> device) {
			assert(device);
			devices_.push_back(std::move(device));
			return *this;
		}
};

inline void bus::put16(int addr, int value) {
	put8(addr, value);
	put8(addr + 1, value >> 8);
}

inline int bus::get16(int addr) {
	return get8(addr) | (get8(addr + 1) << 8);
}
```

`bus.cpp`


```c++
#include "bus.h"

#include <cassert>

void bus::put8(int addr, int value) {
	++clk_;
	int found { 0 };
	for (auto &d : devices_) {
		if (addr >= d->begin() && addr < d->end()) {
			d->put8(addr, value);
			++found;
		}
	}
	assert(found && "invalid put address");
}

#include <iostream>

int bus::get8(int addr) {
	++clk_;
	for (auto &d : devices_) {
		if (addr >= d->begin() && addr < d->end()) {
			return d->get8(addr);
		}
	}
	assert(false && "invalid get address");
	return 0x00;
}
```

`mem.h`

```c++
#pragma once

#include "bus.h"

#include <cassert>

class ram: public device {
		char *data_;
	public:
		ram(int start, char *data_begin, char *data_end): device { start, start + static_cast<int>(data_end - data_begin) }, data_ { data_begin } { }
		void put8(int addr, int value) override { data_[addr - begin()] = static_cast<char>(value); }
		int get8(int addr) override { return data_[addr - begin()] & 0xff; }
};

class rom: public device {
		const char *data_;
	public:
		rom(int start, char *data_begin, char *data_end): device { start, start + static_cast<int>(data_end - data_begin) }, data_ { data_begin } { }
		void put8(int addr, int value) override { assert(false && "put to ROM"); }
		int get8(int addr) override { return data_[addr - begin()] & 0xff; }
};
```

`cpu.h`

```c++
#pragma once

class bus;

class cpu {
		enum {
			p_c = 0x1, p_z = 0x2, p_i = 0x3, p_d = 0x4,
			p_b = 0x5, p_e = 0x6, p_v = 0x7, p_n = 0x8
		};
		enum {
			op_brk = 0x00,
			op_nop = 0xea
		};
		int a_;
		int x_;
		int y_;
		int p_ { p_e };
		int sp_ { 0 };
		int pc_ { 0 };
	public:
		void reset(bus &b);
		void run(bus &b);
};
```

`cpu.cpp`

```c++
#include "cpu.h"

#include "mem.h"

#include <cassert>

void cpu::reset(bus &b) {
	p_ = p_e | p_i;
	pc_ = b.get16(0xfffc);
}

void cpu::run(bus &b) {
	for (;;) {
		auto cmd { b.get8(pc_++) };
		switch (cmd) {
			case op_brk: return;
			case op_nop: break;
			default: assert(false && "unknown opcode");
			
		}
	}
}
```

`sim.cpp`

```c++
#include "bus.h"
#include "clk.h"
#include "cpu.h"
#include "mem.h"

int main() {
	clk ck;
	bus b { ck };
	char ram_data[0x4000];
	char rom_data[0x4000];
	rom_data[0x3ffe] = '\x00';
	rom_data[0x3fff] = '\xc0';
	rom_data[0x3ffc] = '\x00';
	rom_data[0x3ffd] = '\xc0';
	rom_data[0x0000] = '\xea';
	rom_data[0x0001] = '\xea';
	b.add(std::make_unique<ram>(0x0000, ram_data, ram_data + sizeof(ram_data)));
	b.add(std::make_unique<rom>(0xc000, rom_data, rom_data + sizeof(rom_data)));
	cpu cp;
	cp.reset(b);
	cp.run(b);
}
```
