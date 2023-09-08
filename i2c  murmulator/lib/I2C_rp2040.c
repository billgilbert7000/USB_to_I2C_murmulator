#include "I2C_rp2040.h"
 
 

void I2C_Init0(int baudrt)
{
i2c_inst_t *i2c = i2c0; //use port 0
i2c_init(i2c, baudrt);  //400K speed
}


void I2C_Init1(int baudrt)
{
i2c_inst_t *i2c = i2c1; //use port 0
i2c_init(i2c, baudrt);  //400K speed
}


void I2C_DInit0()
{
i2c_inst_t *i2c = i2c0; //use port 0
i2c_deinit(i2c);
}

void I2C_DInit1()
{
i2c_inst_t *i2c = i2c1; //use port 0
i2c_deinit(i2c);
}


void I2C_Pins(uint8_t sdapn, uint8_t sclpn)
{
    //set GPIO pins
    const uint sda_pin = sdapn;
    const uint scl_pin = sclpn;
    //use them for I2C
    gpio_set_function(sda_pin, GPIO_FUNC_I2C);
    gpio_set_function(scl_pin, GPIO_FUNC_I2C);
    
    //pull it up--that's what she said
    gpio_pull_up(sda_pin);
    gpio_pull_up(scl_pin);

}


void I2C_Pins_NoPullup(uint8_t sdapn, uint8_t sclpn)
{
    //set GPIO pins
    const uint sda_pin = sdapn;
    const uint scl_pin = sclpn;
    //use them for I2C
    gpio_set_function(sda_pin, GPIO_FUNC_I2C);
    gpio_set_function(scl_pin, GPIO_FUNC_I2C);

}


uint16_t I2C_Write_nbytes_stop(i2c_inst_t *i2c, const uint addr, const uint8_t *src, const uint8_t nbytes)
{
    uint16_t retx = 0;     
    uint16_t num_bytes_written = 0;  //return value--how many bytes written  
    uint8_t msg[nbytes + 1];

    // Check to make sure caller is sending 1 or more bytes
    if (nbytes < 1) {
        return 0;
    }
 
    // Write data to register(s) over I2C
//i2c_write_blocking(i2c, addr, src, nbytes, false);
retx = i2c_write_blocking(i2c, addr, src, nbytes, false);

return retx;
     
}


uint16_t I2C_Write_nbytes_nostop(i2c_inst_t *i2c, const uint addr, const uint8_t *src, const uint8_t nbytes)
{
    uint16_t retx = 0;     
    uint16_t num_bytes_written = 0;  //return value--how many bytes written  
    uint8_t msg[nbytes + 1];

    // Check to make sure caller is sending 1 or more bytes
    if (nbytes < 1) {
        return 0;
    }
 
    // Write data to register(s) over I2C
 
retx = i2c_write_blocking(i2c, addr, src, nbytes, true);

return retx;
     
}


/////////////Write above tested with MCP4728--no reads////////////////////


uint16_t I2C_Read_nbytes_stop(i2c_inst_t *i2c, uint8_t addr, uint8_t *dst, uint8_t nbytes)

{
uint16_t retx = 0;  
//if (i2c_get_read_available(i2c) == 0) return false;
retx = i2c_read_blocking(i2c, addr, dst, nbytes,false);
return retx;
}

uint16_t I2C_Read_nbytes_nostop(i2c_inst_t *i2c, uint8_t addr, uint8_t *dst, uint8_t nbytes)

{
 uint16_t retx = 0;   
// if (i2c_get_read_available(i2c) == 0) return 0;
retx = i2c_read_blocking(i2c, addr, dst, nbytes,true);
return retx;
}
/////////////Write above tested with PCF8591--write then read////////////////////