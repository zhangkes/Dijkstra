// Dijkstra.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"MGraph.h"

int _tmain(int argc, _TCHAR* argv[])
{
	cout << "有权图的单源最短路算法" << endl;
	MGraph Graph = BuildMGraph();
	MGraph MST = NULL;
	ShowGraph(Graph);
	cout << endl << "--------------------" << endl;
	int dist[MaxVertexNum];
	int path[MaxVertexNum];
loop:cout << "请输入要求任意两点" << endl;
	int begin, end;
	cin >> begin >> end;
	ShortestPath_Dijkstra(Graph, dist, path, begin);
	PrintPath(path, begin, end);
	cout << "*********************" << endl;
	goto loop;
	return 0;
}

