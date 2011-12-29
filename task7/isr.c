#include "common.h"
#include "isr.h"
#include "monitor.h"

void isr_handler(registers_t regs)
{
    char str[30] = "recieved interrupt: ";
    monitor_write(2, str);
  
    char str2[10];
    str2[0] = regs.int_no + 0x30;
    monitor_write(3, str2);
}
