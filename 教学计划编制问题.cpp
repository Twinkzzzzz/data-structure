#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std; 
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define MAX_NAME 3
#define MAXCLASS 100  //�����ַ�������󳤶�
#define MAX_VERTEX_NUM 100 //��󶥵���

//typedef int int; // ����������,��ֵ�Ǻ������״̬���룬��1��
typedef char VertexType[MAX_NAME]; 

int TotalTerms ; //ѧ������
int MaxScores; //ѧ������

/* ----ͼ���ڽӱ�洢��ʾ---- */
typedef struct node
{
	int adjvex; // �û���ָ��Ķ����λ��
	struct node *nextarc; //ָ����һ������ָ��
}node; // ����

typedef struct
{
	char data[101];  //������Ϣ
	int grades;  //�洢ѧ����Ϣ
	node *firstarc; //ָ���һ�������ö���Ļ���ָ��
}VNode, AdjList[MAX_VERTEX_NUM]; // ͷ���

typedef struct
{
	AdjList vertices; //vertices �洢�γ���
	int vexnum, arcnum; // ͼ�ĵ�ǰ�������ͻ���
}ALGraph;


/*  ͼ���ڽӱ�洢�Ļ������� */
int LocateVex(ALGraph G, char u[])	// ��G�д��ڶ���u,�򷵻ظö�����ͼ��λ��;���򷵻�-1
{ 
	int i;
	for (i = 0;i < G.vexnum;++i)
		if (strcmp(u, G.vertices[i].data) == 0)
			return i;
	return -1;
}

int CreateGraph(ALGraph *G)  //�����ڽӱ�洢�ṹ,����û�������Ϣ��ͼG
{ 
	int i, j, k;
	char va[101];
	node *p;
	cout << "�������ѧ�ƻ��Ŀγ���: " << endl;
	cin >> (*G).vexnum;
	cout << "����������γ̵����޿γ̵��ܺ�(������): " << endl;
	cin >> (*G).arcnum;

	cout << "������" << (*G).vexnum << "���γ̵Ŀγ̺�(���" << MAX_NAME << "���ַ�,����+��ĸ):" << endl;
	for (i = 0;i < (*G).vexnum;++i) // ����γ̺�
	{
		cin >> (*G).vertices[i].data;
		(*G).vertices[i].firstarc = NULL;
	}

	cout << "������" << (*G).vexnum << "���γ̵�ѧ��ֵ:" << endl;
	for (i = 0;i < (*G).vexnum;++i) // ����ѧ��
	{
		cin >> (*G).vertices[i].grades ;
	}
 
	for (k = 0;k < (*G).vexnum;++k) // �����������
	{
		cout << "������ " << (*G).vertices[k].data << " �����޿γ�(�����޿γ���ֱ������0)" << endl;
		cin >> va;
		while (va[0] != '0')
		{
			i = LocateVex(*G, va);//��ͷ
			j = k;//��β
			p = (node*)malloc(sizeof(node));
			p->adjvex = j;
			p->nextarc = (*G).vertices[i].firstarc; // ���ڱ�ͷ
			(*G).vertices[i].firstarc = p;
			cout << "      ��������� " << (*G).vertices[k].data << " �����޿γ�(ֻ��������Щ��ֱ������0)" << endl;
			cin >> va;
		}
	}
	return 1;
}

void Display(ALGraph G)// ���ͼ���ڽӾ���G
{ 
	int i;
	node *p;
    cout << "����ͼ" << endl;
	cout << "\n" << G.vexnum << "������" << endl;
	for (i = 0;i < G.vexnum;++i)
		cout << G.vertices[i].data << " ";
	cout << "\n" << G.arcnum << "����(��)" << endl;
	for (i = 0;i < G.vexnum;i++)
	{
		p = G.vertices[i].firstarc;
		while (p)
		{
			cout << G.vertices[i].data << "->" << G.vertices[p->adjvex].data << " ";
			p = p->nextarc;
		}
		cout << endl;
	}
}
void FindInDegree(ALGraph G, int indegree[])//�󶥵�����
{ 
	int i;
	node *p;
	for (i = 0;i < G.vexnum;i++) indegree[i] = 0; // ����ֵ		
	for (i = 0;i < G.vexnum;i++)
	{
		p = G.vertices[i].firstarc;
		while (p)
		{
			indegree[p->adjvex]++;
			p = p->nextarc;
		}
	}
}

