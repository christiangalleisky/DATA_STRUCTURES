//Christian Galleisky
//id: 100222190
//email: galle038@cougars.csusm.edu

#include <iostream>

using namespace std;

struct Node {
	char *name;
	long long int id;
	int age;
	float GPA;
	Node *next;
	Node(char name[], long long int id, int age, float GPA) {
		this->name = name;
		this->id = id;
		this->age = age;
		this->GPA = GPA;
		next = NULL;
	}
};

class HashTable {
private:
	Node **seperateChains;
	int size;
public:
	HashTable(int size);
	void insert(char name[], long long int id, int age, float GPA);
	Node* search(long long int key);
	void printTable();
	unsigned long hash(char *str);
	~HashTable();
};

HashTable::HashTable(int size){
	seperateChains = new Node*[size];
	for (int i = 0; i < size; i++) {
		seperateChains[i] = NULL;
	}
	this->size = size;
}
void HashTable::printTable(){
	for (int i = 0; i < size; i++) {
		Node *curr = seperateChains[i];
		while (curr != NULL) {
			cout << curr->name << " : " << curr->id << endl;
			curr = curr->next;
		}
	}
}
unsigned long HashTable::hash(char *str){
	unsigned long hash = 5381;
	int c;
	while (c = *str++) {
		hash = hash * 33 + c;
	}
	return hash;
}
void HashTable::insert(char name[], long long int id, int age, float GPA) {
	int index = (hash(name) % size);
	Node *curr = seperateChains[index];
	Node *newElement = new Node(name, id, age, GPA);
	if (curr == NULL) {
		seperateChains[index] = newElement;
	}
	else if (curr->next != NULL) {
		while (curr->next != NULL) {
			curr = curr->next;
		}
		curr->next = newElement;
	}
	else {
		curr->next = newElement;
	}
}
Node* HashTable::search(long long int key) {
	Node *curr = NULL;
	for (int i = 0; i < size; i++) {
		curr = seperateChains[i];
		while (curr != NULL) {
			if (curr->id == key) {
				return curr;
			}
			curr = curr->next;
		}
	}
	return curr;
}
HashTable::~HashTable() {
	for (int i = 0; i < size; i++) {
		while (seperateChains[i] != NULL) {
			Node *temp = seperateChains[i];
			seperateChains[i] = seperateChains[i]->next;
			delete temp;
		}
	}
}

int main() {

	char name0[] = "CHRIS";
	char name1[] = "ANGIE";
	char name2[] = "MEL";
	char name3[] = "MILO";
	HashTable ll0(100);
	ll0.insert(name0, 1234567890, 29, 2.9);
	ll0.insert(name1, 1234567809, 35, 3.9);
	ll0.insert(name2, 1234567908, 30, 2.5);
	ll0.insert(name3, 1234560897, 31, 1.5);
	ll0.printTable();

	Node *item0 = ll0.search(1234567890);
	Node *item1 = ll0.search(1234567777);

	cout << endl << endl;
	cout << item0->name << endl;
	if (item1 == NULL) {
		cout << "null" << endl;
	}



	system("PAUSE");

	return 0;
}