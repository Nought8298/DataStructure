#include <stdio.h>
#include <stdlib.h>

//定义函数结果状态
#define FALSE 0
#define TRUE 1
#define ERROR 0
#define OK 1
#define OVERFLOW -1
#define MaxInt 32677
#define VEXMAX 10

typedef int Status;
typedef int VRType;
typedef char VexType;
int visited[VEXMAX];         //辅助数组，是否访问

typedef struct QNode        //单个结点的结构
{
	int data;			//数据
	struct QNode *next;		//下一个结点位置
}QNode, *QueuePtr;

typedef struct				//队列结构
{
	QueuePtr front;			
	QueuePtr rear;			
}LinkQueue;					//带头结点的链队列

struct adj
{
    VexType adjvex;
    VRType lowcost;
}adj,closedge[VEXMAX];     //最短路径数组结构体

typedef struct ArcCell
{
    VRType adj; //存储权值
}ArcCell, AdjMatrix[VEXMAX][VEXMAX];    //邻接矩阵
typedef struct
{
    VexType vexs[VEXMAX];       //顶点向量
    AdjMatrix arcs;     //邻接矩阵
    int vexnum,arcnum;

}Undinetwork;       //无向网

//队列的初始化
void InitQueue(LinkQueue &Q)
{
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));	//指针都指向头结点
	if (!Q.front)
		exit(0);
	Q.front->next = NULL;
}
//销毁队
void DestroyQueue(LinkQueue &Q)
{
	while (Q.front)					
	{
		Q.rear = Q.front->next;		
		free(Q.front);				//释放当前头指针指向的结点空间
		Q.front = Q.rear;			//再到下一个结点
	}
}
//入队
void EnQueue(LinkQueue &Q, int e)
{
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));	
	if (!p)				
		exit(0);
	p->data = e;		
	p->next = NULL;
	Q.rear->next = p;	
	Q.rear = p;			
}
//出队
void DeQueue(LinkQueue &Q, int &e)
{
	if (Q.front == Q.rear)				
		return;
	QueuePtr p = Q.front->next;			
	e = p->data;						
	Q.front->next = p->next;			//头指针始终在头结点处，只是释放第一个结点，然后连接第二个结点
	if (Q.rear == p)
		Q.rear = Q.front;
	free(p);
}

//判断队列是否为空
int QueueEmpty(LinkQueue Q)
{
	if (Q.front == Q.rear)		//如果头指针和尾指针指向同一结点，则队列为空
		return 1;
	return 0;
}

//在顶点向量中找到v，返回其下标
int LocateVex(Undinetwork g,VexType v)
{
    int i;
    for(i = 0;i<g.vexnum;i++)
    {
        if(v == g.vexs[i])
            break;
    }
    return i;      
}

//设置visited数组
Status visitedSet(Undinetwork g)
{

    for(int i = 0; i < g.vexnum;i++)
    {
        visited[i] = 0;
    }
    return OK;
}

//无向网的初始化
Status CreateUDN(Undinetwork &g)
{
    printf("请输入点数：");
    scanf("%d",&g.vexnum);
    printf("请输入边数：");
    scanf("%d",&g.arcnum);
    printf("请依次输入%d个顶点：\n",g.vexnum);
    
    fflush(stdin);      //scanf会读取回车，空格等，所以要及时释放缓冲区
    for(int m = 0;m<g.vexnum;m++)
    {
        scanf("%c",&g.vexs[m]);
        fflush(stdin);
    }
    
    //printf("输入顶点元素(无需空格隔开)：");
	//scanf("%s",g.vexs);
    printf("顶点输入完毕\n请输入各边之间的权值：（示例：a-b 1）\n");
    int i,j;
    for(i = 0;i<VEXMAX;i++)
    {
        for (j = 0;j<VEXMAX;j++)
            g.arcs[i][j].adj = MaxInt;      //所有权值赋值为最大值
    }
    int k;
    i = 0;
    j = 0;
    for(k = 0; k<g.arcnum; k++)
    {
        VexType v1,v2;
        VRType weight;
        scanf("%c-%c %d",&v1,&v2,&weight);
        fflush(stdin);
        i = LocateVex(g,v1);
        j = LocateVex(g,v2);
        g.arcs[i][j].adj = weight;
        g.arcs[j][i] = g.arcs[i][j];        //分别对权值和邻接矩阵赋值
    }
    printf("边和权值输入完毕\n无向网创建成功\n\n");
    return OK;
}

