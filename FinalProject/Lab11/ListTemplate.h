#pragma once
#include "Product.h"
#include <iostream>

using namespace std;

template<typename ElementType>
class IteratorList;

template<typename ElementType>
class ListTemplate;

typedef Product Element;

template<typename ElementType>
class Node
{
	friend class ListTemplate<ElementType>;

private:
	ElementType value;
	Node<ElementType>* next;

public:
	Node(const ElementType &_value, Node<ElementType> *_next) : value{ _value }, next{ _next } {}
	Node(const ElementType &_value) : value{ _value }, next{ nullptr } {}
};

template<typename ElementType>
class ListTemplate
{
	friend class IteratorList<ElementType>;

private:
	int length;
	Node<ElementType>* head;

public:
	ListTemplate() noexcept : length{ 0 }, head{ nullptr } {}
	ListTemplate(const ListTemplate<ElementType>& _list)
	{
		length = _list.length;
		head = copyNode(_list.head);
	}

	Node<ElementType>* copyNode(const Node<ElementType> *node)
	{
		if (node == nullptr)
			return nullptr;
		return new Node<ElementType>{ node->value, copyNode(node->next) };
	}

	ListTemplate<ElementType>& operator=(ListTemplate<ElementType> &_list)
	{
		destroyList();
		length = _list.length;
		head = copyNode(_list.head);
		return *this;
	}

	void destroyList();
	void append(const ElementType& element);
	void remove(int index);
	int size();
	ElementType& at(int index) const;
	IteratorList<ElementType> begin() noexcept;
	IteratorList<ElementType> end() noexcept;
	void set(int index, const ElementType& element) const;
	void sort(bool(*compare_function)(const Element &elem1, const Element &elem2));

	~ListTemplate()
	{
		destroyList();
	}
};

template <typename ElementType>
void ListTemplate<ElementType>::destroyList()
{
	while (head != nullptr)
	{
		auto node = head;
		head = head->next;
		delete node;
	}
}

template <typename ElementType>
void ListTemplate<ElementType>::append(const ElementType& element)
{
	if (length == 0)
	{
		auto node = new Node<ElementType>{ element };
		head = node;
	}
	else
	{
		auto node = head;
		while (head->next != nullptr)
			head = head->next;
		auto newNode = new Node<ElementType>{ element };
		head->next = newNode;
		head = node;
	}
	length++;
}

template <typename ElementType>
void ListTemplate<ElementType>::remove(int index)
{
	if (index == 0)
	{
		auto node = head;
		head = head->next;
		delete node;
	}
	else if (index == length - 1)
	{
	}
	else
	{
		auto node = head;
		int current = 0;
		while (current < length - 1)
		{
			if (current + 1 == index)
			{
				auto node2 = head->next;
				head->next = node2->next;
				delete node2;
			}
			current++;
			head = head->next;
		}
		head = node;
	}
	length--;
}

template <typename ElementType>
int ListTemplate<ElementType>::size()
{
	return length;
}

template <typename ElementType>
ElementType& ListTemplate<ElementType>::at(int index) const {
	if (index >= length) throw exception();
	int current = 0;
	auto node = head;
	while (current < length) {
		if (current == index)
			return node->value;
		node = node->next;
		current++;
	}
	throw exception();
}

template <typename ElementType>
IteratorList<ElementType> ListTemplate<ElementType>::begin() noexcept
{
	return IteratorList<ElementType>(*this);
}

template <typename ElementType>
IteratorList<ElementType> ListTemplate<ElementType>::end() noexcept
{
	return IteratorList<ElementType>(*this, length);
}

template <typename ElementType>
void ListTemplate<ElementType>::set(int index, const ElementType& element) const
{
	if (index >= length) throw exception();
	int current = 0;
	auto node = head;
	while (current < length - index - 1) {
		node = node->next;
		current++;
	}
	node->value = element;
}

template <typename ElementType>
void ListTemplate<ElementType>::sort(bool(*compare_function)(const Element &elem1, const Element &elem2)) {
	if (length == 1) return;

	bool sorted = false;
	while (!sorted) {
		Node<ElementType>* prec = head;
		Node<ElementType>* current = head->next;
		sorted = true;
		while (current != nullptr) {
			if (compare_function(prec->value, current->value)) {
				sorted = false;
				ElementType element = prec->value;
				prec->value = current->value;
				current->value = element;
			}
			prec = prec->next;
			current = current->next;
		}
	}
}


template<typename ElementType>
class IteratorList
{
	friend class ListTemplate<ElementType>;

private:
	int index;
	const ListTemplate<ElementType>& list;

public:
	IteratorList(const ListTemplate<ElementType>& _list) noexcept : list{ _list }, index{ 0 } {}
	IteratorList(const ListTemplate<ElementType>& _list, int _index) noexcept : list{ _list }, index{ _index } {}
	bool valid() const;
	void next() noexcept;
	ElementType& element() const;

	bool operator==(const IteratorList<ElementType>& iterator) noexcept
	{
		return index == iterator.index;
	}
	bool operator!=(const IteratorList<ElementType>& iterator) noexcept
	{
		return !(index == iterator.index);
	}
	IteratorList<ElementType> operator++() noexcept
	{
		next();
		return *this;
	}
	ElementType& operator*()
	{
		return element();
	}
};

template<typename ElementType>
bool IteratorList<ElementType>::valid() const
{
	return index < list.size();
}

template<typename ElementType>
void IteratorList<ElementType>::next() noexcept
{
	index++;
}

template<typename ElementType>
ElementType& IteratorList<ElementType>::element() const
{
	return list.at(index);
}