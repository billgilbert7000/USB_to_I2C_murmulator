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

#include <Wire.h>
// pio-usb is required for rp2040 host
#include "pio_usb.h"
#include "Adafruit_TinyUSB.h"
#include "init_main.h" 

long int t = 0;


// Pin D+ for host, D- = D+ + 1
#ifndef  PIN_USB_HOST_DP
#define  PIN_USB_HOST_DP 2
#endif

// Pin for enabling Host VBUS. comment out if not used
#ifndef  PIN_5V_EN
#define PIN_5V_EN        18
#endif

#ifndef PIN_5V_EN_STATE
#define PIN_5V_EN_STATE  1
#endif

// Language ID: English
#define LANGUAGE_ID 0x0409

// USB Host object
Adafruit_USBH_Host USBHost;
//------------------------------------
typedef struct kb_u_state
{
   uint32_t u[4];

}kb_u_state;

kb_u_state kb_st;
//-----------------------------
void translate_scancode_s(uint8_t code);
void translate_scancode(uint8_t code);
//-----------------------------------------------------------------------------
// i2c

void req(){
   //     digitalWrite(STATUS_PIN, HIGH);
       // t = micros() ;
        
        buffer[0] = mode_usb ; // 0 - нет устройств usb 
                               // 1 - есть мышь
                               // 2 - есть клавиатура
                               // 3 - клавиатура + мышь
                               // 4 - клавиатура + мышь + gamepad
        // mouse
        buffer[1] = mouse_b;// #FADF
        buffer[2] = mouse_x;// #FBDF
        buffer[3] = mouse_y;// #FFDF
        buffer[4] = joy_k   ;// джойстик #1F
       // buffer[5] // reserved
       // buffer[6] // reserved
       // buffer[7] // reserved
       // buffer[8] // reserved
       // buffer[9] // reserved
      Wire.write(buffer, 32);

  //    t = t - micros() ;
  //    Serial.println(t);
 static uint16_t blink_led =0x00;
        blink_led++;
        if (blink_led==1000) {
        blink_led = 0;  
        status_led = !status_led;
        digitalWrite(STATUS_PIN, status_led);
        }     
}
// Called when the I2C slave gets written to
void recv(int len) {
 //    int i;
 //    i= Wire.read();
}

