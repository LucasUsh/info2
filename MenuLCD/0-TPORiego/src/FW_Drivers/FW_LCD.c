
#include "Aplicacion.h"

extern volatile uint16_t DemoraLCD;

void LCDDelay(uint16_t demora)
{
	DemoraLCD = demora;
	while(DemoraLCD);
}

void LatchLcd(void)
{
	SetPIN(LCD_E,ON);
	LCDDelay(2);
	SetPIN(LCD_E,OFF);
}

void Escribir (char *p) {
	while(*p != '\0') WDato(*p++);
}

void WComando8(uint8_t comando)
{
	SetPIN(LCD_RS,OFF);
	// Parte Alta del comando
	SetPIN(LCD_D4,((comando & 0x10) >> 4));
	SetPIN(LCD_D5,((comando & 0x20) >> 5));
	SetPIN(LCD_D6,((comando & 0x40) >> 6));
	SetPIN(LCD_D7,((comando & 0x80) >> 7));
	LatchLcd();
	LCDDelay(2);

	// Parte Baja del comando
	SetPIN(LCD_D4,(comando & 0x01));
	SetPIN(LCD_D5,((comando & 0x02) >> 1));
	SetPIN(LCD_D6,((comando & 0x04) >> 2));
	SetPIN(LCD_D7,((comando & 0x08) >> 3));
	LatchLcd();
	LCDDelay(2);
}

void WComando4(uint8_t comando)
{
	SetPIN(LCD_RS,OFF);
	SetPIN(LCD_D4,((comando & 0x10) >> 4));
	SetPIN(LCD_D5,((comando & 0x20) >> 5));
	SetPIN(LCD_D6,((comando & 0x40) >> 6));
	SetPIN(LCD_D7,((comando & 0x80) >> 7));
	LatchLcd();
	LCDDelay(2);
}

void WDato (uint8_t dato)
{
	SetPIN(LCD_RS,ON);
	// Parte Alta del comando
	SetPIN(LCD_D4,((dato & 0x10) >> 4));
	SetPIN(LCD_D5,((dato & 0x20) >> 5));
	SetPIN(LCD_D6,((dato & 0x40) >> 6));
	SetPIN(LCD_D7,((dato & 0x80) >> 7));
	LatchLcd();
	LCDDelay(2);

	// Parte Baja del comando
	SetPIN(LCD_D4,(dato & 0x01));
	SetPIN(LCD_D5,((dato & 0x02) >> 1));
	SetPIN(LCD_D6,((dato & 0x04) >> 2));
	SetPIN(LCD_D7,((dato & 0x08) >> 3));
	LatchLcd();
	LCDDelay(2);
}

void LCD_Menu (void) {
	WComando8(LCD_CLEAR);
	WDato (0x7E); 					//Escribe "->"
	Escribir ((char*) "Tierra");
	WDato (0x7E);
	Escribir ((char*) "Ambiente");
	WComando8(LCD_2POS0);
	WDato (0xB4);
	WComando8(LCD_2POS4);
	Escribir ((char*) "Info2.UTN");
	WComando8(FLECHA_TIERRA);
}

void LCD_Tierra (void) {
	WComando8(LCD_CLEAR);
	Escribir ("Humedad:");
	WComando8 (LCD_1POS10);
	WDato('%');
	WComando8(LCD_2POS10);
	WDato (0x7E);
	Escribir ("Atras");
	WComando8(FLECHA_ATRAS);
}

void LCD_Ambiente (void) {
	WComando8(LCD_CLEAR);
	Escribir ((char *) "Temperatura:");
	WComando8 (LCD_1POS14);
	WDato (0xD2);
	WDato ('C'); // ver si funciona con 'C'
	WComando8(LCD_2POS0);
	Escribir ((char *) "Humed.:");
	WComando8(LCD_2POS9);
	WDato('%'); //funca?
	WDato (0x7E);
	Escribir ((char*) "Atras");
	WComando8(FLECHA_ATRAS);
}

void LCD_Settings (void) {
	WComando8(LCD_CLEAR);
	Escribir ((char*) "Config.:  ");
	WDato (0x7E);
	Escribir ((char*) "Riego");
	WComando8(LCD_2POS0);
	WDato (0x7E);
	Escribir ((char*) "Hora/Dia ");
	WDato (0x7E);
	Escribir ((char*) "Atras");
	WComando8(FLECHA_ATRAS);
}
void LCD_RiegoC (void) {
	WComando8(LCD_CLEAR);
	Escribir ((char *) "Hum. Critica:");
	WComando8(LCD_1POS15);
	WDato('%');
	WComando8(LCD_2POS0);
	WDato (0x7E);
	Escribir ((char *) "HorasAut.");
	WDato (0x7E);
	Escribir ((char*) "Atras");
	WComando8(FLECHA_ATRAS);
}

