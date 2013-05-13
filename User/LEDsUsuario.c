//------------------------------------------------------------------------------
// LEDs.c
//
//Se ocupa de encender los LEDs
//   
//   
//
// 
// 
//------------------------------------------------------------------------------

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
//---------------------------------------------------------
// void LEDs(void)
//
// Descripción:
//   Enciende los LEDs de una columna. Tantos como el int de entrada.
//   
//
// 
//  
//---------------------------------------------------------
int leds;
int v;
void enciendeLeds(int banda, int nivel)
{	
	char *buf= malloc(sizeof (char));
 	printf("enciendeLeds\n");
	*buf = (char)nivel;
	*buf = *buf<<4;
	*buf |= (char)banda; 
	printf("buf= 0x%x \n",*(buf));
	printf("leds_init #%d\n",leds);
	v=write(leds,buf,1);	//da -1
        printf("Error opening file: %s\n",strerror(errno));
	printf(" Comprobacion write = %d\n",v);
	free(buf);
	
	
	
}

//---------------------------------------------------------
// void __init(void)
//
// Descripción:
//   Función por defecto de inicialización del sistema
//
//---------------------------------------------------------
void leds_init(void)
{
	leds=open ("/dev/leds",O_RDWR);
	printf("Leds inicializados #%d\n",leds);
}

void close_leds(void){

	close(leds);
	printf("LEDs cerrado\n");
}

