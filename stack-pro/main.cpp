#include <stdio.h>
#include <stdlib.h>

//定义函数结果状态
#define FALSE 0
#define TRUE 1
#define ERROR 0
#define OK 1
#define OVERFLOW -1

#define STACK_SIZE 20   //定义栈初始长度
#define EXTRASIZE 10
typedef int Status;

typedef struct
{
    char* top;           //栈构造之前和销毁之后，均为NULL
    char* base;
    int stacksize;       //当前已分配的存储空间
} SeqStack;

SeqStack* InitStack()
{
    SeqStack* s=(SeqStack*)malloc(sizeof(SeqStack));
    s->base = (char*)malloc(sizeof(char) * STACK_SIZE);
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

Status IsEmpty(SeqStack* s)
{
    if (s->top == s->base) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}

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
Status Push(SeqStack* s, char value)
{
    if (IsFull(s) == TRUE) {
        s->base = (char*)malloc(sizeof(char) * (STACK_SIZE + EXTRASIZE));
    }
    *s->top = value;
    s->top++;
    return TRUE;
}
//出栈
Status Pop(SeqStack* s, char &value)
{
    if (IsEmpty(s) == TRUE) {
        return FALSE;
    }
    s->top--;
    value = *s->top;
    return OK;
}
//取栈顶元素
char GetTop(SeqStack* s)
{
    char value;
    if (IsEmpty(s) == TRUE) {
        return FALSE;
    }
    value = *(s->top-1);
    return value;
}
/*
int main()
{
    SeqStack *S;
    S=InitStack();
    int i;
    for (i=0;!IsFull(S);i++)
    {
        Push(S,48+i);
    }
    char value;
    GetTop(S,&value);
    printf("Top:%c\n", value);
    while (!IsEmpty(S))
    {
        Pop(S, &value);
        printf("Pop:%c\n", value);
    }
    return 0;
}
*/

//判断优先级
char Compare(char c1,char c2)
{
    char c;
    switch(c1)
    {
        case '+':
        case '-':
            {
                if(c2=='*' || c2=='/' || c2=='(')
                    c = '<';
                else
                    c = '>';
            }
            break;
        case '*':
        case '/':
            {
                if(c2=='(')
                    c = '<';
                else
                    c = '>';
            }
            break;
        case '(':
            {
                if(c2 == ')')
                    c = '=';
                else if(c2 == '#')
                    return ERROR;
                else
                    c = '<';
            }
            break;
        case ')':
            {
                if(c2 == '(')
                    return ERROR;
                else
                    c = '>';
            }
            break;
        case '#':
            {
                if(c2 == ')')
                    return ERROR;
                else if(c2 == '#')
                    c = '=';
                else
                    c = '<';
            }
            break;
        default:break;
    }
    return c;
}

//运算，返回类型是char
char Operate(char n1,char c,char n2)
{
    char result;
    switch(c)
    {
        case '+':result = (n1-48)+(n2-48)+48;break;
        case '-':result = (n1-48)-(n2-48)+48;break;
        case '*':result = (n1-48)*(n2-48)+48;break;
        case '/':
            if(n2==0)
            {
                printf("除数为0！");
                return ERROR;
            }
            result = (n1-48)/(n2-48)+48;break;
    }
    return result;
}

//判断输入字符是否为运算符
Status In(char c)
{
    if((c>=48)&&(c<=57))
        return 0;
    else if((c=='+')||(c=='-')||(c=='*')||(c=='/')||(c=='(')||(c==')')||(c=='#'))
        return 1;
    else
        return -1;
}
int main()
{
    char n1,n2,c,theta,result;
    SeqStack *OPTR = InitStack();
    SeqStack *OPND = InitStack();
    Push(OPTR,'#');
    printf("请输入运算表达式(要以'#'号结尾)：\n");
    c = getchar();
    //当符号栈无运算符号且输入为'#'，循环结束
    while(c!='#'||GetTop(OPTR)!='#')
    {
        if(In(c)==1)
        {
            //将符号栈和输入符号比较，判断优先级
            switch(Compare(GetTop(OPTR),c))
            {
                case '<':
                    Push(OPTR,c);
                    c = getchar();
                    break;
                case '=':
                    Pop(OPTR,result);
                    c = getchar();
                    break;
                case '>':
                    Pop(OPTR,theta);
                    Pop(OPND,n2);
                    Pop(OPND,n1);
                    Push(OPND,Operate(n1,theta,n2));  //将操作完的数入栈
                    break;
                default:break;
            }

        }
        //如果输入为数字，入OPND栈
        else if (In(c)== 0)
        {
            Push(OPND,c);
            c = getchar();
        }
        else
            return ERROR;
    }
    //循环结束，取出数字栈的栈顶
    printf("运算结果为：%d",GetTop(OPND)-48);
    return 0;
}

