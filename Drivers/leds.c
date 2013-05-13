#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/ioport.h>
#include <asm/io.h>

#define DIO_DA 0x12c00002 //DIO_0 al DIO_7 DATA REGISTER
#define DIO_DDA 0x12c00000 //DIO_0 al DIO_7 DIRECTION REGISTER
#define DIO_B 0x12000001 //DIO_16 al DIO_19 DIRECTION/DATA REGISTER


#define LEDS_MAJOR_NUMBER 73
MODULE_LICENSE("GPL");


volatile char *dio_da; // declarar como volatile o como unsigned?
volatile char *dio_dda;
volatile char *dio_b;


int 
reg_open(struct inode *inode, struct file *filp)
{



	MOD_INC_USE_COUNT; 
	printk("<1>Opening leds...\n");
	
	//comprueba memoria
	if(check_mem_region(DIO_DDA, 1)) {
               printk("DUMB: espacio de memoria en uso: DIO_DDA\n");
               return -EBUSY;
       }
	

       if(check_mem_region(DIO_DA, 1)) {
               printk("DUMB: espacio de memoria en uso: DIO_DA\n");
               return -EBUSY;
       }
	if(check_mem_region(DIO_B, 1)) {
               printk("DUMB: espacio de memoria en uso: DIO_B\n");
               return -EBUSY;
       }
	

 



      
	//Tomar memoria

	 request_mem_region(DIO_DDA, 1, "dio_dda");
	 dio_dda = __ioremap(DIO_DDA, 1, 0);

	 request_mem_region(DIO_DA, 1, "dio_da");
	 dio_da = __ioremap(DIO_DA, 1, 0);

 	request_mem_region(DIO_B, 1, "dio_b");
	 dio_b = __ioremap(DIO_B, 1, 0);




	

	 printk("dumb: dio_dda remap = %p\n", dio_dda);
	 printk("dumb: dio_da remap = %p\n", dio_da);
	 printk("dumb: dio_b remap = %p\n", dio_b);
	
	
	*dio_dda = 0xFF; // hacer con mascaras?
	*dio_b = 0xF0;
	printk("<1> dio_dda= 0x%x \n", *dio_dda);
	printk("<1> dio_b= 0x%x \n", *dio_b);
/**
  _peddr = inb(0x80840024);
  _peddr |= 0x03;
  outb(_peddr, 0x80840024);

  _pedr = inl (0x80840020);
  _pedr &= (~0xFFFFFFFC);
  outl (_pedr, 0x80840020);
**/

  printk("<1>leds init done\n");
  
  return 0;
}

int 
reg_release(struct inode *inode, struct file *filep)
{ 

	MOD_DEC_USE_COUNT;   
	
	release_mem_region(DIO_DDA, 1);
	release_mem_region(DIO_DA, 1);
	release_mem_region(DIO_B, 1);
	printk("<1>Closing leds\n");
	return 0;
}

ssize_t 
reg_read(struct file *filep, char *buf, size_t count, loff_t *f_pos)
{
  return 0;
}

ssize_t 
reg_write(struct file *filep, const char *buf, size_t count, loff_t *f_pos)
{
	unsigned char _dio_da;//puerto a son las columnas
	unsigned char _dio_b;//puerto f son las filas	
	_dio_b = (*buf) & 0x07; //Me quedo con los tres bits de la banda
	_dio_da = (*buf) & 0xF0; //Me quedo con el nivel de energía
	switch (_dio_da){
		case 0x00: _dio_da=0x00;
		break;
		case 0x10: _dio_da=0x01;
		break;
		case 0x20: _dio_da=0x03;
		break;
		case 0x30: _dio_da=0x07;
		break;
		case 0x40: _dio_da=0x0F;
		break;
		case 0x50: _dio_da=0x1F;
		break;
		case 0x60: _dio_da=0x3F;
		break;
		case 0x70: _dio_da=0x7F;
		break; 
		case 0x80: _dio_da=0xFF;
		break;
	}

	*dio_da = _dio_da;
	*dio_b &= 0xF0;
	*dio_b |= _dio_b;
 
  printk("<1>Columnas= 0x%x \nFilas= 0x%x \n", _dio_da, _dio_b);

  return 1;
}

struct file_operations reg_fops = {
        read: reg_read,
        write: reg_write,
        open: reg_open,
        release: reg_release
};

int my_init(void){
  int result;

  printk("<1>Good LEDs!\n");
  result = register_chrdev(LEDS_MAJOR_NUMBER, "leds", &reg_fops);
  if(result<0){
    printk("<1>Fail major number %d\n", LEDS_MAJOR_NUMBER);
    return result;
  }
  
  //check_region(REG_ADDR, 1);
  printk("<1>Register!!!\n");
  return 0;
}

void my_end(void) {
  //Free major number
  unregister_chrdev(LEDS_MAJOR_NUMBER, "leds");
        
  //Unlock access to register
  //release_region(REG_ADDR, 1);
  printk("<1>Bye by leds");
}

module_init(my_init);
module_exit(my_end);
