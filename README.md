# GBDisassembler

This is a really simple gameboy rom disassembler, it only supports roms with no memory controller (being limited to 32k).
This is due to the fact that bank switching logic needs partial "emulator implementation" as it needs to keep "watching" specific registers and memory rangesthat might be used for bank switching.

The idea here is to have a simple disassembler that can be easily understood, there is no cmake or makefile, to compile just use plain: 
g++ main.cpp header.cpp stringify.cpp tracer.cpp decoder.cpp --std=c++11

To run the disassembler just use ./a.out [ROM].

Code to handle "Call" opcodes was partially implemented but it seems to be failling due to extra opcode handling and this might not be possible as it might need (like bank switching) to be aware of register states, so it remains commented.

This is an attempt to demonstrate how a disassembler would be implemented and for the most part the code is simple and avoid "tricks".
It should be used with a gameboy documentation to understand from where the "magic values" came from, I recommend the following links:

https://gekkio.fi/files/gb-docs/gbctr.pdf
http://marc.rawer.de/Gameboy/Docs/GBCPUman.pdf
http://gbdev.gg8.se/wiki/articles/Memory_Bank_Controllers#0000-3FFF_-_ROM_Bank_00_.28Read_Only.29
https://www.pastraiser.com/cpu/gameboy/gameboy_opcodes.html