echo Now assembling, compiling, and linking your kernel:
nasm -f aout -o start.o start.asm
rem Remember this spot here: We will add 'gcc' commands here to compile C sources

gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o main.o main.c



rem This links all your files. Remember that as you add *.o files, you need to
rem add them after start.o. If you don't add them at all, they won't be in your kernel!
ld -T link.ld -o kernel.bin main.o start.o
echo Done!
pause