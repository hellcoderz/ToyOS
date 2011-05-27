#include "types.h"

void init_tables();

/* Reduce local variables as much as possible to preserve stack space. */



unsigned char *memcpy(unsigned char *dest, const unsigned char *src, int count)
{
	while(count--)
		*dest++ = *src++;
    	return dest;
}

unsigned char *memset(unsigned char *dest, unsigned char val, int count)
{
    while(count--)
        *dest++ = (unsigned char)val;
    return dest;
}

unsigned short *memsetw(unsigned short *dest, unsigned short val, int count)
{
    while(count--)
        *dest++ = (unsigned short)val;
    return dest;
}

int strlen(const char *str)
{
     const char *s;
     for (s = str; *s; ++s)
                ;
    return (s - str);
}

/* We will use this later on for reading from the I/O ports to get data
*  from devices such as the keyboard. We are using what is called
*  'inline assembly' in these routines to actually do the work */
unsigned char inportb (unsigned short _port)
{
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

/* We will use this to write to I/O ports to send bytes to devices. This
*  will be used in the next tutorial for changing the textmode cursor
*  position. Again, we use some inline assembly for the stuff that simply
*  cannot be done in C */
void outportb (unsigned short _port, unsigned char _data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}

/* This is a very simple main() function. All it does is sit in an
*  infinite loop. This will be like our 'idle' loop */
void main()
{
    /* You would add commands after here */

	init_tables();
	init_video();
	puts("GREETINGS PROFESSOR FALKEN");
	puts("\r\nWOULD YOU LIKE TO PLAY A GAME?\r\n");
	puthex(12345);
	putdec(8808);
	asm volatile ("int $0x3");
 	/* busy wait */
    	for (;;);
}