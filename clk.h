#line 4 "1_memory.md"
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
