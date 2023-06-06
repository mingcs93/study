#pragma once
#include <string>
#include <vector>

class ManacherAlgorithm
{
public:
	static int32_t maxPalindromeLength(const std::string& str)
	{
		if (str.length() == 0) return 0;
		std::string manacher_str;
		//abcdcba -> #a#b#c#d#c#b#a �ַ������Ȳ�����ż��ͳһ����
		for (const char ch : str)
		{
			manacher_str += "#";
			manacher_str += ch;
		}
		manacher_str += "#";

		std::vector<int32_t> palindrome_radius_vec(manacher_str.length(), 0); //���İ뾶����
		int32_t r = -1; //������ұ߽�
		int32_t c = -1; //�����İ뾶ʱ�����ĵ�
		int32_t max = INT32_MIN;
		for (int32_t idx = 0; idx < manacher_str.length(); idx++)
		{
			palindrome_radius_vec.at(idx) = r > idx ? std::min(int32_t(r - idx), palindrome_radius_vec.at(2 * c - idx)) : 1;

			while (idx + palindrome_radius_vec.at(idx) < manacher_str.length() && idx - palindrome_radius_vec.at(idx) > -1)
			{
				if (manacher_str.at(idx + palindrome_radius_vec.at(idx)) == manacher_str.at(idx - palindrome_radius_vec.at(idx)))
				{
					palindrome_radius_vec.at(idx)++;
				}
				else
				{
					break;
				}
			}

			if (idx + palindrome_radius_vec.at(idx) > r)
			{
				r = idx + palindrome_radius_vec.at(idx);
				c = idx;
			}
			max = std::max(max, palindrome_radius_vec.at(idx));
		}

		return max - 1;
	}
};