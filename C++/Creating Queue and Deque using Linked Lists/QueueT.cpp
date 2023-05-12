#pragma once
#include "DequeT.h"
#include <iostream>
#include <string>
#include <cstdio>
#include <stdexcept>
using namespace std;

template<class T>
class QueueT  {

public:

	QueueT(){
	} 

	void enqueue(T par) {
	
		dq.insertBack(par);
	
	};

	T dequeue() {

	return dq.removeFront();
	} 

	bool empty(){
	return dq.empty();
	} 

	int size(){
	return dq.size();
	} 

private:

	DequeT<T> dq;
};