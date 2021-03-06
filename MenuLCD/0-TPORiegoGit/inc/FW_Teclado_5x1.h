/*
 * Teclado_4x1.h
 *
 *  Created on: 30/09/2013
 *      Author: marcelo
 */

#ifndef FW_TECLADO_5X1_H_
#define FW_TECLADO_5X1_H_

	#include "Aplicacion.h"

	#define     SW1_PRESS     	GetPIN(KEY0,ACTIVO_BAJO)
    #define     SW2_PRESS    	GetPIN(KEY1,ACTIVO_BAJO)
    #define     SW3_PRESS	  	GetPIN(KEY2,ACTIVO_BAJO)
    #define     SW4_PRESS    	GetPIN(KEY3_RC,ACTIVO_BAJO)
    #define     SW5_PRESS    	GetPIN(KEY4_RC,ACTIVO_BAJO)

	#define 	CANT_REBOTES	50 			//!< valor empírico
	#define		REPOSO			0
	#define		DETECCION		1
	#define		CHEQUEO			2
	#define		EMERGENCIA		CHEQUEO
	#define		NO_KEY			(uint8_t) 0xFF

	/** -------------------------------------------------------------------------------------
	 * Prototipos
	 */
	uint8_t TecladoHW (void);
	void TecladoSW (uint8_t);
	void DriverTeclado(void);

#endif /* FW_TECLADO_5X1_H_ */
