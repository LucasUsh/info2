#include "Aplicacion.h"


void InicSysTick (void){ //si divido x 4, interrumpe cada 2,5ms
		STRELOAD  = ( STCALIB / 5 ) - 1 ;   //N=1 para 10ms
		STCURR = 0;

		ENABLE = 1;
		TICKINT = 1;
		CLKSOURCE = 1;
		return;
}