#include <iostream>
#include <string>
#include "merge_sort.hpp"

struct Student
{
	std::string name;
	int16_t age;

	friend bool operator<= (const Student& l, const Student& r)
	{
		if (l.age <= r.age) return true;
		return false;
	}

	friend std::ostream& operator<<(std::ostream& output, const Student& stu)
	{
		output << "(" << "name: " << stu.name << ", " << "age: " << stu.age << ")";
		return output;
	}
};

int main(int argc, char** argv)
{
	{
		MergeSort<int32_t> mySort{ std::initializer_list<int>{5, 4, 7, 3, 10, 2, 7, 9, 32} };
		mySort.sort();
		mySort.show();
	}

	{
		Student stu1;
		stu1.name = "zhangsan";
		stu1.age = 20;

		Student stu2;
		stu2.name = "jack";
		stu2.age = 10;

		Student stu3;
		stu3.name = "tom";
		stu3.age = 24;

		MergeSort<Student> mySort{ std::initializer_list<Student>{stu1, stu2, stu3} };
		mySort.sort();
		mySort.show();
	}
	return 0;
}