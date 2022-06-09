#line 24 "1_memory.md"
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
