//------------------------------------------------------------------------------
// DAC.c
//
//   Para manejar el conversor
// 
//------------------------------------------------------------------------------

#include <stdio.h>

//------------------------------------------------------
// void _init(void)
//
// Descripci�n:
//   Funci�n por defecto de inicializaci�n del sistema
//------------------------------------------------------
void dac_init(void)
{
  printf("dac_init");
}

//------------------------------------------------------
// void rampas(void)
//
// Descripci�n:
//   Convierte los bits a rampas que siguen la se�al.
//------------------------------------------------------
void rampas(void)
{
 /** WORD valor, incremento = 100;

  // Imprime intrucciones
  output("CONECTE EL OSCILOSCOPIO EN LA SALIDA ANAL�GICA\r\n");
  output("PULSE UNA TECLA CUANDO EST� LISTO PARA MEDIR LA SE�AL...\r\n");

  // Espera a que se pulse una tecla
  inch();

  // Imprime mensaje de generando se�al
  output("...GENERANDO SE�AL TRIANGULAR...\r\n");

  // Bucle de generaci�n de se�al
  while(TRUE)
  {
    // Rampa de subida
    for(valor = 0; valor <= 0xFFF; valor += incremento)
      DAC_dato(valor);

    // Rampa de bajada
    for(valor = 0xFFF; valor >= 0; valor -= incremento)
      DAC_dato(valor);
  }**/
}


