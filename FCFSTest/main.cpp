#include<stdio.h>
#include <malloc.h>
#include <string.h>
/*
 *  Created by rxl on 16-10-25.
 *
 *  先来先服务调度算法（FCFS）
 *   1,按照FCFS的规则 用单链表的思想
 *     通过指针的指向来判断 后面是否还有继续要执行的进程
 *   2,网上一个错误的例子改编过来的  用到连表时 注意指针的指向问题
 */

//首先定义一些所需变量

//处理过程中 需要的时间
int time;
char strPID[10];
//输入进程数的变量
int num;
//定义操作进程队列所需要的指针  也可以分开定义 方便使用
struct PCB  *start,*startHead,*temp,*newNode;

/*
 * 在此算法中 无需人为设置系统中段时间 中段时间由cpu自行处理 个人见解
 */


//结构体-->具体声明一些所需变量,方便使用
//typedef-->用来给某一个变量起一个别名 见名思意
typedef struct PCB
{
    //进程ID   在此,我默认最多10个 方便测试
    char PID[10];
    //进程到达时间
    int PRTime;
    //进程需要时间
    int needTime;
    //进程的状态 start running end
    char state;
    //队列指针-->用来对进程队列排序
    struct PCB* next;
}PCB;


//main函数  即整个工程文件的入口函数 系统默认为期分配一个进程 来率先启动程序
int main()
{
    printf("请输入当前系统有多少个进程:");
    scanf("%d",&num);
    //首先为进程开辟一块内存 注意是堆内存 sizeof关键字使我们没必要考虑具体内存中分布情况
    start=(PCB*)malloc(sizeof(PCB));
    //进程首地址 (PCB*)-->强制类型转换为(PCB*)
    startHead=(PCB*)malloc(sizeof(PCB));
    //默认为空
    start=NULL;
    startHead=start;
    //temp是一个中间变量
    temp=(PCB*)malloc(sizeof(PCB));
    temp=startHead;
    //循环创建进程 并在堆内存中动态开辟空间
    for (int i=0;i<num;i++)
    {
        startHead=start;
        temp=startHead;
        newNode=(PCB*)malloc(sizeof(PCB));
        printf("======================");
        printf("请输入该进程ID:");
        scanf("%s",strPID);
        strcpy(newNode->PID,strPID);
        printf("======================");
        printf("请输入该进程到达时间:");
        scanf("%d",&time);
        newNode->PRTime=time;
        printf("======================");
        printf("请输入该进程需要时间:");
        scanf("%d",&time);
        //此处操作为进程链表操作  数据结构
        newNode->needTime=time;
        //此处R为开始的符号 可以随便取 不影响程序运行
        newNode->state='R';
        newNode->next=NULL;

        /*
         * 在这里 输入的进程数 我分三种情况判断 分别为0时,1时,*时
         *
         * 由于进程调度强调的一点是并发情况下
         * 也就是说我只有在进程数至少有两个的情况下才去判断采用何种调度算法
         * 故:0和1的情况单独讨论  多个进程的情况使用FCFS算法思想
         */


        //如果我输入的进程数位0 让头指向尾 类似于数据结构中  头指针==尾指针 链表为空
        if(i==0)
        {
            start=newNode;
            startHead=start;
        }
        else if (i==1)
        {
            if(start->PRTime<=newNode->PRTime)
            {
                startHead->next=newNode;
            }
            else
            {
                newNode->next=startHead;
                start=newNode;
            }
        }
        else
        {
            for(startHead=start;startHead!=NULL;startHead=startHead->next)
            {
                temp=startHead;
                if(start->PRTime>newNode->PRTime)
                {
                    newNode->next=startHead;
                    start=newNode;
                    break;
                }
                 //注意后面两个的顺序，如果顺序调换会发生错误
                else if(startHead->PRTime<=newNode->PRTime &&startHead->next!=NULL&& startHead->next->PRTime>newNode->PRTime)
                {
                    newNode->next=startHead->next;
                    temp->next=newNode;
                    break;
                }

                else if(startHead->next==NULL)
                {
                    temp->next=newNode;
                    break;
                }
            }
        }

    }

    //进程开始运行的时间 默认为0
    int startTime=0;
    startHead=start;
    for(int i=0;startHead!=NULL;i++)
    {
        if (startHead->PRTime<=i&&startHead->state=='R')
        {
            startTime=i;//记录开始时间i为astartTime
            startHead->state='E';//进程为执行状态
            printf("在%d时刻：",i);
            printf("进程%s开始运行\n",startHead->PID);
        }
        else if (i-startTime<startHead->needTime&&i-startTime>0&&startHead->state=='E')
        {
            printf("在%d时刻：",i);
            printf("进程%s正在运行\n",startHead->PID);
        }
        else if (i-startTime==startHead->needTime&&startHead->state=='E')
        {
            startHead->state='F';
            printf("在%d时刻：",i);
            printf("进程%s结束运行\n",startHead->PID);
            startHead=startHead->next;
            //这个很重要，主要在结束时刻是否有进程执行
            i--;
        }

        if(startHead==NULL)
        {
            printf("进程调度结束");
        }
    }
}