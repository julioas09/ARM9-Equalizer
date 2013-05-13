//------------------------------------------------------------------------------
// Tutorial del driver del Timer del microcontrolador ARM920T.
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


#define TIMER2_CONTROL 0x80810028 
#define TIMER2_LOAD 0x80810020 
#define TIMER2_VALUE 0x80810024 



#define TIMER_MAJOR_NUMBER 71
MODULE_LICENSE("GPL");

//------------------------------------------------------
// int reg_open(struct inode *inode, struct file *filp)
//
// Descripción:
// 	Función para abrir e inicializar	
//	 
//------------------------------------------------------
volatile char *timer2_control;
volatile char *timer2_load;
volatile char *timer2_value;

int 
reg_open(struct inode *inode, struct file *filp)
{
	MOD_INC_USE_COUNT;  //para "decir" que lo estoy usando
	printk("<1>Opening timer...\n");
	if(check_mem_region(TIMER2_CONTROL, 4)) {
               printk("DUMB: espacio de memoria en uso: TIMER2_CONTROL\n");
               return -EBUSY;
       }
		if(check_mem_region(TIMER2_VALUE, 4)) {
               printk("DUMB: espacio de memoria en uso: TIMER2_VALUE\n");
               return -EBUSY;
       }

       if(check_mem_region(TIMER2_LOAD, 4)) {
               printk("DUMB: espacio de memoria en uso: TIMER2_LOAD\n");
               return -EBUSY;
       }


      
	//Tomar memoria

	 request_mem_region(TIMER2_CONTROL, 4, "timer2_control");
	 timer2_control = __ioremap(TIMER2_CONTROL, 4, 0);

	 request_mem_region(TIMER2_VALUE, 4, "timer2_value");
	 timer2_value = __ioremap(TIMER2_VALUE, 4, 0);

	 request_mem_region(TIMER2_LOAD, 4, "timer2_load");
	 timer2_load = __ioremap(TIMER2_LOAD, 4, 0);



	

	 printk("dumb: timer2_control remap = %p\n", timer2_control);
	 printk("dumb: timer2_load remap = %p\n", timer2_load);
	 printk("dumb: timer2_value remap = %p\n", timer2_value);
	 
	//Configura registros

	*timer2_control = 0x48;
	*timer2_load = 63;
	*timer2_control |= 0x80;

	printk("<1> Timer 2 value = 0x%x \n", *(timer2_value));
	printk("<1> Timer 2 value = 0x%x \n", *(timer2_value));
	printk("<1> Timer 2 value = 0x%x \n", *(timer2_value));
	printk("<1> Timer 2 value = 0x%x \n", *(timer2_value));	
/**
	*((volatile unsigned int *)(TIMER1_CONTROL)) = 0x48;
	*((volatile unsigned int *)(TIMER1_LOAD)) = 63;
	*((volatile unsigned int *)(TIMER1_CONTROL)) = 0xc8;
**/
	printk("<1>Timer init done\n");
  
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
	MOD_DEC_USE_COUNT;   //para "decir" que dejo de usarlo
	release_mem_region(TIMER2_LOAD, 4);
	release_mem_region(TIMER2_CONTROL, 4);
	release_mem_region(TIMER2_VALUE,4);
	printk("<1>Closing timer\n");
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
	return 0;
}

//------------------------------------------------------
// ssize_t reg_write(struct file *filep, const char *buf, size_t count, loff_t *f_pos)
//
// Descripción:
// 	Función para escribir 
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

	printk("<1>Timer!\n");
	result = register_chrdev(TIMER_MAJOR_NUMBER, "timer", &reg_fops);
	if(result<0){
		printk("<1>Fail major number %d\n", TIMER_MAJOR_NUMBER);
		return result;
	}
  
  //check_region(REG_ADDR, 1);
	printk("<1>Timer registrado!\n");
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
	unregister_chrdev(TIMER_MAJOR_NUMBER, "timer");
        
  //Unlock access to register
  //release_region(REG_ADDR, 1);
	printk("<1>Cierro Timer!");
}

module_init(my_init);
module_exit(my_end);
