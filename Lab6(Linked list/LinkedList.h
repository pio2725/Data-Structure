#pragma once
#include "LinkedListInterface.h"
#include <sstream>

template <typename T>
class LinkedList : public LinkedListInterface<T>
{
public:
	LinkedList()
	{
		mylist = NULL;
		num_items = 0;
	}
	~LinkedList()
	{
		while (mylist != NULL)
		{
			Node* temp = mylist;
			mylist = mylist->next;
			delete temp;
		}
	}

	bool Find(T value)
	{
		bool isValue = false;

		Node* ptr = mylist;
		while (ptr != NULL)
		{
			if (ptr->data == value)
			{
				isValue = true;
				break;
			}
			else
			{
				ptr = ptr->next;
			}
		}
		return isValue;
	}

	void insertHead(T value)
	{
		//insert at the beginning of the list
		if (mylist == NULL)
		{
			//if the list is empty
			mylist = new Node(value, NULL);
			++num_items;
		}
		else
		{
			//should find a duplicate value
			//There is no duplicates
			if (!Find(value))
			{
				//insert at index 0
				//mylist is pointing the head
				//newnode becomes the new head
				Node* newnode = new Node(value, NULL);
				newnode->next = mylist;
				mylist = newnode;
				++num_items;
			}
		}
	}

	void insertAfter(T value, T insertionNode)
	{
		//insertionNode has to be in the list
		if (Find(insertionNode))
		{
			if (!Find(value))
			{
				Node* ptr = mylist;
				while (ptr != NULL)
				{
					if (ptr->data == insertionNode)
					{
						Node* newnode = new Node(value, NULL);
						newnode->next = ptr->next;
						ptr->next = newnode;
						++num_items;
						break;
					}
					else
					{
						ptr = ptr->next;
					}
				}
			}
		}
	}

	void insertTail(T value)
	{
		if (mylist == NULL)
		{
			insertHead(value);
		}
		else
		{
			if (!Find(value))
			{
				Node* ptr = mylist;

				while (ptr != NULL)
				{
					if (ptr->next == NULL)
					{
						ptr->next = new Node(value, NULL);
						break;
					}
					else
					{
						ptr = ptr->next;
					}
				}
				++num_items;

			}
		}
	}

	void remove(T value)
	{
		//make sure if there is a node with the value
		if (Find(value))
		{
			Node* ptr = mylist; // to travel
			if (value == ptr->data)
			{
				//case 1 : removing the head
				Node* temp = mylist;
				mylist = ptr->next;
				delete temp;
				--num_items;
			}
			else
			{
				//not removing head
				int eraseIndex = 0;
				while (ptr != NULL)
				{
					if (ptr->data == value)
					{
						break;
					}
					else
					{
						ptr = ptr->next;
						++eraseIndex;
					}
				}

				ptr = mylist;
				for (int i = 0; i <= eraseIndex; i++)
				{
					if (i == (eraseIndex - 1))
					{
						Node* temp = ptr->next;
						ptr->next = ptr->next->next;
						delete temp;
						--num_items;
						break;
					}
					else
					{
						ptr = ptr->next;
					}
				}
			}
		}
	}

	void clear()
	{
		while (mylist != NULL)
		{
			Node* temp = mylist;
			mylist = mylist->next;
			delete temp;
		}
		num_items = 0;
	}

	T at(int index)
	{
		if (index >= num_items || index < 0)
		{
			throw std::out_of_range("error");
		}

		if (mylist != NULL)
		{
			Node* ptr = mylist;

			for (int i = 0; i <= index; i++)
			{
				if (i == index)
				{
					return ptr->data;
				}
				else
				{
					ptr = ptr->next;
				}
			}
		}
	}

	int size()
	{
		return num_items;
	}

	string toString()
	{
		Node* ptr = mylist;
		ostringstream ss;
		string output;
		while (ptr != NULL)
		{
			ss << ptr->data << " ";
			ptr = ptr->next;
		}

		output = ss.str();

		if (!output.empty())
		{
			output.erase(output.size() - 1, 1);
		}
		return output;
	}

private:
	struct Node
	{
		T data;
		Node* next;

		Node(const T& the_data, Node* next_val = NULL) : data(the_data)
		{
			next = next_val;
		}
	};

	Node* mylist;
	int num_items;
};