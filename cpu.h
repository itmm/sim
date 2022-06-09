#line 129 "1_memory.md"
#pragma once

class bus;

class cpu {
		int a_;
		int x_;
		int y_;
		int p_ { 0 };
		int sp_ { 0 };
		int pc_ { 0 };
	public:
		void run(bus &b);
};
