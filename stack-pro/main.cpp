#include <stdio.h>
#include <stdlib.h>

//���庯�����״̬
#define FALSE 0
#define TRUE 1
#define ERROR 0
#define OK 1
#define OVERFLOW -1

#define STACK_SIZE 20   //����ջ��ʼ����
#define EXTRASIZE 10
typedef int Status;

typedef struct
{
    char* top;           //ջ����֮ǰ������֮�󣬾�ΪNULL
    char* base;
    int stacksize;       //��ǰ�ѷ���Ĵ洢�ռ�
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
//���ջ
Status ClearStack(SeqStack *s)
{
    s->top = s->base;//ջ��ָ��ָ��ջ��
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

//��ջ
Status Push(SeqStack* s, char value)
{
    if (IsFull(s) == TRUE) {
        s->base = (char*)malloc(sizeof(char) * (STACK_SIZE + EXTRASIZE));
    }
    *s->top = value;
    s->top++;
    return TRUE;
}
//��ջ
Status Pop(SeqStack* s, char &value)
{
    if (IsEmpty(s) == TRUE) {
        return FALSE;
    }
    s->top--;
    value = *s->top;
    return OK;
}
//ȡջ��Ԫ��
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

//�ж����ȼ�
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

//���㣬����������char
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
                printf("����Ϊ0��");
                return ERROR;
            }
            result = (n1-48)/(n2-48)+48;break;
    }
    return result;
}

//�ж������ַ��Ƿ�Ϊ�����
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
    printf("������������ʽ(Ҫ��'#'�Ž�β)��\n");
    c = getchar();
    //������ջ���������������Ϊ'#'��ѭ������
    while(c!='#'||GetTop(OPTR)!='#')
    {
        if(In(c)==1)
        {
            //������ջ��������űȽϣ��ж����ȼ�
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
                    Push(OPND,Operate(n1,theta,n2));  //�������������ջ
                    break;
                default:break;
            }

        }
        //�������Ϊ���֣���OPNDջ
        else if (In(c)== 0)
        {
            Push(OPND,c);
            c = getchar();
        }
        else
            return ERROR;
    }
    //ѭ��������ȡ������ջ��ջ��
    printf("������Ϊ��%d",GetTop(OPND)-48);
    return 0;
}

