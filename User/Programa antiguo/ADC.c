//------------------------------------------------------------------------------
// ADC.c
//
//   
//   
//
// 
//
//------------------------------------------------------------------------------

#include <stdio.h>
#define SYS_SW_LOCK 0x809300C0   //para desbloquear registros del sistema
#define ADC_CLK_DIV 0x80930090   //para el reloj del ADC
#define DEVICE_CFG 0x80930080    //configurar dispositivos
#define ADC_RESULT 0x80900008   // lectura
#define ADC_SWITCH 0x80900018  //selecciona entrada
#define ADC_SW_LOCK 0x80900020  //Para desbloquear registros ADC
#define ADC_INT_EN 0x80900024  // Activa interrupciones en el bit 11


 

#define FONDO_ESCALA 0xFFF	// Valor de lectura m�xima del ADC
#define V_MAX 3.3		// Valores de tensi�n m�xima del ADC  �?�?�?�?�

//------------------------------------------------------
// void __init(void)
//
// Descripci�n:
//   Funci�n por defecto de inicializaci�n del sistema
//
//------------------------------------------------------
void adc_init(void)
{
	*((volatile unsigned int *)(SYS_SW_LOCK)) = 0xAA;   //este registro tiene que tecarlo el driver
	*((volatile unsigned int *)(ADC_CLK_DIV)) = 0x80000000; //reloj dividido por 16
	*((volatile unsigned int *)(DEVICE_CFG)) = 0x00020000; //activa ADC
	*((volatile unsigned int *)(ADC_SW_LOCK)) = 0xAA;  
	*((volatile unsigned int *)(ADC_SWITCH)) = 0x00000608; //ADC0 pin 27
	*((volatile unsigned int *)(ADC_INT_EN)) = 0x00000000;     //activar interrupciones-> no
	printf ("ADC inicializado \n");
}

//------------------------------------------------------
// void bucleMain(void)
//
// Descripci�n:
//   Funci�n del programa principal
//
//------------------------------------------------------

double lectura_adc(void)
{


	int lectura;
	double tension;

	printf("lectura_adc");



  // Imprime intrucciones
	printf("\r\nCONECTE EN LA ENTRADA ANAL�GICA 1 UNA TENSI�N ENTRE 0 Y 3.3 V.\r\n");
	printf("PULSE UNA TECLA PARA REALIZAR LA MEDIDA...\r\n");

  // Espera a recibir un car�cter
	getchar();

  // Lee un dato de la entrada anal�gica 1
	lectura= *((volatile unsigned int *)(ADC_RESULT));

  // Calcula la tensi�n correspondiente al valor le�do
	tension = V_MAX * ((double)lectura/FONDO_ESCALA);

  // Imprime la primera parte del mensaje de resultado
	printf("VALOR MEDIDO ENTRE 0V (000000000000) Y 3.3V (111111111111) ES: \n");
	printf("%f", tension);
	

	return tension;

  // Imprime 'tensi�n' con 2 cifras decimales sin signo
  //outNumDec(10,tension,2,SIN_SIGNO); 
  //printf("V (");

  // Imprime el dato le�do en binario
 // outNum(2, lectura, SIN_SIGNO);

  // Imprime el final del mensaje de resultado
  //printf(")\r\n"); 

}




