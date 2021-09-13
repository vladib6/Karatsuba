#include"stack.h"
void stack::makeEmpty() {
	node* temp;
	while (top != nullptr)
	{
		temp = top;
		top = top->next;
		delete temp;
	}
}
bool stack::isEmpty() {
	return(top == nullptr);
}
void stack::push(item data) {
	node* temp = new node;
	temp->box = data;
	temp->next = top;
	top = temp;
}
item stack::pop() {
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