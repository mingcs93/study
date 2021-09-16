#pragma once
#include <iostream>
#include <vector>

template<typename T>
class MergeSort
{
public:
	MergeSort(std::initializer_list<T>& values)
		: m_nums(values.begin(), values.end())
	{
	}

	void sort()
	{
		process(0, m_nums.size() - 1);
	}

	void show()
	{
		for (auto& item : m_nums)
		{
			std::cout << item << " ";
		}
		std::cout << std::endl;
	}

private:
	void process(size_t left, size_t right)
	{
		if (left == right) return;

		size_t mid = left + ((right - left) >> 1);
		process(left, mid);
		process(mid + 1, right);
		merge(left, mid, right);
	}

	void merge(size_t lelt, size_t mid, size_t right)
	{
		std::vector<T> tmp(right-lelt+1);
		size_t idx = 0;
		size_t p1 = lelt;
		size_t p2 = mid + 1;
		while (p1 <= mid && p2 <= right) 
		{
			tmp.at(idx++) = m_nums.at(p1) <= m_nums.at(p2) ? m_nums.at(p1++) : m_nums.at(p2++);
		}

		while (p1 <= mid)
		{
			tmp.at(idx++) = m_nums.at(p1++);
		}

		while (p2 <= right)
		{
			tmp.at(idx++) = m_nums.at(p2++);
		}

		for (auto& item : tmp)
		{
			m_nums.at(lelt++) = item;
		}
	}

private:
	std::vector<T> m_nums;
};