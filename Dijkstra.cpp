// Dijkstra.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include"MGraph.h"

int _tmain(int argc, _TCHAR* argv[])
{
	cout << "��Ȩͼ�ĵ�Դ���·�㷨" << endl;
	MGraph Graph = BuildMGraph();
	MGraph MST = NULL;
	ShowGraph(Graph);
	cout << endl << "--------------------" << endl;
	int dist[MaxVertexNum];
	int path[MaxVertexNum];
loop:cout << "������Ҫ����������" << endl;
	int begin, end;
	cin >> begin >> end;
	ShortestPath_Dijkstra(Graph, dist, path, begin);
	PrintPath(path, begin, end);
	cout << "*********************" << endl;
	goto loop;
	return 0;
}

