#include<linux/module.h> //needs to be included for every module
#include<linux/kernel.h> //required for macro expansion of printk
int init_module(void) //executed when module is loaded into the kernel
{
 printk(KERN_INFO “CARNET: 201503413 \n”);
 return 0;
}
void cleanup_module(void) //executed as the kernel module is removed from the kernel
{
 printk(KERN_INFO “CURSO: Sistemas Operativos 1 \n”);
}
