//------------------------------------------------------------------------------
// Tutorial de la aplicación de usuario del ADC del microcontrolador ARM920T con driver.
//
// Inicializa y realiza una lectura del ADC, utilizando el ADCdriver.
//   
// Autores: María del Pino Ruiz de Toledo Gutiérrez del Álamo y Julio Alberto Seijas Diego
//------------------------------------------------------------------------------


#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#define FONDO_ESCALA 0xFFF	// Valor de lectura máxima del ADC
#define V_MAX 3.3		// Valores de tensión máxima del ADC  


int adc; //descriptor de fichero

//------------------------------------------------------
// void adc_init(void)
//
// Descripción:
// 	Función por defecto de inicialización del sistema	
//	Utiliza la funcion open del ADCdriver 
//------------------------------------------------------
void adc_init(void)
{
	adc=open ("/dev/adc",S_IRUSR);
	printf("ADC inicializado \n");
}


void close_adc(void){

	close(adc);
	printf("ADC cerrado\n");
}
//------------------------------------------------------
// double lectura_adc(void)
//
// Descripción:
// 	Función del programa para leer un valor del ADC.
//	Utiliza la funcion open de ADCdriver
//------------------------------------------------------
/*
double lectura_adc(void)
{
	int bytes,i;
	int lectura;
	double tension;
	char *buf=0;
	//while(1){
	printf("lectura_adc");


  // Imprime intrucciones
	//printf("\r\nCONECTE EN LA ENTRADA ANALÓGICA 1 UNA TENSIÓN ENTRE 0 Y 3.3 V.\r\n");
	//printf("PULSE UNA TECLA PARA REALIZAR LA MEDIDA...\r\n");

  // Espera a recibir un carácter para leer
	//getchar();
	for(i=0;i<5;i++)
	{
		bytes=read(adc,buf,2);
		printf("VALOR LEIDO Ox%d\n",bytes);
	}
	sleep(5);

	lectura= (int)(buf[0]*256 + buf[1]); //lo convierte otra vez a un int
	printf("lectura = %f",lectura);

  // Calcula la tensión correspondiente al valor leído
	tension = V_MAX * ((double)lectura/FONDO_ESCALA);

  // Imprime la primera parte del mensaje de resultado
	printf("VALOR MEDIDO ENTRE 0V (000000000000) Y 3.3V (111111111111) ES: \n");
	printf("%f", tension);
//While	}
	return tension;
}
*/

