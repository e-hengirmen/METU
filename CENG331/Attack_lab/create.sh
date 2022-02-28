gcc -g deneme.c
objdump -d a.out >deneme.asm
./hex2raw <solve >solve.raw
gdb a.out -x commandHelp
