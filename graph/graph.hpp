#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <array>
#include <queue>
#include <stack>

struct Edge;
struct Node
{
	int64_t value;
	uint32_t in;  //该节点入度
	uint32_t out; //该节点出度
	std::vector<std::shared_ptr<Node>> nexts;
	std::vector<std::shared_ptr<Edge>> edges; //若为无向图，则每两个节点之间包含两条边

	Node(int64_t _value)
		: value(_value)
		, in(0)
		, out(0)
	{}
};

struct Edge
{
	int64_t weight;
	std::shared_ptr<Node> from;
	std::shared_ptr<Node> to;

	Edge(int64_t _weight, const std::shared_ptr<Node>& _from, const std::shared_ptr<Node>& _to)
		: weight(_weight)
		, from(_from)
		, to(_to)
	{}
};

struct EdgeCompare
{
	bool operator()(const std::shared_ptr<Edge>& l, const std::shared_ptr<Edge>& r)
	{
		return l->weight > r->weight;
	}
};

class UnionFind
{
public:
	UnionFind(const std::unordered_map<int64_t, std::shared_ptr<Node>>& nodes)
	{
		for (const auto& item : nodes)
		{
			auto tmp = std::make_shared<std::unordered_set<std::shared_ptr<Node>>>();
			tmp->insert(item.second);
			m_unions[item.second] = tmp;
		}
	}

	bool isSameSet(const std::shared_ptr<Node>& from, const std::shared_ptr<Node>& to)
	{
		return m_unions[from] == m_unions[to];
	}

	void unionSet(const std::shared_ptr<Node>& from, const std::shared_ptr<Node>& to)
	{
		auto fromSet = m_unions[from];
		auto toSet = m_unions[to];
		fromSet->insert(toSet->begin(), toSet->end());
		m_unions[to] = fromSet;
	}

private:
	std::unordered_map<std::shared_ptr<Node>, std::shared_ptr<std::unordered_set<std::shared_ptr<Node>>>> m_unions;
};

class Graph
{
public:
	void createGraph(const std::vector<std::array<int64_t, 3>>& matrix) //{[from, to, weight]}
	{
		for (const auto& row : matrix)
		{
			int64_t from = row.at(0);
			int64_t to = row.at(1);
			int64_t weight = row.at(2);

			if (m_nodes.find(from) == m_nodes.cend())
			{
				std::shared_ptr<Node> tmp{std::make_shared<Node>(from)};
				m_nodes[from] = tmp;
			}
			if (m_nodes.find(to) == m_nodes.cend())
			{
				std::shared_ptr<Node> tmp{ std::make_shared<Node>(to) };
				m_nodes[to] = tmp;
			}

			std::shared_ptr<Node> fromNode = m_nodes[from];
			std::shared_ptr<Node> toNode = m_nodes[to];
			std::shared_ptr<Edge> edge{ std::make_shared<Edge>(weight, fromNode, toNode) };

			fromNode->nexts.push_back(toNode);
			fromNode->out++;
			fromNode->edges.push_back(edge);
			toNode->in++;
			m_edges.insert(edge);
		}
	}

	void bfs(const std::shared_ptr<Node>& node = nullptr)
	{
		std::shared_ptr<Node> first = node;
		if (first == nullptr)
		{
			first = m_nodes.begin()->second;
		}

		std::queue<std::shared_ptr<Node>> qNode;
		std::unordered_set<std::shared_ptr<Node>> visited;
		qNode.push(first);
		visited.insert(first);

		while (!qNode.empty())
		{
			std::shared_ptr<Node> cur = qNode.front();
			qNode.pop();
			std::cout << cur->value << std::endl;

			for (const auto& next : cur->nexts)
			{
				if (visited.find(next) == visited.cend())
				{
					qNode.push(next);
					visited.insert(next);
				}
			}
		}
	}

	void dfs(const std::shared_ptr<Node>& node = nullptr)
	{
		std::shared_ptr<Node> first = node;
		if (first == nullptr)
		{
			first = m_nodes.begin()->second;
		}

		std::stack<std::shared_ptr<Node>> sNode;
		std::unordered_set<std::shared_ptr<Node>> s;
		sNode.push(first);
		s.insert(first);
		std::cout << first->value << std::endl;

		while (!sNode.empty())
		{
			std::shared_ptr<Node> cur = sNode.top();
			sNode.pop();
			for (const auto& next : cur->nexts)
			{
				if (s.find(next) == s.cend())
				{
					sNode.push(cur);
					sNode.push(next);
					s.insert(next);
					std::cout << next->value << std::endl;
					break;
				}
			}
		}
	}

