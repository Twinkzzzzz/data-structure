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
#define MAXCLASS 100  //顶点字符串的最大长度
#define MAX_VERTEX_NUM 100 //最大顶点数

//typedef int int; // 函数的类型,其值是函数结果状态代码，如1等
typedef char VertexType[MAX_NAME]; 

int TotalTerms ; //学期总数
int MaxScores; //学分上限

/* ----图的邻接表存储表示---- */
typedef struct node
{
	int adjvex; // 该弧所指向的顶点的位置
	struct node *nextarc; //指向下一条弧的指针
}node; // 表结点

typedef struct
{
	char data[101];  //顶点信息
	int grades;  //存储学分信息
	node *firstarc; //指向第一条依附该顶点的弧的指针
}VNode, AdjList[MAX_VERTEX_NUM]; // 头结点

typedef struct
{
	AdjList vertices; //vertices 存储课程名
	int vexnum, arcnum; // 图的当前顶点数和弧数
}ALGraph;


/*  图的邻接表存储的基本操作 */
int LocateVex(ALGraph G, char u[])	// 若G中存在顶点u,则返回该顶点在图中位置;否则返回-1
{ 
	int i;
	for (i = 0;i < G.vexnum;++i)
		if (strcmp(u, G.vertices[i].data) == 0)
			return i;
	return -1;
}

int CreateGraph(ALGraph *G)  //采用邻接表存储结构,构造没有相关信息的图G
{ 
	int i, j, k;
	char va[101];
	node *p;
	cout << "请输入教学计划的课程数: " << endl;
	cin >> (*G).vexnum;
	cout << "请输入各个课程的先修课程的总和(弧总数): " << endl;
	cin >> (*G).arcnum;

	cout << "请输入" << (*G).vexnum << "个课程的课程号(最多" << MAX_NAME << "个字符,数字+字母):" << endl;
	for (i = 0;i < (*G).vexnum;++i) // 输入课程号
	{
		cin >> (*G).vertices[i].data;
		(*G).vertices[i].firstarc = NULL;
	}

	cout << "请输入" << (*G).vexnum << "个课程的学分值:" << endl;
	for (i = 0;i < (*G).vexnum;++i) // 输入学分
	{
		cin >> (*G).vertices[i].grades ;
	}
 
	for (k = 0;k < (*G).vexnum;++k) // 构造表结点链表
	{
		cout << "请输入 " << (*G).vertices[k].data << " 的先修课程(无先修课程则直接输入0)" << endl;
		cin >> va;
		while (va[0] != '0')
		{
			i = LocateVex(*G, va);//弧头
			j = k;//弧尾
			p = (node*)malloc(sizeof(node));
			p->adjvex = j;
			p->nextarc = (*G).vertices[i].firstarc; // 插在表头
			(*G).vertices[i].firstarc = p;
			cout << "      请继续输入 " << (*G).vertices[k].data << " 的先修课程(只有以上那些则直接输入0)" << endl;
			cin >> va;
		}
	}
	return 1;
}

void Display(ALGraph G)// 输出图的邻接矩阵G
{ 
	int i;
	node *p;
    cout << "有向图" << endl;
	cout << "\n" << G.vexnum << "个顶点" << endl;
	for (i = 0;i < G.vexnum;++i)
		cout << G.vertices[i].data << " ";
	cout << "\n" << G.arcnum << "条弧(边)" << endl;
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
void FindInDegree(ALGraph G, int indegree[])//求顶点的入度
{ 
	int i;
	node *p;
	for (i = 0;i < G.vexnum;i++) indegree[i] = 0; // 赋初值		
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

/*栈定义*/
typedef int SElemType; // 栈类型
#define STACK_INIT_SIZE 10 //存储空间初始分配量
#define STACKINCREMENT 2 // 存储空间分配增量
typedef struct SqStack
{
	SElemType *base; // 在栈构造之前和销毁之后，base的值为NULL
	SElemType *top; // 栈顶指针
	int stacksize; //当前已分配的存储空间，以元素为单位
}SqStack;

// 顺序栈的基本操作
int InitStack(SqStack *S)// 构造一个空栈S
{ 
	(*S).base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	if (!(*S).base)
		exit(OVERFLOW);
	(*S).top = (*S).base;
	(*S).stacksize = STACK_INIT_SIZE;
	return 1;
}

int StackEmpty(SqStack S)// 若栈S为空栈，则返回1，否则返回0
{ 
	if (S.top == S.base)
		return 1;
	else
		return 0;
}

int Pop(SqStack *S, SElemType *e)// 若栈不空，则删除S的栈顶元素，用e返回其值，并返回1；否则返回0
{ 
	if ((*S).top == (*S).base)
		return 0;
	*e = *--(*S).top;
	return 1;
}

int Push(SqStack *S, SElemType e) // 插入元素e为新的栈顶元素
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

int TopologicalSort(ALGraph G) // 有向图G采用邻接表存储结构。若G无回路,则输出G的顶点的一个拓扑序列并返回1, 否则返回0
{

	int i, k, j = 0, count, indegree[MAX_VERTEX_NUM];
	AdjList Temp; //后面输出个学期课程时到
	SqStack S;
	node *p;
	FindInDegree(G, indegree);  // 对各顶点求入度indegree[0..vernum-1]
	InitStack(&S);  // 初始化栈
	for (i = 0;i < G.vexnum;++i)  //建零入度顶点栈S
		if (!indegree[i]) Push(&S, i);  // 入度为0者进栈
	count = 0; // 对输出顶点计数
	while (!StackEmpty(S))
	{ 
		Pop(&S, &i);
		cout << "" << G.vertices[i].data << "(" << G.vertices[i].grades << "分) ->  ";
		Temp[j++] = G.vertices[i];//将当前的拓扑序列保存起来
	
		++count;	// 输出i号顶点并计数
		for (p =G.vertices[i].firstarc; p; p=p->nextarc)// 对i号顶点的每个邻接点的入度减1
		{ 
			k = p->adjvex;
			if (!(--indegree[k])) // 若入度减为0,则入栈
				Push(&S, k);
		}
	}
	if (count < G.vexnum)
	{
		cout << "此有向图有回路无法完成拓扑排序" << endl;
		return 0;
	}
	else cout << "   为一个拓扑序列" << endl;

	cout << endl;

	int q = 1,  Z = 0, X = 0;
	while (q <= TotalTerms)
	{
		int C = Temp[Z].grades ;
		cout << "第" << q << "个学期应学课程:";
		while (C <= MaxScores)
		{
			C = C + Temp[Z].grades;
			if (Z < G.vexnum)	cout << Temp[Z].data << " ";
			++Z;
		}
		cout << endl;
		if (q == TotalTerms)cout << "课程编制完成！" << endl;
		q++;
	}

	return 1;
}
int main()
{
	ALGraph f;
	cout << "**********教学计划编制问题**********" << endl;
	cout << endl;
	cout << "请输入学期总数:" << endl;
	cin >> TotalTerms;
	cout << "请输入学期的学分上限:" << endl;
	cin >> MaxScores;
	CreateGraph(&f);
	Display(f);
	TopologicalSort(f);
	return 0;
}

