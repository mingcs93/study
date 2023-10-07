#pragma once

/* ����ʵ�� */

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

    // find, ����ҵ�����ָ�룬û�з���NULL
    std::pair<const K, E>* find(const K& theKey) const;
    // level�����ķ���
    int level() const;
    // search������
    skipNode<K, E>* search(const K& theKey) const;
    // insert�� �������
    void insert(const std::pair<const K, E>& thePair);
    // erase��ɾ������
    void erase(const K& theKey);

private:
    float cutOff;               // ����ȷ������
    int levels;                 // ��ǰ���ķǿ�����
    int dSize;                  // �ֵ�����Ը���
    int maxLevel;               // ���������������
    K tailKey;                  // ���ؼ���
    skipNode<K, E>* headerNode; // ͷ���ָ��
    skipNode<K, E>* tailNode;   // β�ڵ�ָ��
    skipNode<K, E>** last;      // last[i] ��ʾi������ڵ�
};


template <typename K, typename E>
SkipList<K, E>::SkipList(K largeKey, int maxPairs, float prob)
{
    // ���캯�����ؼ���С��largeKey�����Ը���size���ΪmaxPairs, 0 < prob < 1;
    cutOff = prob * RAND_MAX;
    maxLevel = (int)ceil(logf((float)maxPairs) / logf(1 / prob)) - 1;   // ����ȡ��
    levels = 0;
    dSize = 0;
    tailKey = largeKey;

    // ����ͷ��㣬β�ڵ������last
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
    // ����ƥ������Ե�ָ��
    // ����ؼ��ִ������ؼ��֣�����NULL
    if (theKey >= tailKey)
        return NULL;

    // λ��beforeNode�ǹؼ���ΪtheKey�Ľڵ�֮���ұߵ�λ��
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
    // ����һ����ʾ������������������������maxLevel
    int lev = 0;
    while (rand() <= cutOff)
        lev++;
    return (lev <= maxLevel) ? lev : maxLevel;
}

template <typename K, typename E>
skipNode<K, E>* SkipList<K, E>::search(const K& theKey) const
{
    // ����beforeNodeʱ�ؼ���
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

    // �鿴�ؼ����Ƿ��Ѿ�����
    skipNode<K, E>* theNode = search(thePair.first);
    if (theNode->element.first == thePair.first)
    {
        theNode->element.second = thePair.second;
        return;
    }

    // ��������, ȷ������������
    int theLevel = level();
    if (theLevel > levels)
    {
        theLevel = ++levels;
        last[theLevel] = headerNode;
    }
    // �ٽ��theNode ֮������½ڵ�
    skipNode<K, E>* newNode = new skipNode<K, E>(thePair, theLevel + 1);
    for (int i = 0; i < theLevel; i++)
    {
        // ����i������
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

    //�鿴�Ƿ���ƥ�������
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
