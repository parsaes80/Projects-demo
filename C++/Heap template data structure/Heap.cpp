#include <iostream>
#include <stdexcept>
#include <vector>
using std::runtime_error;
using std::cout;
using std::vector;
#ifndef hh
#define hh
//helper methods
template <class T>
void swap(T& i, T& j) {
	T temp = i;
	i = j;
	j = temp;
}
int parent(int index) {

	if (index % 2 == 0) {  // cheak if its the right childs 
		return (index - 2) / 2;  
	}
	else { // when its left childs 
		return (index - 1) / 2;
	}

}
template <class T>
class Heap {

public:
	Heap(int si) {
		T* temp = new T[si];
		arr = temp;
		siz = 0;
		maxsiz = si;
	}

	Heap(const Heap& obj) {
		siz = obj.siz;
		maxsiz = obj.maxsiz;
		T* temp = new T[maxsiz];
		arr = temp;
		for (int i = 0; i < obj.siz; i++) {
			arr[i] = obj.arr[i]; //no need to use insert since obj.arr is already in heap form
		}

	}

	~Heap() {
		delete[] arr;
	}

	Heap& operator=(const Heap& obj) {
		
		siz = obj.siz;
		maxsiz = obj.maxsiz;
		T* temp = new T[siz];
		arr = temp;
		for (int i = 0; i < siz; i++) {
			arr[i] = obj.arr[i];  //no need to use insert since obj.arr is already in heap form
		}
		return *this;
	}

	void insert(int num) {
		if (siz == maxsiz) { // array is full
			throw runtime_error("yeet");
		}
	
		else {
			int i = siz;
			arr[i] = num; //puting new value to the end of the array
			//compering the new value to its parent until its at the right location
			while (arr[i] > arr[parent(i)] && i>0) { 
				swap(arr[i], arr[parent(i)]);
				i = parent(i);
			}
		}
		siz++;
	}
	T remove() {
		if (siz == 0) {
			throw runtime_error("yeet");
		}
		else {
			int i=0;
			T val = arr[0];
			siz--; //last element is not considered in array anymore
			arr[0] = arr[siz];
			while ((2*i+2) < siz) { //loop continues until there is at least a left child

				if ((2 * i + 2) < siz) { //arr[i] has 2 childs
					if (arr[2 * i + 2] > arr[2 * i + 1]) {//right is bigger
						swap(arr[2 * i + 2], arr[i]);
						i = i * 2 + 2;
					}
					else {//equal or left is bigger
						swap(arr[2 * i + 1], arr[i]);
						i = i * 2 + 1;
					}
				}
				else {
					if (arr[2 * i + 1] > arr[i]) {//left is bigger
						swap(arr[2 * i + 1], arr[i]);
						i = i * 2 + 1;
					}
				}
			
			}

			return val;
		}
		
	}
	T peek() const {
		if (siz == 0) {
			throw runtime_error("yeet");
		}
		return arr[0];
	}

	Heap merge(const Heap& obj) {

		Heap a(siz + obj.siz);

		for (int i = 0; i < siz; i++) {
			a.arr[i] = arr[i];//arr is already in heap form so no need to use insert()
			a.siz=a.siz+1;
		}
		for (int i = 0; i < obj.siz; i++) {
			a.insert(obj.arr[i]);  // use insert() to retain the heap form
		}
		return a;
	}
	int size() const {
		return siz;

	}
	void print() const {//a helper method that prints heap 
		int n = 0;
		for (int i = 0; i < siz; i++) {
			cout <<" "<< arr[i];
			if (n == i) {
				cout << std::endl;
				n = 2 * n + 2;
			}
		}
		cout << std::endl;

	}

private:

	T* arr;
	int siz, maxsiz;
};

template <class T>
vector<T> smallestm(vector<T> input, int m) {
	//when m is too big or small set it to the length if the vector.
	if ((m > input.size()) || ( m<0) ) {
		m = input.size();
	}

	int n = input.size();
	//we reverse the sign of the values in the input vector so that the minimum value
	//goes to the top of the max heap then we can easily remove it
	for (int i = 0; i < n; i++) {  
		                          
		input[i] = -1* input[i];
	}
	Heap<T> obj(n);  // The template heap parameter

	for (int i = 0; i < n; i++) {

		obj.insert(input[i]);  //using insert to maintain the heap properties
	}
	vector<T> output;
	//removing m numbers of root from heap a to vector b, and reversing the sign to its original
	for (int i = 0; i < m; i++) {

		output.push_back( -1 * obj.remove() );
	}


	return output;
}


#endif 
