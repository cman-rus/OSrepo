#include "common.h"
#include "isr.h"
#include "monitor.h"

void isr_handler(registers_t regs)
{
    char str[30] = "recieved interrupt: ";
    monitor_write(2, str);
}
