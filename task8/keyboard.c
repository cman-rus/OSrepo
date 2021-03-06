#include "common.h"
#include "keyboard.h"

unsigned short key_buffer_head, key_buffer_tail;
char key_buffer[KEYBOARD_BUFFER_SIZE];
bool key_shift, key_ctrl, key_alt, key_caps, key_spec;

char mapNormal[] = { 0x00,0x1B,'1','2','3','4','5','6','7','8','9','0','-','=','\r','\t','q','w','e','r','t','y','u','i','o','p','[',']','\n',0x80,'a','s','d','f','g','h','j','k','l',';',0x2F,0x8C,0x80,0x86,'z','x','c','v','b','n','m',',','.','/',0x80,'*',0x80,' ',0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,'0',0xB1 };
char mapShifted[] = { 0x00,0x21,'!','@','#','$','%','^','&','*','(',')','_','+','\r','\t','Q','W','E','R','T','Y','U','I','O','P','{','}',0x0F,0x80,'A','S','D','F','G','H','J','K','L',':',0x2A,'~',0x80,'|','Z','X','C','V','B','N','M','<','>','?',0x80,'*',0x80,' ',0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,'7','8','9',0x80,'4','5','6',0x80,'1','2','3','0',0xB1};
char capsNormal[] = { 0x00,0x1B,'1','2','3','4','5','6','7','8','9','0','-','=','\r','\t','Q','W','E','R','T','Y','U','I','O','P','[',']','\n',0x80,'A','S','D','F','G','H','J','K','L',';',0x2F,0x8C,0x80,'|','Z','X','C','V','B','N','M',',','.','/',0x80,'*',0x80,' ',0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,'0',0xB1};
char capsShifted[] = {0,0x1B,'!','@','#','$','%','^','&','*','(',')','_','+','\r','\t','q','w','e','r','t','y','u','i','o','p','{','}',015,0x80,'a','s','d','f','g','h','j','k','l',':',0x2A,'~',0x80,0x86,'z','x','c','v','b','n','m','<','>','?',0x80,'*',0x80,' ',0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,'7','8','9',0x80,'4','5','6',0x80,'1','2','3','0',0xB1};


void key_init(){
	key_buffer_head = 0;
	key_buffer_tail = 0;
}

char key_get(){
	char c = key_buffer[key_buffer_tail];
	key_buffer_tail = (key_buffer_tail+1) % KEYBOARD_BUFFER_SIZE;
	return c;
}

bool key_isEmpty(){
	return key_buffer_head == key_buffer_tail;
}

int key_special(unsigned char code){
	switch(code)	{
		case 0x36: //R-Shift down
		case 0x2A: //L-Shift down
			key_shift = 1;
			break;
		case 0xB6: //R-Shift up
		case 0xAA: //L-Shift up
			key_shift = 0;
			break;
		case 0x1D: //Control down
			key_ctrl = 1;
			break;
		case 0x9D: //Control up
			key_ctrl = 0;
			break;
		case 0x38: //Alt down
			key_alt = 1;
			break;
		case 0xB8: //Alt up
			key_alt = 0;
			break;
		case 0x3A: //Caps down
			if(key_spec == 1){
				key_caps = key_caps^1;
				key_spec = 0;
			}
			break;
		case 0xBA: //Caps Up
			key_spec = 1;
			break;
		case 0xE0:
			break;
		default:
			return 0;
		}
	return 1;
}

void key_interrupt(){
	unsigned char scanCode = inb(0x60), asciiCode;
	outb(0x20, 0x20);

	if(!(key_special(scanCode) | (scanCode >= 0x80))){
		if(key_shift)
			if(!key_caps)
				asciiCode = mapShifted[scanCode];
			else
				asciiCode = capsShifted[scanCode];
		else
			if(!key_caps)
				asciiCode = mapNormal[scanCode];
			else
				asciiCode = capsNormal[scanCode];
		key_buffer[key_buffer_head] = asciiCode;
		key_buffer_head = (key_buffer_head+1) % KEYBOARD_BUFFER_SIZE;
	}
}
