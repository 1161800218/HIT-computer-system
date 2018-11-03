#include <stdio.h>
#include <stdlib.h>

char A[25]={'a','0','0','b','a','L','g','a','R','c','b','L','d','b','R','h','g','L','e','d','L','f','d','R','#'};
char B[34]={'1','0','0','2','1','L','3','1','R','4','2','L','5','2','R','6','3','L','7','3','R','8','4','L','9','4','R','a','6','R','b','7','L','#'};


typedef struct biTree{
	char data;
	struct biTree *lchild,*rchild,*next;
	char parent_data;
	char tag;
}biTree;

void initList(biTree **biTree)
{
    *biTree = NULL;
    printf("��ʼ���ɹ�\n");
}


//�������ж�ȡ���ݴ�����
biTree *createtree_link(char A[])
{
    biTree *root =(biTree*)malloc(sizeof(biTree));
    int i=0;
    biTree *p;
    biTree *q;
    p=q=root;


    while(A[i]!='#')
    {
       q=(biTree*)malloc(sizeof(biTree));
       q->data=A[i];
       q->parent_data=A[i+1];
       q->tag=A[i+2];
       q->lchild=NULL;
       q->rchild=NULL;
       p->next=q;
       p=q;

       i+=3;
    }
    p->next=NULL;
    printf("�������ɹ���\n");

    return root;
}


void levelOrderTraverse(biTree *root)
{
    if(NULL == root)   //��Ϊ��
    {
        printf("��Ϊ��\n");
    }
    else
    {
        while(NULL != root->next)
        {
            root = root->next;
            printf("%c ",root->data);
        }
        printf("\n");
    }
}

biTree *createtree(biTree *root)
{
    biTree *q=root->next;
    while(NULL != q->next)
    {
        biTree *p=q->next;
        while(NULL != p)
        {
            if(p->parent_data==q->data)
            {
                if(p->tag=='L')
                    q->lchild=p;
                else if(p->tag=='R')
                    q->rchild=p;
            }
            p=p->next;
        }
        q=q->next;
    }

    return root;
}

void PreOrderTraverse(biTree *bt)//���������
{
    if(bt)
    {
        printf("%c ",bt->data);
        PreOrderTraverse(bt->lchild);
        PreOrderTraverse(bt->rchild);
    }
}

int inOrderTraverse(struct biTree * bt)
{
	if(bt!=NULL){
		inOrderTraverse(bt->lchild);
		printf("%c ",bt->data);
		inOrderTraverse(bt->rchild);
	}
	return 0;
}

int postOrderTraverse(struct biTree * bt){
	if(bt!=NULL){
		postOrderTraverse(bt->lchild);
		postOrderTraverse(bt->rchild);
		printf("%c ",bt->data);
	}
	return 0;
}

void LevelOrderTraverse(struct biTree * root)
{
    struct biTree *temp[100];                                //�ؼ��м�������ÿһ�������
    int in = 0, out = 0;
    temp[in++] = root;                                     //ÿ�ΰ���һ����룬Ȼ�������ʱ��Ͱ��������ҽڵ����
    while(in > out)                                         //����һ����ȫ������abcdefg  ���a��ʱ���bc����,���b��ʱ���b
    {                                                       //�ĺ��ӷ���Ҳ����de�������c���ҷ��뺢��fg�������������ﵽ�����Ҫ��
        if(temp[out])
        {
            printf("%c ",temp[out]->data);
            temp[in++] = temp[out]->lchild;
            temp[in++] = temp[out]->rchild;
        }
        out++;
    }
}


int main()
{
    biTree * bt=NULL;
    initList(&bt);
    levelOrderTraverse(bt);

    printf("����ĵڶ������ݽṹʵ��\n");
    printf("\n");

    printf("��һ��");

    bt=createtree_link(A);

    bt=createtree(bt);

	printf("�������������: ");
    PreOrderTraverse(bt->next);
	printf("\n");

	printf("�������������: ");
	inOrderTraverse(bt->next);
	printf("\n");

	printf("�������������: ");
	postOrderTraverse(bt->next);
	printf("\n");

    printf("�������������: ");
	levelOrderTraverse(bt);
	printf("\n");

    printf("�ڶ���");
	bt=createtree_link(B);

    bt=createtree(bt);

	printf("�������������: ");
    PreOrderTraverse(bt->next);
	printf("\n");

	printf("�������������: ");
	inOrderTraverse(bt->next);
	printf("\n");

	printf("�������������: ");
	postOrderTraverse(bt->next);
	printf("\n");

    printf("�������������: ");
	levelOrderTraverse(bt);
	return 0;


    return 0;
}



