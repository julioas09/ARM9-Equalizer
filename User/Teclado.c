//------------------------------------------------------------------------------
//Mirar includes
//Mirar funciones raras
//
//------------------------------------------------------------------------------

#include <stdio.h>
#define NUM_FILAS 4
#define NUM_COLS 4
#define EXCIT 1

//------------------------------------------------------
// char teclado(void)
//
// Descripci�n:
//   Explora el teclado matricial y devuelve la tecla 
//   pulsada
//------------------------------------------------------
char teclado(void)
{
printf("/n Teclado /n"); //QUITAR
  /**char tecla;
  BYTE fila, columna, fila_mask;
  static char teclas[4][4] = {{"123C"},
                              {"456D"},
                              {"789E"},
                              {"A0BF"}};
  // Bucle de exploraci�n del teclado
  while(TRUE){

    // Excitamos una columna
    for(columna = NUM_COLS - 1; columna >= 0; columna--){
      set16_puertoS(EXCIT << columna);		// Se env�a la excitaci�n de columna
      retardo(1150);				// Esperamos respuesta de optoacopladores

      // Exploramos las filas en busca de respuesta
      for(fila = NUM_FILAS - 1; fila >= 0; fila--){
        fila_mask = EXCIT << fila;		// M�scara para leer el bit de la fila actual
        if(lee16_puertoE() & fila_mask){		// Si encuentra tecla pulsada,
          while(lee16_puertoE() & fila_mask);	//   Esperamos a que se suelte
          retardo(1150);			//   Retardo antirrebotes
          return teclas[fila][columna];		//   Devolvemos la tecla pulsada
        }
      }
      // Siguiente columna
    }
    // Exploraci�n finalizada sin encontrar una tecla pulsada
  }**/
return 'a'; // QUITAR
  // Reiniciamos exploraci�n
}

