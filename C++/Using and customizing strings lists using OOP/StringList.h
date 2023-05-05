#pragma once
#include <iostream>
#include <string>
using namespace std;

class StringList {
public:
	StringList();
	StringList(const StringList & List);
	~StringList();
	StringList& operator=(const StringList& currentStudent);

	void insert(string parameter,int dex);
	string remove(int a);
	void swap(int num1, int num2) ;
	string retrieve(int a) const;
	int size() const;
	StringList concatenate(const StringList& List);

private:
	string *data;
	int curSize;
	int maxSize;
}; 
void print(const StringList &List);
void reverse(StringList& List);
StringList& readFile(string file);
StringList merge(const StringList& List1, const StringList& List2);