/*
*
*  V0.2015112721	  新增FLoyd算法：求得任意一对顶点之间的最短路径
*  v0.1.201511281207  新增Dijkstra算法：单源最短路径
*/
#include<iostream>
#include <malloc.h>
#include <conio.h>
using namespace std;

#define ERROR -1
/* 图的邻接矩阵表示法 */

#define MaxVertexNum 100        /* 最大顶点数设为100 */
#define INFINITY 99              /* ∞设为双字节无符号整数的最大值65535*/
typedef int Vertex;             /* 用顶点下标表示顶点,为整型 */
typedef int WeightType;         /* 边的权值设为整型 */
typedef char DataType;          /* 顶点存储的数据类型设为字符型 */
bool  Visited[MaxVertexNum];

/* 边的定义 */
typedef struct ENode *PtrToENode;
struct ENode{
	Vertex V1, V2;      /* 有向边<V1, V2> */
	WeightType Weight;  /* 权重 */
};
typedef PtrToENode Edge;

/* 图结点的定义 */
typedef struct GNode *PtrToGNode;
struct GNode{
	int Nv;  /* 顶点数 */
	int Ne;  /* 边数   */
	WeightType G[MaxVertexNum][MaxVertexNum];  /* 邻接矩阵 */
	DataType Data[MaxVertexNum];               /* 存顶点的数据 */
	/* 注意：很多情况下，顶点无数据，此时Data[]可以不用出现 */
};
typedef PtrToGNode MGraph; /* 以邻接矩阵存储的图类型 */


MGraph CreateMGraph(int VertexNum)
{ /* 初始化一个有VertexNum个顶点但没有边的图 */
	Vertex V, W;
	MGraph Graph;

	Graph = (MGraph)malloc(sizeof(struct GNode)); /* 建立图 */
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	/* 初始化邻接矩阵 */
	/* 注意：这里默认顶点编号从0开始，到(Graph->Nv - 1) */
	for (V = 0; V<Graph->Nv; V++)
		for (W = 0; W<Graph->Nv; W++)
			Graph->G[V][W] = INFINITY;

	return Graph;
}

void InsertEdge(MGraph Graph, Edge E)
{
	/* 插入边 <V1, V2> */
	Graph->G[E->V1][E->V2] = E->Weight;
	/* 若是无向图，还要插入边<V2, V1> */
	//Graph->G[E->V2][E->V1] = E->Weight;
}

MGraph BuildMGraph()
{
	MGraph Graph;
	Edge E;
	Vertex V;
	int Nv, i;

	cout << "输入顶点的个数和边数" << endl;
	cin >> Nv;   /* 读入顶点个数 */
	Graph = CreateMGraph(Nv); /* 初始化有Nv个顶点但没有边的图 */

	cin >> Graph->Ne; /* 读入边数 */
	if (Graph->Ne != 0) { /* 如果有边 */
		E = (Edge)malloc(sizeof(struct ENode)); /* 建立边结点 */
		/* 读入边，格式为"起点 终点 权重"，插入邻接矩阵 */
		for (i = 0; i<Graph->Ne; i++) {
			cout << "读入边，格式为 起点 终点 权重 " << endl;
			cin >> E->V1 >> E->V2 >> E->Weight;
			/* 注意：如果权重不是整型，Weight的读入格式要改 */
			InsertEdge(Graph, E);
		}
	}

	/* 如果顶点有数据的话，读入数据 */
	/*for (V = 0; V < Graph->Nv; V++)
	{
	cout << "第" << V << "个顶点的数据 " << endl;
	cin >> Graph->Data[V];
	}*/

	return Graph;
}

void ShowGraph(MGraph Graph){

	/*邻接矩阵显示*/
	cout << endl << "邻接矩阵" << endl;
	for (int i = 0; i < Graph->Nv; ++i)
	{
		cout << "  " << i;
	}
	cout << endl;
	for (int i = 0; i < Graph->Nv; ++i)
	{
		cout << i << "|";
		for (int j = 0; j<Graph->Nv; ++j)
		{
			cout << Graph->G[i][j] << "  ";
		}
		cout << endl;
	}
}

Vertex FindMinDist(MGraph Graph, int dist[], int collected[])
{ /* 返回未被收录顶点中dist最小者 */
	Vertex MinV, V;
	int MinDist = INFINITY;

	for (V = 0; V<Graph->Nv; V++) {
		if (collected[V] == false && dist[V]<MinDist) {
			/* 若V未被收录，且dist[V]更小 */
			MinDist = dist[V]; /* 更新最小距离 */
			MinV = V; /* 更新对应顶点 */
		}
	}
	if (MinDist < INFINITY) /* 若找到最小dist */
		return MinV; /* 返回对应的顶点下标 */
	else return ERROR;  /* 若这样的顶点不存在，返回错误标记 */
}

bool ShortestPath_Dijkstra(MGraph Graph, int dist[], int path[], Vertex S)
{
	int collected[MaxVertexNum];
	Vertex V, W;

	/* 初始化：此处默认邻接矩阵中不存在的边用INFINITY表示 */
	for (V = 0; V<Graph->Nv; V++) {
		dist[V] = Graph->G[S][V];
		path[V] = -1;
		collected[V] = false;
	}
	/* 先将起点收入集合 */
	dist[S] = 0;
	collected[S] = true;

	while (1) {
		/* V = 未被收录顶点中dist最小者 */
		V = FindMinDist(Graph, dist, collected);
		if (V == ERROR) /* 若这样的V不存在 */
			break;      /* 算法结束 */
		collected[V] = true;  /* 收录V */
		for (W = 0; W<Graph->Nv; W++) /* 对图中的每个顶点W */
			/* 若W是V的邻接点并且未被收录 */
			if (collected[W] == false && Graph->G[V][W]<INFINITY) {
				if (Graph->G[V][W]<0) /* 若有负边 */
					return false; /* 不能正确解决，返回错误标记 */
				/* 若收录V使得dist[W]变小 */
				if (dist[V] + Graph->G[V][W] < dist[W]) {
					dist[W] = dist[V] + Graph->G[V][W]; /* 更新dist[W] */
					path[W] = V; /* 更新S到W的路径 */
				}
			}
	} /* while结束*/
	return true; /* 算法执行完毕，返回正确标记 */
}
/*打印任意两点的路径*/
void PrintPath(Vertex path[], int begin, int end)
{
	/*省略边界检查*/
	int index;           /*当前路径下标*/
	index = end;
	while (index >= 0)
	{
		cout << index << "<-";   /*打印一个顶点*/
		index = path[index];
	}
	cout << begin << "<-begin";
	cout << endl;
}