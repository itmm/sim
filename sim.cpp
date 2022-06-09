#line 166 "1_memory.md"
#include "bus.h"
#include "clk.h"
#include "cpu.h"
#include "mem.h"

int main() {
	clk ck;
	bus b { ck };
	char ram_data[0x4000];
	char rom_data[0x4000];
	b.add(std::make_unique<ram>(0x0000, ram_data, ram_data + sizeof(ram_data)));
	b.add(std::make_unique<rom>(0xc000, rom_data, rom_data + sizeof(rom_data)));
	cpu cp;
	cp.run(b);
}
