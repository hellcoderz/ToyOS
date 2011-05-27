/* Basically, we are going to use this as a GDT entry to section of memory and permissions/access 

   Interesting resources about what is going on here:
	http://linuxgazette.net/82/raghu.html
	http://wiki.osdev.org/GDT_Tutorial
	http://www.jamesmolloy.co.uk/tutorial_html/4.-The%20GDT%20and%20IDT.html
*/

static void idt_install();
static void gdt_install();
static void idt_set_gate(unsigned char,unsigned long,unsigned int,unsigned char);
static void gdt_set_gate(int num, unsigned long, unsigned long, unsigned char, unsigned char);


struct gdt_entry
{
    unsigned short limit_low;
    unsigned short base_low;
    unsigned char base_middle;
    unsigned char access;
    unsigned char granularity;
    unsigned char base_high;
} __attribute__((packed));


struct gdt_ptr
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));


void init_tables()
{
	gdt_install();
	idt_install();
}


/* Mix of code from Bran's tutorial and JamesM's. */
struct gdt_entry gdt_entries[5];
struct gdt_ptr gp;


static void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran)
{
    /* Setup the descriptor base address */
    gdt_entries[num].base_low = (base & 0xFFFF);
    gdt_entries[num].base_middle = (base >> 16) & 0xFF;
    gdt_entries[num].base_high = (base >> 24) & 0xFF;

    /* Setup the descriptor limits */
    gdt_entries[num].limit_low = (limit & 0xFFFF);
    gdt_entries[num].granularity = ((limit >> 16) & 0x0F);

    /* Finally, set up the granularity and access flags */
    gdt_entries[num].granularity |= (gran & 0xF0);
    gdt_entries[num].access = access;
}


static void gdt_install()
{
    /* Setup the GDT pointer and limit 
    */
   gp.limit = (sizeof(struct gdt_entry) * 5) - 1;
   gp.base = &gdt_entries;

   gdt_set_gate(0, 0, 0, 0, 0);                // Null segment
   gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
   gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
   gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
   gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

  
    /* Flush out the old GDT and install the new changes! */
    gdt_flush();

	
}




struct idt_entry
{
	unsigned int base_lo;
	unsigned int sel;
	unsigned char always0;
	unsigned char flags;
	unsigned int	base_hi;
} __attribute__((packed));

struct idt_ptr
{
	unsigned int limit;
	unsigned long base;
} __attribute__((packed));




struct idt_entry idt_entries[256];
struct idt_ptr id;


extern void isr0 ();
extern void isr1 ();
extern void isr2 ();
extern void isr3 ();
extern void isr4 ();
extern void isr5 ();
extern void isr6 ();
extern void isr7 ();
extern void isr8 ();
extern void isr9 ();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();



static void idt_set_gate(unsigned char num, unsigned long base, unsigned int sel, unsigned char flags)
{	
	idt_entries[num].base_lo = base & 0xFFFF;
   	idt_entries[num].base_hi = (base >> 16) & 0xFFFF;

   	idt_entries[num].sel     = sel;
   	idt_entries[num].always0 = 0;
   	idt_entries[num].flags   = flags 
}



static void idt_install()
{
	id.limit = sizeof(struct idt_entry) * 256 -1;
   	id.base  = &idt_entries;

   	memsetw(&idt_entries, 0, sizeof(struct idt_entry)*256);

   	idt_set_gate( 0, (unsigned long)isr0 , 0x08, 0x8E);
   	idt_set_gate( 1, (unsigned long)isr1 , 0x08, 0x8E);
   	idt_set_gate( 2, (unsigned long)isr2 , 0x08, 0x8E);
	idt_set_gate( 3, (unsigned long)isr3 , 0x08, 0x8E);
	idt_set_gate( 4, (unsigned long)isr4 , 0x08, 0x8E);
	idt_set_gate( 5, (unsigned long)isr5 , 0x08, 0x8E);
	idt_set_gate( 6, (unsigned long)isr6 , 0x08, 0x8E);
	idt_set_gate( 7, (unsigned long)isr7 , 0x08, 0x8E);
	idt_set_gate( 8, (unsigned long)isr8 , 0x08, 0x8E);
	idt_set_gate( 9, (unsigned long)isr9 , 0x08, 0x8E);
	idt_set_gate( 10, (unsigned long)isr10 , 0x08, 0x8E);
	idt_set_gate( 11, (unsigned long)isr11 , 0x08, 0x8E);
	idt_set_gate( 12, (unsigned long)isr12 , 0x08, 0x8E);
	idt_set_gate( 13, (unsigned long)isr13 , 0x08, 0x8E);
	idt_set_gate( 14, (unsigned long)isr14 , 0x08, 0x8E);
	idt_set_gate( 15, (unsigned long)isr15 , 0x08, 0x8E);
	idt_set_gate( 16, (unsigned long)isr16 , 0x08, 0x8E);
	idt_set_gate( 17, (unsigned long)isr17 , 0x08, 0x8E);
	idt_set_gate( 18, (unsigned long)isr18 , 0x08, 0x8E);
	idt_set_gate( 19, (unsigned long)isr19 , 0x08, 0x8E);
	idt_set_gate( 20, (unsigned long)isr20 , 0x08, 0x8E);
	idt_set_gate( 21, (unsigned long)isr21 , 0x08, 0x8E);
	idt_set_gate( 22, (unsigned long)isr22 , 0x08, 0x8E);
	idt_set_gate( 23, (unsigned long)isr23 , 0x08, 0x8E);
	idt_set_gate( 24, (unsigned long)isr24 , 0x08, 0x8E);
	idt_set_gate( 25, (unsigned long)isr25 , 0x08, 0x8E);
	idt_set_gate( 26, (unsigned long)isr26 , 0x08, 0x8E);
	idt_set_gate( 27, (unsigned long)isr27 , 0x08, 0x8E);
	idt_set_gate( 28, (unsigned long)isr28 , 0x08, 0x8E);
	idt_set_gate( 29, (unsigned long)isr29 , 0x08, 0x8E);
	idt_set_gate( 30, (unsigned long)isr30 , 0x08, 0x8E);
	idt_set_gate( 31, (unsigned long)isr31 , 0x08, 0x8E);

   	idt_flush((unsigned long)&id);

}







