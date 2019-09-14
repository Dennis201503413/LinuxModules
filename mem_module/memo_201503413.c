#include <linux/module.h> //needs to be included for every module
#include <linux/kernel.h> //required for macro expansion of printk
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>
#define BUFSIZE 100

MODULE_AUTHOR("Dennis Masaya");

static struct proc_dir_entry *ent;

static ssize_t mywrite(struct file *file, const char __user *ubuf, size_t count, loff_t *ppos){
  printk(KERN_DEBUG "write handler\n");
  return -1;
}

static ssize_t mywrite(struct file *file, char __user *ubuf, size_t count, loff_t *ppos){
  printk(KERN_DEBUG "read handler\n");
  return 0;
}

static struct file_operations myops =
{
  .owner = THIS_MODULE,
  .read = myread,
  .write = mywrite,
};

int init_module(void) //executed when module is loaded into the kernel
{
 printk(KERN_INFO “CARNET: 201503413 \n”);
 ent = proc_create("memo_201503413",0660,NULL,&myops)
 return 0;
}
void cleanup_module(void) //executed as the kernel module is removed from the kernel
{
  proc_remove(ent);
 printk(KERN_INFO “CURSO: Sistemas Operativos 1 \n”);
}
