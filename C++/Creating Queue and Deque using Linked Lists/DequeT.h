#pragma once
#include <iostream>
#include <string>
#include <cstdio>
#include <stdexcept>
using namespace std;
template<class T>
class Node {  //template Node class
public:
	Node(T var) {
		data = var;
		Node* front = NULL;
		Node* back = NULL;
	}

	T data;
	Node* front;
	Node* back;

};

template<class T>
class DequeT {
public:
	DequeT() {  //defual constructor
		siz = 0;
		Node<T>* head=NULL;
		Node<T>* tail=NULL;
	}
	DequeT(const DequeT<T>& List) {  //copy constructor

		*this = List;
	}
	~DequeT() {   //destructor
		Node<T> *temp1= head;
		Node<T>* temp2 = temp1;

		while (temp1 != NULL) {
			temp1 = temp1->back;
			delete temp2;
			temp2 = temp1;
		}

	}
	DequeT<T>& operator=(const DequeT<T>& List) {

		Node<T>* temp = List.head;

		while (temp != NULL) {
			this->insertBack(temp->data);
			temp = temp->back;
		}

		return *this;
	}

	void insertFront(T num) {
		if (head == NULL) {  //if empty
			Node<T>* temp = new Node<T>(num);
			tail = head= temp;
		}
		else {    //if not empty
			Node<T>* temp = new Node<T>(num);
			head->front = temp;
			temp->back = head;
			head = temp;
		}
		siz++;  //keep track of the size
	}
	void insertBack(T num) {
		if (tail == NULL) {  //if empty
			Node<T>* temp = new Node<T>(num);
			head = tail= temp;
		}
		else {    //if not empty
			Node<T>* temp = new Node<T>(num);
			tail->back = temp;
			temp->front = tail;
			tail = temp;
		}
		siz++;  //keep track of the size
	}
	T removeFront() {
		if (head == NULL) {
			throw std::runtime_error("yeey");  //runtime error when empty
		}
		else {
			if (siz > 1) {    //removing front when more than 1 element 
				T val = head->data;
				Node<T>* temp = head;
				head = head->back;
				head->front = NULL;
				delete temp;
				siz--;
				return val;
			}
			else {   //removing the last element 
				T val = head->data;
				siz = 0;
				Node<T>* temp = tail;
				tail = NULL;
				head = NULL;
				delete temp;
				return val;
			}
		}
	}
	T removeBack() {
		if (tail == NULL) {
			throw std::runtime_error("yeey");   //runtime error when empty
		}
		else {
			if (siz > 1) {  //removing back when more than 1 element 
				T val = tail->data;
				Node<T>* temp = tail;
				tail = tail->front;
				tail->back = NULL;
				delete temp;
				siz--;
				return val;
			}
			else
			{   //removing the last element 
				T val = tail->data;
				siz = 0;
				Node<T>* temp = tail;
				tail = NULL;
				head = NULL;
				delete temp;
				return val;
			}
		}
	}
	T peekFront() {   
		return head->data;   //returning value at head
	}
	T peekBack() {
		return tail->data;   //returning value at tail
	}
	bool empty() {
		return siz==0;
	}
	int size() {
		return siz;

	}

	void print() {
		Node<T>* temp = head;
		while(temp != NULL) {
			cout << temp->data << " ";
			temp = temp->back;
		}
		cout << endl;
	}

private:
	int siz;
	Node<T>* head;
	Node<T>* tail;

};