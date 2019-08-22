//Christian Galleisky
//100222190
//galle038@cougars.csusm.edu

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct BSTNode {
	int data;
	int height;
	BSTNode *LC;
	BSTNode *RC;
	BSTNode(int data) {
		this->data = data;
		LC = NULL;
		RC = NULL;
		height = 0;
	}
};

class BST {
private:
	BSTNode *root;
public:
	BST();
	void prettyprint();
	void preorder();
	void preorder(BSTNode *root);
	void inorder();
	void inorder(BSTNode *root);
	void postorder();
	void postorder(BSTNode *root);
	BSTNode* search(int key);
	BSTNode* search(BSTNode *root, int key);
	void insert(int data);
	BSTNode* insert(BSTNode *root, int data);
	void remove(int key);
	BSTNode* remove(BSTNode *root, int key);
	void balancedInsert(int data);
	BSTNode* balancedInsert(BSTNode *root, int data);
	void readInFile(BST& bst);
	void readInFileSelfBalancing(BST& bst);
	BSTNode* rightMostNode(BSTNode *root);
	BSTNode* rightRotate(BSTNode *z);
	BSTNode* leftRotate(BSTNode *z);
	int getBalance(BSTNode *node);
	int height(BSTNode *node);
	int max(int a, int b);

};
//--------------------------------
//--------------------------------
BST::BST() {
	root = NULL;
}
//--------------------------------
//--------------------------------
void BST::prettyprint() {

}
//--------------------------------
//--------------------------------
void BST::preorder() {
	preorder(root);
}
//--------------------------------
//--------------------------------
void BST::preorder(BSTNode *root) {
	if (root == NULL) {
		return;
	}
	cout << root->data << endl;
	preorder(root->LC);
	preorder(root->RC);
}
//--------------------------------
//--------------------------------
void BST::inorder() {
	inorder(root);
}
//--------------------------------
//--------------------------------
void BST::inorder(BSTNode *root) {
	if (root == NULL) {
		return;
	}
	inorder(root->LC);
	cout << root->data << endl;
	inorder(root->RC);
}
//--------------------------------
//--------------------------------
void BST::postorder() {
	postorder(root);
}
//--------------------------------
//--------------------------------
void BST::postorder(BSTNode *root) {
	if (root == NULL) {
		return;
	}
	postorder(root->LC);
	postorder(root->RC);
	cout << root->data << endl;
}
//--------------------------------
//--------------------------------
BSTNode* BST::search(int key) {
	return search(this->root, key);
}
//--------------------------------
//--------------------------------
BSTNode* BST::search(BSTNode *root, int key) {
	if (root == NULL || root->data == key) {
		return root;
	}
	else if (root->data < key) {
		search(root->RC, key);
	}
	else {
		search(root->LC, key);
	}
}
//--------------------------------
//--------------------------------
void BST::insert(int data) {
	root = insert(root, data);
}
//--------------------------------
//--------------------------------
BSTNode* BST::insert(BSTNode *root, int data) {
	if (root == NULL) {
		root = new BSTNode(data);
		return root;
	}
	else if (root->data > data) {
		root->LC = insert(root->LC, data);
	}
	else if (data > root->data) {
		root->RC = insert(root->RC, data);
	}
	else {
		return root;//no duplicate keys allowed
	}
}
//--------------------------------
//--------------------------------
void BST::remove(int key) {
	root = remove(root, key);
}
//--------------------------------
//--------------------------------
BSTNode* BST::remove(BSTNode *root, int key) {
	if (root == NULL) {
		return root;
	}
	if (root->data > key) {
		root->LC = remove(root->LC, key);
	}
	else if (key > root->data) {
		root->RC = remove(root->RC, key);
	}
	else {
		if (root->LC == NULL) {
			BSTNode *temp = root->RC;
			delete root;
			return temp;
		}
		else if (root->RC == NULL) {
			BSTNode *temp = root->LC;
			delete root;
			return temp;
		}
		else {
			BSTNode *temp = rightMostNode(root->LC);
			root->data = temp->data;
			root->LC = remove(root->LC, temp->data);
		}
		return root;//don't perfectly understand this step, still...
	}
}
//--------------------------------
//--------------------------------
BSTNode* BST::rightMostNode(BSTNode *root) {
	BSTNode *current = root;
	while (current->RC != NULL) {
		current = current->RC;
	}
	return current;
}
//--------------------------------
//--------------------------------
int BST::max(int a, int b){
	return (a > b) ? a : b;
}
//--------------------------------
//--------------------------------
int BST::height(BSTNode *node){
	if (node == NULL) {
		return -1;
	}
	return node->height;
}
//--------------------------------
//--------------------------------
int BST::getBalance(BSTNode *node){
	if (node == NULL) {
		return 0;
	}
	return height(node->LC) - height(node->RC);
}
//--------------------------------
//--------------------------------
BSTNode* BST::leftRotate(BSTNode *z){
	BSTNode *y = z->RC;
	BSTNode *leaf = y->LC;
	//perform rotation
	y->LC = z;
	z->RC = leaf;
	//update heights
	z->height = max(height(z->LC), height(z->RC)) + 1;
	y->height = max(height(y->LC), height(y->RC)) + 1;
	//return new root
	return y;
}
//--------------------------------
//--------------------------------
BSTNode* BST::rightRotate(BSTNode *z) {
	BSTNode *y = z->LC;
	BSTNode *leaf = y->RC;
	//perform rotation
	y->RC = z;
	z->LC = leaf;
	//update heights
	z->height = max(height(z->LC), height(z->RC)) + 1;
	y->height = max(height(y->LC), height(y->RC)) + 1;
	//return new root
	return y;
}
//--------------------------------
//--------------------------------
void BST::balancedInsert(int data) {
	root = balancedInsert(root, data);
}
//--------------------------------
//--------------------------------
BSTNode* BST::balancedInsert(BSTNode *root, int data){
	if (root == NULL) {
		 return (root = new BSTNode(data));
	}
	else if (root->data > data) {
		root->LC = insert(root->LC, data);
	}
	else if (data > root->data) {
		root->RC = insert(root->RC, data);
	}
	else {//equal keys not allowed
		return root;
	}
	root->height = 1 + max(height(root->LC), height(root->RC));
	int balance = getBalance(root);
	if (balance > 1 && data < root->LC->data) {
		return rightRotate(root);
	}
	else if (balance < -1 && data > root->RC->data) {
		return leftRotate(root);
	}
	else if (balance > 1 && data > root->LC->data) {
		root->LC = leftRotate(root->LC);
		return rightRotate(root);
	}
	else if (balance < -1 && data < root->RC->data) {
		root->RC = rightRotate(root->RC);
		return leftRotate(root);
	}
	else {
		return root;
	}
}
//--------------------------------
//--------------------------------
void BST::readInFile(BST& bst) {
	cout << endl;
	cout << "Enter an integers to store in your BST(Because it is a BST no repeats are allowed):" << endl;
	cout << "Enter a negative integer to discountinue input." << endl;
	int x;
	cin >> x;
	while (x >= 0) {
		bst.insert(x);
		cout << "Next number will be...?" << endl;
		cin >> x;
	}
}
//--------------------------------
//--------------------------------
void BST::readInFileSelfBalancing(BST& bst) {
	cout << endl;
	cout << "Enter an integers to store in your BST(Because it is a BST no repeats are allowed):" << endl;
	cout << "Enter a negative integer to discountinue input." << endl;
	int x;
	cin >> x;
	while (x >= 0) {
		bst.balancedInsert(x);
		cout << "Next number will be...?" << endl;
		cin >> x;
	}
}
//--------------------------------
//--------------------------------
int main() {
	BST bst0;
	bst0.readInFile(bst0);
	cout << "Preorder:" << endl;
	bst0.preorder();
	cout << endl << endl;
	cout << "Inorder:" << endl;
	bst0.inorder();
	cout << endl << endl;
	cout << "Postorder:" << endl;
	bst0.postorder();
	cout << endl << endl;

	system("PAUSE");
	
	cout << "Self Balancing Search Tree:" << endl;

	BST bst1;
	bst1.readInFileSelfBalancing(bst1);
	cout << "Preorder:" << endl;
	bst1.preorder();
	cout << endl << endl;
	cout << "Inorder:" << endl;
	bst1.inorder();
	cout << endl << endl;
	cout << "Postorder:" << endl;
	bst1.postorder();
	cout << endl << endl;

	system("PAUSE");
	
	return 0;
}