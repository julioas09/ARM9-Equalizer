#include <stdio.h>

#define TIMER1_CONTROL 0x80810008 
#define TIMER1_LOAD 0x80810000 


void init_timer1(void){

*((volatile unsigned int *)(TIMER1_CONTROL)) = 0x48;
*((volatile unsigned int *)(TIMER1_LOAD)) = 63;
*((volatile unsigned int *)(TIMER1_CONTROL)) = 0xc8;
printf ("Timer1 inicializado");

}





