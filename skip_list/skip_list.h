#pragma once

/* 跳表实现 */

#include <iostream>
#include <cstdlib>  // RAND_MAX
#include <cmath>    // ceil()

template <typename K, typename E>
struct skipNode
{
    typedef std::pair<const K, E> pairType;

    pairType element;
    skipNode<K, E>** next;

    skipNode() {}

    skipNode(const pairType& thePair, int size) : element(thePair)
    {
        next = new skipNode<K, E>*[size];
    }
};

template <typename K, typename E>
class SkipList
{
public:
    SkipList() {}
    SkipList(K largeKey, int maxPairs, float prob);
    ~SkipList();

    // find, 如果找到返回指针，没有返回NULL
    std::pair<const K, E>* find(const K& theKey) const;
    // level，级的分配
    int level() const;
    // search，搜索
    skipNode<K, E>* search(const K& theKey) const;
    // insert， 插入操作
    void insert(const std::pair<const K, E>& thePair);
    // erase，删除操作
    void erase(const K& theKey);

private:
    float cutOff;               // 用来确定层数
    int levels;                 // 当前最大的非空链对
    int dSize;                  // 字典的数对个数
    int maxLevel;               // 允许的最大链表层数
    K tailKey;                  // 最大关键字
    skipNode<K, E>* headerNode; // 头结点指针
    skipNode<K, E>* tailNode;   // 尾节点指针
    skipNode<K, E>** last;      // last[i] 表示i层的最后节点
};


template <typename K, typename E>
SkipList<K, E>::SkipList(K largeKey, int maxPairs, float prob)
{
    // 构造函数，关键字小于largeKey且数对个数size最多为maxPairs, 0 < prob < 1;
    cutOff = prob * RAND_MAX;
    maxLevel = (int)ceil(logf((float)maxPairs) / logf(1 / prob)) - 1;   // 向上取整
    levels = 0;
    dSize = 0;
    tailKey = largeKey;

    // 生产头结点，尾节点和数组last
    std::pair<K, E> tailPair;
    tailPair.first = tailKey;
    headerNode = new skipNode<K, E>(tailPair, maxLevel + 1);
    tailNode = new skipNode<K, E>(tailPair, 0);
    last = new skipNode<K, E>*[maxLevel + 1];

    for (int i = 0; i <= maxLevel; i++)
        headerNode->next[i] = tailNode;
}

template <typename K, typename E>
SkipList<K, E>::~SkipList()
{
    // Empty
}

template <typename K, typename E>
std::pair<const K, E>* SkipList<K, E>::find(const K& theKey) const
{
    // 返回匹配的数对的指针
    // 如果关键字大于最大关键字，返回NULL
    if (theKey >= tailKey)
        return NULL;

    // 位置beforeNode是关键字为theKey的节点之最右边的位置
    skipNode<K, E>* beforeNode = headerNode;
    for (int i = levels; i >= 0; i--)
        while (beforeNode->next[i]->element.first < theKey)
            beforeNode = beforeNode->next[i];

    if (beforeNode->next[0]->element.first == theKey)
        return &beforeNode->next[0]->element;

    return NULL;
}

template <typename K, typename E>
int SkipList<K, E>::level() const
{
    // 返回一个表示链表级的随机数，这个数不大于maxLevel
    int lev = 0;
    while (rand() <= cutOff)
        lev++;
    return (lev <= maxLevel) ? lev : maxLevel;
}

template <typename K, typename E>
skipNode<K, E>* SkipList<K, E>::search(const K& theKey) const
{
    // 返回beforeNode时关键字
    skipNode<K, E>* beforeNode = headerNode;
    for (int i = levels; i >= 0; i--)
    {
        while (beforeNode->next[i]->element.first < theKey)
            beforeNode = beforeNode->next[i];
        last[i] = beforeNode;
    }
    return beforeNode->next[0];
}

template <typename K, typename E>
void SkipList<K, E>::insert(const std::pair<const K, E>& thePair)
{
    if (thePair.first >= tailKey)
    {
        std::cout << "Key = " << thePair.first << " must be < " << tailKey << std::endl;;
        return;
    }

    // 查看关键字是否已经存在
    skipNode<K, E>* theNode = search(thePair.first);
    if (theNode->element.first == thePair.first)
    {
        theNode->element.second = thePair.second;
        return;
    }

    // 若不存在, 确定所在链级数
    int theLevel = level();
    if (theLevel > levels)
    {
        theLevel = ++levels;
        last[theLevel] = headerNode;
    }
    // 再借点theNode 之后插入新节点
    skipNode<K, E>* newNode = new skipNode<K, E>(thePair, theLevel + 1);
    for (int i = 0; i < theLevel; i++)
    {
        // 插入i级链表
        newNode->next[i] = last[i]->next[i];
        last[i]->next[i] = newNode;
    }

    dSize++;
    return;
}

template <typename K, typename E>
void SkipList<K, E>::erase(const K& theKey)
{
    if (theKey >= tailKey)
        return;

    //查看是否有匹配的数对
    skipNode<K, E>* theNode = search(theKey);
    if (theNode->element.first != theKey)
        return;

    for (int i = 0; i <= levels && last[i]->next[i] == theNode; i++)
        last[i]->next[i] = theNode->next[i];

    while (levels > 0 && headerNode->next[levels] == tailNode)
        levels--;

    delete theNode;
    dSize--;
}
