/*
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

//�������״̬����
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFOLW -1

typedef int Status;

//����ڵ�����
typedef struct LNode
{
    int n;
    int password;
    struct LNode *next;   //����ָ��ڵ��ָ������
}LNode,*CirList;          //�����������ͣ�����һ��Ϊָ������

//����һ��ѭ��������ͷ�ڵ㣬�����а�˳��������������
CirList CreateList_Cir(int num)
{
    LNode *L;
    L = (LNode *)malloc(sizeof(LNode));
    if (L == NULL)
        printf("�����ڴ�ռ�ʧ��\n");
    int i = 1;
    int pw ;
    printf("�������%d��password:",i);
    scanf("%d",&pw);
    //��L��n��password��ֵ
    L -> n = i;
    L -> password = pw;
    L -> next = L;
    LNode *p = NULL;
    for (i = 2 ; i<=num;i++)
    {
        p = (LNode *)malloc(sizeof(LNode));
        if(p)
        {
            printf("�������%d��password:",i);
            scanf("%d",&pw);
            p -> n = i;
            p -> password = pw;
            //��p���ӵ�L�ĺ��棬��L��p�ƶ�
            p -> next = L -> next;
            L -> next = p;
            //���L=p��L������ָ�ص�һ���ڵ�
            L = p;
        }
    }
    //free(p);
    return L;
}

//ģ����е�ȫ����
Status ListDelete_CIr(CirList L,int number,int pw)
{
    if(number<1)
        return ERROR;
    printf("���е��ˣ�\n");
    LNode *q ;
    while(L->next != L)
    {
        //ֱ��������������ѭ��
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
        printf("��%d���˳���\n",j);
        L -> next = q -> next;
        pw = q -> password;
        free(q);
        q = NULL;
        i = 1;
        --number;
    }
    //������һ��δ���е���
    printf("��%d���˳���\n",L->n);
    return OK;
}//ListDelete_Cir

int main()
{
    int number;
    //m Ϊ��ʼ����ֵ
    int m = 20;
    printf("������������");
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
