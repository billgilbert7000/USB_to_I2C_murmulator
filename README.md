# USB_to_I2C_murmulator
Keyboard and mouse controller for i2C transmission for MURMURATOR (RP2040)
/*
 * USB to I2C для MURMULATOR
данные передаваеиые через I2C

ibuff[0] какие устройства подключены по USB 
ibuff[1] мышь кнопки 
ibuff[2] мышь X
ibuff[3] мышь Y
ibuff[4] джойстик кемпстон пока зарезервированно данные с него можно наверное уже куда то пихать отдает 0xff если не подключен 
ibuff[5 6 7 8 9] резерв
ibuff[10]   по ibuff[25] клавиатура
ibuff[26] ibuff[31] пока оставил для ровного счета можно их не считывать

*/