//访问函数
Status visit(VexType v)
{
    printf("%c", v);
    return OK;
}

//深度优先遍历
Status DFS(Undinetwork g,int n)
{
    VexType v = g.vexs[n];
    visited[n] = 1;
    visit(v);
    //在矩阵中，在v所在一行寻找与其相连的顶点
    for(int w = 0;w<g.vexnum;w++)
    {
        if((!visited[w]) && (g.arcs[n][w].adj!=0)&&(g.arcs[n][w].adj!=MaxInt))
            DFS(g,w);
    }
    return OK;
}

//深度优先遍历
Status DFSTraverse(Undinetwork g)
{
    visitedSet(g);
    //VexType v;
    int m;
    for(m = 0; m < g.vexnum;m++)
    {
        if(visited[m]==0)
        {
            DFS(g,m);
        }

    }
    return OK;
}

//广度优先遍历
Status BFSTraverse(Undinetwork g)
{
    VexType v;
    visitedSet(g);          //重置visited数组
    LinkQueue Q;
    InitQueue(Q);
    for(int i=0;i< g.vexnum;i++)
    {
        v = g.vexs[i];
        //若未被访问，则入队
        if(visited[i]==0)
        {
            visit(v);
            visited[i] = 1;
            EnQueue(Q,i);
        }
        while(!QueueEmpty(Q))
        {
            int val;
            DeQueue(Q,val);
            //遍历这个顶点周围的所有顶点
            for(int w = 0;w<g.vexnum;w++)
            {
                if((!visited[w]) && (g.arcs[i][w].adj!=MaxInt))
                {
                    visited[w] = 1;
                    VexType v2 = g.vexs[w];
                    visit(v2);
                    EnQueue(Q, w);  //访问该顶点并入队
                }
            }
        }


    }
    return OK;
}

//寻找此时的最小权值
int minimum(Undinetwork g)
{
    int i;
    int min,loc;

    min = MaxInt; 
    for(i = 1;i<g.vexnum;i++)
    {
        if(min>closedge[i].lowcost&&closedge[i].lowcost!=0)
        {
            min = closedge[i].lowcost;
            loc = i;
        }
    }
    return loc;
}

//Prim算法
Status Mini_Prim(Undinetwork g,VexType v)
{
    int i,j,k;
    k = LocateVex(g,v);
    for(i = 0; i < g.vexnum;i++)
    {
        closedge[i].adjvex = v;
        closedge[i].lowcost = g.arcs[k][i].adj;
    }
    closedge[k].lowcost = 0;
    //printf("%c",v);
    for(i = 0; i < g.vexnum-1;i++)
    {
        k = minimum(g);
        printf("%c-%c %d\n",closedge[k].adjvex,g.vexs[k],closedge[k].lowcost);
        //printf(",%c",g.vexs[k]);
        closedge[k].lowcost = 0;

        for(j = 0; j < g.vexnum;j++)
        {
            if(g.arcs[k][j].adj<closedge[j].lowcost)
            {
                closedge[j].lowcost = g.arcs[k][j].adj;
                closedge[j].adjvex = g.vexs[k];
            }
        }
    }
}


int main()
{
    /*
    LinkQueue Q;
	InitQueue(Q);
	for (int i = 1; i <= 10; i++)
		EnQueue(Q, i);
	int e;
	DeQueue(Q, e);
	printf("一次删除：%3d\n", e);
	DeQueue(Q, e);
	printf("二次删除：%3d\n", e);
	DestroyQueue(Q);
    */
    Undinetwork g;
    CreateUDN(g);
    printf("深度优先遍历：");
    DFSTraverse(g);
    printf("\n广度优先遍历：");
    BFSTraverse(g);
    printf("\nPrim算法\n请输入起始点：");
    VexType vex;
    scanf("%c",&vex);
    int loca = LocateVex(g,vex);
    printf("最小生成树边集：\n");
    Mini_Prim(g,g.vexs[loca]);
    system("pause");
}

