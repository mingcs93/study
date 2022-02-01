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
			std::shared_ptr<Node> cur = m_head;
			while (cur->next != nullptr)
			{
				cur = cur->next;
			}
			cur->next = tmp;
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
	
	bool isPalindromicLink()
	{
		if (m_head == nullptr || m_head->next == nullptr)
		{
			return true;
		}

		std::shared_ptr<Node> s = m_head;
		std::shared_ptr<Node> f = m_head;
		while (f->next != nullptr && f->next->next != nullptr)
		{
			s = s->next;
			f = f->next->next;
		}

		///将慢指针后的节点反转
		std::shared_ptr<Node> cur = s->next;
		std::shared_ptr<Node> head = nullptr;
		while (cur != nullptr)
		{
			std::shared_ptr<Node> tmp = cur->next;
			cur->next = head;
			head = cur;
			cur = tmp;
		}

		bool res = true;
		std::shared_ptr<Node> l = m_head;
		std::shared_ptr<Node> r = head;
		while (l != nullptr && r != nullptr)
		{
			if (l->value != r->value)
			{
				res = false;
				break;
			}
			l = l->next;
			r = r->next;
		}

		///还原原链表
		cur = head;
		head = nullptr;
		while (cur != nullptr)
		{
			std::shared_ptr<Node> tmp = cur->next;
			cur->next = head;
			head = cur;
			cur = tmp;
		}
		return res;
	}

/// <summary>
/// 将链表按某个值(pivot)进行划分，小于pivot放在左边，等于pivot放在中间，大于pivot放在右边
/// </summary>



private:
	std::shared_ptr<Node> m_head{ nullptr };
	//std::shared_ptr<Node> m_tail{ nullptr };
};

int main(int argc, char** argv)
{
	MyList<int32_t> list;
	list.pushBack(2);
	list.pushBack(13);
	list.pushBack(5);
	list.pushBack(6);
	list.pushBack(7);
	list.pushBack(5);
	list.pushBack(13);
	list.pushBack(2);
	list.show();

	//list.reverseList();
	//list.show();
	bool res = list.isPalindromicLink();
	std::cout << "isPalindromicLink: " << res << std::endl;
	list.show();
	return 0;
}