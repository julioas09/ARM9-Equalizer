#include <stdio.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int timer;

void init_timer2(void){

	timer=open ("/dev/timer",S_IRUSR);

printf ("Timer1 inicializado\n");

}



void close_timer2(void){

	close(timer);
	printf("Timer cerrado\n");
}