void LCD_HorasAutC (void) {
	WComando8(LCD_CLEAR);
	Escribir ((char*) "1 2 3 4 5 6 7 8");
	WComando8(LCD_2POS10);
	WDato (0x7E);
	Escribir ((char*) "Atras");
	WComando8(FLECHA_ATRAS);
}
void LCD_HoraFechaC (void) {
	WComando8(LCD_CLEAR);
	Escribir ((char*) "Fecha:");
	WComando8 (LCD_1POS8);
	WDato ('/');
	WComando8(LCD_1POS11);
	WDato ('/');
	WComando8(LCD_2POS0);
	Escribir ((char*) "Hora:");
	WComando8(LCD_2POS7);
	WDato (':');
	WComando8(LCD_2POS10);
	WDato (0x7E);
	Escribir ((char*) "Atras");
	WComando8(FLECHA_ATRAS);
}

void LCD_HoraRiegoC (void) {
	WComando8(LCD_CLEAR);
	Escribir ((char*) "Hora:");
	WComando8 (LCD_1POS7);
	WDato (':');
	WComando8(LCD_1POS11);
	WDato(0x7E);
	WComando8(LCD_1POS12);
	Escribir ((char*) "OFF");
	WComando8(LCD_2POS10);
	WDato (0x7E);
	Escribir ((char*) "Atras");
	WComando8(FLECHA_ATRAS);
}


void ActualizarTierra (uint8_t Hum_t){
	WComando8(LCD_CURSOROFF);
	WComando8(LCD_1POS8);
	WDato(Hum_t/10+48);
	WDato(Hum_t%10+48);
	WComando8(FLECHA_ATRAS);
	WComando8(BLINK_ON);
}

void ActualizarAmbiente (uint8_t Temp, uint8_t Hum_a){
	WComando8(LCD_CURSOROFF);
	WComando8(LCD_1POS12);
	WDato(Temp/10+48);
	WDato(Temp%10+48);
	WComando8(LCD_2POS7);
	WDato(Hum_a/10+48);
	WDato(Hum_a%10+48);
	WComando8(FLECHA_ATRAS);
	WComando8(BLINK_ON);
}

const uint8_t Array_PMenu[]=			{FLECHA_TIERRA,FLECHA_AMBIENTE,FLECHA_SETTINGS};

const uint8_t Array_PSettings[]=		{FLECHA_ATRAS,FLECHA_RIEGO,FLECHA_HORAFECHA};

const uint8_t Array_PRiegoC[]=		{FLECHA_ATRAS,FLECHA_RIEGOAUT,LCD_1POS13,LCD_1POS14};

const uint8_t Array_PHorasAutC[]=		{FLECHA_ATRAS, LCD_1POS0, LCD_1POS2, LCD_1POS4,
									LCD_1POS6, LCD_1POS8, LCD_1POS10,
									LCD_1POS12, LCD_1POS14};

const uint8_t Array_PHoraFechaC[]=	{FLECHA_ATRAS, LCD_1POS6, LCD_1POS7, LCD_1POS9,
									LCD_1POS10, LCD_1POS12, LCD_1POS13,LCD_2POS5,
									LCD_2POS6, LCD_2POS8, LCD_2POS9};

const uint8_t Array_PHoraRiegoC[]=	{FLECHA_ATRAS, LCD_1POS5, LCD_1POS6, LCD_1POS8,
									LCD_1POS9, LCD_1POS11};


uint8_t MuevoCursor (uint8_t Pant, uint8_t Cursor) {
	static uint8_t i=0;
	if (Cursor==RENUEVO_POS) i=0;
	switch (Pant) {
		case Pantalla_Menu:
			Cursor=Array_PMenu[i++];
			i%=3;
			break;

		case Pantalla_Settings:
			Cursor=Array_PSettings[i++];
			i%=3;
			break;

		case Pantalla_RiegoC:
			Cursor=Array_PRiegoC[i++];
			i%=4;
			break;

		case Pantalla_HorasAutC:
			Cursor=Array_PHorasAutC[i++];
			i%=9;
			break;

		case Pantalla_HoraFechaC:
			Cursor=Array_PHoraFechaC[i++];
			i%=11;
			break;

		case Pantalla_HoraRiegoC:
			Cursor=Array_PHoraRiegoC[i++];
			i%=6;
			break;

		default: break;
	}
	WComando8 (Cursor);
	return Cursor;
}

char* itoa2dig (uint8_t num) {
      if (num<0){
            num=-num;
            static char str[4];
            str[0]='-';
            str[1]=num/10+48;
            str[2]=num%10+48;
            str[3]='\n';
            return str;
      }
      else {
            static char str[3];
            str[0]=num/10+48;
            str[1]=num%10+48;
            str[2]='\n';
            return str;
      }
}