// end i2c
//----------------------------------------------------------------------------
void gamepad (uint8_t const *report, uint8_t len){
 #ifdef DEBUG  
 Serial.printf("HID GP : ");
  for (uint16_t i = 0; i < len; i++) {Serial.printf("0x%02X ", report[i]);}
    Serial.println();
     
#endif   
// Logitech RumblePad 2
// report[4]
//        7 6 5 4    3 2 1 0
// 0x08   0 0 0 0    1 0 0 0   не нажато 
// 0x18   0 0 0 1    1 0 0 0   [1]  bit
// 0x28   0 0 1 0    1 0 0 0   [2] 5 bit
// 0x48   0 1 0 0    1 0 0 0   [3] 6 bit
// 0x88   1 0 0 0    1 0 0 0   [4] 7 bit
// 0x02   0 0 0 0    0 0 1 0   [right] 1 bit
// 0x06   0 0 0 0    0 1 1 0   [left] 1 и 2 bit 
// 0x02   0 0 0 0    0 0 0 0   [up]  3 bit инверсия 0x08
// 0x04   0 0 0 0    0 1 0 0   [down] 2 bit 
// 0x01   0 0 0 0    0 0 0 1   верх и право


// report[5]
//        7 6 5 4    3 2 1 0
// 0x08   0 0 0 0    0 0 0 0   не нажато 
// 0x01   0 0 0 0    0 0 0 1   [5] 
// 0x02   0 0 0 0    0 0 1 0   [6] 
// 0x04   0 0 0 0    0 1 0 0   [7] 
// 0x08   0 0 0 0    1 0 0 0   [8] 
// 0x10   0 0 0 1    0 0 0 0   [9] 
// 0x20   0 0 1 0    0 0 0 0   [10] 
// 0x40   0 1 0 0    0 0 0 0   [left  stick] 
// 0x80   1 0 0 0    0 0 0 0   [right stick] 

// report[0] X left stick 0x80 центр
// report[1] Y left stick 0x80 центр
// report[2] X right stick 0x80 центр
// report[3] X right stick 0x80 центр
// 0x00 - 0xff




    joy_k = 0x00 ;//#1F - кемпстон джойстик 0001 1111 

     uint8_t joy = report[4] ;

 if (joy & (1<<5)) // [2] 5 bit
   
    joy_k |= (1 << 4); //4 бит left button
    
    if (joy & (1<<6))  // [3] 6 bit
    joy_k |= (1 << 5); //5 бит right button

 
 //------------  
 
// иначе это стрелки

     joy = joy & 0x0f; // 0000XXXX 0-8
     switch (joy){
      case 0:  joy_k |= (1 << 3); break; //3 бит  up
      case 1:  joy_k |= (1 << 3); joy_k |= (1 << 0); break; //3 бит up  0 бит  right  up right
      case 2:  joy_k |= (1 << 0); break; // 0 бит  right
      case 3:  joy_k |= (1 << 2); joy_k |= (1 << 0); break; //2 бит down  0 бит  right  down right
      case 4:  joy_k |= (1 << 2); break; //2 бит down  
      case 5:  joy_k |= (1 << 2); joy_k |= (1 << 1); break; //2 бит down  1 бит  left  down left
      case 6:  joy_k |= (1 << 1); break; // 1 бит  left
      case 7:  joy_k |= (1 << 3); joy_k |= (1 << 3); break; //3 бит up  1 бит  left  up left
      default: break;
      
     }
     
//----------------------------------
      joy = report[5] ;
      
    if (joy & (1<<3)) // [8] 3 bit
    joy_k |= (1 << 4); //4 бит left button
    
    if (joy & (1<<2))  // [7] 2 bit
    joy_k |= (1 << 5); //5 бит right button

    if (joy & (1<<1)) // [6] 1 bit
    joy_k |= (1 << 4); //4 бит left button
    
    if (joy & (1<<0))  // [5] 0 bit
    joy_k |= (1 << 5); //5 бит right button

//-----------------------------------------------
// report[0] X left stick 0x80 центр
// report[1] Y left stick 0x80 центр   
    joy = report[0] ;
   if (report[1] > 0xA0) joy_k |= (1 << 2); //2 бит down  
   if (report[1] < 0x60) joy_k |= (1 << 3); //3 бит  up

   if (report[0] > 0xA0) joy_k |= (1 << 0);  // 0 бит  right
   if (report[0] < 0x60) joy_k |= (1 << 1);  // 1 бит  left 






//-----------------------------------------------
//Serial.printf("   0x%02X \r\n", joy_k);
//Serial.printf("   0x%02X \r\n", joy);
}

