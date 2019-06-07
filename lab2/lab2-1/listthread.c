# include <linux/init.h>
# include <linux/module.h>
# include <linux/kernel.h>
# include <linux/sched/signal.h>

MODULE_LICENSE("GPL");
static int listthreads_init(void)
{

        struct task_struct *p;
        printk("%-20s%-6s%-6s%-6s%-6s","NAME","PID","STATE","PRIO","PPID");
        printk("我是分割符-----------------------------------------");

        for_each_process(p)
        {
                if(p->mm==NULL)
                {
                        printk("%20s%6lu%6ld%6ld%6lu",p->comm,p->pid,p->state,p->prio,p->parent->pid);
                }
        }
        return 0;
}

static void listthreads_exit(void)
{
        printk("[listthreads] Module unistalled");
}

module_init(listthreads_init);
module_exit(listthreads_exit);
