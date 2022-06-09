#line 188 "1_memory.md"
#include "bus.h"
#include "clk.h"
#include "cpu.h"
#include "mem.h"

int main() {
	clk ck;
	bus b { ck };
	char ram_data[0x4000];
	char rom_data[0x4000];
	rom_data[0x3ffe] = '\x00';
	rom_data[0x3fff] = '\xc0';
	rom_data[0x3ffc] = '\x00';
	rom_data[0x3ffd] = '\xc0';
	rom_data[0x0000] = '\xea';
	rom_data[0x0001] = '\xea';
	b.add(std::make_unique<ram>(0x0000, ram_data, ram_data + sizeof(ram_data)));
	b.add(std::make_unique<rom>(0xc000, rom_data, rom_data + sizeof(rom_data)));
	cpu cp;
	cp.reset(b);
	cp.run(b);
}