//----------------------------------------------------------------------------
void keyboard (uint8_t const *report, uint16_t len){
    kb_st.u[0] = 0;
    kb_st.u[1] = 0;
    kb_st.u[2] = 0;
    kb_st.u[3] = 0;

#ifdef DEBUG  
 Serial.printf("HID KB : ");
  for (uint16_t i = 0; i < len; i++) {Serial.printf("0x%02X ", report[i]);}
   
#endif  

    translate_scancode_s(report[0]); // Ctrl, Shift, Alt, Win  
   
    //translate_scancode(report[1]);
    
    translate_scancode(report[2]);
    
    translate_scancode(report[3]);
   
    translate_scancode(report[4]);
    
    translate_scancode(report[5]);

    translate_scancode(report[6]);
 
    translate_scancode(report[7]);
    
   //       buffer[1] = 0xff;// #FADF
   //       buffer[2] = 0xff;// #FBDF
   //       buffer[3] = 0xff;// #FFDF
   //       buffer[4] = 0xff  ;// джойстик #1F
    
          buffer[10] = (kb_st.u[0] & 0xff000000UL) >> 24;
          buffer[11] = (kb_st.u[0] & 0x00ff0000UL) >> 16;
          buffer[12] = (kb_st.u[0] & 0x0000ff00UL) >>  8;
          buffer[13] = (kb_st.u[0] & 0x000000ffUL)      ;

          buffer[14] =  (kb_st.u[1] & 0xff000000UL) >> 24;
          buffer[15] =  (kb_st.u[1] & 0x00ff0000UL) >> 16;
          buffer[16] = (kb_st.u[1] & 0x0000ff00UL) >>  8;
          buffer[17] = (kb_st.u[1] & 0x000000ffUL)      ;
          
          buffer[18] = (kb_st.u[2] & 0xff000000UL) >> 24;
          buffer[19] = (kb_st.u[2] & 0x00ff0000UL) >> 16;
          buffer[20] = (kb_st.u[2] & 0x0000ff00UL) >>  8;
          buffer[21] = (kb_st.u[2] & 0x000000ffUL)      ;

          buffer[22] = (kb_st.u[3] & 0xff000000UL) >> 24;
          buffer[23] = (kb_st.u[3] & 0x00ff0000UL) >> 16;
          buffer[24] = (kb_st.u[3] & 0x0000ff00UL) >>  8;
          buffer[25] = (kb_st.u[3] & 0x000000ffUL)      ;
          
#ifdef DEBUG  
 Serial.printf("   0x%08X ", kb_st.u[0]);
 Serial.printf("   0x%08X ", kb_st.u[1]);
 Serial.printf("   0x%08X ", kb_st.u[2]);
 Serial.printf("   0x%08X ", kb_st.u[3]);
 Serial.println();
#endif
}
//--------------------------------------------------------------------
/*
 * данные от мыша
 * 

Я в основном следовал этому примеру, и, похоже, 
существует крайний случай, когда tuh_hid_interface_protocol возвращаются HID_ITF_PROTOCOL_MOUSE,
даже если отчеты из этого экземпляра следует рассматривать как "составные" отчеты. 
Итак, в моем случае process_mouse_report запускался необработанный отчет, 
хотя первый байт этого отчета на самом деле был report_id,
А НЕ началом данных мыши (как видел OP, идентификатор отчета был 0x01, из-за чего казалось,
что левая кнопка мыши всегда была нажата). Итак, я изменил свой обратный вызов, чтобы он выглядел следующим образом 
, который проверяет дескриптор отчета экземпляра, чтобы увидеть,
следует ли ожидать, что в отчете появится report_id. Кажется, работает не очень эффективно? 
Константы, извлеченные из (скрытых таблиц использования)
[https://usb.org/document-library/hid-usage-tables-14].
 * 
 * 
 * 
 * 
 */
//------------------------------------------------------------------------------
//void mouse(uint8_t const *report, uint16_t len ) 
void mouse(uint8_t const *report, uint8_t len ) 
     
{
  
  //if (len==0) return;
#ifdef DEBUG  
  Serial.printf("MOUSE : ");
  for (uint16_t i = 0; i < len; i++) {Serial.printf("0x%02X ", report[i]);}
  Serial.printf("   LEN=%02X\r\n", len );  
#endif 
       mouse_b = 0xff;
       static uint8_t ms_x =0;
       static uint8_t ms_y =0;
       static uint8_t ms_w =0;


    mouse_b = 0xff ;//#FADF - поpт  кнопок

  
  if (report[1] & (1<<0) ) mouse_b &= ~(1 << 1); //1 бит - состояние левой кнопки;MOUSE_BUTTON_LEFT
  if (report[1] & (1<<1) ) mouse_b &= ~(1 << 1); //0 бит - состояние правой кнопки; MOUSE_BUTTON_RIGHT
  if (report[1] & (1<<2) ) mouse_b &= ~(1 << 2); //2 бит - состояние сpедней кнопки; MOUSE_BUTTON_MIDDLE)
 
  // X
    if (ms_x != report[2]){ 
    if (report[2]&(1<<7)) mouse_x = mouse_x-2;//mouse_x--;//left
    else mouse_x = mouse_x+2;//mouse_x++;//right 
    ms_x = report[2];
    }

  // мышь 8 байт 
    if (len==8) report++;
  // Y   
    if (ms_y != report[3]){ 
    if (report[3]&(1<<7)) mouse_y = mouse_y+2;//mouse_y++;//up
    else mouse_y = mouse_y-2;//mouse_y--; //down
    ms_y = report[3];
    }
  
  // колесо
    if (report[5] !=0){ 
    if (report[5]&(1<<7)) mouse_w++;//up
    else mouse_w--; //down
   }

//------------------------------------------------------------------
//Serial.printf("Button:%02x X=%02x Y=%02x W=%02x \n", report[0], report[1], report[2], report[3] ); 
 Serial.printf("T=%01X    B=%02X X=%02d Y=%02d  W=%02X        %02X\r\n", mode_usb, mouse_b, mouse_x, mouse_y, mouse_w ,len ); 
}
//------------------------------------------------------------------

