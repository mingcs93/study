#include <iostream>
#include "union_find.hpp"
#include <vector>

int main(int argc, char** argv)
{
    std::vector<int> nums{ 5,4,0,3,1,6,2 };
    UnionFind myUnion;
    myUnion.initialize(nums.size());
    for (size_t idx = 0; idx < nums.size(); idx++) {
        int root1 = myUnion.find(idx);
        int root2 = myUnion.find(nums.at(idx));
        if (root1 == root2) continue;
        myUnion.unite(root1, root2);
    }

    int32_t res = myUnion.getMaxUnionCount();

	return 0;
}