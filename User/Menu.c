//------------------------------------------------------------------------------
// 
// 
//  
//
// 
// 
//------------------------------------------------------------------------------

#include "ADCUsuario.h"
#include "InterUsuario.h"
#include "TimerUsuario.h"
#include "LEDsUsuario.h"
#include <stdio.h>
#include <unistd.h>

//#define MENU 0
//#define CARACTERIZACION 1
//#define ECUALIZACION 2
//#define REVERBERACION 3


void GestionMenuPrincipal(void);
void GestionCaracterizacion(void);
void GestionEcualizacion(void);
void GestionReverb(void);
void MenuPrincipal(void);
//int estado;

//------------------------------------------------------
//------------------------------------------------------
void init(void){
	printf("Inicializaciones:\n");
	//adc_init();
	//init_timer2();
	leds_init();
	//inter_init();
	
}

void cerrar(void){
	printf("Cerrando: \n");
	//close_inter();
	//close_timer2();
	//close_adc();
	close_leds();
}


void MenuPrincipal(void)   {
	printf("\n***********************************************\n");     
	printf("\n*              Menu Principal                 *\n");
	printf("\n***********************************************\n");
	printf("\n* Seleccione una de las siguientes opciones   *\n");
	printf("\n* 1 -  Caracterizacion de filtros             *\n");
	printf("\n* 2 -  Ecualizacion Grafica                   *\n");
	printf("\n* 3 -  Incorporacion de Reverberacion Simple  *\n");
	printf("\n***********************************************\n");
	printf("\n");
	//estado=MENU;
}

void GestionMenuPrincipal(void){
}
//------------------------------------------------------
// void bucleMain(void)
//
// Descripción:
//   Función del programa principal
//------------------------------------------------------
int
main (int argc, char* argv[])
{
//char tecla;
	init();

	while (1){
		enciendeLeds(0,8);
		sleep(5);
		enciendeLeds(1,7);
		sleep(5);
		enciendeLeds(2,6);
		sleep(5);
		enciendeLeds(3,5);
		sleep(5);
		enciendeLeds(4,4);
		sleep(5);
		enciendeLeds(5,3);
		sleep(5);
		enciendeLeds(6,2);
		sleep(5);
		enciendeLeds(0,1);
		sleep(5);
		enciendeLeds(1,0);
		sleep(5);

	}
	//MenuPrincipal();
	cerrar();
/**while (1){
	tecla = teclado();
	estado=tecla -'0';					
	switch (estado){
		case MENU:                         // se queda dando vueltas		GestionMenuPrincipal();
		break;
		case CARACTERIZACION:                        //Caracterizacion
		GestionCaracterizacion();
		break;
		case ECUALIZACION:                        //Ecualizacion
		GestionEcualizacion();
		break;
		case REVERBERACION:                        //Reverb
		GestionReverb();
		break;
		default:
		printf("\n*** Opcion elegida erronea. Vuelva a intentarlo. ***\n");
		MenuPrincipal();
		break;
	}
}	**/
return 0;
}

void GestionCaracterizacion (void){
	//char tecla;
	printf("\n***CARACERIZACION DE FILTROS***\n");
	printf("\nSeleccione el filtro que quiere caracterizar (1-7) o 'A' para volver al menú de inicio\n");
	/**tecla=teclado();
		switch (tecla){
		case '1':                         //Filtro 1
		printf("\n Ha seleccionado el filtro numero 1");
		break;
		case '2':                        //Filtro2
		printf("\n Ha seleccionado el filtro numero 2");
		break;
		case '3':                        //Filtro3
		printf("\n Ha seleccionado el filtro numero 3");
		break;
		case '4':                        //Filtro4
		printf("\n Ha seleccionado el filtro numero 4");
		break;
		case '5':                         //Filtro5
		printf("\n Ha seleccionado el filtro numero 5");
		break;
		case '6':                        //Filtro6
		printf("\n Ha seleccionado el filtro numero 6");
		break;
		case '7':                        //Filtro7
		printf("\n Ha seleccionado el filtro numero 7");
		break;
		case 'A':                        //Volver
		MenuPrincipal();
		break;
		default:
		printf("\n*** Tecla no válida. Por favor,  pulse de 1 a 7  para seleccionar ***\n");
		GestionCaracterizacion();
		break; 
	}**/
}

void GestionEcualizacion (void){
	printf("\nBANDA:      32Hz	64Hz	125Hz	250Hz	500Hz	1kHz	2kHz \n");
	printf("\nGANANCIA: \n");
	printf("\nNIVEL: \n");
}

void GestionReverb (void){
	printf("\nReverb\n");
}


