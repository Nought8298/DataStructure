/*
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

//函数结果状态代码
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFOLW -1

typedef int Status;

//定义节点类型
typedef struct LNode
{
    int n;
    int password;
    struct LNode *next;   //定义指向节点的指针类型
}LNode,*CirList;          //定义两个类型，其中一个为指针类型

//构造一个循环链表，无头节点，在其中按顺序依次输入密码
CirList CreateList_Cir(int num)
{
    LNode *L;
    L = (LNode *)malloc(sizeof(LNode));
    if (L == NULL)
        printf("申请内存空间失败\n");
    int i = 1;
    int pw ;
    printf("请输入第%d个password:",i);
    scanf("%d",&pw);
    //将L的n和password赋值
    L -> n = i;
    L -> password = pw;
    L -> next = L;
    LNode *p = NULL;
    for (i = 2 ; i<=num;i++)
    {
        p = (LNode *)malloc(sizeof(LNode));
        if(p)
        {
            printf("请输入第%d个password:",i);
            scanf("%d",&pw);
            p -> n = i;
            p -> password = pw;
            //将p连接到L的后面，且L随p移动
            p -> next = L -> next;
            L -> next = p;
            //最后L=p，L又重新指回第一个节点
            L = p;
        }
    }
    //free(p);
    return L;
}

//模拟出列的全过程
Status ListDelete_CIr(CirList L,int number,int pw)
{
    if(number<1)
        return ERROR;
    printf("出列的人：\n");
    LNode *q ;
    while(L->next != L)
    {
        //直接跳过几个整的循环
        pw = pw % number;
        int i;
        if(pw == 1)
        {
            for(i = 1;i < number - 1;i++)
                L = L -> next;
        }
        else
        {
            for (i = 1 ; i < pw;i++)
                L = L -> next;
        }
        q = L -> next;
        int j = q->n;
        printf("第%d个人出列\n",j);
        L -> next = q -> next;
        pw = q -> password;
        free(q);
        q = NULL;
        i = 1;
        --number;
    }
    //输出最后一个未出列的人
    printf("第%d个人出列\n",L->n);
    return OK;
}//ListDelete_Cir

int main()
{
    int number;
    //m 为初始密码值
    int m = 20;
    printf("请输入人数：");
    scanf("%d",&number);
    CirList cl = CreateList_Cir(number);
    ListDelete_CIr(cl,number,m);
    return 0;
}
*/

#include<stdio.h>
#include<stdlib.h>

int main()
{
    for(int i = 0; i < 5;i++)
        printf("%d ",i);
    printf("\n");
    for(jint j = 0; j < 5;++j)
        printf("%d ",j);
}
