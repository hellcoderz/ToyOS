#include "isr.h"


typedef void (*isr_t)(registers_t); void register_interrupt_handler(unsigned char n, isr_t handler);

isr_t interrupt_handlers[256];

void register_interrupt_handler(unsigned char n, isr_t handler)
{
  puts("Inserting Handler");
  interrupt_handlers[n] = handler;
  puts("Handler inserted");
}

void isr_handler(registers_t regs)
{
   puts("recieved interrupt: ");
   putdec(regs.int_no);
   putch('\n');
}

void irq_handler(registers_t regs)
{
   if (regs.int_no >= 40)
   {
       outportb(0xA0, 0x20);
   }

   outportb(0x20, 0x20);

   if (interrupt_handlers[regs.int_no] != 0)
   {
       isr_t handler = interrupt_handlers[regs.int_no];
       handler(regs);
   }
}