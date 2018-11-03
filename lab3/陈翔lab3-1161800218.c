#include<stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>


#define MAX_VERTEX_NUM 20    //最大顶点个数
#define INFINITY INT_MAX  //最大值∞
#define MAX 10000//表示两顶点间无连接

#define MaxSize 5

#define Infinity 1000

int S,d[1000],Min,flag[1000],t;
int stk[100],pre[100],top;
void push(int i){
	stk[top]=i;
	top++;
}
int pop(){
	top--;
	return stk[top];
}
int empty(){
	return top==0;
}

typedef char VertexType;   //顶点向量类型
typedef int VRType;
typedef int InfoType;
typedef int QElemType;

//图的数组存储表示
 typedef struct{
    VertexType vexs[MAX_VERTEX_NUM];    //顶点向量
    VRType arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];  //邻接矩阵,于无权图1、0表示两个顶点是否相邻，对于有权图为权值
    int vexnum,arcnum; //图的顶点数和弧数
}MGraph;


bool visited[MAX_VERTEX_NUM];  //标记顶点是否被访问，访问为true,否则为false

//查找顶点在顶点向量中的位置
int locateVertex(MGraph umg, VertexType v)
{
    int i;
    for(i=0;i<umg.vexnum;i++)
    {
        if(v == umg.vexs[i])
            return i;
    }
    return -1;
 }

 //创建无向（有向）有权图
createMGraph(MGraph *mg,VRType A[][5],VertexType P[],int arc,int vex)
{
    int i,j,v,w;
    char v1,v2;
    (*mg).vexnum=vex;
    (*mg).arcnum=arc;

    for(v=0;v<(*mg).vexnum;v++)
        visited[v] = false;

    //顶点
    for(v=0;v<(*mg).vexnum;v++)
    {
        (*mg).vexs[v]=P[v];
    }

    //初始化邻接矩阵
    for(i=0;i<(*mg).vexnum;i++)
        for(j=0;j<(*mg).vexnum;j++)
                (*mg).arcs[i][j] = INFINITY;

    //将图中相邻的顶点的邻接矩阵值设为边的权值
    for(i=0;i<(*mg).vexnum;i++)
    {
        for(j=0;j<(*mg).vexnum;j++)
        {
            (*mg).arcs[i][j] = A[i][j];    //有向图，边为单向
        }
    }

}

void print(MGraph G)
{
    int i,j;
    printf("图的邻接矩阵\n");
    for(i=0;i<G.vexnum;i++)
    {
        for(j=0;j<G.vexnum;j++)
        {
                printf("%d ",G.arcs[i][j]);
        }
        printf("\n");

    }
    printf("\n");
 }

//深度优先遍历图
int FirstAdjVex(MGraph G,int v)
{   //获取与顶点v相邻的第一个顶点下标
    int i;
    for(i=0;i<G.vexnum;i++)
    {
        if(G.arcs[v][i]!=0 && G.arcs[v][i]!=-1 && !visited[i])
            return i;
    }
    return -1;
}

int NextAdjVex(MGraph G,int v,int w)
{   //得到v的下一个未被访问的相邻顶点下标
    int i;
    for(i=w;i<G.vexnum;i++)
    {
        if(G.arcs[v][i]!=0 && G.arcs[v][i]!=-1 && !visited[i])
            return i;
     }
     return -1;
}

void DFS(MGraph G,int v)
{
    int w;
    visited[v] = true;
    printf("%c ",G.vexs[v]);         //访问第v个顶点
    for(w = FirstAdjVex(G,v); w >= 0;w = NextAdjVex(G,v,w))
        if(!visited[w])
            DFS(G,w);              //对v的尚未访问的邻接顶点w递归调用DFS
}

void DFSTraverse(MGraph G)
{
    printf("深度优先遍历序列：");
    int v;
    for(v = 0; v<G.vexnum;v++)
        visited[v] = false;
    for(v=0;v<G.vexnum;v++)
        if(!visited[v])
            DFS(G,v);
    printf("\n");
 }


//广度优先遍历

//创建用于广度优先遍历的队列
typedef struct QNode
{
    QElemType data;
    struct QNode *qnext;
}QNode,*PQNode;

typedef struct Queue
{
    PQNode front;
    PQNode rear;
}Queue,*PQueue;

