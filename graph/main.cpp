#include "graph.hpp"


/// <summary>
/// leetcode 2699
/// </summary>
class Solution {
public:
    std::vector<std::vector<int>> modifiedGraphEdges(
        int n, 
        std::vector<std::vector<int>>& edges, 
        int source, 
        int destination,
        int target) {
        int k = 0;
        for (const auto& e : edges) {
            if (e[2] == -1) {
                ++k;
            }
        }

        if (dijkstra(source, destination, construct(n, edges, 0, target)) > target) {
            return {};
        }
        if (dijkstra(source, destination, construct(n, edges, static_cast<long long>(k) * (target - 1), target)) < target) {
            return {};
        }

        long long left = 0, right = static_cast<long long>(k) * (target - 1), ans = 0;
        while (left <= right) {
            long long mid = (left + right) / 2;
            if (dijkstra(source, destination, construct(n, edges, mid, target)) >= target) {
                ans = mid;
                right = mid - 1;
            }
            else {
                left = mid + 1;
            }
        }

        for (auto& e : edges) {
            if (e[2] == -1) {
                if (ans >= target - 1) {
                    e[2] = target;
                    ans -= (target - 1);
                }
                else {
                    e[2] = 1 + ans;
                    ans = 0;
                }
            }
        }

        return edges;
    }

    long long dijkstra(int source, int destination, const std::vector<std::vector<int>>& adj_matrix) {
        // 朴素的 dijkstra 算法
        // adj_matrix 是一个邻接矩阵
        int n = adj_matrix.size();
        std::vector<long long> dist(n, INT_MAX / 2);
        std::vector<int> used(n);
        dist[source] = 0;

        for (int round = 0; round < n - 1; ++round) {
            int u = -1;
            for (int i = 0; i < n; ++i) {
                if (!used[i] && (u == -1 || dist[i] < dist[u])) {
                    u = i;
                }
            }
            used[u] = true;
            for (int v = 0; v < n; ++v) {
                if (!used[v] && adj_matrix[u][v] != -1) {
                    dist[v] = std::min(dist[v], dist[u] + adj_matrix[u][v]);
                }
            }
        }

        return dist[destination];
    }

    std::vector<std::vector<int>> construct(int n, const std::vector<std::vector<int>>& edges, long long idx, int target) {
        // 需要构造出第 idx 种不同的边权情况，返回一个邻接矩阵
        std::vector<std::vector<int>> adj_matrix(n, std::vector<int>(n, -1));
        for (const auto& e : edges) {
            int u = e[0], v = e[1], w = e[2];
            if (w != -1) {
                adj_matrix[u][v] = adj_matrix[v][u] = w;
            }
            else {
                if (idx >= target - 1) {
                    adj_matrix[u][v] = adj_matrix[v][u] = target;
                    idx -= (target - 1);
                }
                else {
                    adj_matrix[u][v] = adj_matrix[v][u] = 1 + idx;
                    idx = 0;
                }
            }
        }
        return adj_matrix;
    }
};

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

	auto res = graph.dijkstra(1);

	return 0;
}