sudo apt-get install gcc-multilib

nasm -f elf32 asmModule.asm -o asmModule 
gcc -m32 main.c -o asmModule -o main 