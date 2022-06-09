#line 148 "1_memory.md"
#include "cpu.h"

#include "mem.h"

void cpu::run(bus &b) {
	for (;;) {
		auto cmd { b.get8(pc_++) };
		switch (cmd) {
			case 0x00: return;
			
		}
	}
}
