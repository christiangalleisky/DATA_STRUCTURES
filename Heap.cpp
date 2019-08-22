//student id: 100222190
//email: galle038@cougars.csusm.edu
//name: Christian Galleisky

#include <iostream>

class MaxHeap {
private:
	int *data;
	int capacity;
	int size;
public:
	MaxHeap(int capacity);
	void Insert(int e) throw();//throws -1 overflow error code
	void Delete(int e) throw();//throws -3 underflow error code and -5 no element found error code
	int ExtractMax() throw();
	void BuildHeap(int *a, int length);
	int parent(int i);
	int left(int i);
	int right(int i);
	int getSize();
	bool isLeaf(int i);
	void swap(int *x, int *y);
	void siftup(int i);
	void siftdown(int i);
	void printHeap();
};
//-----------------------------------------
//-----------------------------------------
MaxHeap::MaxHeap(int capacity){
	data = new int[capacity];
	size = 0;
	this->capacity = capacity;
}
//-----------------------------------------
//-----------------------------------------
int MaxHeap::parent(int i) { return (i - 1) / 2; }
//-----------------------------------------
//-----------------------------------------
int MaxHeap::left(int i) { return (2 * i) + 1; }
//-----------------------------------------
//-----------------------------------------
int MaxHeap::right(int i) { return (2 * i) + 2; }
//-----------------------------------------
//-----------------------------------------
int MaxHeap::getSize() { return size; }
//-----------------------------------------
//-----------------------------------------
bool MaxHeap::isLeaf(int i) {return (i < (this->getSize()) / 2) ? false : true; }
//-----------------------------------------
//-----------------------------------------
void MaxHeap::swap(int *x, int *y) {
		int temp = *x;
		*x = *y;
		*y = temp;
}
//-----------------------------------------
//-----------------------------------------
void MaxHeap::siftup(int i) {
	while (i > 0 && (data[parent(i)] < data[i])) {
		swap(&data[i], &data[parent(i)]);
		i = parent(i);
	}
}
//-----------------------------------------
//-----------------------------------------
void MaxHeap::siftdown(int i) {
	while (!isLeaf(i)) {
		int l = left(i);
		int r = right(i);
		int larger = l;
		if (r < size) {
			larger = (data[l] > data[r]) ? l : r;
		}
		if (data[i] >= data[larger]) {
			break;
		}
		swap(&data[i], &data[larger]);
		i = larger;
	}

}
//-----------------------------------------
//-----------------------------------------
//throws -1 overflow error code
void MaxHeap::Insert(int e) throw(){
	if (size >= capacity) {
		throw - 1;
	}
	int i = size;
	data[i] = e;
	siftup(i);
	size++;
}
//-----------------------------------------
//-----------------------------------------
//throws -3 underflow error code and -5 no element found error code
//also, will remove multiple elements of same value
void MaxHeap::Delete(int e) throw(){
	if (size <= 0) {
		throw - 3;
	}
	bool sentinal = false, wasAnElement = false;
	int i;
	while(i != size){
		for (i = 0; i < size; i++) {
			if (data[i] = e) {
				wasAnElement = true;
				break;
			}
			
		}
		if (i == size && !wasAnElement) {
			sentinal = true;
		}
		data[i] = data[size - 1];
		size--;
		if (data[i] > data[parent(i)]) {
			siftup(i);
		}
		else {
			siftdown(i);
		}
	}
	if (sentinal) {
		throw - 5;
	}
}
//-----------------------------------------
//-----------------------------------------
int MaxHeap::ExtractMax() throw(){
	if (size <= 0) {
		throw - 3;
	}
	if (size == 1) {
		return data[--size];
	}
	int r = data[0];
	data[0] = data[size - 1];
	size--;
	siftdown(0);
	return r;
}
//-----------------------------------------
//-----------------------------------------
void MaxHeap::BuildHeap(int *a, int length){
	data = new int[length];
	data = a;
	capacity = size = length;
	int half = (size / 2) - 1;
	for (int i = half; i >= 0; i--) {
		siftdown(i);
	}
}
//-----------------------------------------
//-----------------------------------------
void MaxHeap::printHeap(){
	cout << endl;
}
//-----------------------------------------
//-----------------------------------------

int main() {
	
	try {

		int A[15] = { 0,1,2,3,4,5,6,7,8,9,10,14,13,12,11 };

		MaxHeap heap0(10);
		heap0.BuildHeap(A, 15);
	}
	catch (int e) {
		system("PAUSE");
	}
	

	return 0;
}