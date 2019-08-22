//name: Christian Galleisky
//student id#: 100222190
//email: galle038@cougars.csusm.edu

#include <iostream>
#include <stack>

using namespace std;

class Stack;
class CharStack;
class calculator;

struct Node
{
	double data;
	Node *next;
};

struct Node2
{
	char data;
	Node2 *next;
};

class Stack {
private:
	Node *topp;
public:
	Stack();
	~Stack();
	void push(double data);
	double pop();
	double top();
	bool empty();
	void clearStack();
};

Stack::Stack() {
	topp = NULL;
}
Stack::~Stack() {
	this->clearStack();
}
void Stack::push(double data){
	Node *newElement = new Node;
	newElement->data = data;
	if(topp == NULL) {
		newElement->next = NULL;
		topp = newElement;
	}
	else {
		newElement->next = topp;
		topp = newElement;
	}
}
double Stack::pop(){
	double val = topp->data;
	Node *temp = topp;
	topp = topp->next;
	delete temp;
	return val;
}
double Stack::top(){
	return topp->data;
}
bool Stack::empty(){
	if (topp == NULL) {
		return true;
	}
	else {
		return false;
	}
}
void Stack::clearStack(){
	while (topp != NULL) {
		this->pop();
	}
}

class CharStack {
private:
	Node2 *topp;
public:
	CharStack();
	~CharStack();
	void push(char data);
	char pop();
	char top();
	bool empty();
	void clearStack();
};

CharStack::CharStack() {
	topp = NULL;
}
CharStack::~CharStack() {
	this->clearStack();
}
void CharStack::push(char data) {
	Node2 *newElement = new Node2;
	newElement->data = data;
	if (topp == NULL) {
		newElement->next = NULL;
		topp = newElement;
	}
	else {
		newElement->next = topp;
		topp = newElement;
	}
}
char CharStack::pop() {
	char val = topp->data;
	Node2 *temp = topp;
	topp = topp->next;
	delete temp;
	return val;
}
char CharStack::top() {
	return topp->data;
}
bool CharStack::empty(){
	if (topp == NULL) {
		return true;
	}
	else {
		return false;
	}
}
void CharStack::clearStack() {
	while (topp != NULL) {
		this->pop();
	}
}

class calculator {
private:
	Stack values;
	CharStack ops;
	
public:
	double evalExpression(const char* expression);
	int getPrecedence(const char character);
	double applyOp(double a, double b, char op);
	bool isdigit(char character);
};

int calculator::getPrecedence(const char character) {
	if (character == '+' || character == '-') {
		return 1;
	}
	else if (character == '*' || character == '/') {
		return 2;
	}
	else {
		return 0;
	}
}

double calculator::applyOp(double a, double b, char op) {
	switch (op) {
	case '+': return a + b;
	case '-': return a - b;
	case '*': return a * b;
	case '/': return a / b;
	default:
		return NULL;
	}
}

bool calculator::isdigit(char character) {
	switch ((int)character) {
	case 48: return true;
	case 49: return true;
	case 50: return true;
	case 51: return true;
	case 52: return true;
	case 53: return true;
	case 54: return true;
	case 55: return true;
	case 56: return true;
	case 57: return true;
	default:
		return false;

	}
}

double calculator::evalExpression(const char* tokens) {
	int i = 0;
	int k = strlen(tokens);

	while (i < k) {

		if (tokens[i] == ' ')
			continue;

		else if (tokens[i] == '(') {
			ops.push(tokens[i]);
		}
 
		else if (isdigit(tokens[i])) {
			double val = 0.0;
			bool incrementedUp = false;
			while (i < k &&
				isdigit(tokens[i]))
			{
				val = (val * 10) + (tokens[i] - '0');
				i++;
				incrementedUp = true;
			}
			if (incrementedUp) {
				i--;
			}
			values.push(val);
		}

		else if (tokens[i] == ')')
		{
			while (!ops.empty() && ops.top() != '(')
			{
				double val2 = values.top();
				values.pop();

				double val1 = values.top();
				values.pop();

				char op = ops.top();
				ops.pop();

				values.push(applyOp(val1, val2, op));
			}

			// pop opening brace. 
			ops.pop();
		}

		// Current token is an operator 
		else
		{ 
			while (!ops.empty() && getPrecedence(ops.top())
				>= getPrecedence(tokens[i])) {
				double val2 = values.top();
				values.pop();

				double val1 = values.top();
				values.pop();

				char op = ops.top();
				ops.pop();

				values.push(applyOp(val1, val2, op));
			}
			ops.push(tokens[i]);
		}
		i++;
	}

	// Entire expression has been parsed at this 
	// point, apply remaining ops to remaining 
	// values. 
	while (!ops.empty()) {
		double val2 = values.top();
		values.pop();

		double val1 = values.top();
		values.pop();

		char op = ops.top();
		ops.pop();

		values.push(applyOp(val1, val2, op));
	}
	return values.top();
}


int main(){
	char exp1[] = "20*(8+2/4)";
	calculator calc;
	double answer = calc.evalExpression(exp1);
	if (answer == 170.0) {
		cout << "Expression 1 was evaluated correctly." << endl;
	}
	else {
		cout << "Expression 1 was incorrectly evaluated." << endl;
	}
	system("PAUSE");
	return 0;
}