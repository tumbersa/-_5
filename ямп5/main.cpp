#include <iostream>
using namespace std;

struct Queue {
	int info;
	Queue* next;
};

struct Stack {
	int info;
	Stack* next;
};

void initQ(Queue*&tail,Queue*& head) {
	tail = nullptr;
	head = nullptr;
}

void pushQ(Queue*& head, Queue*& tail, int x) {
	if (!head) {
		Queue* q = new Queue;
		q->info = x;
		head = q;
		tail = q;
	}
	else {
		Queue* q = new Queue;
		q->info = x;
		q->next = tail;
		tail = q;
	}
}

int popQ(Queue*& head, Queue*& tail) {
	if (!head) {
		cout << "Queue is empty" << endl;
		return 0;
	}
	else if (tail == head) {
		int x = tail->info;
		delete tail;
		head = tail = nullptr;
		return x;
	}
	else {
		int x = head->info;
		Queue* temp = tail;
		while (temp->next != head) temp = temp->next;
		temp->next = nullptr;
		delete head;
		head = temp;
		return x;
	}
}


void pushS(Stack*& p, int m) {
	Stack* tmp = new Stack;
	tmp->info = m;
	if (!p) {
		tmp->next = nullptr;
		p = tmp;
	}
	else {
		tmp->next = p;
		p = tmp;
	}
}

void initS(Stack*&p) {
	p = nullptr;
}

int popS(Stack*& p) {
	if (p) {
		Stack* tmp = p;
		int x = tmp->info;
		p = p->next;
		tmp->next = nullptr;
		delete tmp;
		return x;
	}
	else return 0;
}

void revQ(Queue*& head, Queue*& tail) {
	Stack* tmp = new Stack;
	initS(tmp);
	while (head) {
		pushS(tmp,popQ(head,tail));
	}
	while (tmp) {
		pushQ(head, tail, popS(tmp));
	}
}

void printQ(Queue*& head, Queue*& tail) {
	Queue* copeHead = nullptr;
	Queue* copeTail = nullptr;
	while (head) {
		int n = popQ(head,tail);
		pushQ(copeHead, copeTail, n);
		cout << n<<" ";
	}
	cout << endl;
	while (copeHead) {
		pushQ(head, tail, popQ(copeHead, copeTail));
	}
}

void lenta(Queue*& head, Queue*& tail, int n) {
	Queue* t1 = new Queue;
	Queue* h1 = new Queue;
	initQ(t1, h1);
	Queue* t2 = new Queue;
	Queue* h2 = new Queue;
	initQ(t2, h2);
	for (int k = n - 1; k >= 0; k--) {
		while (head) {
			for (int i = 0; i < pow(2, k); i++) {
				pushQ(h1, t1, popQ(head, tail));
			}
			for (int i = 0; i < pow(2, k); i++) {
				pushQ(h2, t2, popQ(head, tail));
			}
		}
		while (h1) {
			pushQ(head, tail, popQ(h1, t1));
		}
		revQ(h2, t2);
		while (h2) {
			pushQ(head, tail, popQ(h2, t2));
		}
		printQ(head, tail);
	}
	
}

int main() {
	int n;
	cin >> n;
	Queue* tail, * head;
	initQ(tail,head);
	for (int i = 1; i <= pow(2, n); i++) {
		pushQ(head, tail, i);
	}
	printQ(head, tail);
	cout << endl;
	lenta(head, tail, n);
	cout << endl<<endl;
	lenta(head, tail, n);
	return 0;
}