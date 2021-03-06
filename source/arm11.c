#include "arm11.h"

#include <string.h>

void ARM11(void* fptr){
	ARM11Entry = (u32)fptr;
	while(ARM11Entry);
}

void debug(void* fptr){ //kinda like a thread?
	ARM11Entry = (u32)fptr; //don't wait (not recommended)
}

void ARM11Start(void){
	void setup(){
		__asm__ volatile (
			".WORD 0xF10C01C0 \n" //CPSID AIF ; Disable Interrupts
			"LDR SP, =0x27800000" //Set the Stack Pointer
		);
		
		while(1){
			ARM11Entry = 0;
			while(!ARM11Entry);
			((void (*)())ARM11Entry)();
		}
	}
	ARM11(setup);
}