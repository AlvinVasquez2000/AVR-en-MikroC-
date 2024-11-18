/*LCD con I2C usando el expansor de puerto PCF8574 
Julio 2022 hecho por Alvin Brandon Vasquez Monroy 
Version 1.0*/

#define NOP                       0x00
#define CLEAR_DISPLAY             0x01
#define CURSOR_HOME               0x02

#define ENTRY_MODE_SET            0x04

#define DECREMENT                 0x00
#define INCREMENT                 0x02

#define SCROLL_ON                 0x01
#define SCROLL_OFF                0x00

#define DISPLAY_CONTROL           0x08

#define DISPLAY_ON                0x04
#define DISPLAY_OFF               0x00

#define CURSOR_ON                 0x02
#define CURSOR_OFF                0x00

#define BLINK_ON                  0x01
#define BLINK_OFF                 0x00

#define CURSOR_SHIFT              0x10

#define SHIFT_SCREEN              0x08
#define SHIFT_CURSOR              0x00

#define SHIFT_RIGHT               0x04
#define SHIFT_LEFT                0x00



#define LCD_BL 0x08
#define LCD_EN 0x04
#define LCD_RS 0x01


 //funcion que escribe en el PCF8574
 I2C_PCF8574_Write(unsigned char Adr,unsigned char value)
{
     TWI_Start();
     TWI_Write( Adr );
     TWI_Write(value);
     TWI_Stop();
}

void I2C_LCD_Cmd(char out_char)
{
    unsigned char lcddata;
  //Coloca  4 bit alto
    lcddata = (out_char & 0xF0)|LCD_BL;
    I2C_PCF8574_Write(LCD_ADDR,lcddata | LCD_EN);
    Delay_ms(1);
  // RE=0
    I2C_PCF8574_Write(LCD_ADDR,lcddata & ~LCD_EN);
    Delay_ms(1);

    // Coloca los 4 bits bajo
    lcddata = ((out_char << 4) & 0xF0)|LCD_BL;
    I2C_PCF8574_Write(LCD_ADDR,lcddata | LCD_EN);
    Delay_ms(1);
    // ESCRIBE PULSO DE RE
    I2C_PCF8574_Write(LCD_ADDR,lcddata & ~LCD_EN);
    Delay_ms(1);

}

 void I2C_LCD_init()
{
  unsigned char lcddata;
  Delay_ms(20); //retardo de inicializacion
  // INICIA PROCESO DE INICIALIZACION
  lcddata=0x30;
  I2C_PCF8574_Write(LCD_ADDR,lcddata | LCD_EN); //envia comando de inicializacion
   Delay_ms(1);
  I2C_PCF8574_Write(LCD_ADDR,lcddata & ~LCD_EN);
   Delay_ms(5);

  lcddata=0x30;
  I2C_PCF8574_Write(LCD_ADDR,lcddata | LCD_EN); //envia comando de inicializacion
   Delay_ms(1);
  I2C_PCF8574_Write(LCD_ADDR,lcddata & ~LCD_EN);
   Delay_ms(5);

  lcddata=0x30;
  I2C_PCF8574_Write(LCD_ADDR,lcddata | LCD_EN); //envia comando de inicializacion
   Delay_ms(1);
  I2C_PCF8574_Write(LCD_ADDR,lcddata & ~LCD_EN);
   Delay_ms(5);


  //modo a 4  bits
  lcddata=0x20;
  I2C_PCF8574_Write(LCD_ADDR,lcddata | LCD_EN);
   Delay_ms(1);
  I2C_PCF8574_Write(LCD_ADDR,lcddata & ~LCD_EN);
   Delay_ms(1);

  //modo a 4 lineas
  lcddata=0x20;
  I2C_PCF8574_Write(LCD_ADDR,lcddata | LCD_EN);
   Delay_ms(1);
  I2C_PCF8574_Write(LCD_ADDR,lcddata & ~LCD_EN);
   Delay_ms(1);
  lcddata=0x80;
  I2C_PCF8574_Write(LCD_ADDR,lcddata | LCD_EN);
   Delay_ms(1);
  I2C_PCF8574_Write(LCD_ADDR,lcddata & ~LCD_EN);
   Delay_ms(5);

  //Apaga el LCD
  lcddata=0x00;
  I2C_PCF8574_Write(LCD_ADDR,lcddata | LCD_EN);
   Delay_ms(1);
  I2C_PCF8574_Write(LCD_ADDR,lcddata & ~LCD_EN);
   Delay_ms(1);
  lcddata=0x80;
  I2C_PCF8574_Write(LCD_ADDR,lcddata | LCD_EN);
   Delay_ms(1);
  I2C_PCF8574_Write(LCD_ADDR,lcddata & ~LCD_EN);
   Delay_ms(1);


   //Prende el LCD
  lcddata=0x00;
  I2C_PCF8574_Write(LCD_ADDR,lcddata | LCD_EN);
   Delay_ms(1);
  I2C_PCF8574_Write(LCD_ADDR,lcddata & ~LCD_EN);
   Delay_ms(1);
  lcddata=0xC0;
  I2C_PCF8574_Write(LCD_ADDR,lcddata | LCD_EN);
   Delay_ms(1);
  I2C_PCF8574_Write(LCD_ADDR,lcddata & ~LCD_EN);
   Delay_ms(1);

   //Ajusta desplazamiento del cursor
  lcddata=0x00;
  I2C_PCF8574_Write(LCD_ADDR,lcddata | LCD_EN);
   Delay_ms(1);
  I2C_PCF8574_Write(LCD_ADDR,lcddata & ~LCD_EN);
   Delay_ms(1);
  lcddata=0x20 | LCD_BL;
  I2C_PCF8574_Write(LCD_ADDR,lcddata | LCD_EN);
   Delay_ms(1);
  I2C_PCF8574_Write(LCD_ADDR,lcddata & ~LCD_EN);
   Delay_ms(1);



   //Borra la pantalla
  lcddata=0x00;
  I2C_PCF8574_Write(LCD_ADDR,lcddata | LCD_EN);
   Delay_ms(1);
  I2C_PCF8574_Write(LCD_ADDR,lcddata & ~LCD_EN);
   Delay_ms(1);
  lcddata=0x10;
  I2C_PCF8574_Write(LCD_ADDR,lcddata | LCD_EN);
   Delay_ms(1);
  I2C_PCF8574_Write(LCD_ADDR,lcddata & ~LCD_EN);
   Delay_ms(1);
}


