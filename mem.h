#line 107 "1_memory.md"
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
