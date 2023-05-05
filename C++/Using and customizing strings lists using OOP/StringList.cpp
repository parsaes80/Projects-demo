#include "StringList.h"
#include <string>
#include <stdexcept>
#include <fstream>
using namespace std;

StringList::StringList() {
	string *arr= new string[4];
	data = arr;
	curSize=0;
	maxSize=4;
}

StringList::StringList(const StringList& List)
{
	string* arr = new string[4];
	data = arr;
	curSize = 0;
	maxSize = 4;
	int i = 0;
	for (i = 0; i < List.size(); i++)
	{
		this->insert(List.retrieve(i), i);
	}
}
StringList::~StringList(){
	
	delete[] data;

}
StringList& StringList::operator=(const StringList& List)  {
	//for (int i = 0; i < maxSize; i++) {
	//	data[i] = "";
	//}
	delete[] data;
	data = new string[4];
	curSize = 0;
	maxSize = 4;
	for (int i = 0; i < List.size(); i++) {
		this->insert(List.retrieve(i),i);
	}
	
	return *this; 
}

void StringList::insert(string name, int num) { 
	if (num< 0 || num > curSize)
	{
		throw std::out_of_range("bruh");
	}
	else if (curSize == maxSize) {

		maxSize = 2 * maxSize;
		string* arr = new string[maxSize];
	
		for (int i = 0; i < (curSize); i++) { //copy into new array
			arr[i] = data[i];
		}

		delete[] data;

		data = arr;
		curSize++;
		data[num] = name;
	}
	else {
		for (int i = curSize; i > num; i--) {

			data[i] = data[i - 1];

		}
		curSize++;
		data[num] = name;
	
	}
}

string StringList::remove(int num) {
	if ((num < 0) || (num > (curSize - 1))) {

		throw std::out_of_range("bruh");
	}
	else {
		
		for (int i = num; i < (maxSize-1); i++) {
			data[i]=data[i + 1];
			
		}
		curSize--;
	}

	return ""; }

void StringList::swap(int num1, int num2) {
	if ((num1 < 0) || (num1 > (curSize - 1 ))) {

		throw std::out_of_range("bruh");
	}
	if ((num2 < 0) || (num2 > (curSize - 1))) {

		throw std::out_of_range("bruh");
	}
	else {
		string mid = data[num1];
		data[num1] = data[num2];
		data[num2] = mid;
	}

	
}

string StringList::retrieve(int num) const {

	if ((num < 0) || (num > (curSize - 1))) {

		throw std::out_of_range("bruh");
	}
	else {
		return data[num];

	}

}

int StringList::size() const{ 
	
	return curSize;
}

StringList StringList::concatenate(const StringList& List)  {
	StringList ans(*this);
	/*
	int tsize = List.size() + curSize;
	int n = 0;
	for (int i = 0; i < curSize; i++) {

		ans.insert(data[i], i);
		
	}
	*/
	for (int i = 0; i <List.size(); i++) {
		
		ans.insert(List.retrieve(i), i+this->curSize);
	}

	return ans;
}


void print(const StringList& List) {
	

	for (int i = 0; i < (List.size()); i++) {
		
			cout << List.retrieve(i) << " ";
		
	}
	cout << endl;
	return;
}
void reverse(StringList& List) {
	int size = List.size();
	int i;


	for (i = 0; i < size / 2; i++) {
		List.swap(i, size - i - 1);
	}

}
StringList& readFile(string filename) {

	StringList List;
	std::ifstream file(filename);
	if (file.is_open()) {
		std::string line;
		int i = 0;
		while (std::getline(file, line)) {
			List.insert(line, i);
			i++;
		}
		file.close();
	}

	return List; 
}


StringList merge(const StringList& List1, const StringList& List2) {
	StringList List;
	int size = List1.size() + List2.size();
	bool useFirst = List1.size() > 0 ;
	int counter1 = 0;
	int counter2 = 0;
	for (int i = 0; i < size; i++) {
		if (useFirst && counter1< List1.size()) {
			List.insert(List1.retrieve(counter1),i);
			counter1++;
			if (counter2 < List2.size())
			useFirst = false;
		}
		else if (!useFirst && counter2 < List1.size()) {
			List.insert(List2.retrieve(counter2),i);
			counter2++;
			if (counter1 < List1.size())
			useFirst = true;
		}
	}
	return List;
}