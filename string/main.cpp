#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "kmp.hpp"
#include "manacher.hpp"

class StringUtils
{
public:
	/// <summary>
	/// 子序列
	/// </summary>
	/// <param name="str"></param>
	/// <returns></returns>
	static std::vector<std::string> sub_serial_string(const std::string& str)
	{
		std::string tmp_str;
		std::vector<std::string> res;
		process_sub_serial_helper(str, 0, tmp_str, res);
		return res;
	}

	/// <summary>
	/// 全排列
	/// </summary>
	/// <param name="str"></param>
	/// <returns></returns>
	static std::vector<std::string> permutation(const std::string& str)
	{
		std::string tmp_str = str;
		std::vector<std::string> res;
		process_permutation_helper(tmp_str, 0, res);
		return res;
	}

private:
	/// <summary>
	/// process_sub_serial_helper
	/// </summary>
	/// <param name="str"></param>
	/// <param name="idx"></param>
	/// <param name="tmp_str">0-idx做的选择</param>
	/// <param name="res"></param>
	static void process_sub_serial_helper(const std::string& str, const size_t idx, const std::string& tmp_str, std::vector<std::string>& res)
	{
		if (idx == str.length())
		{
			res.push_back(tmp_str);
			return;
		}

		//要当前字符
		std::string tmp_str1 = tmp_str;
		tmp_str1 += str.at(idx);
		process_sub_serial_helper(str, idx + 1, tmp_str1, res);
		//不要当前字符
		std::string tmp_str2 = tmp_str;
		process_sub_serial_helper(str, idx + 1, tmp_str2, res);
	}

	/// <summary>
	/// process_permutation_helper
	/// </summary>
	/// <param name="str"></param>
	/// <param name="idx"></param>
	/// <param name="res"></param>
	static void process_permutation_helper(std::string& str, const size_t idx, std::vector<std::string>& res)
	{
		if (idx == str.length())
		{
			res.push_back(str);
			return;
		}

		bool visited[26] = { false };
		for (size_t i = idx; i < str.length(); i++)
		{
			//去重
			if (visited[str.at(i) - 'a']) continue;
			visited[str.at(i) - 'a'] = true;
			std::swap(str.at(idx), str.at(i));
			process_permutation_helper(str, idx + 1, res);
			std::swap(str.at(idx), str.at(i));
		}
	}
};

int main(int argc, char** argv)
{
	{
		auto res = StringUtils::sub_serial_string("acr");
		std::cout << "size: " << res.size() << "\n";
		/*for (const std::string& str : res)
		{
			std::cout << str << "\n";
		}*/
	}

	{
		/*auto res = StringUtils::permutation("acccfddf");
		for (const std::string& str : res)
		{
			std::cout << str << "\n";
		}*/
	}

	{
		std::string str1 = "abadabadabag";
		std::string str2 = "abadabag";
		size_t idx = KMPAlgorithm::get_index_of(str1, str2);
	}

	{
		std::string str1 = "abcdcbakskabcdcbagu";
		size_t idx = ManacherAlgorithm::maxPalindromeLength(str1);
	}
	return 0;
}