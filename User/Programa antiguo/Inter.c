//Inter.c
//Se ocupa de las interrupciones
//

#include <stdio.h>
#include "Inter.h"

#define IO_BASE_PHYS 0x80000000UL //direccion base de registros del canal 0 (transmisión)
#define EP93XX_AHB_BASE (IO_BASE_PHYS+0x00000000UL)

#define VIC1_BASE (EP93XX_AHB_BASE+0x000b0000) //tabla 1 de vectores de interrupción que contienen las direcciones de las rutinas de atención de interrupción(dentro de ella se encontrará la del Timer)
#define VIC2_BASE (EP93XX_AHB_BASE+0x000c0000) 

#define VIC_IRQ_STATUS 0x00 //muestra las interrupciones activas con un 1
#define VIC_INT_SELECT 0x0c /* tipo de interrupción: 1 = FIQ, 0 = IRQ */
#define VIC_INT_ENABLE 0x10 /* 1 = enable, 0 = disable */
#define VIC_INT_ENABLE_CLEAR 0x14 //para limpiar el VIC_INT_ENABLE (poniendo un "1" en lo que se quiera desactivar)
#define VIC_INT_SOFT_CLEAR 0x1c
#define VIC_VECT_ADDR 0x30 //contiene la dirección de la rutina de atención a la interrupción activa
#define VIC_DEF_VECT_ADDR 0x34 //dirección por defecto, es decir, si no  tiene ninguna asignada

#define VIC_VECT_ADDR0 0x100 /* 0 to 15 */ //contiene la dirección de la rutina que indique el VIC_VECT_CNTL0
#define VIC_VECT_CNTL0 0x200 /* 0 to 15 */ //nos indica de que fuente de interrupción es la dirección que hay en VIC_VECT_ADDR0

#define VIC_ITCR 0x300 /* VIC test control register */

//typedef en el .h!!
/* table of vector functions */
static vector_func vector_tbl[64];
static void __attribute__((interrupt ("IRQ"))) lowlevel_int(void)  //lowlevel_int ->interrupciones a bajo nivel
{
	int i;
	unsigned int status;

	status = *((volatile unsigned int *)(VIC1_BASE+VIC_IRQ_STATUS));
	if(status)
	{
		unsigned int c = *((volatile unsigned int *)(VIC1_BASE+VIC_VECT_ADDR));


		for(i=0;i<32;i++)
		{
			if(status & (1<<i))
			{
				if(vector_tbl[i] != 0)
				vector_tbl[i]();
			}
		}
	*((volatile unsigned int *)(VIC1_BASE+VIC_VECT_ADDR)) = c;
	}
	status = *((volatile unsigned int *)(VIC2_BASE+VIC_IRQ_STATUS));
	if(status)
	{
		unsigned int c = *((volatile unsigned int *)(VIC2_BASE+VIC_VECT_ADDR));


		for(i=0;i<32;i++)
		{
			if(status & (1<<i))
			{
				if(vector_tbl[32+i] != 0)
				vector_tbl[32+i]();
			}
		}

		*((volatile unsigned int *)(VIC2_BASE+VIC_VECT_ADDR)) = c;
	}
}
static char firsttime = 1;

int setvect(int offset, vector_func func)
{
	if(firsttime)
	{
		int i;
		unsigned int tmp;

		firsttime = 0;

		for(i=0;i<64;i++) vector_tbl[i] = 0;

		/* disable all */
		*((volatile unsigned int *)(VIC1_BASE+VIC_INT_SELECT)) = 0;
		*((volatile unsigned int *)(VIC1_BASE+VIC_INT_ENABLE_CLEAR)) = ~0;
		*((volatile unsigned int *)(VIC1_BASE+VIC_ITCR)) = 0;
		*((volatile unsigned int *)(VIC1_BASE+VIC_INT_SOFT_CLEAR)) = ~0;
		/* ensure cleared existing ints */
		for(i=0;i<19;i++)
		{
			tmp = *((volatile unsigned int *)(VIC1_BASE+VIC_VECT_ADDR)); 
			*((volatile unsigned int *)(VIC1_BASE+VIC_VECT_ADDR)) = tmp;
		}

		/* set the vecored ints to disabled -> we arent using them */
		for(i=0;i<16;i++)
		{
			*((volatile unsigned int *)(VIC1_BASE+VIC_VECT_CNTL0+(4*i))) = 0;
			*((volatile unsigned int *)(VIC1_BASE+VIC_VECT_ADDR0+(4*i))) = 0;
		}


		*((volatile unsigned int *)(VIC1_BASE+VIC_DEF_VECT_ADDR)) = (unsigned int)lowlevel_int; 
		*((volatile unsigned int *)(VIC1_BASE+VIC_VECT_ADDR)) = (unsigned int)lowlevel_int; 

		/* disable all */
		*((volatile unsigned int *)(VIC2_BASE+VIC_INT_SELECT)) = 0;
		*((volatile unsigned int *)(VIC2_BASE+VIC_INT_ENABLE_CLEAR)) = ~0; 
		*((volatile unsigned int *)(VIC2_BASE+VIC_ITCR)) = 0;
		*((volatile unsigned int *)(VIC2_BASE+VIC_INT_SOFT_CLEAR)) = ~0;

		/* ensure cleared existing ints */
		for(i=0;i<19;i++)
		{
			tmp = *((volatile unsigned int *)(VIC2_BASE+VIC_VECT_ADDR));
			*((volatile unsigned int *)(VIC2_BASE+VIC_VECT_ADDR)) = tmp;
		}

		/* set the vecored ints to disabled -> we arent using them */
		for(i=0;i<16;i++)
		{
			*((volatile unsigned int *)(VIC2_BASE+VIC_VECT_CNTL0+(4*i))) = 0;
			*((volatile unsigned int *)(VIC2_BASE+VIC_VECT_ADDR0+(4*i))) = 0;
		}
			*((volatile unsigned int *)(VIC2_BASE+VIC_DEF_VECT_ADDR))
			= (unsigned int)lowlevel_int;
			*((volatile unsigned int *)(VIC2_BASE+VIC_VECT_ADDR))
			= (unsigned int)lowlevel_int;


			/* redboot has the address for IRQ interrupt stored at 0x38 */
			*((volatile unsigned int *)(0x38)) = (unsigned int)lowlevel_int;

	}
	disableIRQ(offset);
	if(offset < 32)
	{
		vector_tbl[offset] = func;
	}
	else if(offset < 64)
	{
		vector_tbl[offset] = func;
	}
	enableIRQ(offset);
	
	printf ("Interrupciones inicializadas");
	return 0;
}

void enableIRQ(int offset) // "activa" interrupciones
{
	if(offset < 32)
	{
		*((volatile unsigned int *)(VIC1_BASE+VIC_INT_ENABLE)) |= (1<<offset);
	}
	else if(offset < 64)
	{
		*((volatile unsigned int *)(VIC2_BASE+VIC_INT_ENABLE)) |= (1<<(offset-32));
	}

}
void disableIRQ(int offset) // "desactiva" interrupciones
{
	if(offset < 32)
	{
		*((volatile unsigned int *)(VIC1_BASE+VIC_INT_ENABLE_CLEAR)) |= (1<<offset);
	}
	else if(offset < 64)
	{
		*((volatile unsigned int *)(VIC2_BASE+VIC_INT_ENABLE_CLEAR)) |= (1<<(offset-32));
	}
}
int getvect(int offset, vector_func *func) 
{
	if(offset < 0 || offset >= 64) return -1;

	*func = vector_tbl[offset];

	return 0;
} 
