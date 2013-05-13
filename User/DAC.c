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
// Descripción:
//   Función por defecto de inicialización del sistema
//------------------------------------------------------
void dac_init(void)
{
  printf("dac_init");
}

//------------------------------------------------------
// void rampas(void)
//
// Descripción:
//   Convierte los bits a rampas que siguen la señal.
//------------------------------------------------------
void rampas(void)
{
 /** WORD valor, incremento = 100;

  // Imprime intrucciones
  output("CONECTE EL OSCILOSCOPIO EN LA SALIDA ANALÓGICA\r\n");
  output("PULSE UNA TECLA CUANDO ESTÉ LISTO PARA MEDIR LA SEÑAL...\r\n");

  // Espera a que se pulse una tecla
  inch();

  // Imprime mensaje de generando señal
  output("...GENERANDO SEÑAL TRIANGULAR...\r\n");

  // Bucle de generación de señal
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


