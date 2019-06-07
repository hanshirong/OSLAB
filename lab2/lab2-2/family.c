# include <linux/init.h>
# include <linux/module.h>
# include <linux/moduleparam.h>
# include <linux/list.h>
# include <linux/sched.h>
# include <linux/kernel.h>
# include <linux/signal.h>
MODULE_LICENSE("GPL");
static int pid=1;

module_param(pid,int, 0644);

static int __init family_init(void)
{
        struct pid *rpid;
        struct task_struct *p;
        struct task_struct *pos;

        rpid=find_get_pid(pid);
        if(rpid==NULL)
        {
                printk("error,this pid is not found\n");
                return -1;
        }
        p=pid_task(rpid,PIDTYPE_PID);

        printk("%-15s%-20s%-6s%-6s\n","TYPE","NAME","PID","STATE");
        printk("我是分隔符--------------------------------------\n");


        printk("%-15s%-20s%-6ld%-6ld\n","MYSELF",p->comm,p->pid,p->state);

        printk("%-15s%-20s%-6ld%-6ld\n","father",p->real_parent->comm,p->real_parent->pid,p->real_parent->state);

        list_for_each_entry(pos,&(p->real_parent->children),sibling)
        {
                if(pos->pid == pid)
                continue;
                printk("%-15s%-20s%-6ld%-6ld\n","sibling",pos->comm,pos->pid,pos->state);
        }

        list_for_each_entry(pos,&(p->children),sibling)
        {

                printk("%-15s%-20s%-6ld%-6ld\n","mychildren",pos->comm,pos->pid,pos->state);
        }
        return 0;
}
static void __exit family_exit(void)
{
        printk("module uninstalled\n");
}
module_init(family_init);
module_exit(family_exit);
