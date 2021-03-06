//------------------------------------------------------------------------------
// Tutorial del driver del ADC del microcontrolador ARM920T.
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

#define ADC_PAGE 0x8090000
#define SYS_PAGE 0x8093000

#define SYS_SW_LOCK 0xC0   //para desbloquear registros del sistema
#define ADC_CLK_DIV 0x90   //para el reloj del ADC
#define DEVICE_CFG 0x80    //configurar dispositivos

#define ADC_RESULT 0x08   // lectura
#define ADC_SWITCH 0x18  //selecciona entrada
#define ADC_SW_LOCK 0x20  //para desbloquear registros ADC

#define FONDO_ESCALA 0xFFF
#define V_MAX 3.3


//#define ADC_INT_EN 0x80900024  // para activar las interrupciones procedentes del adc

#define ADC_MAJOR_NUMBER 70
MODULE_LICENSE("GPL");
volatile char *adc_page;
volatile char *sys_page;

char *kbuf;
//------------------------------------------------------
// int reg_open(struct inode *inode, struct file *filp)
//
// Descripción:
// 	Función para abrir e inicializar	
//	 
//------------------------------------------------------
int 
reg_open(struct inode *inode, struct file *filp)
{
	unsigned long val;	
	MOD_INC_USE_COUNT;  //para "decir" que lo estoy usando
	printk("<1>Opening adc...\n");
	
//comprobar disponibilidad de memoria
/**
 	if(check_mem_region(SYS_SW_LOCK, 4)) {
               printk("DUMB: espacio de memoria en uso: SYS_SW_LOCK\n");
               return -EBUSY;
       }
	printk ("hola hola hola hola");
	

       if(check_mem_region(ADC_CLK_DIV, 4)) {
               printk("DUMB: espacio de memoria en uso: ADC_CLK_DIV\n");
               return -EBUSY;
       }

	printk ("hola2 hola2 hola2 hola2");
	

 	if(check_mem_region(DEVICE_CFG, 4)) {
               printk("DUMB: espacio de memoria en uso: DEVICE_CFG\n");
               return -EBUSY;
       }


       if(check_mem_region(ADC_RESULT, 4)) {
               printk("DUMB: espacio de memoria en uso: ADC_RESULT\n");
               return -EBUSY;
       }
 	if(check_mem_region(ADC_SWITCH, 4)) {
               printk("DUMB: espacio de memoria en uso: ADC_SWITCH\n");
               return -EBUSY;
       }


       if(check_mem_region(ADC_SW_LOCK, 4)) {
               printk("DUMB: espacio de memoria en uso: ADC_SW_LOCK\n");
               return -EBUSY;
       }
**/

	if(check_mem_region(SYS_PAGE, 1024)) {
               printk("DUMB: espacio de memoria en uso: SYS_PAGE\n");
               return -EBUSY;
       }
	

       if(check_mem_region(ADC_PAGE, 1024)) {
               printk("DUMB: espacio de memoria en uso: ADC_PAGE\n");
               return -EBUSY;
       }	
	//Tomar memoria

	 /*request_mem_region(SYS_SW_LOCK, 4, "sys_sw_lock");
	 sys_sw_lock = __ioremap(SYS_SW_LOCK, 4, 0);

	 request_mem_region(ADC_CLK_DIV, 4, "adc_clk_div");
	 adc_clk_div = __ioremap(ADC_CLK_DIV, 4, 0);

	 request_mem_region(DEVICE_CFG, 4, "device_cfg");
	 device_cfg = __ioremap(DEVICE_CFG, 4, 0);

	 request_mem_region(ADC_RESULT, 4, "adc_result");
	 adc_result = __ioremap(ADC_RESULT, 4, 0);

	 request_mem_region(ADC_SWITCH, 4, "adc_switch");
	 adc_switch = __ioremap(ADC_SWITCH, 4, 0);

	 request_mem_region(ADC_SW_LOCK, 4, "adc_sw_lock");
	 adc_sw_lock = __ioremap(ADC_SW_LOCK, 4, 0);*/
	
	request_mem_region(SYS_PAGE, 1024, "sys_page");
	 sys_page = __ioremap(SYS_PAGE, 1024, 0);

	request_mem_region(ADC_PAGE, 1024, "adc_page");
	 adc_page = __ioremap(ADC_PAGE, 1024, 0);
	

	 /*printk("dumb: sys_sw_lock remap = %p\n", sys_sw_lock);
	 printk("dumb: adc_clk_div remap = %p\n", adc_clk_div);
	 printk("dumb: device_cfg remap = %p\n", device_cfg);
	 printk("dumb: adc_result remap = %p\n", adc_result);
	 printk("dumb: adc_switch remap = %p\n", adc_switch);
	 printk("dumb: adc_sw_lock remap = %p\n", adc_sw_lock);
	*/
	printk("dumb: sys_page remap = %p\n", sys_page);
	printk("dumb: adc_page remap = %p\n", adc_page);

	//Configura registros
	//val = *adc_clk_div;
	//*adc_sw_lock = 0xAA;
	val = *(sys_page + ADC_CLK_DIV);	
	*(sys_page + SYS_SW_LOCK) = 0xAA;	
	*(sys_page + ADC_CLK_DIV)= val | 0x80000000;
	//*sys_sw_lock = 0x000000AA;
	//*device_cfg = 0x08000D00;// <---da error (Pag.91 manual EP...)
	val = *(sys_page + DEVICE_CFG);
	*(sys_page + SYS_SW_LOCK) = 0xAA;
	*(sys_page + DEVICE_CFG)= val | 0x20000;//mascara para activar ADCEN	
	//*sys_sw_lock = 0xAA;
	//*device_cfg = val | 0x20000;
	val = *(sys_page +DEVICE_CFG);
	*(sys_page + SYS_SW_LOCK) = 0xAA;
	*(sys_page +DEVICE_CFG)= val & ~0x04;//Mascara para poner a "0" ADCPD
	
	//*sys_sw_lock = 0x000000AA;
	//*device_cfg &= 0xFFFFFFFB;
	val = *(adc_page + ADC_SWITCH);
	*(adc_page + ADC_SW_LOCK) = 0xAA;
	*(adc_page + ADC_SWITCH)= 0x0608;
	//*adc_sw_lock = 0x000000AA;
	//*adc_switch = 0x00000608;

/**
	//*((volatile unsigned int *)(SYS_SW_LOCK)) = 0xAA;   //desbloqueo software
	*((volatile unsigned int *)(ADC_SW_LOCK)) = 0xAA;
	//*((volatile unsigned int *)(ADC_CLK_DIV)) = 0x80000000; //reloj dividido por 16
	*((volatile unsigned int *)(ADC_CLK_DIV)) |= 0x80000000 ;
	*((volatile unsigned int *)(SYS_SW_LOCK)) = 0xAA;
	//*((volatile unsigned int *)(DEVICE_CFG)) = 0x00020000; //activar ADC	
	*((volatile unsigned int *)(DEVICE_CFG)) | 0x00020000; //ADCEN a "1"
	*((volatile unsigned int *)(SYS_SW_LOCK)) = 0xAA;
	*((volatile unsigned int *)(DEVICE_CFG)) & 0xFFFFFFFB; //ADCPD a "0"
	*((volatile unsigned int *)(ADC_SW_LOCK)) = 0xAA;  
	*((volatile unsigned int *)(ADC_SWITCH)) = 0x00000608; //ADC0 pin 27
	//*((volatile unsigned int *)(ADC_INT_EN)) = 0x00000000;     //desactivar interrupciones
**/
	printk("<1>adc init done\n");
  
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
	release_mem_region(SYS_PAGE, 1024);
	release_mem_region(ADC_PAGE, 1024);
	printk("<1>Closing adc\n");
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


/*
   char cero;
   char uno;
   int i=5;
   unsigned long lectura;
//while(i){
//  i--;
	//while((*(adc_page+ADC_RESULT) & 0x80000000)== 0x80000000){
   while(*(adc_page+ADC_RESULT+3) < 0x80){
   }
   //lectura= *(adc_page+ADC_RESULT);
   //lectura= *((volatile unsigned int *)(adc_page+ADC_RESULT));
   lectura= *((volatile unsigned int *)(adc_page+ADC_RESULT));
   //printk("<1> adc_page+ADC_RESULT= 0x%x", adc_page+ADC_RESULT);
   //Divide en 2 "char"
   //*buf=(lectura & 0x00FF);
   //printk("<1> OK");
   //*(buf+1)=((lectura>>8)&0x000F);
   lectura = lectura & 0xFFFF;
   //cero= *(adc_page + ADC_RESULT);
   //uno= *(adc_page + ADC_RESULT + 1) & 0x0F;
   cero=lectura; //Hacer los cambios necesarios para devolver dos char por cada lectura XXXaraujo
   uno=lectura;	
   buf= (char*)lectura;
   //*(buf +1)=uno;
	
   //printk("\n lectura=0x%x, uno=0x%x, cero=0x%x",lectura,uno,cero);
   */
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

	printk("<1>ADC!\n");
	result = register_chrdev(ADC_MAJOR_NUMBER, "adc", &reg_fops);
	if(result<0){
		printk("<1>Fail major number %d\n", ADC_MAJOR_NUMBER);
		return result;
	}
  
  //check_region(REG_ADDR, 1);
	printk("<1>ADC registrado!\n");
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
	unregister_chrdev(ADC_MAJOR_NUMBER, "adc");
        
  //Unlock access to register
  //release_region(REG_ADDR, 1);
	printk("<1>Cierro ADC!");
}
int lee_adc(void){

   	unsigned int lectura;

	//double tension;

	while(*(adc_page+ADC_RESULT+3) < 0x80){
	}
	lectura= *((volatile unsigned int *)(adc_page+ADC_RESULT));
	lectura = lectura & 0xFFF;
	//printk("\n<1> lectura=0x%x",lectura);


	//tension = V_MAX * ((double)lectura/FONDO_ESCALA);
	//printk("<1> Tension = %f", tension);


	return lectura;
	
}

EXPORT_SYMBOL(lee_adc);  //para que pueda llamarle desde inter
module_init(my_init);
module_exit(my_end);