void I2C_LCD_Chr(char row, char column, char out_char)
{

    unsigned char byte,lcddata;

    switch(row){

        case 1:
        I2C_LCD_Cmd(0x80 + (column - 1));
        break;
        case 2:
        I2C_LCD_Cmd(0xC0 + (column - 1));
        break;
        case 3:
        I2C_LCD_Cmd(0x94 + (column - 1));
        break;
        case 4:
        I2C_LCD_Cmd(0xD4 + (column - 1));
        break;
    }


  lcddata = (out_char & 0xF0)| LCD_RS |LCD_BL;
  I2C_PCF8574_Write(LCD_ADDR,lcddata | LCD_EN);
  Delay_ms(1);
  I2C_PCF8574_Write(LCD_ADDR,lcddata & ~LCD_EN);
  Delay_ms(1);

  lcddata = ((out_char << 4) & 0xF0) |LCD_RS |LCD_BL;
  I2C_PCF8574_Write(LCD_ADDR,lcddata | LCD_EN);
  Delay_ms(1);
  I2C_PCF8574_Write(LCD_ADDR,lcddata & ~LCD_EN);
  I2C_PCF8574_Write(LCD_ADDR,lcddata & ~LCD_RS);
  Delay_ms(1);


}

void I2C_LCD_Chr_Cp(char out_char)
 {
   unsigned char lcddata;
  lcddata = (out_char & 0xF0)|LCD_RS |LCD_BL;
  I2C_PCF8574_Write(LCD_ADDR,lcddata | LCD_EN);
  Delay_ms(1);
  I2C_PCF8574_Write(LCD_ADDR,lcddata & ~LCD_EN);
  Delay_ms(1);

  lcddata = ((out_char << 4) & 0xF0)|LCD_RS |LCD_BL;
  I2C_PCF8574_Write(LCD_ADDR,lcddata | LCD_EN);
  Delay_ms(1);
  I2C_PCF8574_Write(LCD_ADDR,lcddata & ~LCD_EN);
  I2C_PCF8574_Write(LCD_ADDR,lcddata & ~LCD_RS);
  Delay_ms(1);



}


void I2C_LCD_Out(char row, char col, char *text) {
    while(*text)
         I2C_LCD_Chr(row, col++, *text++);
}

void I2C_LCD_Out_Cp(char *text) {
    while(*text)
         I2C_LCD_Chr_Cp(*text++);
}
/*libreria lcd por I2c con expansor de puerto PCF8574
diseñado por Univ. Alvin Brandon Vasquez Monroy
se puede usar en cualquier AVR ATMEGA siempre y cuando
tenga comunicacion I2C*/