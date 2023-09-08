/*
 * IC2_rp2040.h
 *
 * 
 *  Author: audioDIWHY
 */ 


#ifndef RP2040I2C_H_
#define RP2040I2C_H_
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#include "stdint.h"

//choose IC2 port 0 and set speed
void I2C_Init0(int baudrt);

//choose IC2 port 1 and set speed
void I2C_Init1(int baudrt);

void I2C_DInit0(void);
void I2C_DInit1(void);



//choose GPIO to use for I2C ex: GPIO4,5 would be 4,5. Pull yer pins UP.
void I2C_Pins(uint8_t sdapn, uint8_t sclpn);

//choose GPIO to use for I2C ex: GPIO4,5 would be 4,5. No Pullup from MCU.
void I2C_Pins_NoPullup(uint8_t sdapn, uint8_t sclpn);

//write I2C bytes then stop
//arguments:
//*i2c    i2c0 or i2c1
//addr    address of I2C chip 
//*src    pointer to buffer that has the data you want to write
//nbytes  number of data to write, not including address
uint16_t I2C_Write_nbytes_stop(i2c_inst_t *i2c, const uint addr, const uint8_t *src, const uint8_t nbytes);

//write I2C bytes without stop
//arguments:
//*i2c    i2c0 or i2c1
//addr    address of I2C chip 
//*src pointer to buffer that has the data you want to write
//nbytes--number of data to write, not including address
uint16_t I2C_Write_nbytes_nostop(i2c_inst_t *i2c, const uint addr, const uint8_t *src, const uint8_t nbytes);
 
//read I2C bytes then stop
//argments:
//*i2c    i2c0 or i2c1
//addr if I2C chip 
//*dst buffer that has the data you read--output goes to buffer, not returned by function
//nbytes--number of data to write, not including address
uint16_t I2C_Read_nbytes_stop(i2c_inst_t *i2c, uint8_t addr, uint8_t *dst, uint8_t nbytes);

//read I2C bytes without stop
//argments:
//*i2c    i2c0 or i2c1
//addr if I2C chip 
//*dst buffer that has the data you read--output goes to buffer, not returned by function
//nbytes--number of data to write, not including address
uint16_t I2C_Read_nbytes_nostop(i2c_inst_t *i2c, uint8_t addr, uint8_t *dst, uint8_t nbytes);

 
#endif /* RP2040I2C_H_ */
