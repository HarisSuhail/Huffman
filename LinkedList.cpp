#include "LinkedList.h"


template<class T>
void List<T>::append(T x)
{
	Node<T> *q = new Node<T>();
	Node<T> *p = ptr;
	q->data = x;
	q->next = NULL;
	if (ptr == NULL)
	{
		ptr = q;
	}
	else
	{
		while (p->next != NULL)
		{
			p = p->next;

		}
		p->next = q;
	}
}

template<class T>
void List<T>::insert(T x)
{
	Node<T> *q = new Node<T>();
	Node<T> *p = ptr;
	q->data = x;
	q->next = NULL;
	if (ptr == NULL)
	{
		ptr = q;
	}
	else
	{
		q->next = ptr;
		ptr = q;
	}
}

template<class T>
void List<T>::finddelete(T a)
{
	Node *p = ptr;
	Node *q = NULL;
	while (p != NULL)
	{
		if (p->data == a)
		{
			if (p == ptr)
			{
				//q = ptr;
				ptr = ptr->next;
				delete q;
				break;

			}
			else
			{
				q->next = p->next;
				delete p;
				break;

			}
		}
		q = p;
		p = p->next;


	}
}

template<class T>
void List<T>::show()
{
	Node<T> *p = ptr;
	while (p != NULL)
	{
		cout << p->data << endl;
		p = p->next;

	}



}
template <class T>
bool List<T>::oneLeft()
{
	if (ptr != NULL && ptr->next == NULL)
	{
		return true;
	}
	return false;
}
template <class T>
void List<T>::push(T& data)
{


	if (ptr == NULL)
	{

		ptr = new Node<T>();
		ptr->data = data;

		ptr->next = NULL;
		return;
	}

	else
	{

		Node<T>* leader = ptr;
		Node<T> * follower = NULL;

		while (leader != NULL)
		{
			if (leader->data > data)
			{
				//Insert Before Leader
				if (follower == NULL)
				{
					follower = new Node<T>();
					follower->next = ptr;
					follower->data = data;

					ptr = follower;
					return;
				}
				else
				{
					follower->next = new Node<T>();
					follower->next->data = data;

					follower->next->next = leader;
					return;
				}

			}
			follower = leader;
			leader = leader->next;
		}

		follower->next = new Node<T>();
		follower->next->data = data;

		follower->next->next = NULL;

	}
}

template<class T>
bool List<T>::isEmpty()
{

	return ptr == NULL ? true : false;
}


template<class T>
T List<T>::pop()
{

	if (!isEmpty())
	{

		T data = ptr->data;
		Node<T>* i = ptr;
		ptr = ptr->next;
		delete i;
		return data;
	}
	throw 1;

}


template<class T>
void List<T>::operator = (List<T> thelist)
{
	if (thelist.ptr == NULL)
	{


		this->ptr = NULL;
		return;
	}

	Node<T>* temp = thelist.ptr, *init;

	ptr = new Node<T>();
	init = ptr;

	while (temp != NULL)
	{
		init->data = temp->data;
		temp = temp->next;
		if (temp == NULL)
		{
			init->next = NULL;
			break;
		}
		init->next = new Node<T>();
		init = init->next;

	}





}