#include "monitor.h"

u16int * video_memory;
int n=0;
int p=0;

void monitor_put(char c)
{
	u8int attributeByte = (0 /*black*/ << 4) | (15 /*white*/ & 0x0F);
	u16int blank = c /* ci */ | (attributeByte << 8);
	video_memory[p+n*80] = blank;
	return;
}

// Clears the screen, by copying lots of spaces to the framebuffer.
void monitor_clear()
{
	n=0;
	p=0;
	video_memory = (u16int *)0xB8000;

	int i=0;
        while(i<80*25)
        {
		u8int attributeByte = (0 /*black*/ << 4) | (15 /*white*/ & 0x0F);
    		u16int blank = 0x20 /* space */ | (attributeByte << 8);
		video_memory[i++] =  blank;
        }

	return;

}

void monitor_write(int n1, char *c)
{
	n = n1;
	p=0;
	
	while(c[p])
	{	
		monitor_put(c[p]);
		++p;
	}
	return;
}

