#line 74 "1_memory.md"
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
