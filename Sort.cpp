#include <iostream>

using namespace std;

class arraySorter {
private:
public:
	void selectionSort(int A[], int s);
	void bubbleSort(int A[], int s);
	void insertionSort(int A[], int s);
	int partition2(int A[], int pivot, int size);
	void quickSort2(int A[], int pivot, int size);
	int partition(int A[], int pivot, int size);
	void quickSort(int A[], int pivot, int size);
	void merge(int A[], int left, int center, int right);
	void mergeSort(int A[], int left, int right);
	void printArray(int A[], int s);

};
//--------------------------------------------------
//--------------------------------------------------
void arraySorter::printArray(int A[], int s){
	cout << endl;
	for (int i = 0; i < s; i++) {
		cout << A[i];
		if (i == s - 1) {
			break;
		}
			cout << ", ";
	}
	cout << endl;
}
//--------------------------------------------------
//--------------------------------------------------
void arraySorter::selectionSort(int A[], int s){
	for (int i = 0; i < s-1; i++) {
		int largest = A[0];
		int indexOfLargest = 0;
		for (int k = 1; k < s - i; k++) {
			if (A[k] >= largest) {
				largest = A[k];
				indexOfLargest = k;
			}
		}
		int temp = A[s-i-1];
		A[s-i-1] = largest;
		A[indexOfLargest] = temp;
	}
}
//---------------------------------------------------
//---------------------------------------------------
void arraySorter::bubbleSort(int A[], int s){
	
	bool didSwap = true;
	for (int i = 0; i < s-1 && didSwap; i++) {
		didSwap = false;
		for (int k = 0; k < s-i-1; k++) {
			if (A[k] > A[k + 1]) {
				int temp = A[k];
				A[k] = A[k + 1];
				A[k + 1] = temp;
				didSwap = true;
			}
		}
	}
}
//---------------------------------------------------
//---------------------------------------------------
void arraySorter::insertionSort(int A[], int s){
	int i, key, j;
	for (i = 1; i < s; i++) {
		key = A[i];//the element to be inserted
		j = i - 1;
		while (j >= 0 && A[j] > key) {
			A[j + 1] = A[j];
			j--;
		}
		A[j + 1] = key;
	}
}
//----------------------------------------------------
//----------------------------------------------------
int arraySorter::partition2(int A[], int left, int right){
	int i = left, j = right;
	int tmp;
	int pivot = A[(left + right) / 2];

	while (i <= j) {
		while (A[i] < pivot)
			i++;
		while (A[j] > pivot)
			j--;
		if (i <= j) {
			tmp = A[i];
			A[i] = A[j];
			A[j] = tmp;
			i++;
			j--;
		}
	};
	return i;
}
//----------------------------------------------------
//----------------------------------------------------
void arraySorter::quickSort2(int A[], int left, int right){
	int index = partition(A, left, right);
	if (left < index - 1)
		quickSort(A, left, index - 1);
	if (index < right)
		quickSort(A, index, right);
}
//----------------------------------------------------
//----------------------------------------------------
int arraySorter::partition(int A[], int pivot, int size) {
	int i, q, temp;
	int num = A[pivot];
	i = q = pivot + 1;
	while (i <= size) {
		if (A[i] <= num) {
			temp = A[i];
			A[i] = A[q];
			A[q] = temp;
			q++;
		}
		i++;
	}
	temp = A[pivot];
	A[pivot] = A[q - 1];
	A[q - 1] = temp;
	return (q - 1);
}
//----------------------------------------------------
//----------------------------------------------------
void arraySorter::quickSort(int A[], int pivot, int size){
	
	if (pivot >= size) {
		return;
	}
	else {
		int q = partition(A, pivot, size);
		quickSort(A, pivot, q - 1);
		quickSort(A, q + 1, size);
	}
}
//----------------------------------------------------
//----------------------------------------------------
void arraySorter::merge(int A[], int left, int center, int right) {
	
	int i, k, j;
	int *B = new int(right);//couldn't figure out how to address compiler complaint for constant value in 'B' array index
	i = k = left; //(cont.) initializer. Wanted variable B index. couldn't get it. Help!
	j = center + 1;
	while (i <= center && j <= right) {
		if (A[i] <= A[j]) {
			B[k++] = A[i++];
		}
		else {
			B[k++] = A[j++];
		}
	}
	while (i <= center) {
		B[k++] = A[i++];
	}
	while (j <= right) {
		B[k++] = A[j++];
	}
	for (int i = left; i <= right; i++) {
		A[i] = B[i];
	}
}
//----------------------------------------------------
//----------------------------------------------------
void arraySorter::mergeSort(int A[], int left, int right){
	if (left == right) {
		return;
	}
	int q = (left + right) / 2;
	mergeSort(A, left, q);
	mergeSort(A, q + 1, right);
	merge(A, left, q, right);
}
//----------------------------------------------------
//----------------------------------------------------
int main() {

	arraySorter obj0;
	int A[10] = { 9, 0, 8, 1, 7, 2, 6, 3, 5, 4 };
	int s = 10;
	cout << "Array to be sorted." << endl;
	obj0.printArray(A, s);
	system("PAUSE");

	int B[10] = { 9, 0, 8, 1, 7, 2, 6, 3, 5, 4 };
	s = 10;
	obj0.selectionSort(B, s);
	cout << "Selection sort:" << endl;
	obj0.printArray(B, s);
	system("PAUSE");

	int C[10] = { 9, 0, 8, 1, 7, 2, 6, 3, 5, 4 };
	s = 10;
	obj0.bubbleSort(C, s);
	cout << "Bubble sort:" << endl;
	obj0.printArray(C, s);
	system("PAUSE");

	int D[10] = { 9, 0, 8, 1, 7, 2, 6, 3, 5, 4 };
	s = 10;
	obj0.insertionSort(D, s);
	cout << "Insertion sort:" << endl;
	obj0.printArray(D, s);
	system("PAUSE");

	int E[10] = { 9, 0, 8, 1, 7, 2, 6, 3, 5, 4 };
	s = 10;
	//must pass the max array index as size to this function!!!
	//must also pass a 0 as the pivot, doesn't work othewise!!!
	obj0.quickSort(E, 0, s-1);
	cout << "Quicksort pivot at beginning:" << endl;
	obj0.printArray(E, s);
	system("PAUSE");

	int F[10] = { 9, 0, 8, 1, 7, 2, 6, 3, 5, 4 };
	s = 10;
	obj0.mergeSort(F, 0, 9);
	cout << "Mergesort:" << endl;
	obj0.printArray(F, s);
	system("PAUSE");

	int G[10] = { 9, 0, 8, 1, 7, 2, 6, 3, 5, 4 };
	s = 10;
	//must pass the max array index as size to this function!!!
	//parameters or beginning and end of array in this quicksort imp.
	obj0.quickSort2(G, 0, s - 1);
	cout << "Quicksort pivot in middle:" << endl;
	obj0.printArray(G, s);
	system("PAUSE");

	cout << "Take a last look, this is the end of main." << endl;
	system("PAUSE");

	return 0;
}