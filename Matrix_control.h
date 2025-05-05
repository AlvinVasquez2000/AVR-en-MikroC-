/*Libreria Spi para manejar el chip Max7219 con microcontroladores 
AVR en Mikroc pro for AVR */
/*se requiere la habilitaion de la libreria SPI de mikroc pro for AVR, 
la libreria string.h 
obligatoriamente se usara el puerto SPI hardware del microcontrolador 
proximamente se hara que funcione con SPI software para que se pueda 
coenctar en otros pines 
V1.0 creado por Alvin Brandon Vasquez Monroy*/


sbit M_SS at DDB4_bit;
sbit M_MOSI at DDB5_bit;
sbit M_MISO at DDB6_bit;
sbit M_SCK at DDB7_bit;
sbit Habilitador at PORTB4_bit;

int inicializacion_Max7219 =1;
int contador_dispositivos_Max7219=1;

void SPI_Init(){
    M_SS = 1; //SS
    M_MOSI = 1; //MOSI
    M_MISO = 0; //MISO
    M_SCK = 1; //SCK
    SPCR = (1 << SPE) | (1 << MSTR) ;
}
void spi_envio(int dato){
     SPDR=dato;
     while(!(SPSR&(1<<SPIF)));
}
void spi_datos(int direccion, int dato,int dispositivo){
     int i;
     int contador=0;
     if(dispositivo!=0){
         while(dispositivo>0){
               Habilitador=0;
               spi_envio(direccion);
               spi_envio(dato);
               for(i=1;i<=dispositivo;i++)
               {
                   spi_envio(0x00);
                   spi_envio(0x00);
               }
               Habilitador=1;
               dispositivo--;
               if(inicializacion_Max7219==0)
                  break;
               if(inicializacion_Max7219==1)
                   contador_dispositivos_Max7219++;
          }
      }else{
          Habilitador=0;
          spi_envio(direccion);
          spi_envio(dato);
          Habilitador=1;
      }
      if (inicializacion_Max7219==1){
          Habilitador=0;
          spi_envio(direccion);
          spi_envio(dato);
          Habilitador=1;
      }
}


void Max7219_Init(int decodificacion,int dispositivo){
   SPI_Init();

   if(decodificacion==1){
       spi_datos(0x0C,0x01,dispositivo);
       spi_datos(0x09,0xFF,dispositivo);
       spi_datos(0x0B,0x07,dispositivo);
       spi_datos(0x0F,0x00,dispositivo);
       inicializacion_Max7219=0;

   }else{
       spi_datos(0x0C,0x01,dispositivo);
       spi_datos(0x09,0x00,dispositivo);
       spi_datos(0x0B,0x07,dispositivo);
       spi_datos(0x0F,0x00,dispositivo);
       inicializacion_Max7219=0;
   }
}
void Max7219_brillo(int brillo, int dispositivo){
     int i;
     if(dispositivo==0xff){
         dispositivo= contador_dispositivos_Max7219 ;
         for(i=0;i<=dispositivo;i++){
             spi_datos(0x0A,brillo,i);
         }
     }else{
         spi_datos(0x0A,brillo,dispositivo);
     }

}
void Max7219_Manual(int fila, int dato, int dispositivo){
     spi_datos(fila,dato,dispositivo);
}


