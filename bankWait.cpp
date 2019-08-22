//Christian Galleisky
//Student id: 100222190
//Email: galle038@cougars.csusm.edu

#include <iostream>
#include <cstdlib>
#include <time.h>
#include <exception>

using namespace std;

class Bank;
class Event_Queue;
class Customer_Queue;

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
/////build Event handling

struct Event_Node {
	int type;//number >= 0 means arrival, negative number means departure
	long occuranceTime;
	bool accessed = false; //can I do this? Initialize a variable like this?
	Event_Node * next;
};

class Event_Queue {
private:
	Event_Node *front;
public:
	Event_Queue();
	void enQueue(int data, long occuranceTime);
	Event_Node* deQueue();
	Event_Node getHead();
	bool isEmpty();
	int getSize();
};

Event_Queue::Event_Queue() {
	front = NULL;
}

void Event_Queue::enQueue(int type, long occuranceTime) {
	Event_Node *newElement = new Event_Node;
	newElement->type = type;
	newElement->occuranceTime = occuranceTime;
	Event_Node *curr = front;
	if (front == NULL) {
		newElement->next = NULL;
		front = newElement;
	}
	else {
		while (curr->next != NULL) {
			curr = curr->next;
		}
		newElement->next = NULL;
		curr->next = newElement;
	}
}

//we must handle the data block pointed to by the returned pointer
//this value must be deallocated AFTER this function executes
Event_Node* Event_Queue::deQueue() {
	Event_Node *temp = front;
	//Event_Node *toBeDeleted = front;
	if (front == NULL) {
		return temp;
	}
	else if (front->next == NULL) {
		front = NULL;
		//delete toBeDeleted;
		return temp;
	}
	else {
		front = front->next;
		//delete toBeDeleted;
		return temp;
	}
}

Event_Node Event_Queue::getHead() {
	return *front;
}

bool Event_Queue::isEmpty() {
	return front == NULL;
}

int Event_Queue::getSize() {
	Event_Node *curr = front;
	int size = 0;
	while (curr != NULL) {
		size++;
		curr = curr->next;
	}
	return size;
}
////////////////////////////////////////////////
////////////////////////////////////////////////
//setup second Queue (for customer data)

struct Customer_Node {
	long arrivalTime; //absolute time in seconds only
	long serviceTime; //delta time in seconds only
	Customer_Node *next;
};

class Customer_Queue {
private:
	Customer_Node *front;
public:
	Customer_Queue();
	void enQueue(long arrivalTime, long serviceTime);
	Customer_Node* deQueue();
	Customer_Node* getHead();
	bool isEmpty();
	int getSize();
};

Customer_Queue::Customer_Queue() {
	front = NULL;
}

void Customer_Queue::enQueue(long arrivalTime, long serviceTime) {
	Customer_Node *newElement = new Customer_Node;
	newElement->arrivalTime = arrivalTime;
	newElement->serviceTime = serviceTime;
	Customer_Node *curr = front;
	if (front == NULL) {
		newElement->next = NULL;
		front = newElement;
	}
	else {//front next might be dangling
		while (curr->next != NULL) {
			curr = curr->next;
		}
		newElement->next = NULL;
		curr->next = newElement;
	}
}

//we must handle the data block pointed to by the returned pointer
//this value must be deallocated AFTER this function executes
Customer_Node* Customer_Queue::deQueue() {
	Customer_Node *temp = front;
	//Customer_Node *toBeDeleted = front;//What do I delete?
	if (front == NULL) {
		return temp;
		//delete toBeDeleted;
	}
	else if (front->next == NULL) {
		front = NULL;
		//delete toBeDeleted;//What do I delete?
		return temp;
		//delete toBeDeleted;
	}
	else {
		front = front->next;
		//delete toBeDeleted;//What do I delete?
		return temp;
		//delete toBeDeleted;
	}
}

Customer_Node* Customer_Queue::getHead() {
	Customer_Node *temp = front;
	return temp;
}

bool Customer_Queue::isEmpty() {
	return front == NULL;
}

int Customer_Queue::getSize() {
	Customer_Node *curr = front;
	int size = 0;
	while (curr != NULL) {
		size++;
		curr = curr->next;
	}
	return size;
}
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
/////build Bank class

