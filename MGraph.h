/*
*
*  V0.2015112721	  ����FLoyd�㷨���������һ�Զ���֮������·��
*  v0.1.201511281207  ����Dijkstra�㷨����Դ���·��
*/
#include<iostream>
#include <malloc.h>
#include <conio.h>
using namespace std;

#define ERROR -1
/* ͼ���ڽӾ����ʾ�� */

#define MaxVertexNum 100        /* ��󶥵�����Ϊ100 */
#define INFINITY 99              /* ����Ϊ˫�ֽ��޷������������ֵ65535*/
typedef int Vertex;             /* �ö����±��ʾ����,Ϊ���� */
typedef int WeightType;         /* �ߵ�Ȩֵ��Ϊ���� */
typedef char DataType;          /* ����洢������������Ϊ�ַ��� */
bool  Visited[MaxVertexNum];

/* �ߵĶ��� */
typedef struct ENode *PtrToENode;
struct ENode{
	Vertex V1, V2;      /* �����<V1, V2> */
	WeightType Weight;  /* Ȩ�� */
};
typedef PtrToENode Edge;

/* ͼ���Ķ��� */
typedef struct GNode *PtrToGNode;
struct GNode{
	int Nv;  /* ������ */
	int Ne;  /* ����   */
	WeightType G[MaxVertexNum][MaxVertexNum];  /* �ڽӾ��� */
	DataType Data[MaxVertexNum];               /* �涥������� */
	/* ע�⣺�ܶ�����£����������ݣ���ʱData[]���Բ��ó��� */
};
typedef PtrToGNode MGraph; /* ���ڽӾ���洢��ͼ���� */


MGraph CreateMGraph(int VertexNum)
{ /* ��ʼ��һ����VertexNum�����㵫û�бߵ�ͼ */
	Vertex V, W;
	MGraph Graph;

	Graph = (MGraph)malloc(sizeof(struct GNode)); /* ����ͼ */
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	/* ��ʼ���ڽӾ��� */
	/* ע�⣺����Ĭ�϶����Ŵ�0��ʼ����(Graph->Nv - 1) */
	for (V = 0; V<Graph->Nv; V++)
		for (W = 0; W<Graph->Nv; W++)
			Graph->G[V][W] = INFINITY;

	return Graph;
}

void InsertEdge(MGraph Graph, Edge E)
{
	/* ����� <V1, V2> */
	Graph->G[E->V1][E->V2] = E->Weight;
	/* ��������ͼ����Ҫ�����<V2, V1> */
	//Graph->G[E->V2][E->V1] = E->Weight;
}

MGraph BuildMGraph()
{
	MGraph Graph;
	Edge E;
	Vertex V;
	int Nv, i;

	cout << "���붥��ĸ����ͱ���" << endl;
	cin >> Nv;   /* ���붥����� */
	Graph = CreateMGraph(Nv); /* ��ʼ����Nv�����㵫û�бߵ�ͼ */

	cin >> Graph->Ne; /* ������� */
	if (Graph->Ne != 0) { /* ����б� */
		E = (Edge)malloc(sizeof(struct ENode)); /* �����߽�� */
		/* ����ߣ���ʽΪ"��� �յ� Ȩ��"�������ڽӾ��� */
		for (i = 0; i<Graph->Ne; i++) {
			cout << "����ߣ���ʽΪ ��� �յ� Ȩ�� " << endl;
			cin >> E->V1 >> E->V2 >> E->Weight;
			/* ע�⣺���Ȩ�ز������ͣ�Weight�Ķ����ʽҪ�� */
			InsertEdge(Graph, E);
		}
	}

	/* ������������ݵĻ����������� */
	/*for (V = 0; V < Graph->Nv; V++)
	{
	cout << "��" << V << "����������� " << endl;
	cin >> Graph->Data[V];
	}*/

	return Graph;
}

void ShowGraph(MGraph Graph){

	/*�ڽӾ�����ʾ*/
	cout << endl << "�ڽӾ���" << endl;
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
{ /* ����δ����¼������dist��С�� */
	Vertex MinV, V;
	int MinDist = INFINITY;

	for (V = 0; V<Graph->Nv; V++) {
		if (collected[V] == false && dist[V]<MinDist) {
			/* ��Vδ����¼����dist[V]��С */
			MinDist = dist[V]; /* ������С���� */
			MinV = V; /* ���¶�Ӧ���� */
		}
	}
	if (MinDist < INFINITY) /* ���ҵ���Сdist */
		return MinV; /* ���ض�Ӧ�Ķ����±� */
	else return ERROR;  /* �������Ķ��㲻���ڣ����ش����� */
}

bool ShortestPath_Dijkstra(MGraph Graph, int dist[], int path[], Vertex S)
{
	int collected[MaxVertexNum];
	Vertex V, W;

	/* ��ʼ�����˴�Ĭ���ڽӾ����в����ڵı���INFINITY��ʾ */
	for (V = 0; V<Graph->Nv; V++) {
		dist[V] = Graph->G[S][V];
		path[V] = -1;
		collected[V] = false;
	}
	/* �Ƚ�������뼯�� */
	dist[S] = 0;
	collected[S] = true;

	while (1) {
		/* V = δ����¼������dist��С�� */
		V = FindMinDist(Graph, dist, collected);
		if (V == ERROR) /* ��������V������ */
			break;      /* �㷨���� */
		collected[V] = true;  /* ��¼V */
		for (W = 0; W<Graph->Nv; W++) /* ��ͼ�е�ÿ������W */
			/* ��W��V���ڽӵ㲢��δ����¼ */
			if (collected[W] == false && Graph->G[V][W]<INFINITY) {
				if (Graph->G[V][W]<0) /* ���и��� */
					return false; /* ������ȷ��������ش����� */
				/* ����¼Vʹ��dist[W]��С */
				if (dist[V] + Graph->G[V][W] < dist[W]) {
					dist[W] = dist[V] + Graph->G[V][W]; /* ����dist[W] */
					path[W] = V; /* ����S��W��·�� */
				}
			}
	} /* while����*/
	return true; /* �㷨ִ����ϣ�������ȷ��� */
}
/*��ӡ���������·��*/
void PrintPath(Vertex path[], int begin, int end)
{
	/*ʡ�Ա߽���*/
	int index;           /*��ǰ·���±�*/
	index = end;
	while (index >= 0)
	{
		cout << index << "<-";   /*��ӡһ������*/
		index = path[index];
	}
	cout << begin << "<-begin";
	cout << endl;
}