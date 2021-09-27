#include <iostream>
#include <string>
#include <memory>

template<typename T>
class MyList
{
	class Node
	{
	public:
		Node(const T& val)
			: value(val)
			, next(nullptr)
		{
		}

	public:
		T value;
		std::shared_ptr<Node> next;
	};

public:
	void pushBack(const T& value)
	{
		std::shared_ptr<Node> tmp = std::make_shared<Node>(value);
		if (m_head == nullptr)
		{
			m_head = tmp;
		}
		else
		{
			std::shared_ptr<Node> last = m_head;
			while (last->next != nullptr)
			{
				last = last->next;
			}
			last->next = tmp;
		}
	}

	void show()
	{
		std::shared_ptr<Node> cur = m_head;
		while (cur != nullptr)
		{
			std::cout << cur->value << " ";
			cur = cur->next;
		}
		std::cout << std::endl;
	}

/// <summary>
/// 反转链表
/// </summary>
	void reverseList()
	{
		//if (m_head == nullptr || m_head->next == nullptr) return;

		std::shared_ptr<Node> cur = m_head;
		m_head = nullptr;
		while (cur != nullptr)
		{
			std::shared_ptr<Node> tmp = cur->next;

			///头插法
			cur->next = m_head;
			m_head = cur;
			cur = tmp;
		}
	}

/// <summary>
/// 判断链表是否为回文结构
/// </summary>
	


/// <summary>
/// 将链表按某个值(pivot)进行划分，小于pivot放在左边，等于pivot放在中间，大于pivot放在右边
/// </summary>



private:
	std::shared_ptr<Node> m_head{ nullptr };
	std::shared_ptr<Node> m_tail{ nullptr };
};

int main(int argc, char** argv)
{
	MyList<int32_t> list;
	list.pushBack(2);
	list.pushBack(13);
	list.pushBack(5);
	list.pushBack(4);
	list.pushBack(8);
	list.pushBack(30);
	list.show();

	list.reverseList();
	list.show();
	return 0;
}