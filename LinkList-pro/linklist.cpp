#include<stdlib.h>
#include<stdio.h>

//定义函数结果状态
#define FALSE 0
#define TRUE 1
#define ERROR 0
#define OK 1
#define OVERFLOW -1

typedef int Status;
typedef int ElemType;

typedef struct LNode {
    ElemType data;
    struct LNode * next;
}LNode, *Linklist;

Status CreateList_Linklist(Linklist &L){
    //逆位序输入n个元素的值，建立带头结点的单链线性表
    L = (LNode *)malloc(sizeof(LNode));
    L->next = NULL;
    int n;
    printf("请输入单链表初始长度：");
    scanf("%d", &n);
    printf("请逆序输入各个数据：");
    for(int i = n ;i>0;--i){
        Linklist p = (LNode *) malloc(sizeof(LNode));
        scanf("%d", &p->data);
        p->next = L->next;
        L->next = p;
    }
    return OK;
}

//非随机存取
Status GetElem_LinkList(Linklist L,int i,ElemType &e){
    //L为带头结点的头指针
    Linklist p = L->next;
    int j = 1;
    while(p&&j<i){
        p = p->next;
        ++j;
    }
    if(!p||j>i)
        return ERROR;
    e = p->data;
    return OK;
}

//第i个位置前插入结点
Status ListInsert(Linklist &L,int i,ElemType e){
    Linklist p = L;
    int j = 1;
    while(p&&j<i){      //寻找第i-1个结点
        p = p->next;
        ++j;
    }
    if(!p||j>i)
        return ERROR;
    Linklist q = (LNode *)malloc(sizeof(LNode));
    q->data = e;
    q->next = p->next;
    p->next = q;
    return OK;
}

//删除第i个元素
Status ListDelete(Linklist &L,int i,ElemType &e){
    Linklist p = L;
    int j = 1;
    while(p&&j<i){      //寻找第i-1个结点
        p = p->next;
        ++j;
    }
    if(!p||j>i)
        return ERROR;
    Linklist q = p->next;
    e = q->data;
    p->next = q->next;
    free(q);
    return OK;
}

//就地逆置
Status Reverse_Linklist(Linklist &L){
    Linklist p = L->next;
    L->next = NULL;
    Linklist q;
    while(p){
        q = p;
        p = p->next;
        //头插法
        q->next = L->next;
        L->next = q;
    }
}

//单链表遍历
Status showList_LinkList(Linklist &L){
    for(Linklist p = L->next;p!=NULL;p=p->next){
        printf("%d\t",p->data);
    }
    printf("\n");
}

int main(){
    Linklist L;
    CreateList_Linklist(L);
    showList_LinkList(L);
    Reverse_Linklist(L);
    ElemType e;
    ListDelete(L,1,e);
    showList_LinkList(L);
    ListInsert(L,2,e);
    showList_LinkList(L);
    system("pause");
    return 0;
}