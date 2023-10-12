//--------------------------------------------------------------------
// необходимо изменить и добавить в исходник мурмулятора
// main.c
#include "usb_key.h"

//....................................................................
	d_joy_init();
	
	g_delay_ms(100);

	// init_TFT();
	startVGA();
	
	g_delay_ms(100);
	//start_PS2_capture(); // заменить на Init_keyboard (400000,18,19,0x77);
  Init_keyboard (400000,18,19,0x77);
  //....................................................................
  
  	printf("starting main loop \n");

	while(1){
		//current_time = get_absolute_time();
	//	if (decode_PS2())  
		if (decode_key())   // заменить decode_PS2() на decode_key()
//.......................................................................

// для мыши
//zx_machine.c

static uint8_t FAST_FUNC(in_z80)(z80* const z, uint8_t port) {
	
	uint8_t portH=z->_hi_addr_port;
	uint8_t portL=port;
	uint16_t port16=(portH<<8)|portL;


	if (port16&1)
	{
		uint16_t not_port16=~port16;
		
//================================================
/*
 Kempston Mouse i2c address 0x77
1 #FADF - поpт  кнопок
2 #FBDF - поpт X-кооpдинаты;
3 #FFDF - поpт У-кооpдинаты.
4 Kempston джойстик направления движения мыши
проверять до kempston
 */
         
		if ((port16 == 0xfadf)||(port16 == 0xfbdf)||(port16 == 0xffdf))
		
		{   
			

		if (port16 == 0xfadf){
		  //   G_PRINTF("port #FADF: %x=%x\n",port16,ibuff[1]);	
            return ibuff[1];  //#FADF
		} 
		
		if (port16 == 0xfbdf) {

			return ibuff[2];  //#FBDF
		}
		if (port16 == 0xffdf) {

			return ibuff[3];  //#FFDF
		}
	}
// кемпстое джой анологично добавляется  ibuff[4]
	//if ((port16&0x20)==0x0) {return zx_input.kempston;}  //kempston{return 0xff;};//
        //if ((port16&0x20)==0x0) {return ibuff[4];}//Kempston джойстик
        if ((port16 & 0x20) == 0x0) {return (zx_input.kempston  | ibuff[4]);}
//================================================

//как то так


/*
USB to I2C для MURMULATOR данные передаваеиые через I2C
ibuff[0] какие устройства подключены по USB

ibuff[1] мышь кнопки

ibuff[2] мышь X

ibuff[3] мышь Y

ibuff[4] джойстик кемпстон пока зарезервированно данные с него можно наверное уже куда то пихать отдает 0xff если не подключен

ibuff[5 6 7 8 9] резерв

ibuff[10] по ibuff[25] клавиатура

ibuff[26] ibuff[31] пока оставил для ровного счета можно их не считывать
*/