//--------------------------------------------------------------------+
// Setup and Loop on Core0
//--------------------------------------------------------------------+

void setup()
{
#ifdef DEBUG
    Serial.begin(115200);
  //  while ( !Serial ) delay(10);   // wait for native usb
    Serial.println("ZX KEYBOARD USB to I2C");
#endif
//i2c
/*
 Wire.setClock(clockFrequency);
Параметры
clockFrequency — Обязательный параметр. Новое значение частоты обмена данными в герцах. 
Доступные значения: 10000 — медленный режим 100000 — стандартное значение 
400000 — быстрый режим 1000000 — быстрый режим плюс 3400000 — высокоскоростной режим

 */
pinMode(STATUS_PIN, OUTPUT); 
digitalWrite(STATUS_PIN, LOW);

  mode_usb = NO_USB;
  Wire.setSDA(0);
  Wire.setSCL(1);
  Wire.begin(0x77);//7-битный адрес ведомого устройства; если не задан, плата подключается к шине как мастер.
  Wire.onReceive(recv);
  /*
   Wire.onReceive(handler);
Параметры
handler — Имя функции, которая будет выполняться 
когда ведомое устройство принимает данные.
Функция должна принимать один параметр int и ничего не возвращать. 
   */
  Wire.onRequest(req);//Wire.onRequest(handler);
  /*
   handler — Имя функции, которая будет
   выполняться когда ведомое устройство получает запрос от ведущего. 
   Функция не принимает параметров и ничего не возвращает.
   */
//i2c end

  }

void loop()
{
  Serial.flush();
}

//--------------------------------------------------------------------+
// Setup and Loop on Core1
//--------------------------------------------------------------------+

void setup1() {
#ifdef DEBUG  
 // while ( !Serial ) delay(10);   // wait for native usb
  Serial.println("Core1 setup to run TinyUSB host with pio-usb");
#endif
  // Check for CPU frequency, must be multiple of 120Mhz for bit-banging USB
  uint32_t cpu_hz = clock_get_hz(clk_sys);
  if ( cpu_hz != 120000000UL && cpu_hz != 240000000UL ) {
#ifdef DEBUG    
  //  while ( !Serial ) delay(10);   // wait for native usb
    Serial.printf("Error: CPU Clock = %lu, PIO USB require CPU clock must be multiple of 120 Mhz\r\n", cpu_hz);
    Serial.printf("Change your CPU Clock to either 120 or 240 Mhz in Menu->CPU Speed \r\n");
    while(1) delay(1);
#endif    
  }

#ifdef PIN_5V_EN
  pinMode(PIN_5V_EN, OUTPUT);
  digitalWrite(PIN_5V_EN, PIN_5V_EN_STATE);
#endif

  pio_usb_configuration_t pio_cfg = PIO_USB_DEFAULT_CONFIG;
  pio_cfg.pin_dp = PIN_USB_HOST_DP;


  USBHost.configure_pio_usb(1, &pio_cfg);

  // run host stack on controller (rhport) 1
  // Note: For rp2040 pico-pio-usb, calling USBHost.begin() on core1 will have most of the
  // host bit-banging processing works done in core1 to free up core0 for other works
  USBHost.begin(1);
}

void loop1()
{
  USBHost.task();
}