//初始化一个空队列
PQueue initQueue()
{
    PQueue pqueue = (PQueue)malloc(sizeof(Queue));
    PQNode pqnode = (PQNode)malloc(sizeof(QNode));
    if(pqnode==NULL)
    {
        printf("队列头空间申请失败！\n");
        exit(-1);
    }
    pqueue->front = pqueue->rear = pqnode;
    pqnode->qnext = NULL;
    return pqueue;
}

//队尾入队
void enQueue(PQueue pqueue,QElemType data)
{
    PQNode pqnode = (PQNode)malloc(sizeof(QNode));
    if(pqnode==NULL)
    {
        printf("队列结点申请失败！\n");
        exit(-1);
    }
    pqnode->data = data;
    pqnode->qnext = NULL;
    pqueue->rear->qnext = pqnode;
    pqueue->rear = pqnode;
 }
//判断队列是否为空
bool isEmpty(PQueue pqueue)
{
    if(pqueue->front == pqueue->rear)
        return true;
    return false;
 }
//队头出队
QElemType deQueue(PQueue pqueue)
{
    if(isEmpty(pqueue))
    {
        printf("队列为空\n");
        exit(-1);
    }

    PQNode pqnode = pqueue->front->qnext;
    pqueue->front->qnext = pqnode->qnext;
    if(pqnode == pqueue->rear)
        pqueue->rear = pqueue->front;
    QElemType data = pqnode->data;
    free(pqnode);
    return data;

}
void BFSTraverse(MGraph G)
{
    printf("广度优先遍历序列：");
    int i,v,w;
    for(i=0;i<G.vexnum;i++)
        visited[i] = false;
    PQueue pqueue = initQueue();    //初始化辅助队列
    for(i=0;i<G.vexnum;i++)
    {
        if(!visited[i])             //i未被访问
        {
            visited[i] = true;
            printf("%c ",G.vexs[i]);
            enQueue(pqueue,i);
            while(!isEmpty(pqueue))
            {
                v = deQueue(pqueue);    //队头元素出队
                for(w=FirstAdjVex(G,v);w>=0;w=NextAdjVex(G,v,w))
                    if(!visited[w])            //w为v的尚未访问的邻接顶点
                    {
                        visited[w] = true;
                        printf("%c ",G.vexs[w]);
                        enQueue(pqueue,w);
                    }

            }
        }
    }
    printf("\n");
 }


int main()
{
    printf("陈翔的第三次数据结构实验\n\n");
    int G[6][5];
    int i,j,k;
    int point,line;
    char P[5];
    FILE* fp=fopen("graph1.txt","r"); //打开文件

    if(fp==NULL)
    {
        printf("open error\n");
        return -1;
    }

    fscanf(fp,"%d ",&point);
    fscanf(fp,"%d ",&line);
    fscanf(fp,"\n");

    for(k=0;k<5;k++)
        fscanf(fp,"%c ",&P[k]);
    fscanf(fp,"\n");


    for(i=0;i<5;i++)
    {
        for(j=0;j<5;j++)
            {
                fscanf(fp,"%d",&G[i][j]);/*每次读取一个数，fscanf函数遇到空格或者换行结束*/
            }
                fscanf(fp,"\n");
    }
    fclose(fp);

    MGraph mg;
    createMGraph(&mg,G,P,line,point);
    print(mg);
    DFSTraverse(mg);
    BFSTraverse(mg);

    printf("\n最短路径\n");

    for(i=0;i<5;i++)
    {
        for(j=0;j<5;j++)
        {
            if(i!=j&&G[i][j]==-1)
                G[i][j]=Infinity;
            else if(i==j)
                G[i][j]=0;
        }
    }

    for(i=0;i<5;i++)
		d[i]=Infinity;
	d[0]=0;
	for(i=0;i<5;i++){
		Min=Infinity;
		for(j=0;j<5;j++)
		if(!flag[j]&&d[j]<Min){
			Min=d[j];
			t=j;
		}
		for(j=0;j<5;j++){
			if(d[t]+G[t][j]<d[j]){
				d[j]=d[t]+G[t][j];
				pre[j]=t;
			}
		}
		flag[t]=true;
	}
	for(i=1;i<5;i++) {
		j=i;
		push(j);
		while(j!=0){
			push(pre[j]);
			j=pre[j];
		}
		printf("%c->%c ",P[0],P[i]);
		while(1){
			int tmp=pop();
			printf("%c",P[tmp]);
			if(!empty()){
				printf(",");
			}
			else {
			printf(" ");
			break;
			}
		}
			printf("value=%d\n",d[i]);
	}

    return 0;
}
