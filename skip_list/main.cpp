#include <iostream>
#include "skip_list.h"


int main(int argc, char** argv)
{
	SkipList<int, std::string> skipList(INT_MAX, INT_MAX, 0.5);
    skipList.insert(std::make_pair(1, "jack"));
	return 0;
}