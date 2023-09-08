/*

 */
 //----------------------------------------------------------
void translate_scancode_s(uint8_t code){

  if (code & 0x02) kb_st.u[1]|=KB_U1_L_SHIFT;// left shift  
 //  if (code & 0x02) kb_st.u[1]|=KB_U1_R_SHIFT;// left shift  переназначение на правый
   if (code & 0x20) kb_st.u[1]|=KB_U1_R_SHIFT;// righr shift 

   
   if (code & 0x04) kb_st.u[1]|=KB_U1_L_ALT;  // left alt     0000 0100
   if (code & 0x40) kb_st.u[1]|=KB_U1_R_ALT;; // right alt   0100 0000
   
   if (code & 0x01) kb_st.u[1]|=KB_U1_L_CTRL; // right ctrl   
   if (code & 0x10) kb_st.u[1]|=KB_U1_R_CTRL;
   
   if (code & 0x08) kb_st.u[1]|=KB_U1_L_WIN;; // win  l
   if (code & 0x80) kb_st.u[1]|=KB_U1_L_WIN;; // win r
   }
//----------------------------------------------------------
 void translate_scancode(uint8_t code){
   
   switch (code)
   {

    case 0x04:  kb_st.u[0]|=KB_U0_A; break;
    case 0x05:  kb_st.u[0]|=KB_U0_B; break;
    case 0x06:  kb_st.u[0]|=KB_U0_C; break;
    case 0x07:  kb_st.u[0]|=KB_U0_D; break;
    case 0x08:  kb_st.u[0]|=KB_U0_E; break;
    case 0x09:  kb_st.u[0]|=KB_U0_F; break;
    case 0x0a:  kb_st.u[0]|=KB_U0_G; break;
    case 0x0b:  kb_st.u[0]|=KB_U0_H; break;
    case 0x0c:  kb_st.u[0]|=KB_U0_I; break;
    case 0x0d:  kb_st.u[0]|=KB_U0_J; break;
    
    case 0x0e:  kb_st.u[0]|=KB_U0_K; break;
    case 0x0f:  kb_st.u[0]|=KB_U0_L; break;
    case 0x10:  kb_st.u[0]|=KB_U0_M; break;
    case 0x11:  kb_st.u[0]|=KB_U0_N; break;
    case 0x12:  kb_st.u[0]|=KB_U0_O; break;
    case 0x13:  kb_st.u[0]|=KB_U0_P; break;
    case 0x14:  kb_st.u[0]|=KB_U0_Q; break;
    case 0x15:  kb_st.u[0]|=KB_U0_R; break;
    case 0x16:  kb_st.u[0]|=KB_U0_S; break;
    case 0x17:  kb_st.u[0]|=KB_U0_T; break;
    
    case 0x18:  kb_st.u[0]|=KB_U0_U; break;
    case 0x19:  kb_st.u[0]|=KB_U0_V; break;
    case 0x1a:  kb_st.u[0]|=KB_U0_W; break;
    case 0x1b:  kb_st.u[0]|=KB_U0_X; break;
    case 0x1c:  kb_st.u[0]|=KB_U0_Y; break;
    case 0x1d:  kb_st.u[0]|=KB_U0_Z; break;
    
    case 0x2f:  kb_st.u[0]|=KB_U0_LEFT_BR; break;
    case 0x30:  kb_st.u[0]|=KB_U0_RIGHT_BR; break;
    case 0x33:  kb_st.u[0]|=KB_U0_SEMICOLON; break;
    case 0x34:  kb_st.u[0]|=KB_U0_QUOTE; break;
    case 0x36:  kb_st.u[0]|=KB_U0_COMMA; break;
    case 0x37:  kb_st.u[0]|=KB_U0_PERIOD; break;
    
    //1 -----------
    case 0x27:  kb_st.u[1]|=KB_U1_0; break;
    case 0x1e:  kb_st.u[1]|=KB_U1_1; break;
    case 0x1f:  kb_st.u[1]|=KB_U1_2; break;
    case 0x20:  kb_st.u[1]|=KB_U1_3; break;
    case 0x21:  kb_st.u[1]|=KB_U1_4; break;
    case 0x22:  kb_st.u[1]|=KB_U1_5; break;
    case 0x23:  kb_st.u[1]|=KB_U1_6; break;
    case 0x24:  kb_st.u[1]|=KB_U1_7; break;
    case 0x25:  kb_st.u[1]|=KB_U1_8; break;
    case 0x26:  kb_st.u[1]|=KB_U1_9; break;
    
    case 0x2d:  kb_st.u[1]|=KB_U1_MINUS; break;
    case 0x2e:  kb_st.u[1]|=KB_U1_EQUALS; break;
    case 0x31:  kb_st.u[1]|=KB_U1_BACKSLASH;break;
    case 0x2a:  kb_st.u[1]|=KB_U1_BACK_SPACE; break;
    case 0x28:  kb_st.u[1]|=KB_U1_ENTER; break;
    case 0x38:  kb_st.u[1]|=KB_U1_SLASH; break;
    case 0x32:  kb_st.u[1]|=KB_U1_TILDE; break;
    case 0x2b:  kb_st.u[1]|=KB_U1_TAB; break;
    case 0x39:  kb_st.u[1]|=KB_U1_CAPS_LOCK; break;
    case 0x29:  kb_st.u[1]|=KB_U1_ESC;break;
    case 0x65:  kb_st.u[1]|=KB_U1_MENU;  break;
    case 0x2c:  kb_st.u[1]|=KB_U1_SPACE; break;
    
    //2 -----------
    case 0x48:  kb_st.u[2]|=KB_U2_PAUSE_BREAK; break;
    
    case 0x53:  kb_st.u[2]|=KB_U2_NUM_LOCK; break;
    case 0x59:  kb_st.u[2]|=KB_U2_NUM_1; break;
    case 0x5a:  kb_st.u[2]|=KB_U2_NUM_2; break;
    case 0x5b:  kb_st.u[2]|=KB_U2_NUM_3; break;
    case 0x5c:  kb_st.u[2]|=KB_U2_NUM_4; break;
    case 0x5d:  kb_st.u[2]|=KB_U2_NUM_5; break;
    case 0x5e:  kb_st.u[2]|=KB_U2_NUM_6; break;
    case 0x5f:  kb_st.u[2]|=KB_U2_NUM_7; break;
    case 0x60:  kb_st.u[2]|=KB_U2_NUM_8; break;
    case 0x61:  kb_st.u[2]|=KB_U2_NUM_9; break;
    case 0x62:  kb_st.u[2]|=KB_U2_NUM_0; break;
    case 0x63:  kb_st.u[2]|=KB_U2_NUM_PERIOD; break;
    
    case 0x55:  kb_st.u[2]|=KB_U2_NUM_MULT; break;
    case 0x56:  kb_st.u[2]|=KB_U2_NUM_MINUS; break;
    case 0x57:  kb_st.u[2]|=KB_U2_NUM_PLUS; break;
    
    case 0x47:  kb_st.u[2]|=KB_U2_SCROLL_LOCK;break;
    case 0x46:  kb_st.u[2]|=KB_U2_PRT_SCR; break;

    case 0x54:  kb_st.u[2]|=KB_U2_NUM_SLASH;break;
    case 0x58:  kb_st.u[2]|=KB_U2_NUM_ENTER;  break;
    case 0x52:  kb_st.u[2]|=KB_U2_UP;  break;
    case 0x51:  kb_st.u[2]|=KB_U2_DOWN;  break;
    case 0x4f:  kb_st.u[2]|=KB_U2_RIGHT; break;
    case 0x50:  kb_st.u[2]|=KB_U2_LEFT;  break;
    case 0x4c:  kb_st.u[2]|=KB_U2_DELETE; break;
    case 0x4d:  kb_st.u[2]|=KB_U2_END;  break;
    case 0x4e:  kb_st.u[2]|=KB_U2_PAGE_DOWN;  break;
    case 0x4b:  kb_st.u[2]|=KB_U2_PAGE_UP;  break; 
    case 0x4a:  kb_st.u[2]|=KB_U2_HOME; break;
    case 0x49:  kb_st.u[2]|=KB_U2_INSERT;  break;

    
    //3 -----------
    case 0x3a:  kb_st.u[3]|=KB_U3_F1; break;
    case 0x3b:  kb_st.u[3]|=KB_U3_F2; break;
    case 0x3c:  kb_st.u[3]|=KB_U3_F3; break;
    case 0x3d:  kb_st.u[3]|=KB_U3_F4; break;
    case 0x3e:  kb_st.u[3]|=KB_U3_F5; break;
    case 0x3f:  kb_st.u[3]|=KB_U3_F6; break;
    case 0x40:  kb_st.u[3]|=KB_U3_F7; break;
    case 0x41:  kb_st.u[3]|=KB_U3_F8; break;
    case 0x42:  kb_st.u[3]|=KB_U3_F9; break;
    case 0x43:  kb_st.u[3]|=KB_U3_F10;break;
    case 0x44:  kb_st.u[3]|=KB_U3_F11; break;
    case 0x45:  kb_st.u[3]|=KB_U3_F12; break;
    default : break;
   }
 }
    
    
