#include "monitor.h"
#include "descriptor_tables.h"

int main()
{
	monitor_clear();

	char str2[30]="Hello, Test program there!";
	monitor_write(0, str2);
	
	init_descriptor_tables();

	asm volatile("int $0x3");
	return 0;
}
