//Christian Galleisky
//id 100222190
//email galle038@cougars.csusm.edu

#include <iostream>

using namespace std;

struct Edge {
	int adjacent_Vertice;
	Edge *next;
	Edge(int data) {
		this->adjacent_Vertice = data;
		this->next = NULL;
	};
};

class Queue {
private:
	Edge *rootFront;
public:
	Queue();
	void push_back(int data);
	int front();
	int pop();
	void printQ();
	bool isEmpty();
};

Queue::Queue() {
	this->rootFront = NULL;
}

void Queue::push_back(int data) {
	Edge *curr = this->rootFront;
	Edge *newElement = new Edge(data);
	if (rootFront == NULL) {
		newElement->next = NULL;
		rootFront = newElement;
	}
	else {
		while (curr->next != NULL) {
			curr = curr->next;
		}
		newElement->next = NULL;
		curr->next = newElement;
	}
}

int Queue::front() {
	while (!isEmpty()) {
		return rootFront->adjacent_Vertice;
	}
	return -1;
}

int Queue::pop() {
	if (!isEmpty()) {
		int val = rootFront->adjacent_Vertice;
		Edge *temp = rootFront;
		rootFront = rootFront->next;
		delete temp;
		return val;
	}
	return -1;//find static constant perhaps global var for minimum integer
}

void Queue::printQ() {
	Edge *current = rootFront;
	cout << "Here lies front of Queue: ";
	while (current != NULL) {
		cout << current->adjacent_Vertice << "->";
		current = current->next;
	}
	cout << endl;
}

bool Queue::isEmpty() {
	return rootFront == NULL;
}

class Graph {
private:
	int Vertices;
	Edge **adj;
	void DFSUtility(int vertice, bool *visited);
public:
	Graph(int v);
	void addEdge(int v, int w);
	void DFS(int v);
	void BFS(int v);
	void addNodes(int n);
};

Graph::Graph(int vertices_total){
	Vertices = vertices_total;
	adj = new Edge*[vertices_total];
	for (int i = 0; i < vertices_total; i++) {
		adj[i] = NULL;
	}
}

void Graph::addEdge(int v, int w) {
	//insert w into v's adjacency list
	Edge *current = adj[v];
	if (current == NULL) {
		Edge *newElement = new Edge(w);
		adj[v] = newElement;
	}
	else {
		while (current->next != NULL) {
			current = current->next;
		}
		Edge *newElement = new Edge(w);
		current->next = newElement;
	}
	//insert v into w's adjacency list, the edge is in both lists
	current = adj[w];
	if (current == NULL) {
		Edge *newElement = new Edge(v);
		adj[w] = newElement;
	}
	else {
		while (current->next != NULL) {
			current = current->next;
		}
		Edge *newElement = new Edge(v);
		current->next = newElement;
	}
}

void Graph::DFS(int v) {
	bool *visited = new bool[Vertices];
	for (int i = 0; i < Vertices; i++) {
		visited[i] = false;
	}
	DFSUtility(v, visited);
	cout << endl << endl;
}

void Graph::DFSUtility(int v, bool *visited) {
	visited[v] = true;
	cout << v << "->";
	Edge *current = adj[v];
	while (current != NULL) {
		int val = current->adjacent_Vertice;
		if (!visited[val]) {
			DFSUtility(val, visited);
		}
		current = current->next;
	}
}

void Graph::BFS(int v) {
	bool *visited = new bool[Vertices];
	for (int i = 0; i < Vertices; i++) {
		visited[i] = false;
	}
	Queue que;
	visited[v] = true;
	que.push_back(v);
	while (!que.isEmpty()) {
		int u = que.front();
		cout << u << "->";
		que.pop();
		Edge *current = adj[u];
		while (current != NULL) {
			int val = current->adjacent_Vertice;
			if (!visited[val]) {
				visited[val] = true;
				que.push_back(val);
			}
			current = current->next;
		}
	}
	cout << endl << endl;
}

//copies all adjacency lists and adds new nodes with empty lists.
void Graph::addNodes(int n) {
	Edge **newAdj = new Edge*[Vertices + n];
	for (int i = 0; i < Vertices; i++) {
		newAdj[i] = adj[i];
	}
	for (int i = Vertices; i < (Vertices + n); i++) {
		newAdj[i] = NULL;
	}
	Vertices = Vertices + n;
	adj = newAdj;
}

int main() {

	Queue q0;
	q0.push_back(0);
	q0.push_back(1);
	q0.push_back(2);
	q0.push_back(3);
	q0.push_back(4);
	q0.printQ();
	int val = q0.pop();
	int val2 = q0.front();
	cout << val << endl;
	cout << val2 << endl;

	Queue q1;//must always enclose a queue in 
	         //"while(!isEmpty()) call for "pop value -1" protection
	int val3 = q1.pop();
	cout << "empty queue pop value: " << val3 << endl;
	system("PAUSE");

	Graph g0(5);
	g0.addEdge(0, 2);
	g0.addEdge(0, 1);
	g0.addEdge(2, 3);
	g0.addEdge(3, 4);
	cout << "Depth first search." << endl;
	g0.DFS(0);
	system("PAUSE");

	Graph g1(8);
	g1.addEdge(0, 1);
	g1.addEdge(0, 2);
	g1.addEdge(0, 3);
	g1.addEdge(1, 4);
	g1.addEdge(1, 5);
	g1.addEdge(2, 6);
	g1.addEdge(2, 7);
	cout << "Breadth first search." << endl;
	g1.BFS(0);
	system("PAUSE");

	g1.addNodes(30);
	cout << "Breadth first search after addition of nodes." << endl;
	g1.BFS(0);
	system("PAUSE");


	return 0;

}