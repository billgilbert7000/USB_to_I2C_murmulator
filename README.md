# USB_to_I2C_murmulator
Keyboard and mouse controller for i2C transmission for MURMULATOR (RP2040)

 * USB to I2C для MURMULATOR
данные передаваеиые через I2C

ibuff[0] какие устройства подключены по USB 

        // 0 - нет устройств usb 

        // 1 - есть мышь

        // 2 - есть клавиатура

        // 3 - клавиатура + мышь

        // 4 - клавиатура + мышь + gamepad


ibuff[1] мышь кнопки 

ibuff[2] мышь X

ibuff[3] мышь Y

ibuff[4] джойстик кемпстон пока зарезервированно данные с него можно наверное уже куда то пихать отдает 0xff если не подключен 

ibuff[5 6 7 8 9] резерв

ibuff[10]   по ibuff[25] клавиатура

ibuff[26] ibuff[31] пока оставил для ровного счета можно их не считывать

RP2040 прошивается этой прошивкой и к ней подключается usb мышь
на эти пины 

PIN USB D+ GPIO 2

PIN USB D- GPIO 3

А эти пины используются для сопряжения с мурмулятором по i2c 

PIN I2C SDA GPIO 0

PIN I2C SCL GPIO 1 


мурмулятор по i2c GPIO 18 и GPIO 19

 GPIO 0 -> GPIO 18 
 
 GPIO 1 -> GPIO 19
 
 
 



