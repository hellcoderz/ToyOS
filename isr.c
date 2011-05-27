typedef struct registers
{
   unsigned long ds;                  // Data segment selector
   unsigned long edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha.
   unsigned long int_no, err_code;    // Interrupt number and error code (if applicable)
   unsigned long eip, cs, eflags, useresp, ss; // Pushed by the processor automatically.
} registers_t;


void isr_handler(registers_t regs)
{
   puts("recieved interrupt: ");
   putdec(regs.int_no);
   putch('\n');
}