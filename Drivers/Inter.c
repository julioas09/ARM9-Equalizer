//------------------------------------------------------------------------------
// Tutorial del driver de las interrupciones del microcontrolador ARM920T.
//
// Define y configura las funciones del driver.
//   
// Autores: María del Pino Ruiz de Toledo Gutiérrez del Álamo y Julio Alberto Seijas Diego
//------------------------------------------------------------------------------



#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/ioport.h>
#include <asm/io.h>
#include <unistd.h>

#include <linux/sched.h> 
#include <linux/signal.h> 
#include <asm/irq.h>



#define TIMER_2_CLEAR 0x8081002C


#define INTER_MAJOR_NUMBER 72
MODULE_LICENSE("GPL");

volatile char *timer_2_clear;

int lectura;
//------------------------------------------------------
// void manejador_timer(int id, void *p, struct pt_regs *regs) 
//
// Descripción:
// 	Es la rutina de atención a la interrupción, que en esta caso llama a la función
//	lee_adc() del driver del ADC
//	 
//------------------------------------------------------
void manejador_timer(int id, void *p, struct pt_regs *regs) 
{ 
	
	lectura=lee_adc();
	//para avisar de que he atendido a la interrupcion
	*timer_2_clear = 0xFF; 
	
}

//------------------------------------------------------
// int reg_open(struct inode *inode, struct file *filp)
//
// Descripción:
// 	Función que en este caso instala el manejador y reserva memoria
//	 
//------------------------------------------------------
int 
reg_open(struct inode *inode, struct file *filp)
{
	MOD_INC_USE_COUNT;  //para "decir" que lo estoy usando
	printk("<1>Opening inter...\n");
	int resultado;

	

	//Comprueba memoria
	if(check_mem_region(TIMER_2_CLEAR, 4)) {
               printk("DUMB: espacio de memoria en uso: TIMER_2_CLEAR\n");
               return -EBUSY;
       }	

	//Toma memoria
	request_mem_region(TIMER_2_CLEAR, 4, "timer_2_clear");
	timer_2_clear = __ioremap(TIMER_2_CLEAR, 4, 0);

	printk("dumb: timer_2_clear remap = %p\n", timer_2_clear);

	// instalar manejador
	resultado=request_irq(5,manejador_timer,SA_INTERRUPT,"timer2",NULL);  // da error
	printk("REQUEST_IRQ = %d \n",resultado);

	printk("<1>inter init done\n");
  
	return 0;
}


//------------------------------------------------------
// int reg_release(struct inode *inode, struct file *filep)
//
// Descripción:
// 	Función para cerrar	
//	 
//------------------------------------------------------
int 
reg_release(struct inode *inode, struct file *filep)
{ 
	MOD_DEC_USE_COUNT;
		 

	//libera memoria
	release_mem_region(TIMER_2_CLEAR, 4);

	printk("<1>Closing inter\n");
	//desinstalar manejador
	free_irq(5, NULL);

	return 0;
}

//------------------------------------------------------
// ssize_t reg_read(struct file *filep, char *buf, size_t count, loff_t *f_pos)
//
// Descripción:
// 	Función para leer. Los drivers se comunican mediante char.	
//	 
//------------------------------------------------------
ssize_t 
reg_read(struct file *filep, char *buf, size_t count, loff_t *f_pos)
{
	buf=lectura;

	return 0;
}

//------------------------------------------------------
// ssize_t reg_write(struct file *filep, const char *buf, size_t count, loff_t *f_pos)
//
// Descripción:
// 	Función para escribir (en el adc no se escribe)	
//	 
//------------------------------------------------------
ssize_t 
reg_write(struct file *filep, const char *buf, size_t count, loff_t *f_pos)
{
	return 0;
}

//struct para definir operaciones
struct file_operations reg_fops = {
        read: reg_read,
        write: reg_write,
        open: reg_open,
        release: reg_release
};


//------------------------------------------------------
// void my_init(void)
//
// Descripción:
// 	Función para registrar el driver	
//	
//------------------------------------------------------
int my_init(void){
	int result;

	printk("<1>INTER!\n");
	result = register_chrdev(INTER_MAJOR_NUMBER, "inter", &reg_fops);
	if(result<0){
		printk("<1>Fail major number %d\n", INTER_MAJOR_NUMBER);
		return result;
	}
  
  //check_region(REG_ADDR, 1);
	printk("<1>INTER registrado!\n");
 	return 0;
}

//------------------------------------------------------
// void my_end(void)
//
// Descripción:
// 	Función para "desregistrar" el driver	
//	 
//------------------------------------------------------
void my_end(void) {
  //libera el MAJOR NUMBER
	unregister_chrdev(INTER_MAJOR_NUMBER, "inter");
  //Unlock access to register
  //release_region(REG_ADDR, 1);
	printk("<1>Cierro INTER!");
}



module_init(my_init);
module_exit(my_end);












