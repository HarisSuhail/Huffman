#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include<iostream>
using namespace std;

template<class T>
struct Node
{
public:
	T data;
	Node *next;

};



template<class T>
class List
{
public:
	Node<T> *ptr;
	Node<T> *current;
	void reset()
	{
		current = ptr;
	}


	//moves the current pointer one step ahead
	bool operator++()
	{


		current = current->next;

		if (current == NULL)
		{
			return false;
		}

		return true;



	}

	List()
	{
		ptr = NULL;


	}
	bool isEmpty();  //returns true when the list is empty
	bool oneLeft();  //returns true when there is a single element left
	T pop();  //pops an element

	void append(T);  //adds to the end

	void insert(T);  //adds to the start

	void push(T&);
	T getData()  //returns data of current pointer
	{
		return current->data;
	}
	bool currentAtEnd()  //returns true when current is at the end
	{
		if (current != NULL && current->next == NULL)
		{
			return true;
		}
		return false;
	}
	void finddelete(T);  //finds the data given in argument and deletes it

	void show();  //prints the list

	void operator = (List<T>);

	void addtostart(T data)
	{
		Node<T>* temp = new Node<T>;
		temp->data = data;
		temp->next = ptr;
		ptr = temp;
		temp = NULL;
	}
};



#endif