/*ջ����*/
typedef int SElemType; // ջ����
#define STACK_INIT_SIZE 10 //�洢�ռ��ʼ������
#define STACKINCREMENT 2 // �洢�ռ��������
typedef struct SqStack
{
	SElemType *base; // ��ջ����֮ǰ������֮��base��ֵΪNULL
	SElemType *top; // ջ��ָ��
	int stacksize; //��ǰ�ѷ���Ĵ洢�ռ䣬��Ԫ��Ϊ��λ
}SqStack;

// ˳��ջ�Ļ�������
int InitStack(SqStack *S)// ����һ����ջS
{ 
	(*S).base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	if (!(*S).base)
		exit(OVERFLOW);
	(*S).top = (*S).base;
	(*S).stacksize = STACK_INIT_SIZE;
	return 1;
}

int StackEmpty(SqStack S)// ��ջSΪ��ջ���򷵻�1�����򷵻�0
{ 
	if (S.top == S.base)
		return 1;
	else
		return 0;
}

int Pop(SqStack *S, SElemType *e)// ��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������1�����򷵻�0
{ 
	if ((*S).top == (*S).base)
		return 0;
	*e = *--(*S).top;
	return 1;
}

int Push(SqStack *S, SElemType e) // ����Ԫ��eΪ�µ�ջ��Ԫ��
{
	if ((*S).top - (*S).base >= (*S).stacksize)
	{
		(*S).base = (SElemType *) realloc ( (*S).base, ( (*S).stacksize + STACKINCREMENT) * sizeof(SElemType));
		if ( !(*S).base ) exit(OVERFLOW);
		(*S).top = (*S).base + (*S).stacksize;
		(*S).stacksize += STACKINCREMENT;
	}
	*((*S).top)++ = e;
	return 1;
}

int TopologicalSort(ALGraph G) // ����ͼG�����ڽӱ�洢�ṹ����G�޻�·,�����G�Ķ����һ���������в�����1, ���򷵻�0
{

	int i, k, j = 0, count, indegree[MAX_VERTEX_NUM];
	AdjList Temp; //���������ѧ�ڿγ�ʱ��
	SqStack S;
	node *p;
	FindInDegree(G, indegree);  // �Ը����������indegree[0..vernum-1]
	InitStack(&S);  // ��ʼ��ջ
	for (i = 0;i < G.vexnum;++i)  //������ȶ���ջS
		if (!indegree[i]) Push(&S, i);  // ���Ϊ0�߽�ջ
	count = 0; // ������������
	while (!StackEmpty(S))
	{ 
		Pop(&S, &i);
		cout << "" << G.vertices[i].data << "(" << G.vertices[i].grades << "��) ->  ";
		Temp[j++] = G.vertices[i];//����ǰ���������б�������
	
		++count;	// ���i�Ŷ��㲢����
		for (p =G.vertices[i].firstarc; p; p=p->nextarc)// ��i�Ŷ����ÿ���ڽӵ����ȼ�1
		{ 
			k = p->adjvex;
			if (!(--indegree[k])) // ����ȼ�Ϊ0,����ջ
				Push(&S, k);
		}
	}
	if (count < G.vexnum)
	{
		cout << "������ͼ�л�·�޷������������" << endl;
		return 0;
	}
	else cout << "   Ϊһ����������" << endl;

	cout << endl;

	int q = 1,  Z = 0, X = 0;
	while (q <= TotalTerms)
	{
		int C = Temp[Z].grades ;
		cout << "��" << q << "��ѧ��Ӧѧ�γ�:";
		while (C <= MaxScores)
		{
			C = C + Temp[Z].grades;
			if (Z < G.vexnum)	cout << Temp[Z].data << " ";
			++Z;
		}
		cout << endl;
		if (q == TotalTerms)cout << "�γ̱�����ɣ�" << endl;
		q++;
	}

	return 1;
}
int main()
{
	ALGraph f;
	cout << "**********��ѧ�ƻ���������**********" << endl;
	cout << endl;
	cout << "������ѧ������:" << endl;
	cin >> TotalTerms;
	cout << "������ѧ�ڵ�ѧ������:" << endl;
	cin >> MaxScores;
	CreateGraph(&f);
	Display(f);
	TopologicalSort(f);
	return 0;
}

