#line 133 "1_memory.md"
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
