SYSCALL_DEFINE5(mysetnice, pid_t, pid, int, flag,int, nicevalue, void __user *, prio, void __user *, nice)
{
        printk("已经成功启动mysetnice系统调用\n");
        struct pid *rpid;
        struct task_struct *task;
        int n;
        int p;
        rpid = find_get_pid(pid);
        printk("find_get_pid执行完成\n");
        task=pid_task(rpid,PIDTYPE_PID);
        printk("已经执行完pid_task，获取到了task_struct\n");
        n=task_nice(task);
        printk("获取到之前的nice值\n");
        p=task_prio(task);
        printk("获取到之前的prio\n");
        if (flag ==1)
        {
                printk("即将进行nice值的修改\n");
                set_user_nice(task,nicevalue);
                printk("nice值修改完成\n");
        }
        else if (flag != 0)
        {
                return EFAULT;
        }
        n=task_nice(task);
        printk("我已经重新获取修改的nice值了");
        p=task_prio(task);
        printk("我已经重新获取修改的prio了\n");
        copy_to_user(nice,&n,sizeof(n));
        copy_to_user(prio,&p,sizeof(p));
        printk("我已经把nice和prio的值放到了用户空间\n");
        return 0;
}
