#include <iostream>
#include <string.h>

struct item {
	char* res;
	char* f1;
	char* f2;
	char* ac;
	char* bd;
	char* f1sumf2sum;
	int size;
	int line;
	int flag;
};
struct node {
	node* next;
	item box;
};
class stack {
private:
	node* top;
public:
	stack() {
		top = nullptr;
	}
	~stack() {
		makeEmpty();
	}
	void makeEmpty() {
		node* temp;
		while (top != nullptr)
		{
			temp = top;
			top = top->next;
			delete temp;
		}
	}
	bool isEmpty() {
		return(top == nullptr);
	}
	void push(item data) {
		node* temp = new node;
		temp->box = data;
		temp->next = top;
		top = temp;
	}
	item pop() {
		if (isEmpty())
		{
			std::cout << "stack empty";
			exit(1);
		}
		node* temp = top;
		item data = top->box;
		top = top->next;
		delete temp;
		return data;
	}
};