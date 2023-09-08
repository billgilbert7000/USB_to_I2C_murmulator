#pragma once
#include "inttypes.h"
#include <stdio.h>
#include "kb_u_codes.h"
#include "ps2.h"
#include "g_config.h"
#include "I2C_rp2040.h"
#include "usb_key.h"
extern kb_u_state kb_st_ps2;
uint8_t ibuff[32] ;


bool (*decode_key)();  // определение указателя на функцию  

bool decode_USB();
void Init_keyboard (int baudrt,uint8_t sdapn, uint8_t sclpn,uint8_t adress_i2c );
