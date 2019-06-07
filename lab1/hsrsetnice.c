# include <unistd.h>
# include <sys/syscall.h>
# include <stdio.h>
# define _SYSCALL_MYSETNICE_ 335
# define EFALUT 14

int main()
{
        int pid,flag,nicevalue;
        int pprio,pnice,nprio,nnice; // pprio,pnice之前的nprio,nnice修改之后的
        int result; //记录返回值

        printf("输入pid,flag,nicevalue\n");
        scanf("%d%d%d",&pid,&flag,&nicevalue);
        //先确保flag值是否有效
        result=syscall(335, pid,0,nicevalue, &pprio,&pnice);
        if(result ==EFALUT)
        {
                printf("ERROR!请确定输入的flag值\n");
                return 1;
        }
        if(flag==1)
        {
                syscall(335,pid,1,nicevalue,&nprio,&nnice);
                printf("之前的prio为[%d],nice值为[%d]\n",pprio,pnice);
                printf("现在的prio为[%d],nice值为[%d]\n",nprio,nnice);
        }
        else if (flag ==0)
        {
                printf("并未修改，将输出原先值,现在的prio为[%d],nice值为[%d]\n",pprio,pnice);
        }
        return 0;
}
