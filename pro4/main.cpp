#include <stdio.h>
#include <stdlib.h>

//���庯�����״̬
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
int visited[VEXMAX];         //�������飬�Ƿ����

typedef struct QNode        //�������Ľṹ
{
	int data;			//����
	struct QNode *next;		//��һ�����λ��
}QNode, *QueuePtr;

typedef struct				//���нṹ
{
	QueuePtr front;			
	QueuePtr rear;			
}LinkQueue;					//��ͷ����������

struct adj
{
    VexType adjvex;
    VRType lowcost;
}adj,closedge[VEXMAX];     //���·������ṹ��

typedef struct ArcCell
{
    VRType adj; //�洢Ȩֵ
}ArcCell, AdjMatrix[VEXMAX][VEXMAX];    //�ڽӾ���
typedef struct
{
    VexType vexs[VEXMAX];       //��������
    AdjMatrix arcs;     //�ڽӾ���
    int vexnum,arcnum;

}Undinetwork;       //������

//���еĳ�ʼ��
void InitQueue(LinkQueue &Q)
{
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));	//ָ�붼ָ��ͷ���
	if (!Q.front)
		exit(0);
	Q.front->next = NULL;
}
//���ٶ�
void DestroyQueue(LinkQueue &Q)
{
	while (Q.front)					
	{
		Q.rear = Q.front->next;		
		free(Q.front);				//�ͷŵ�ǰͷָ��ָ��Ľ��ռ�
		Q.front = Q.rear;			//�ٵ���һ�����
	}
}
//���
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
//����
void DeQueue(LinkQueue &Q, int &e)
{
	if (Q.front == Q.rear)				
		return;
	QueuePtr p = Q.front->next;			
	e = p->data;						
	Q.front->next = p->next;			//ͷָ��ʼ����ͷ��㴦��ֻ���ͷŵ�һ����㣬Ȼ�����ӵڶ������
	if (Q.rear == p)
		Q.rear = Q.front;
	free(p);
}

//�ж϶����Ƿ�Ϊ��
int QueueEmpty(LinkQueue Q)
{
	if (Q.front == Q.rear)		//���ͷָ���βָ��ָ��ͬһ��㣬�����Ϊ��
		return 1;
	return 0;
}

//�ڶ����������ҵ�v���������±�
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

//����visited����
Status visitedSet(Undinetwork g)
{

    for(int i = 0; i < g.vexnum;i++)
    {
        visited[i] = 0;
    }
    return OK;
}

//�������ĳ�ʼ��
Status CreateUDN(Undinetwork &g)
{
    printf("�����������");
    scanf("%d",&g.vexnum);
    printf("�����������");
    scanf("%d",&g.arcnum);
    printf("����������%d�����㣺\n",g.vexnum);
    
    fflush(stdin);      //scanf���ȡ�س����ո�ȣ�����Ҫ��ʱ�ͷŻ�����
    for(int m = 0;m<g.vexnum;m++)
    {
        scanf("%c",&g.vexs[m]);
        fflush(stdin);
    }
    
    //printf("���붥��Ԫ��(����ո����)��");
	//scanf("%s",g.vexs);
    printf("�����������\n���������֮���Ȩֵ����ʾ����a-b 1��\n");
    int i,j;
    for(i = 0;i<VEXMAX;i++)
    {
        for (j = 0;j<VEXMAX;j++)
            g.arcs[i][j].adj = MaxInt;      //����Ȩֵ��ֵΪ���ֵ
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
        g.arcs[j][i] = g.arcs[i][j];        //�ֱ��Ȩֵ���ڽӾ���ֵ
    }
    printf("�ߺ�Ȩֵ�������\n�����������ɹ�\n\n");
    return OK;
}

//���ʺ���
Status visit(VexType v)
{
    printf("%c", v);
    return OK;
}

//������ȱ���
Status DFS(Undinetwork g,int n)
{
    VexType v = g.vexs[n];
    visited[n] = 1;
    visit(v);
    //�ھ����У���v����һ��Ѱ�����������Ķ���
    for(int w = 0;w<g.vexnum;w++)
    {
        if((!visited[w]) && (g.arcs[n][w].adj!=0)&&(g.arcs[n][w].adj!=MaxInt))
            DFS(g,w);
    }
    return OK;
}

//������ȱ���
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

//������ȱ���
Status BFSTraverse(Undinetwork g)
{
    VexType v;
    visitedSet(g);          //����visited����
    LinkQueue Q;
    InitQueue(Q);
    for(int i=0;i< g.vexnum;i++)
    {
        v = g.vexs[i];
        //��δ�����ʣ������
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
            //�������������Χ�����ж���
            for(int w = 0;w<g.vexnum;w++)
            {
                if((!visited[w]) && (g.arcs[i][w].adj!=MaxInt))
                {
                    visited[w] = 1;
                    VexType v2 = g.vexs[w];
                    visit(v2);
                    EnQueue(Q, w);  //���ʸö��㲢���
                }
            }
        }


    }
    return OK;
}

//Ѱ�Ҵ�ʱ����СȨֵ
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

//Prim�㷨
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
	printf("һ��ɾ����%3d\n", e);
	DeQueue(Q, e);
	printf("����ɾ����%3d\n", e);
	DestroyQueue(Q);
    */
    Undinetwork g;
    CreateUDN(g);
    printf("������ȱ�����");
    DFSTraverse(g);
    printf("\n������ȱ�����");
    BFSTraverse(g);
    printf("\nPrim�㷨\n��������ʼ�㣺");
    VexType vex;
    scanf("%c",&vex);
    int loca = LocateVex(g,vex);
    printf("��С�������߼���\n");
    Mini_Prim(g,g.vexs[loca]);
    system("pause");
}

