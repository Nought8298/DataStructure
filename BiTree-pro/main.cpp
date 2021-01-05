#include <stdio.h>
#include <stdlib.h>

//���庯�����״̬
#define FALSE 0
#define TRUE 1
#define ERROR 0
#define OK 1
#define OVERFLOW -1

typedef int Status;
#define STACK_SIZE 20
#define EXTRASIZE 5
#define MAX_TREE_SIZE 100
typedef struct BiTNode
{
    char data;
    struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

typedef struct
{
    BiTree* top;           //ջ����֮ǰ������֮�󣬾�ΪNULL
    BiTree* base;
    int stacksize;       //��ǰ�ѷ���Ĵ洢�ռ�
} SeqStack;

SeqStack* InitStack()
{
    SeqStack* s=(SeqStack*)malloc(sizeof(SeqStack));
    s->base = (BiTree*)malloc(sizeof(BiTNode) * STACK_SIZE);
    if(!s->base)
        exit(OVERFLOW);
    s->top = s->base;
    s->stacksize = STACK_SIZE;
    return s;
}
//���ջ
Status ClearStack(SeqStack *s)
{
    s->top = s->base;//ջ��ָ��ָ��ջ��
    return OK;
}
//�ж�ջ�Ƿ�Ϊ��
Status IsEmpty(SeqStack* s)
{
    if (s->top == s->base) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}
//�ж�ջ�Ƿ�Ϊ��
Status IsFull(SeqStack* s)
{
    if (s->top == s->base+STACK_SIZE - 1) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}

//��ջ
Status Push(SeqStack* s, BiTree value)
{
    if (IsFull(s) == TRUE) {
        s->base = (BiTree*)malloc(sizeof(BiTree) * (STACK_SIZE + EXTRASIZE));
    }
    *s->top = value;
    s->top++;
    return TRUE;
}
//��ջ
Status Pop(SeqStack* s, BiTree &value)
{
    if (IsEmpty(s) == TRUE) {
        return FALSE;
    }
    s->top--;
    value = *s->top;
    return OK;
}
//ȡջ��Ԫ��
BiTree GetTop(SeqStack* s)
{
    BiTree value;
    if (IsEmpty(s) == TRUE) {
        return FALSE;
    }
    value = *(s->top-1);
    return value;
}
//�������������ݹ鷽����
Status CreateBiTree(BiTree &T)
{
    char ch = getchar();
    if(ch=='#')
        T = NULL;
    else
    {
        T = (BiTNode *)malloc(sizeof(BiTNode));
        if(!T)
            exit(OVERFLOW);
        T->data = ch;
        CreateBiTree(T->lchild);
        CreateBiTree(T->rchild);
    }
    return OK;
}
//���ʺ��������������
void visit(char ch)
{
    printf("%c",ch);
}

//ǰ��������ݹ鷽����
void PreorderTraverse(BiTree T)
{
    if(T!=NULL)
    {
        visit(T->data);
        PreorderTraverse(T->lchild);
        PreorderTraverse(T->rchild);
    }
}

//����������ݹ鷽����
Status InorderTraverse(BiTree T)
{
    if(T!=NULL)
    {
        InorderTraverse(T->lchild);
        visit(T->data);
        InorderTraverse(T->rchild);
    }
}

//����������ݹ鷽����
Status PostorderTraverse(BiTree T)
{
    if(T!=NULL)
    {
        PostorderTraverse(T->lchild);
        PostorderTraverse(T->rchild);
        visit(T->data);
    }
}

//ǰ��������ǵݹ鷽����
void Preorder(BiTree T)
{
    SeqStack *s = InitStack();
    while(T!=NULL||!IsEmpty(s))
    {
        while(T!=NULL)
        {
            //���ʽ�����ջ��һ·����
            visit(T->data);
            BiTree t = T;
            Push(s,t);
            T = T->lchild;
        }

        {
            //����������ˣ�ȡջ��Ԫ�س�ջ���������Һ���
            Pop(s,T);
            T = T->rchild;
        }
    }
}

//����������ǵݹ鷽����
void Inorder(BiTree T)
{
    SeqStack *s = InitStack();
    while(T!=NULL||!IsEmpty(s))
    {
        if(T)
        {
            //�����ʽڵ����ջ��һ·����
            BiTree t = T;
            Push(s,t);
            T = T->lchild;
        }
        else
        {
            //������ˣ�ȡջ��Ԫ�س�ջ�����ʸý�㣬�ٷ����Һ���
            Pop(s,T);
            visit(T->data);
            T = T->rchild;
        }
    }
}

//����������ǵݹ鷽����
void PostOrder(BiTree T)
{
    BiTNode *p = T;
    BiTNode *temp = NULL;
    SeqStack *s = InitStack();
    while(p||!IsEmpty(s))
    {
        if(p)
        {
            //�����ʽ�����ջ��һ·����
            Push(s,p);
            p = p->lchild;
        }
        else
        {
            p = GetTop(s);

            if((p->rchild)&&(p->rchild != temp))    //�Һ��Ӵ�����δ������
                p = p->rchild;
            else
            {
                //ȡջ��Ԫ���ҳ�ջ
                BiTree v;
                Pop(s,v);
                free(v);
                visit(p->data);
                temp = p;
                p = NULL;
            }
        }
    }
    free(p);
    free(temp);

}

//����Ҷ��������
Status CountLeaves(BiTree T,int &leaves)
{
    if(T)
    {
        //�������ӣ�Ҳ�޺���
        if((!T->lchild)&&(!T->rchild))
            leaves++;
        CountLeaves(T->lchild,leaves);
        CountLeaves(T->rchild,leaves);
    }
    return OK;
}

//��������������
int Depth(BiTree T)
{
    if(!T)
        return 0;
    else
    {
        int ldepth = Depth(T->lchild);
        int rdepth = Depth(T->rchild);
        if(ldepth>rdepth)
            return ldepth + 1;
        else return rdepth + 1;
    }
}

//�жϿ��ƶ��û���ʹ�õı�������
Status inputJudge(BiTree T)
{
    printf("��ѡ�������ʽ��\n1.ǰ��ݹ������\n2.ǰ��ǵݹ������\n3.����ݹ����\n4.����ǵݹ����\n5.����ݹ����\n6.����ǵݹ����\n�����������ʽ��");
    int num;
    scanf("%d",&num);
    while(num!=0)
    {
        switch(num)
        {
            case 1:
                printf("�ݹ������");
                PreorderTraverse(T);
                break;

            case 2:
                printf("�ǵݹ������");
                Preorder(T);
                break;
            case 3:
                printf("�ݹ������");
                InorderTraverse(T);
                break;
            case 4:
                printf("�ǵݹ������");
                Inorder(T);
                break;
            case 5:
                printf("�ݹ������");
                PostorderTraverse(T);
                break;
            case 6:
                printf("�ǵݹ������");
                PostOrder(T);
                break;

            //default:printf("�������");break;
        }
        printf("\n");
        printf("�����������ʽ:");
        scanf("%d",&num);
    }

}

int main()
{
    BiTree T;
    /*
    PreorderTraverse(T);
    printf("\n");
    Preorder(T);
    printf("\n");
    InorderTraverse(T);
    printf("\n");
    Inorder(T);
    printf("\n");
    PostorderTraverse(T);
    printf("\n");
    */
    printf("�밴��ǰ�����������ַ����У���#������ս�㣩:\n");
    CreateBiTree(T);
    inputJudge(T);
    int leaves = 0;
    CountLeaves(T,leaves);
    printf("�ö�����Ҷ��㹲��%d����\n�ö��������Ϊ%d��\n",leaves,Depth(T));


    system("pause");
    return 0;
}
