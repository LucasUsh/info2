#include "Aplicacion.h"

void SetPINSEL( uint8_t port , uint8_t pin ,uint8_t sel)
{
	port = port * 2 + pin / 16;
	pin = ( pin % 16 ) * 2;
	PINSEL[ port ] = PINSEL[ port ] & ( ~ ( 3 << pin ) );
	PINSEL[ port ] = PINSEL[ port ] | ( sel << pin );
}

void SetPINMODE( uint8_t port , uint8_t pin ,uint8_t modo)
{
	port = port * 2 + pin / 16;
	pin = ( pin % 16 ) * 2;
	PINMODE[ port ] = PINMODE[ port ] & ( ~ ( 3 << pin ) );
	PINMODE[ port ] = PINMODE[ port ] | ( modo << pin );
}

void SetMODE_OD( uint8_t port , uint8_t pin , uint8_t dir )
{

	PINMODE_OD[ port ] = PINMODE_OD[ port ] & ( ~ ( 1 << pin ) );
	PINMODE_OD[ port ] = PINMODE_OD[ port ] | ( dir << pin );

}

void SetDIR( uint8_t port , uint8_t pin , uint8_t dir )
{
	port = port * 8;

	GPIOs[ port ] = GPIOs[ port ] & ( ~ ( 1 << pin ) );
	GPIOs[ port ] = GPIOs[ port ] | ( dir << pin );
}

void SetPIN( uint8_t port , uint8_t pin , uint8_t estado )
{
	port = port * 8 + 5;

	GPIOs[ port ] = GPIOs[ port ] & ( ~ ( 1 << pin ) );
	GPIOs[ port ] = GPIOs[ port ] | ( estado << pin );
}

uint8_t GetPIN( uint8_t port , uint8_t pin , uint8_t actividad )
{
	port = port * 8 + 5;

	return ( ( ( GPIOs[ port ] >> pin ) & 1 ) == actividad ) ? 1 : 0;

}

void TooglePIN( uint8_t port , uint8_t pin)
{
	port = port * 8 + 5;

	if ( (GPIOs[ port ] >> pin) & 1 )
		GPIOs[ port ] &= ( ~ ( 1 << pin ) );
	else
		GPIOs[ port ] |= ( 1 << pin );
}
