#include "common.h"

//I gotta set mmu before this code, that way I can be sure of using physical or virtual addresses

#define	K9_COM_ADDRESS	*((vu32*)0xDFFF5000)
#define	ARM11_BUSY		0xDEADC0DE
#define	ENABLE_TOP_LCD	0x4C434469
#define	SET_SCREEN_BUF	0x42554646

void LCD_Init(void){
	*((u32*)0x10400030) &= 0xFFFFF0FF;
	*((u32*)0x10400004) = 0x70100;
	*((u32*)0x1040001C) &= 0xFFFFFFFD;
	*((u32*)0x1040002C) &= 0xFFFFFFFD;
	*((u32*)0x10400050) = 0x22221200;
	*((u32*)0x10400054) = 0xFF2;
	*((u32*)0x10401000) = 0;
	*((u32*)0x10401080) = 0x12345678;
	*((u32*)0x104010C0) = 0xFFFFFFF0;
	*((u32*)0x104010D0) = 1;
	*((u32*)0x10400C18) &= 0xFFFFFEFF;
	
	*((u32*)0x10202240) = 0xFFFFFFFF; //Enable LCD backlight?
	*((u32*)0x104000C0) = 0x20000000; //Power on the backlight
	
	/* Initialize the Framebuffer Setup */
	*((u32*)0x10400400) = 0x1C2;
	*((u32*)0x10400404) = 0xD1;
	*((u32*)0x10400408) = 0x1C1;
	*((u32*)0x1040040C) = 0x1C1;
	*((u32*)0x10400410) = 0;
	*((u32*)0x10400414) = 0xCF;
	*((u32*)0x10400418) = 0xD1;
	*((u32*)0x1040041C) = 0x1C501C1;
	*((u32*)0x10400420) = 0x10000;
	*((u32*)0x10400424) = 0x19D;
	*((u32*)0x10400428) = 2;
	*((u32*)0x1040042C) = 0x1C2;
	*((u32*)0x10400430) = 0x1C2;
	*((u32*)0x10400434) = 0x1C2;
	*((u32*)0x10400438) = 1;
	*((u32*)0x1040043C) = 2;
	*((u32*)0x10400440) = 0x1960192;
	*((u32*)0x10400444) = 0;
	*((u32*)0x10400448) = 0;
	*((u32*)0x1040045C) = (0x190 << 16) | 0xF0; //Screen Width and Height
	*((u32*)0x10400460) = 0x1c100d1;
	*((u32*)0x10400464) = 0x1920002;
	*((u32*)0x10400470) = 0x80340; //Frame Buffer Format
	*((u32*)0x1040049C) = 0;
	
	*((u32*)0x10400468) = 0x18300000; //Left Framebuffer 0
	*((u32*)0x1040046C) = 0x18300000; //Left Framebuffer 1
	*((u32*)0x10400494) = 0x18300000; //Right Framebuffer 0
	*((u32*)0x10400498) = 0x18300000; //Right Framebuffer 1
	*((u32*)0x10400478) = 1; //Framebuffer Select
	*((u32*)0x10400474) = 0x10501;
}

void Set_Framebuffer(void){
	*((u32*)0x1EF00468) = 0x18300000;
	*((u32*)0x1EF0046C) = 0x18300000;
	*((u32*)0x1EF00494) = 0x18300000;
	*((u32*)0x1EF00498) = 0x18300000;
	
	*((u32*)0x1EF00568) = 0x18346500;
	*((u32*)0x1EF0056C) = 0x18346500;
}

void _start(void){
	while(1){
		while(!K9_COM_ADDRESS);
		if (K9_COM_ADDRESS == ENABLE_TOP_LCD){
			K9_COM_ADDRESS = ARM11_BUSY;
			LCD_Init();
			K9_COM_ADDRESS = 0;
		}
		if (K9_COM_ADDRESS == SET_SCREEN_BUF){
			K9_COM_ADDRESS = ARM11_BUSY;
			Set_Framebuffer();
			K9_COM_ADDRESS = 0;
		}
		K9_COM_ADDRESS = 0;
	}
	while(1);
}