	/// <summary>
	/// 拓扑排序, 有向无环图
	/// </summary>
	/// <returns></returns>
	std::vector<std::shared_ptr<Node>> sortedTopology()
	{
		std::queue<std::shared_ptr<Node>> zeroInQueue;  //入度为0的节点队列
		std::unordered_map<std::shared_ptr<Node>, uint32_t> inMap;  //某一个node对应剩余入度数

		for (const auto& item : m_nodes)
		{
			inMap.insert(std::make_pair(item.second, item.second->in));
			if (item.second->in == 0)
			{
				zeroInQueue.push(item.second);
			}
		}

		std::vector<std::shared_ptr<Node>> res;
		while (!zeroInQueue.empty())
		{
			std::shared_ptr<Node> cur = zeroInQueue.front();
			zeroInQueue.pop();
			res.push_back(cur);
			for (const auto& next : cur->nexts)
			{
				inMap[next]--;
				if (inMap[next] == 0)
				{
					zeroInQueue.push(next);
				}
			}
		}

		return res;
	}

	
	/// <summary>
	/// k算法，最小生成树，需为无向图
	/// </summary>
	/// <returns></returns>
	std::vector<std::shared_ptr<Edge>> kruskalMST()
	{
		std::priority_queue<std::shared_ptr<Edge>, std::vector<std::shared_ptr<Edge>>, EdgeCompare> edgePriorityQueue;
		for (const auto& edge : m_edges)
		{
			edgePriorityQueue.push(edge);
		}

		UnionFind unionFind(m_nodes);
		std::vector<std::shared_ptr<Edge>> res;
		while (!edgePriorityQueue.empty())
		{
			std::shared_ptr<Edge> edge = edgePriorityQueue.top();
			edgePriorityQueue.pop();
			if (!unionFind.isSameSet(edge->from, edge->to))
			{
				res.push_back(edge);
				unionFind.unionSet(edge->from, edge->to);
			}
		}

		return res;
	}


	/// <summary>
	/// p算法，最小生成树
	/// </summary>
	/// <returns></returns>
	std::vector<std::shared_ptr<Edge>> primMST()
	{
		std::priority_queue<std::shared_ptr<Edge>, std::vector<std::shared_ptr<Edge>>, EdgeCompare> edgePriorityQueue;
		std::vector<std::shared_ptr<Edge>> res;
		std::unordered_set<std::shared_ptr<Node>> selectedNodes;

		for (const auto& node : m_nodes)
		{
			if (!selectedNodes.count(node.second))
			{
				selectedNodes.insert(node.second);
				for (const auto& edge : node.second->edges)  //由一个点解锁所有相邻的边
				{
					edgePriorityQueue.push(edge);
				}

				while (!edgePriorityQueue.empty())
				{
					std::shared_ptr<Edge> edge = edgePriorityQueue.top();  //弹出解锁的边中，最小的边
					edgePriorityQueue.pop();
					std::shared_ptr<Node> toNode = edge->to;  //可能是一个新的点
					if (!selectedNodes.count(toNode))
					{
						selectedNodes.insert(toNode);
						res.push_back(edge);
						for (const auto& nextEdge : toNode->edges)
						{
							edgePriorityQueue.push(nextEdge);
						}
					}
				}
			}
		}

		return res;
	}


	/// <summary>
	/// Dijkstra算法,求一个图中一个点到其他所有点的最短路径的算法
	/// 要求边的权重不能为负数（还是形成环的边的权重和不能为负数？）
	/// </summary>
	/// <param name="head"></param>
	/// <returns></returns>
	std::unordered_map<std::shared_ptr<Node>, int64_t> dijkstra(int64_t head)
	{
		std::unordered_map<std::shared_ptr<Node>, int64_t> distanceMap;
		distanceMap[m_nodes[head]] = 0;

		std::unordered_set<std::shared_ptr<Node>> selectedNode;
		std::shared_ptr<Node> minNode = getMinDistanceAndUnselectedNode(distanceMap, selectedNode);

		while (minNode != nullptr)
		{
			int64_t distance = distanceMap[minNode];
			for (const auto& edge : minNode->edges)
			{
				std::shared_ptr<Node> toNode = edge->to;
				if (distanceMap.find(toNode) == distanceMap.end())
				{
					distanceMap[toNode] = distance + edge->weight;
				}
				else
				{
					distanceMap[toNode] = std::min(distanceMap[toNode], distance + edge->weight);
				}
			}
			selectedNode.insert(minNode);
			minNode = getMinDistanceAndUnselectedNode(distanceMap, selectedNode);
		}
		return distanceMap;
	}


private:
	/// <summary>
	/// 从当前结果中选择路径最小的节点
	/// </summary>
	/// <param name="distanceMap"></param>
	/// <param name="touchedNodes"></param>
	/// <returns></returns>
	std::shared_ptr<Node> getMinDistanceAndUnselectedNode(
		const std::unordered_map<std::shared_ptr<Node>, int64_t>& distanceMap,
		const std::unordered_set<std::shared_ptr<Node>>& touchedNodes)
	{
		std::shared_ptr<Node> minNode = nullptr;
		int64_t minDistance = INT_MAX;
		for (const auto& item : distanceMap)
		{
			std::shared_ptr<Node> node = item.first;
			int64_t distance = item.second;
			if (!touchedNodes.count(node) && distance < minDistance)
			{
				minDistance = distance;
				minNode = node;
			}
		}
		return minNode;
	}

private:
	std::unordered_map<int64_t, std::shared_ptr<Node>> m_nodes;
	std::unordered_set<std::shared_ptr<Edge>> m_edges;
};