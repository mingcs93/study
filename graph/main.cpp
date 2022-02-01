#include "graph.hpp"

int main(int argc, char** argv)
{
	std::vector<std::array<int64_t, 3>> rawDatas{
		{1, 2, 7},
		{1, 3, 2},
		{1, 4, 5}, 
		{2, 1, 7}, 
		{2, 3, 2},
		{3, 1, 2},
		{3, 2, 2}, 
		{3, 4, 1}, 
		{4, 1, 5}, 
		{4, 3, 1}, };


	Graph graph;
	graph.createGraph(rawDatas);
	graph.bfs();
	graph.dfs();
	graph.kruskalMST();

	return 0;
}