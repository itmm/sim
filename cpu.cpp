#line 161 "1_memory.md"
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