void Max7219_char(char letra, int dispositivo){
  int i;
  /*MAYUSCULAS*/
  int letra_A[9]={0x44,0x44,0x44,0x7c,0x44,0x44,0x28,0x10} ;
  int letra_B[9]={0x3C,0x44,0x44,0x44,0x7C,0x44,0x44,0x3C} ;
  int letra_C[9]={0x78,0x04,0x04,0x04,0x04,0x04,0x04,0x78} ;
  int letra_D[9]={0x3C,0x44,0x44,0x44,0x44,0x44,0x44,0x3C} ;
  int letra_E[9]={0x3C,0x04,0x04,0x04,0x3C,0x04,0x04,0x3C} ;
  int letra_F[9]={0x04,0x04,0x04,0x04,0x3C,0x04,0x04,0x7C} ;
  int letra_G[9]={0x3E,0x22,0x22,0x32,0x02,0x02,0x02,0x3E} ;
  int letra_H[9]={0x44,0x44,0x44,0x7C,0x7C,0x44,0x44,0x44} ;
  int letra_I[9]={0x7C,0x10,0X10,0x10,0x10,0x10,0x10,0x7C} ;
  int letra_J[9]={0x1C,0x24,0X24,0x04,0x04,0x04,0x04,0x3E} ;
  int letra_K[9]={0x22,0x12,0X0A,0x06,0x06,0x0A,0x12,0x22} ;
  int letra_L[9]={0x7C,0x04,0x04,0x04,0x04,0x04,0x04,0x04} ;
  int letra_M[9]={0x44,0x44,0x44,0x44,0x44,0x54,0x6C,0x44} ;
  int letra_N[9]={0x44,0x44,0x44,0x64,0x54,0x4C,0x44,0x44} ;
  int letra_O[9]={0x7C,0x44,0x44,0x44,0x44,0x44,0x44,0x7C} ;
  int letra_P[9]={0x04,0x04,0x04,0x04,0x7C,0x44,0x44,0x7C} ;
  int letra_Q[9]={0xB8,0x44,0x64,0x54,0x44,0x44,0x44,0x38} ;
  int letra_R[9]={0x22,0x12,0X0A,0x06,0x3E,0x22,0x22,0x3E} ;
  int letra_S[9]={0x7C,0x40,0X40,0x40,0x7C,0x04,0x04,0x3C} ;
  int letra_T[9]={0x10,0x10,0X10,0x10,0x10,0x10,0x10,0x7C} ;
  int letra_U[9]={0x38,0x44,0x44,0x44,0x44,0x44,0x44,0x44} ;
  int letra_V[9]={0x10,0x28,0x44,0x44,0x44,0x44,0x44,0x44} ;
  int letra_W[9]={0x44,0x6C,0x54,0x44,0x44,0x44,0x44,0x44} ;
  int letra_X[9]={0x44,0x44,0x28,0x10,0x10,0x28,0x44,0x44} ;
  int letra_Y[9]={0x10,0x10,0x10,0x10,0x10,0x28,0x44,0x44} ;
  int letra_Z[9]={0x7E,0x02,0x04,0x08,0x10,0x20,0x40,0x7E} ;
   /*MINUSCULAS*/
  int letra_am[9]={0x7C,0x44,0x7C,0x40,0x7C,0x00,0x00,0x00} ;
  int letra_bm[9]={0x7C,0x44,0x7C,0x04,0x04,0x04,0x00,0x00} ;
  int letra_cm[9]={0x7c,0x04,0x04,0x04,0x7C,0x00,0x00,0x00} ;
  int letra_dm[9]={0x7C,0x44,0x7C,0x40,0x40,0x40,0x00,0x00} ;
  int letra_em[9]={0x7c,0x04,0x7c,0x44,0x7C,0x00,0x00,0x00} ;
  int letra_fm[9]={0x04,0x04,0x3C,0x04,0x04,0x3c,0x00,0x00} ;
  int letra_gm[9]={0x7c,0x40,0x7c,0x44,0x7C,0x00,0x00,0x00} ;
  int letra_hm[9]={0x44,0x44,0x7c,0x04,0x04,0x04,0x00,0x00} ;
  int letra_im[9]={0x10,0x10,0X10,0x10,0x00,0x10,0x00,0x00} ;
  int letra_jm[9]={0x70,0x50,0X10,0x10,0x00,0x10,0x00,0x00} ;
  int letra_km[9]={0x12,0x0A,0X06,0x0A,0x12,0x00,0x00,0x00} ;
  int letra_lm[9]={0x10,0x10,0X10,0x10,0x10,0x10,0x00,0x00} ;
  int letra_mm[9]={0x44,0x44,0x54,0x54,0x6c,0x00,0x00,0x00} ;
  int letra_nm[9]={0x44,0x44,0x44,0x44,0x7c,0x00,0x00,0x00} ;
  int letra_om[9]={0x7C,0x44,0x44,0x44,0x7C,0x00,0x00,0x00} ;
  int letra_pm[9]={0x04,0x04,0x7C,0x44,0x7C,0x00,0x00,0x00} ;
  int letra_qm[9]={0x40,0x40,0x7C,0x44,0x7C,0x00,0x00,0x00} ;
  int letra_rm[9]={0x04,0x04,0x04,0x04,0x78,0x00,0x00,0x00} ;
  int letra_sm[9]={0x7C,0x40,0X7C,0x04,0x7C,0x00,0x00,0x00} ;
  int letra_tm[9]={0x30,0x08,0X08,0x08,0x3C,0x08,0x00,0x00} ;
  int letra_um[9]={0x38,0x44,0x44,0x44,0x44,0x00,0x00,0x00} ;
  int letra_vm[9]={0x10,0x28,0x44,0x44,0x44,0x00,0x00,0x00} ;
  int letra_wm[9]={0x6C,0x54,0x54,0x44,0x44,0x00,0x00,0x00} ;
  int letra_xm[9]={0x44,0x28,0x10,0x28,0x44,0x00,0x00,0x00} ;
  int letra_ym[9]={0x40,0x40,0x7C,0x44,0x44,0x00,0x00,0x00} ;
  int letra_zm[9]={0x7C,0x08,0x10,0x20,0x7C,0x00,0x00,0x00} ;
  int letra_esp[9]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00} ;
  int punto_gr[9]={0x00,0x00,0x00,0x00,0x0C,0x0C,0x00,0x00} ;
  int punto[9]={0xC0,0xC0,0x00,0x00,0x0C,0x00,0x00,0x00} ;
  //numeros
  int num0[9]={0x38,0x44,0x44,0x44,0x44,0x44,0x44,0x38} ;
  int num1[9]={0x7C,0x10,0X10,0x10,0x10,0x14,0x18,0x10} ;
  int num2[9]={0x3E,0x02,0x04,0x08,0x10,0x20,0x22,0x1C} ;
  int num3[9]={0x1E,0x20,0x20,0x20,0x3E,0x20,0x20,0x1E} ;
  int num4[9]={0x20,0x20,0x20,0x3E,0x22,0x24,0x28,0x30} ;
  int num5[9]={0x3C,0x40,0X40,0x40,0x3C,0x04,0x04,0x7C} ;
  int num6[9]={0x7C,0x44,0x44,0x7C,0x04,0x04,0x04,0x7C} ;
  int num7[9]={0x00,0x02,0x04,0x08,0x10,0x20,0x40,0x7E} ;
  int num8[9]={0x38,0x44,0x44,0x44,0x7C,0x44,0x44,0x38} ;
  int num9[9]={0x40,0x40,0x40,0x40,0x7C,0x44,0x44,0x7C} ;


  switch(letra){
    case 'A': for(i=1;i<=8;i++){Max7219_Manual(i,letra_A[i-1],dispositivo);delay_ms(1);};break;
    case 'B': for(i=1;i<=8;i++){Max7219_Manual(i,letra_B[i-1],dispositivo);delay_ms(1);};break;
    case 'C': for(i=1;i<=8;i++){Max7219_Manual(i,letra_C[i-1],dispositivo);delay_ms(1);};break;
    case 'D': for(i=1;i<=8;i++){Max7219_Manual(i,letra_D[i-1],dispositivo);delay_ms(1);};break;
    case 'E': for(i=1;i<=8;i++) Max7219_Manual(i,letra_E[i-1],dispositivo);break;
    case 'F': for(i=1;i<=8;i++) Max7219_Manual(i,letra_F[i-1],dispositivo);break;
    case 'G': for(i=1;i<=8;i++) Max7219_Manual(i,letra_G[i-1],dispositivo);break;
    case 'H': for(i=1;i<=8;i++) Max7219_Manual(i,letra_H[i-1],dispositivo);break;
    case 'I': for(i=1;i<=8;i++) Max7219_Manual(i,letra_I[i-1],dispositivo);break;
    case 'J': for(i=1;i<=8;i++) Max7219_Manual(i,letra_J[i-1],dispositivo);break;
    case 'K': for(i=1;i<=8;i++) Max7219_Manual(i,letra_K[i-1],dispositivo);break;
    case 'L': for(i=1;i<=8;i++) Max7219_Manual(i,letra_L[i-1],dispositivo);break;
    case 'M': for(i=1;i<=8;i++) Max7219_Manual(i,letra_M[i-1],dispositivo);break;
    case 'N': for(i=1;i<=8;i++) Max7219_Manual(i,letra_N[i-1],dispositivo);break;
    case 'O': for(i=1;i<=8;i++) Max7219_Manual(i,letra_O[i-1],dispositivo);break;
    case 'P': for(i=1;i<=8;i++) Max7219_Manual(i,letra_P[i-1],dispositivo);break;
    case 'Q': for(i=1;i<=8;i++) Max7219_Manual(i,letra_Q[i-1],dispositivo);break;
    case 'R': for(i=1;i<=8;i++) Max7219_Manual(i,letra_R[i-1],dispositivo);break;
    case 'S': for(i=1;i<=8;i++) Max7219_Manual(i,letra_S[i-1],dispositivo);break;
    case 'T': for(i=1;i<=8;i++) Max7219_Manual(i,letra_T[i-1],dispositivo);break;
    case 'U': for(i=1;i<=8;i++) Max7219_Manual(i,letra_U[i-1],dispositivo);break;
    case 'V': for(i=1;i<=8;i++) Max7219_Manual(i,letra_V[i-1],dispositivo);break;
    case 'W': for(i=1;i<=8;i++) Max7219_Manual(i,letra_W[i-1],dispositivo);break;
    case 'X': for(i=1;i<=8;i++) Max7219_Manual(i,letra_X[i-1],dispositivo);break;
    case 'Y': for(i=1;i<=8;i++) Max7219_Manual(i,letra_Y[i-1],dispositivo);break;
    case 'Z': for(i=1;i<=8;i++) Max7219_Manual(i,letra_Z[i-1],dispositivo);break;

    case 'a': for(i=1;i<=8;i++) Max7219_Manual(i,letra_am[i-1],dispositivo);break;
    case 'b': for(i=1;i<=8;i++) Max7219_Manual(i,letra_bm[i-1],dispositivo);break;
    case 'c': for(i=1;i<=8;i++) Max7219_Manual(i,letra_cm[i-1],dispositivo);break;
    case 'd': for(i=1;i<=8;i++) Max7219_Manual(i,letra_dm[i-1],dispositivo);break;
    case 'e': for(i=1;i<=8;i++) Max7219_Manual(i,letra_em[i-1],dispositivo);break;
    case 'f': for(i=1;i<=8;i++) Max7219_Manual(i,letra_fm[i-1],dispositivo);break;
    case 'g': for(i=1;i<=8;i++) Max7219_Manual(i,letra_gm[i-1],dispositivo);break;
    case 'h': for(i=1;i<=8;i++) Max7219_Manual(i,letra_hm[i-1],dispositivo);break;
    case 'i': for(i=1;i<=8;i++) Max7219_Manual(i,letra_im[i-1],dispositivo);break;
    case 'j': for(i=1;i<=8;i++) Max7219_Manual(i,letra_jm[i-1],dispositivo);break;
    case 'k': for(i=1;i<=8;i++) Max7219_Manual(i,letra_km[i-1],dispositivo);break;
    case 'l': for(i=1;i<=8;i++) Max7219_Manual(i,letra_lm[i-1],dispositivo);break;
    case 'm': for(i=1;i<=8;i++) Max7219_Manual(i,letra_mm[i-1],dispositivo);break;
    case 'n': for(i=1;i<=8;i++) Max7219_Manual(i,letra_nm[i-1],dispositivo);break;
    case 'o': for(i=1;i<=8;i++) Max7219_Manual(i,letra_om[i-1],dispositivo);break;
    case 'p': for(i=1;i<=8;i++) Max7219_Manual(i,letra_pm[i-1],dispositivo);break;
    case 'q': for(i=1;i<=8;i++) Max7219_Manual(i,letra_qm[i-1],dispositivo);break;
    case 'r': for(i=1;i<=8;i++) Max7219_Manual(i,letra_rm[i-1],dispositivo);break;
    case 's': for(i=1;i<=8;i++) Max7219_Manual(i,letra_sm[i-1],dispositivo);break;
    case 't': for(i=1;i<=8;i++) Max7219_Manual(i,letra_tm[i-1],dispositivo);break;
    case 'u': for(i=1;i<=8;i++) Max7219_Manual(i,letra_um[i-1],dispositivo);break;
    case 'v': for(i=1;i<=8;i++) Max7219_Manual(i,letra_vm[i-1],dispositivo);break;
    case 'w': for(i=1;i<=8;i++) Max7219_Manual(i,letra_wm[i-1],dispositivo);break;
    case 'x': for(i=1;i<=8;i++) Max7219_Manual(i,letra_xm[i-1],dispositivo);break;
    case 'y': for(i=1;i<=8;i++) Max7219_Manual(i,letra_ym[i-1],dispositivo);break;
    case 'z': for(i=1;i<=8;i++) Max7219_Manual(i,letra_zm[i-1],dispositivo);break;
    case ' ': for(i=1;i<=8;i++) Max7219_Manual(i,letra_esp[i-1],dispositivo);break;
    case '0': for(i=1;i<=8;i++) Max7219_Manual(i,num0[i-1],dispositivo);break;
    case '1': for(i=1;i<=8;i++) Max7219_Manual(i,num1[i-1],dispositivo);break;
    case '2': for(i=1;i<=8;i++) Max7219_Manual(i,num2[i-1],dispositivo);break;
    case '3': for(i=1;i<=8;i++) Max7219_Manual(i,num3[i-1],dispositivo);break;
    case '4': for(i=1;i<=8;i++) Max7219_Manual(i,num4[i-1],dispositivo);break;
    case '5': for(i=1;i<=8;i++) Max7219_Manual(i,num5[i-1],dispositivo);break;
    case '6': for(i=1;i<=8;i++) Max7219_Manual(i,num6[i-1],dispositivo);break;
    case '7': for(i=1;i<=8;i++) Max7219_Manual(i,num7[i-1],dispositivo);break;
    case '8': for(i=1;i<=8;i++) Max7219_Manual(i,num8[i-1],dispositivo);break;
    case '9': for(i=1;i<=8;i++) Max7219_Manual(i,num9[i-1],dispositivo);break;
    case '°': for(i=1;i<=8;i++) Max7219_Manual(i,punto_gr[i-1],dispositivo);break;
    case '.': for(i=1;i<=8;i++) Max7219_Manual(i,punto[i-1],dispositivo);break;
  }
}
void Max7219_String(char cadena[30]){
    int i;
    for(i=0;i<=strlen(cadena);i++){
        Max7219_char(cadena[i],i);
        delay_us(100);

    }
}
void Max7219_clear(int dispositivo){
     int i,j;
     if(dispositivo==0xff){
         dispositivo= contador_dispositivos_Max7219 ;
         for(i=0;i<=dispositivo;i++){
             for(j=1;j<=8;j++)
             {
                 spi_datos(j,0x00,i);
             }
         }
     }else{
         for(j=1;j<=8;j++)
         {
             spi_datos(j,0x00,dispositivo);
         }
     }
}
void Max7219_scrollIzq(char mensaje[30]){
     int i,j,k=0,l;
     char mensaje_1[30];
     int longitud ;
     strcpy(mensaje_1,mensaje);
     longitud=strlen(mensaje_1);
     mensaje_1[longitud]=' ';
     mensaje_1[longitud+1]='\0';
     longitud=strlen(mensaje_1);
            for(i=0;i<=(strlen(mensaje_1));i++)
        {
            Max7219_String(mensaje_1);
            for(j=0;j<strlen(mensaje_1);j++)
            {
                 if(j==0)
                 {
                     mensaje_1[longitud]=mensaje_1[j];
                 }else
                 {
                     mensaje_1[j-1]=mensaje_1[j];
                 }
             }
             mensaje_1[longitud]='\0';
             delay_ms(700);
        }
}

void Max7219_scrollDer(char mensaje[30]){
     int i,j,k=0,l;
     char mensaje_1[30];
     int longitud ;

     longitud=strlen(mensaje);
     mensaje[longitud]=' ';
     strcpy(mensaje_1,mensaje);
     mensaje_1[longitud+1]='\0';
     longitud=strlen(mensaje_1);
     for(i=0;i<=(strlen(mensaje_1));i++)
        {
            Max7219_String(mensaje_1);
                 for(j=strlen(mensaje_1)-1;j>=0;j--)
            {
                 if(j==longitud-1)
                 {
                     mensaje_1[0]=mensaje[longitud-1];
                 }else
                 {
                     mensaje_1[j+1]=mensaje[j];
                 }
             }

             mensaje_1[longitud]='\0';
             strcpy(mensaje,mensaje_1);
             delay_ms(700);
        }
        mensaje[0]='\0';
        mensaje_1[0]='\0';
}

void Max7219_setLed(int fila, int columna, int estado , int dispositivo){
     int i=0x80;
     i>>=columna;
     if(estado!=0)
         estado=0xFF;
     i&=estado;
     Max7219_Manual(fila,i,dispositivo);
}
