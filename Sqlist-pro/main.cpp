#include <stdio.h>
#include <stdlib.h>

//定义函数结果状态
#define FALSE 0
#define TRUE 1
#define ERROR 0
#define OK 1
#define OVERFLOW -1

#define LIST_INIT_SIZE 100  //初始分配量
#define LISTINCREMENT 10    //分配增量

typedef int Status;
typedef int ElemType;

typedef struct SqList
{
    ElemType *elem; //存储地址基址
    int length;     //当前长度
    int listsize;   //当前分配长度
}SqList;    //顺序表

//构造空的线性表L
Status Init(SqList &L){
    L.elem = (ElemType *)malloc(sizeof(ElemType));
    if(!L.elem)
        exit(OVERFLOW);     //空间分配失败
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;
    return OK;
}

//构造线性表L
Status Init_Sq(SqList &L){
    Init(L);
    printf("请输入线性表插入元素个数：");
    scanf("%d",&L.length);
    if(L.length>L.listsize){
        ElemType *newbase;
        newbase = (ElemType *)realloc(L.elem,(L.listsize + LISTINCREMENT)*sizeof(ElemType));
        if(!newbase)
            exit(OVERFLOW);
        L.elem = newbase;
        L.listsize = L.listsize + LISTINCREMENT;
    }
    for(int i = 0;i<L.length;i++){
        printf("请输入第%d个元素：",(i+1));
        scanf("%d",&L.elem[i]);
    }
    return OK;
}

//第i个位置前插入元素
Status ListInsert_Sq(SqList &L,int i,ElemType e){
    if(i<1||i>L.length+1)
        return ERROR;
    if(L.length>L.listsize){
        //realloc重新分配空间
        /*
        void ＊realloc（void ＊p，size＿t size）
        realloc函数将p指向的对象的长度修改为size个字节，
        如果新分配的内存比原来的大，则原来的数据保持不变，增加的空间不进行初始化。
        如果新分配的内存比原来的内存小，则新的内存空间不被初始化，
        realloc函数返回指向新分配空间的指针，
        若无法满足要求则返回NULL 指针，在这种情况下，原指针p指向的单元内容保持不变。
        */
        ElemType *newbase;
        newbase = (ElemType *)realloc(L.elem,(L.listsize + LISTINCREMENT)*sizeof(ElemType));
        if(!newbase)
            exit(OVERFLOW);
        L.elem = newbase;
        L.listsize = L.listsize + LISTINCREMENT;
    }
    ElemType * q = &L.elem[i-1];    //q为插入位置
    for(ElemType *p = &(L.elem[L.length-1]);p>=q;--p){
        *(p+1) = *p;
    }
    *q = e;
    ++L.length;
    return OK;
}//Insert 

//删除第i个元素，且用e返回其值
Status ListDelete_Sq(SqList &L,int i,ElemType &e){
    if(i<1||i>L.length+1)
        return ERROR;
    ElemType *p = &(L.elem[i-1]);
    e = *p;
    ElemType *q = &(L.elem[L.length-1]);
    for(++p;p<=q;++p)
        *(p-1) = *p;
    --L.length;
    return OK;
}

bool compare(ElemType e1,ElemType e2){
    if(e1==e2)
        return true;
    else
        return false;
    
}

//查找元素
int LocateElem_Sq(SqList L,ElemType e){
    int i = L.length-1;
    //从表尾向前寻找，若找不到，则返回值为0
    ElemType *p = &(L.elem[L.length-1]);
    while(i>=0&&!compare(*p--,e))
        --i;
    return i+1;
    /*
    ElemType *p = L.elem;
    while(i<L.length&&!compare(*p++,e))
        ++i;
    if(i>=L.length)
        i = 0;
    return i+1;
    */
}
//依次输出每个元素
Status ListTraverse_Sq(SqList L){
    for(int i=0;i<L.length;i++)
        printf("%d\n",L.elem[i]);
}

int main(){
    SqList L;
    Init_Sq(L);
    ElemType e;
    ListDelete_Sq(L,2,e);
    ListTraverse_Sq(L);
    printf("\n%d\n",LocateElem_Sq(L,2));
    printf("%d\n",LocateElem_Sq(L,3));
    system("pause");
    return 0;
} 