extern "C" {
void print_device_descriptor(tuh_xfer_t* xfer)

  {
    type_hid = desc_device.iProduct;
   
Serial.printf("  iProduct %u     "     , type_hid);
Serial.printf("  mode_usb  %u   "     , mode_usb);
  }
//////////////////////////////////////////////////////

void tuh_mount_cb (uint8_t dev_addr)
{
  #ifdef DEBUG  
  Serial.printf("Device attached, address = %d\r\n", dev_addr);
  #endif  
// Получить дескриптор устройства
 tuh_descriptor_get_device(dev_addr, &desc_device, 18, print_device_descriptor, 0);
}
//--------------------------------------------------------------------------------------
// Вызывается при подключении устройства с интерфейсом hid
// Дескриптор отчета также доступен для использования.
// tuh_hid_parse_report_descriptor() можно использовать для анализа достаточно распространенных /простых
// дескриптор. Примечание: если длина дескриптора отчета > CFG_TUH_ENUMERATION_BUFSIZE,
// он будет пропущен, следовательно, report_desc = NULL, desc_len = 0
void tuh_hid_mount_cb(uint8_t dev_addr, uint8_t instance, uint8_t const *desc_report, uint16_t desc_len) {
  (void) desc_report;
  (void) desc_len;
  uint16_t vid, pid;
tuh_vid_pid_get(dev_addr, &vid, &pid);
 
//tuh_descriptor_get_device(dev_addr, &desc_device, 18, print_device_descriptor, 0); 
  Serial.printf("  mode_usb  %u   "     , mode_usb);
       switch(tuh_hid_interface_protocol(dev_addr, instance)) {
       case HID_ITF_PROTOCOL_KEYBOARD:
       mode_usb = mode_usb | KEYB ;
      #ifdef DEBUG 
      Serial.printf("HID Interface Protocol = Keyboard\n");
      #endif  
      
      kb_addr = dev_addr;
      kb_inst = instance;
 
      tuh_hid_receive_report(dev_addr, instance);

      
    break;

    case HID_ITF_PROTOCOL_MOUSE:
     mode_usb = mode_usb | MOUSE;


    // mode_usb = 1;///!!!!!!!!!!!!!!!!!!!!
      #ifdef DEBUG 
      Serial.printf("HID Interface Protocol = Mouse\n");
      #endif  
      ms_addr = dev_addr;
      ms_inst = instance;
      tuh_hid_receive_report(dev_addr, instance);
      break;
      
    default:// gamepad
      gp_addr = dev_addr;
      gp_inst = instance;
      tuh_hid_receive_report(dev_addr, instance);
      break;
   

}

 
  
#ifdef DEBUG
  Serial.printf("HID device address = %d, instance = %d is mounted\r\n", dev_addr, instance);
  Serial.printf("VID = %04x, PID = %04x\r\n", vid, pid); 
 // if (!tuh_hid_receive_report(dev_addr, instance)) Serial.printf("Error: cannot request to receive report\r\n");
#endif    
}

// Invoked when device with hid interface is un-mounted
void tuh_hid_umount_cb(uint8_t dev_addr, uint8_t instance) {
  mode_usb = 0;
#ifdef DEBUG  
  Serial.printf("HID device address = %d, instance = %d is unmounted\r\n", dev_addr, instance);
#endif  
}
/////////////////////////////////

/////////////////////////////////
// Вызывается при получении отчета от устройства через конечную точку прерывания
void tuh_hid_report_received_cb(uint8_t dev_addr, uint8_t instance, uint8_t const *report, uint16_t len) {
   //  if (len==0) return;
     
 #ifdef DEBUG  
Serial.println(tuh_hid_interface_protocol(dev_addr, instance));
//Serial.printf("hid = %04x\r\n", (tuh_hid_interface_protocol(dev_addr, instance))); 
#endif 
 
   switch(tuh_hid_interface_protocol(dev_addr, instance)) {

    case HID_ITF_PROTOCOL_KEYBOARD: keyboard (report,len);break; // 1

    case HID_ITF_PROTOCOL_MOUSE: mouse(report, len);break;//2

      case 0:gamepad (report,len);break;
       
     default: break;

    
  // continue to request to receive report
   }
 if (!tuh_hid_receive_report(dev_addr, instance)) 
#ifdef DEBUG  
Serial.printf("Error: cannot request to receive report\r\n");
#endif 
return;
}


} // extern C
