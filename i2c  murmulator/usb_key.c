/*
ibuff[0]
ibuff[1] мышь кнопки 
ibuff[2] мышь X
ibuff[3] мышь Y
ibuff[4] джойстик кемпстон пока зарезервированно данные с него можно наверное уже куда то пихать отдает 0xff
ibuff[5 6 7 8 9] резерв
ibuff[10]   по ibuff[25] клавиатура
ibuff[26] ibuff[31] пока оставил для ровного счета можно их не считывать

*/

#include "usb_key.h"
#include "kb_u_codes.h"
#include "ps2.h"
#include "g_config.h"
#include "I2C_rp2040.h"// это добавить
#include "usb_key.h"// это добавить
kb_u_state kb_st_ps2;
//----------------------------------------------
//   
//----------------------------------------------

//-----------------------------------------------------------------------------------------
// I  400000 18 19   address i2c 0x77
// Init_keyboard (400000,18,19,0x77);
void Init_keyboard (int baudrt,uint8_t sdapn, uint8_t sclpn,uint8_t adress_i2c ){

     I2C_Init1(baudrt);
     I2C_Pins(sdapn,sclpn);

	     ibuff[0] = 0x00; 
        ibuff[1] = 0xff; 
        ibuff[2] = 0xff; 
        ibuff[3] = 0xff; 

        I2C_Read_nbytes_stop(i2c1,adress_i2c , ibuff, 1);

        init_decode_key(ibuff[0]);

}
////////////////////////////////////////////////////////////////	

//---------------------------------------------- 
bool key_ps2(void){ 	return decode_PS2(); }
bool key_ps2_ms(void){ I2C_Read_nbytes_stop(i2c1,0x77, ibuff, 32);    return decode_PS2();  };// мышь
bool key_usb(void){ I2C_Read_nbytes_stop(i2c1,0x77, ibuff, 32);    return decode_USB();  };// клавиатура
bool key_usb_ms(void) { I2C_Read_nbytes_stop(i2c1,0x77, ibuff, 32);    return decode_USB();  }// клавиатура + мышь


bool (*decode_key)(); // определение указателя на функцию
void init_decode_key(uint8_t kms)
{
   switch (kms)
   {
   case 0:
      I2C_DInit1();
      start_PS2_capture();
      decode_key = key_ps2;
      break; // 0 клавиатура ps/2
   case 1:
      start_PS2_capture();
      decode_key = key_ps2_ms;
      break; // 1  клавиатура ps/2 + мышь
   case 2:
      decode_key = key_usb;
      break; // 2  клавиатура usb
   case 3:
      decode_key = key_usb_ms;
      break; // 3 клавиатура usb + мышь
   default:
      I2C_DInit1();
      start_PS2_capture();
      decode_key = key_ps2;
      break;
   }
}

//------------------------------------------------
//--------------------------------------
bool decode_USB()

{ 
static uint32_t  old_kb_0 = 0;
static uint32_t  old_kb_1 = 0;
static uint32_t  old_kb_2 = 0;
static uint32_t  old_kb_3 = 0;

   
   uint32_t unx = 0;
   static uint8_t  flag_kb = 0;

   unx = ibuff[10] ; unx = unx << 24; kb_st_ps2.u[0] =  unx; //!!!
   unx = ibuff[11] ; unx = unx << 16; kb_st_ps2.u[0] = kb_st_ps2.u[0] | unx;
   unx = ibuff[12] ; unx = unx << 8;  kb_st_ps2.u[0] = kb_st_ps2.u[0] | unx; 
   unx = ibuff[13] ;                  kb_st_ps2.u[0] = kb_st_ps2.u[0] | unx;

   unx = ibuff[14] ; unx = unx << 24; kb_st_ps2.u[1] =  unx; //!!!
   unx = ibuff[15] ; unx = unx << 16; kb_st_ps2.u[1] = kb_st_ps2.u[1] | unx;
   unx = ibuff[16] ; unx = unx << 8;  kb_st_ps2.u[1] = kb_st_ps2.u[1] | unx; 
   unx = ibuff[17] ;                  kb_st_ps2.u[1] = kb_st_ps2.u[1] | unx;

   unx = ibuff[18] ; unx = unx << 24; kb_st_ps2.u[2] =  unx; //!!!
   unx = ibuff[19] ; unx = unx << 16; kb_st_ps2.u[2] = kb_st_ps2.u[2] | unx;
   unx = ibuff[20] ; unx = unx << 8;  kb_st_ps2.u[2] = kb_st_ps2.u[2] | unx; 
   unx = ibuff[21] ;                  kb_st_ps2.u[2] = kb_st_ps2.u[2] | unx;

   unx = ibuff[22] ; unx = unx << 24; kb_st_ps2.u[3] =  unx; //!!!
   unx = ibuff[23] ; unx = unx << 16; kb_st_ps2.u[3] = kb_st_ps2.u[3] | unx;
   unx = ibuff[24] ; unx = unx << 8;  kb_st_ps2.u[3] = kb_st_ps2.u[3] | unx; 
   unx = ibuff[25] ;                  kb_st_ps2.u[3] = kb_st_ps2.u[3] | unx;





if ((kb_st_ps2.u[3] == 0) & (kb_st_ps2.u[2] == 0) & (kb_st_ps2.u[1] ==0) & (kb_st_ps2.u[0] == 0)) // кнопки не нажаты
    { 
      if (flag_kb == 0)  return false; 
     else {flag_kb = 0; old_kb_0= 0; old_kb_1=0; old_kb_2=0; old_kb_3=0; return true; }  // кнопки не нажаты но надо обнулить
      }

      // задержка нажатия клавиш up down ///////////////////////////////////////
      if ((kb_st_ps2.u[2] & KB_U2_DOWN) | (kb_st_ps2.u[2] & KB_U2_UP))
      {

     static uint8_t delay_kb = 0; // задержка нажатия клавиш влияет только в ФМ
     delay_kb++;
     if (delay_kb == 36)
        delay_kb = 0;
     else
        return false;
     flag_kb = 1;
     return true;
      }

      /////////////////////////////////////////////////////////////////////////

      if ((kb_st_ps2.u[3] == old_kb_3) & (kb_st_ps2.u[2] == old_kb_2) & (kb_st_ps2.u[1] == old_kb_1) & (kb_st_ps2.u[0] == old_kb_0))
     return false; //

      old_kb_0 = kb_st_ps2.u[0];
      old_kb_1 = kb_st_ps2.u[1];
      old_kb_2 = kb_st_ps2.u[2];
      old_kb_3 = kb_st_ps2.u[3];
      flag_kb = 1;
      return true; // произошли изменения
}

/******************************************************************************************/
