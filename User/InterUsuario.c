//------------------------------------------------------------------------------
// Tutorial de la aplicación de usuario de las interrupciones del microcontrolador ARM920T con driver.
//
// Inicializa configura las interrupciones.
//   
// Autores: María del Pino Ruiz de Toledo Gutiérrez del Álamo y Julio Alberto Seijas Diego
//------------------------------------------------------------------------------


#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
 

int inter;


//------------------------------------------------------
// void inter_init(void)
//
// Descripción:
// 	Función que se encarga de abrir el driver de interrupciones.
//	
//------------------------------------------------------
void inter_init(void){
	inter=open ("/dev/inter",S_IRUSR);
	printf("Interrupciones inicializadas\n");
}

void close_inter(void){
	close(inter);
	printf("Interrupciones cerradas\n");
}



