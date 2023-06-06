#pragma once

class UnionFind {
	struct UnionFindNode {
		int32_t parent;
		bool root;

		UnionFindNode()
			: parent(1)
			, root(true) {}
	};

public:
	void initialize(int32_t numberOfElements) {
		m_size = numberOfElements;
		m_node = new UnionFindNode[numberOfElements+1];
	}

	int32_t find(int32_t thrElement) {
		int32_t theRoot = thrElement;
		while (!m_node[theRoot].root) {
			theRoot = m_node[theRoot].parent;
		}

		int32_t currentNode = thrElement;
		while (currentNode != theRoot) {
			int32_t parentNode = m_node[currentNode].parent;
			m_node[currentNode].parent = theRoot;
			currentNode = parentNode;
		}

		return theRoot;
	}

	void unite(int32_t rootA, int32_t rootB) {
		if (m_node[rootA].parent < m_node[rootB].parent) {
			m_node[rootB].parent += m_node[rootA].parent;
			m_node[rootA].root = false;
			m_node[rootA].parent = rootB;
		}
		else {
			m_node[rootA].parent += m_node[rootB].parent;
			m_node[rootB].root = false;
			m_node[rootB].parent = rootA;
		}
	}

	int32_t getMaxUnionCount() {
		int res = INT_MIN;
		for (int i = 0; i < m_size; i++) {
			if (m_node[i].root) {
				res = std::max(res, m_node[i].parent);
			}
		}

		return res;
	}

private:
	UnionFindNode* m_node;
	int32_t m_size{ 0 };
};