#include <stdio.h>
#include <stdlib.h>

//定义函数结果状态
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
    BiTree* top;           //栈构造之前和销毁之后，均为NULL
    BiTree* base;
    int stacksize;       //当前已分配的存储空间
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
//清空栈
Status ClearStack(SeqStack *s)
{
    s->top = s->base;//栈顶指针指向栈底
    return OK;
}
//判断栈是否为空
Status IsEmpty(SeqStack* s)
{
    if (s->top == s->base) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}
//判断栈是否为满
Status IsFull(SeqStack* s)
{
    if (s->top == s->base+STACK_SIZE - 1) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}

//入栈
Status Push(SeqStack* s, BiTree value)
{
    if (IsFull(s) == TRUE) {
        s->base = (BiTree*)malloc(sizeof(BiTree) * (STACK_SIZE + EXTRASIZE));
    }
    *s->top = value;
    s->top++;
    return TRUE;
}
//出栈
Status Pop(SeqStack* s, BiTree &value)
{
    if (IsEmpty(s) == TRUE) {
        return FALSE;
    }
    s->top--;
    value = *s->top;
    return OK;
}
//取栈顶元素
BiTree GetTop(SeqStack* s)
{
    BiTree value;
    if (IsEmpty(s) == TRUE) {
        return FALSE;
    }
    value = *(s->top-1);
    return value;
}
//创建二叉树（递归方法）
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
//访问函数（将其输出）
void visit(char ch)
{
    printf("%c",ch);
}

//前序遍历（递归方法）
void PreorderTraverse(BiTree T)
{
    if(T!=NULL)
    {
        visit(T->data);
        PreorderTraverse(T->lchild);
        PreorderTraverse(T->rchild);
    }
}

//中序遍历（递归方法）
Status InorderTraverse(BiTree T)
{
    if(T!=NULL)
    {
        InorderTraverse(T->lchild);
        visit(T->data);
        InorderTraverse(T->rchild);
    }
}

//后序遍历（递归方法）
Status PostorderTraverse(BiTree T)
{
    if(T!=NULL)
    {
        PostorderTraverse(T->lchild);
        PostorderTraverse(T->rchild);
        visit(T->data);
    }
}

//前序遍历（非递归方法）
void Preorder(BiTree T)
{
    SeqStack *s = InitStack();
    while(T!=NULL||!IsEmpty(s))
    {
        while(T!=NULL)
        {
            //访问结点后入栈，一路向左
            visit(T->data);
            BiTree t = T;
            Push(s,t);
            T = T->lchild;
        }

        {
            //访问至最左端，取栈顶元素出栈，访问其右孩子
            Pop(s,T);
            T = T->rchild;
        }
    }
}

//中序遍历（非递归方法）
void Inorder(BiTree T)
{
    SeqStack *s = InitStack();
    while(T!=NULL||!IsEmpty(s))
    {
        if(T)
        {
            //不访问节点就入栈，一路向左
            BiTree t = T;
            Push(s,t);
            T = T->lchild;
        }
        else
        {
            //至最左端，取栈顶元素出栈，访问该结点，再访问右孩子
            Pop(s,T);
            visit(T->data);
            T = T->rchild;
        }
    }
}

//后序遍历（非递归方法）
void PostOrder(BiTree T)
{
    BiTNode *p = T;
    BiTNode *temp = NULL;
    SeqStack *s = InitStack();
    while(p||!IsEmpty(s))
    {
        if(p)
        {
            //不访问结点就入栈，一路向左
            Push(s,p);
            p = p->lchild;
        }
        else
        {
            p = GetTop(s);

            if((p->rchild)&&(p->rchild != temp))    //右孩子存在且未被访问
                p = p->rchild;
            else
            {
                //取栈顶元素且出栈
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

//计算叶结点的数量
Status CountLeaves(BiTree T,int &leaves)
{
    if(T)
    {
        //既无左孩子，也无孩子
        if((!T->lchild)&&(!T->rchild))
            leaves++;
        CountLeaves(T->lchild,leaves);
        CountLeaves(T->rchild,leaves);
    }
    return OK;
}

//计算二叉树的深度
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

//判断控制端用户想使用的遍历方法
Status inputJudge(BiTree T)
{
    printf("请选择遍历方式：\n1.前序递归遍历；\n2.前序非递归遍历；\n3.中序递归遍历\n4.中序非递归遍历\n5.后序递归遍历\n6.后序非递归遍历\n请输入遍历方式：");
    int num;
    scanf("%d",&num);
    while(num!=0)
    {
        switch(num)
        {
            case 1:
                printf("递归遍历：");
                PreorderTraverse(T);
                break;

            case 2:
                printf("非递归遍历：");
                Preorder(T);
                break;
            case 3:
                printf("递归遍历：");
                InorderTraverse(T);
                break;
            case 4:
                printf("非递归遍历：");
                Inorder(T);
                break;
            case 5:
                printf("递归遍历：");
                PostorderTraverse(T);
                break;
            case 6:
                printf("非递归遍历：");
                PostOrder(T);
                break;

            //default:printf("输入错误");break;
        }
        printf("\n");
        printf("请输入遍历方式:");
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
    printf("请按照前序依次输入字符序列（‘#’代表空结点）:\n");
    CreateBiTree(T);
    inputJudge(T);
    int leaves = 0;
    CountLeaves(T,leaves);
    printf("该二叉树叶结点共有%d个，\n该二叉树深度为%d。\n",leaves,Depth(T));


    system("pause");
    return 0;
}
