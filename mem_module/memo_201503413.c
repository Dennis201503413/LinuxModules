/*
--------------------------------
Developed by                    |
user: Dennis Masaya             |
id: 201503413                   |
e-mail: dennismasaya@gmail.com  |
--------------------------------
This module demonstrates on how to build a module that displays
information about memory creating a file in the /proc directory.
*/

/*  LIBRARY IMPORTS  */
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/mm.h>
#include <linux/hugetlb.h>
#include <linux/mman.h>
#include <linux/mmzone.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/quicklist.h>
#include <linux/seq_file.h>
#include <linux/swap.h>
#include <linux/vmstat.h>
#include <linux/atomic.h>
#include <linux/vmalloc.h>
#include <asm/page.h>
#include <asm/pgtable.h>
#include <asm/uaccess.h>
#include <linux/sched.h>
#include <linux/cpumask.h>
#include <linux/interrupt.h>
#include <linux/kernel_stat.h>
#include <linux/slab.h>
#include <linux/time.h>
#include <linux/irqnr.h>
#include <linux/tick.h>
#include <asm/apic.h>
#include <linux/smp.h>
#include <linux/timex.h>
#include <linux/string.h>
#include <linux/cpufreq.h>
#include <linux/delay.h>

/*  MODULE INFO  */
MODULE_AUTHOR("Dennis Masaya");
MODULE_DESCRIPTION("This module demonstrates on how to build a module that displays information about memory creating a file in the /proc directory.");
MODULE_LICENSE("GPL");

struct sysinfo i;
static struct proc_dir_entry *ent;

static int mem_info(struct seq_file *m, void *v)
{
  // Se accede a la estructura sysinfo y se cargan sus atributos
  si_meminfo(&i);

  #define Ajuste(x) ((x) << (PAGE_SHIFT - 10))
      seq_printf(m,"Total memory: %d \n", Ajuste(i.totalram));
      seq_printf(m,"Free memory: %d \n", Ajuste(i.freeram));
      seq_printf(m,"Used memory percentage: %d%% \n", (100 - Ajuste(i.freeram)*100/Ajuste(i.totalram)));
  #undef Ajuste
      return 0;

}

static void __exit end(void)
{
  proc_remove(ent);
  printk(KERN_INFO "CURSO: Sistemas Operativos 1 \n");
}

static int mem_info_open(struct inode *inode, struct file *file)
{
    return single_open(file, mem_info, NULL);
}

static const struct file_operations mem_info_fops = {
    .open		= mem_info_open,
    .read		= seq_read,
    .llseek		= seq_lseek,
    .release	= single_release,
};


static int __init start(void)
{
    printk(KERN_INFO "CARNET: 201503413 \n");
    ent = proc_create("memo_201503413", 0, NULL, &mem_info_fops);
    return 0;
}


module_init(start);
module_exit(end);
