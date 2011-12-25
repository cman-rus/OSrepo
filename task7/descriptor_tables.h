#include "common.h"

void init_descriptor_tables();

struct idt_entry_struct
{
    u16int base_lo;
    u16int sel;
    u8int  always0;
    u8int  flags; 
    u16int base_hi;
} __attribute__((packed));

typedef struct idt_entry_struct idt_entry_t;

struct idt_ptr_struct
{
    u16int limit;
    u32int base;
} __attribute__((packed));

typedef struct idt_ptr_struct idt_ptr_t;

extern void isr0 ();
extern void isr1 ();
extern void isr2 ();
extern void isr3 ();
extern void isr4 ();
extern void isr5 ();
extern void isr6 ();
extern void isr7 ();
