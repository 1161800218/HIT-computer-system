#include<stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>


#define MAX_VERTEX_NUM 20    //��󶥵����
#define INFINITY INT_MAX  //���ֵ��
#define MAX 10000//��ʾ�������������

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

typedef char VertexType;   //������������
typedef int VRType;
typedef int InfoType;
typedef int QElemType;

//ͼ������洢��ʾ
 typedef struct{
    VertexType vexs[MAX_VERTEX_NUM];    //��������
    VRType arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];  //�ڽӾ���,����Ȩͼ1��0��ʾ���������Ƿ����ڣ�������ȨͼΪȨֵ
    int vexnum,arcnum; //ͼ�Ķ������ͻ���
}MGraph;


bool visited[MAX_VERTEX_NUM];  //��Ƕ����Ƿ񱻷��ʣ�����Ϊtrue,����Ϊfalse

//���Ҷ����ڶ��������е�λ��
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

 //��������������Ȩͼ
createMGraph(MGraph *mg,VRType A[][5],VertexType P[],int arc,int vex)
{
    int i,j,v,w;
    char v1,v2;
    (*mg).vexnum=vex;
    (*mg).arcnum=arc;

    for(v=0;v<(*mg).vexnum;v++)
        visited[v] = false;

    //����
    for(v=0;v<(*mg).vexnum;v++)
    {
        (*mg).vexs[v]=P[v];
    }

    //��ʼ���ڽӾ���
    for(i=0;i<(*mg).vexnum;i++)
        for(j=0;j<(*mg).vexnum;j++)
                (*mg).arcs[i][j] = INFINITY;

    //��ͼ�����ڵĶ�����ڽӾ���ֵ��Ϊ�ߵ�Ȩֵ
    for(i=0;i<(*mg).vexnum;i++)
    {
        for(j=0;j<(*mg).vexnum;j++)
        {
            (*mg).arcs[i][j] = A[i][j];    //����ͼ����Ϊ����
        }
    }

}

void print(MGraph G)
{
    int i,j;
    printf("ͼ���ڽӾ���\n");
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

//������ȱ���ͼ
int FirstAdjVex(MGraph G,int v)
{   //��ȡ�붥��v���ڵĵ�һ�������±�
    int i;
    for(i=0;i<G.vexnum;i++)
    {
        if(G.arcs[v][i]!=0 && G.arcs[v][i]!=-1 && !visited[i])
            return i;
    }
    return -1;
}

int NextAdjVex(MGraph G,int v,int w)
{   //�õ�v����һ��δ�����ʵ����ڶ����±�
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
    printf("%c ",G.vexs[v]);         //���ʵ�v������
    for(w = FirstAdjVex(G,v); w >= 0;w = NextAdjVex(G,v,w))
        if(!visited[w])
            DFS(G,w);              //��v����δ���ʵ��ڽӶ���w�ݹ����DFS
}

void DFSTraverse(MGraph G)
{
    printf("������ȱ������У�");
    int v;
    for(v = 0; v<G.vexnum;v++)
        visited[v] = false;
    for(v=0;v<G.vexnum;v++)
        if(!visited[v])
            DFS(G,v);
    printf("\n");
 }


//������ȱ���

//�������ڹ�����ȱ����Ķ���
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

//��ʼ��һ���ն���
PQueue initQueue()
{
    PQueue pqueue = (PQueue)malloc(sizeof(Queue));
    PQNode pqnode = (PQNode)malloc(sizeof(QNode));
    if(pqnode==NULL)
    {
        printf("����ͷ�ռ�����ʧ�ܣ�\n");
        exit(-1);
    }
    pqueue->front = pqueue->rear = pqnode;
    pqnode->qnext = NULL;
    return pqueue;
}

//��β���
void enQueue(PQueue pqueue,QElemType data)
{
    PQNode pqnode = (PQNode)malloc(sizeof(QNode));
    if(pqnode==NULL)
    {
        printf("���н������ʧ�ܣ�\n");
        exit(-1);
    }
    pqnode->data = data;
    pqnode->qnext = NULL;
    pqueue->rear->qnext = pqnode;
    pqueue->rear = pqnode;
 }
//�ж϶����Ƿ�Ϊ��
bool isEmpty(PQueue pqueue)
{
    if(pqueue->front == pqueue->rear)
        return true;
    return false;
 }
//��ͷ����
QElemType deQueue(PQueue pqueue)
{
    if(isEmpty(pqueue))
    {
        printf("����Ϊ��\n");
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
    printf("������ȱ������У�");
    int i,v,w;
    for(i=0;i<G.vexnum;i++)
        visited[i] = false;
    PQueue pqueue = initQueue();    //��ʼ����������
    for(i=0;i<G.vexnum;i++)
    {
        if(!visited[i])             //iδ������
        {
            visited[i] = true;
            printf("%c ",G.vexs[i]);
            enQueue(pqueue,i);
            while(!isEmpty(pqueue))
            {
                v = deQueue(pqueue);    //��ͷԪ�س���
                for(w=FirstAdjVex(G,v);w>=0;w=NextAdjVex(G,v,w))
                    if(!visited[w])            //wΪv����δ���ʵ��ڽӶ���
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
    printf("����ĵ��������ݽṹʵ��\n\n");
    int G[6][5];
    int i,j,k;
    int point,line;
    char P[5];
    FILE* fp=fopen("graph1.txt","r"); //���ļ�

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
                fscanf(fp,"%d",&G[i][j]);/*ÿ�ζ�ȡһ������fscanf���������ո���߻��н���*/
            }
                fscanf(fp,"\n");
    }
    fclose(fp);

    MGraph mg;
    createMGraph(&mg,G,P,line,point);
    print(mg);
    DFSTraverse(mg);
    BFSTraverse(mg);

    printf("\n���·��\n");

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
