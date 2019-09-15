/*
--------------------------------
Developed by                    |
user: Dennis Masaya             |
id: 201503413                   |
e-mail: dennismasaya@gmail.com  |
--------------------------------
This module demonstrates on how to build a module that displays
information about processes creating a file in the /proc directory.
*/

/*  LIBRARY IMPORTS  */
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <linux/module.h>
#include <linux/seq_file.h>
#include <linux/proc_fs.h>

/*  MODULE INFO  */
MODULE_AUTHOR("Dennis Masaya");
MODULE_DESCRIPTION("This module demonstrates on how to build a module that displays information about processes creating a file in the /proc directory.");
MODULE_LICENSE("GPL");

static struct proc_dir_entry *ent;

static int proc_show(struct seq_file *m, void *v) {
    int cont = 0;
    struct task_struct *task;
    seq_printf(m,"%10d %-30s %-30s\n","PID","NAME","STATE");

    for_each_process(task){
      if (task->state == TASK_RUNNING) {
        seq_printf(m,"%10d %-30s %-30s\n",task->pid,task->comm,"TASK_RUNNING");
      }
      else if (task->state == TASK_INTERRUPTIBLE) {
        seq_printf(m,"%10d %-30s %-30s\n",task->pid,task->comm,"TASK_INTERRUPTIBLE");
      }
      else if (task->state == TASK_UNINTERRUPTIBLE) {
        seq_printf(m,"%10d %-30s %-30s\n",task->pid,task->comm,"TASK_UNINTERRUPTIBLE");
      }
      else if (task->state == __TASK_STOPPED) {
        seq_printf(m,"%10d %-30s %-30s\n",task->pid,task->comm,"TASK_STOPPED");
      }
      else if (task->state == __TASK_TRACED) {
        seq_printf(m,"%10d %-30s %-30s\n",task->pid,task->comm,"TASK_TRACED");
      }
      else if (task->exit_state == EXIT_DEAD) {
        seq_printf(m,"%10d %-30s %-30s\n",task->pid,task->comm,"EXIT_DEAD");
      }
      else if (task->exit_state == EXIT_ZOMBIE) {
        seq_printf(m,"%10d %-30s %-30s\n",task->pid,task->comm,"EXIT_ZOMBIE");
      }
      else if (task->state == TASK_DEAD) {
        seq_printf(m,"%10d %-30s %-30s\n",task->pid,task->comm,"TASK_DEAD");
      }
      else if (task->state == TASK_NOLOAD) {
        seq_printf(m,"%10d %-30s %-30s\n",task->pid,task->comm,"TASK_NOLOAD");
      }
      else if (task->state == TASK_WAKEKILL) {
        seq_printf(m,"%10d %-30s %-30s\n",task->pid,task->comm,"TASK_WAKEKILL");
      }
      else if (task->state == TASK_WAKING) {
        seq_printf(m,"%10d %-30s %-30s\n",task->pid,task->comm,"TASK_WAKING");
      }



      cont = cont + 1;
    }

    return 0;
}

static void __exit end(void)
{
  proc_remove(ent);
  printk(KERN_INFO "CURSO: Sistemas Operativos 1 \n");
}

static int proc_open(struct inode *inode, struct file *file) {
    return single_open(file, proc_show, NULL);
}

static const struct file_operations proc_fops = {
    .open = proc_open,
    .read = seq_read,
    .llseek = seq_lseek,
    .release = single_release,
};

static int __init start(void) 
{
    printk(KERN_INFO "CARNET: 201503413 \n");
    ent = proc_create("cpu_201503413", 0, NULL, &proc_fops);
    return 0;
}


module_init(start);
module_exit(end);