class Bank {
private:
	Event_Queue events, events_temp;
	Customer_Queue incomplete_customers, temp_incomplete_customers, complete_customers;
	int customerCount;
	long Time;//clock
	long totalWaitTime;
	long lastArrivalTime;
	long lastDepartureTime;
	long arrivalOfFirstInLine;
public:
	Bank();
	double runBank();
	void buildCompleteEventQueue();
};

Bank::Bank() {
	customerCount = 0;
	Time = 0;
	totalWaitTime = 0;
	lastArrivalTime = 0;
	lastDepartureTime = 0;
	arrivalOfFirstInLine = 0;

}

void Bank::buildCompleteEventQueue() {

	bool swvitch = false;

	//build an arrival event node and enqueue it
	//save to lastarrivalTime member, the time, namely zero.

	while (Time <= 480) {
		//build random event type

		//test for type of event

		//if arrival, build random time that is no greater than five more than "lastArrivalTime".
		//update lastArrivalTime to new time. Build new customer without a service time and enqueue it.

		//if departure, generate random number that is no more than ten greater
		//than arrivalOfFirstInLine.
		//find next customers arrivalTime (in customer queue, move them to temp_incomplete_customer)
		//and set arrivalOfFirstInLine equal to it. 
		
		int eventType = (rand() % 100) - 50;

		if (eventType >= 0) {
			long arrivalPlus = rand() % 6;
			long arrivalTime = lastArrivalTime + arrivalPlus;
			Time = arrivalTime;
			events.enQueue(eventType, arrivalTime);
			lastArrivalTime = arrivalTime;
			incomplete_customers.enQueue(arrivalTime, 0);//build incomplete customer, but has what we need to continue
			if (swvitch) {
				arrivalOfFirstInLine = arrivalTime;
				swvitch = false;
			}
		}
		else {
			Customer_Node *cNode = new Customer_Node;//do I need to do this, to catch a returned node*
			cNode = incomplete_customers.deQueue();//access NEXT leader in line and get it's arrivaltime

			if (cNode != NULL) {
				long departurePlus = rand() % 11;
				long departureTime = arrivalOfFirstInLine + departurePlus;//this works because the initial condition is zero
				Time = departureTime;
				events.enQueue(eventType, departureTime);//build event node
				long Arrival_time = cNode->arrivalTime; //this corresponds to the old value of arrivaloffirstinline
				temp_incomplete_customers.enQueue(Arrival_time, 0);//incomplete customer
				delete cNode;

				Customer_Node *cNode = new Customer_Node;//do I need to do this, to catch a returned node*
				cNode = incomplete_customers.getHead();
				if (cNode != NULL) {//if this is true, we will enter upper if on next time through
					Arrival_time = cNode->arrivalTime;
					delete cNode;
					arrivalOfFirstInLine = Arrival_time;//done
					//temp_incomplete_customers.enQueue(Arrival_time, 0);
				}
				else {
					//cNode was NULL, there was no wait time. The next customers' arrival time is the firstinline time 
					swvitch = true;//haha
					delete cNode;
				}
			}
			else {
				//no customers to depart
			}
		}
	}
}

double Bank::runBank() {
	buildCompleteEventQueue();
	
	return 0.0;
}

//////////////////////////////////////////////////
//////////////////////////////////////////////////

int main() {

	Bank bank;
	double result = bank.runBank();
	system("PAUSE");

	return 0;
}

/*
build queue of events
*----*----/--/   *----/*----**---/---/--/  star is arrival dash is time passing in sum and slash is departure
when i get an arrival i build a event node and a customer node, the customer node doesn't get completed (the 
service duration) untill i get a departure. So, we can build a queue of incomplete customers and then dequeue
the front when we get a departure and access and modify its service time based on a few things: 
1-servicetime = departuretime(this)-departuretime(this-1element)
Now we must finish the calculation of total WAIT Time;
To do this we could repeat the process of building an event and then either building a customer or
dequeueing a customer and completing the build of the customer(as was described above, completing their 
service time member). When you dequeue a customer you dequeue from "incomplete_customers" and enqueue the
complete customer_node into "complete_customers". Run this process untill totalTime variable is above 480. Then
you stop adding customers. To complete the customers nodes, randomly generate their departure times and do as 
described above until you have emptied incomplete_customers queue. Now you have a queue of complete customers 
all having an arrival time and a service time. To calculate each wait time do as follows:
we will need a local variable as well as the customer node's variables--
currtime will be our local variable it starts at 0 and updates    
waittime = currtime - arrivaltime (except on the first iteration their is no waittime)
currtime is the total time after a service is completed
*/