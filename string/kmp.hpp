#pragma once
#include <string>
#include <vector>

class KMPAlgorithm
{
public:
	static int32_t get_index_of(const std::string& str1, const std::string& str2)
	{
		std::size_t s1 = str1.length();
		std::size_t s2 = str2.length();
		if (s1 == 0 || s2 == 0 || s1 < s2) return -1;

		std::vector<int32_t> str2_next_array = get_next_array(str2);
		size_t i = 0;
		size_t j = 0;
		while (i < s1 && j < s2)
		{
			if (str1.at(i) == str2.at(j))
			{
				i++;
				j++;
			}
			else if (str2_next_array.at(j) == -1) //j==0
			{
				i++;
			}
			else
			{
				j = str2_next_array.at(j);
			}
		}
		return j == s2 ? i - j : -1; //j==s2 表示str2是str1的字串
	}

private:
	/// <summary>
	/// 返回每个位置之前字符串的前后字串相同的最大长度
	/// abadabae -> [-1,0,0,1,0,0,2,3]
	/// </summary>
	/// <param name="str"></param>
	/// <returns></returns>
	static std::vector<int32_t> get_next_array(const std::string& str)
	{
		std::vector<int32_t> next;
		next.resize(str.length());
		next.at(0) = -1; //第一个字符规定为-1
		if (str.length() == 1) return next;

		next.at(1) = 0; //第二个字符规定为0
		size_t idx = 2;
		int32_t cn = 0;
		while (idx < str.length())
		{
			if (str.at(cn) == str.at(idx - 1))
			{
				next.at(idx++) = ++cn;
			}
			else if (cn > 0)
			{
				cn = next.at(cn);
			}
			else
			{
				next.at(idx++) = 0;
			}
		}
		return next;
	}
};