#line 105 "1_memory.md"
#pragma once

#include "bus.h"

class ram: public device {
		char *data_;
	public:
		ram(int start, char *data_begin, char *data_end): device { start, start + static_cast<int>(data_end - data_begin) }, data_ { data_begin } { }
		void put8(int addr, int value) override { data_[addr] = static_cast<char>(value); }
		int get8(int addr) override { return data_[addr]; }
};

class rom: public device {
		const char *data_;
	public:
		rom(int start, char *data_begin, char *data_end): device { start, start + static_cast<int>(data_end - data_begin) }, data_ { data_begin } { }
		void put8(int addr, int value) override { }
		int get8(int addr) override { return data_[addr]; }
};
