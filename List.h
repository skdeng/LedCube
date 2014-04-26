#ifndef LIST_H
#define LIST_H

#include "Node.h"

template <typename T>
class List
{
    public:
        List():first(0), last(0), length(0){}
        ~List();
        void push_front(T data);
        void push_back(T data);
        void pop_front();
        void pop_back();
        bool contains(T& element) const;
        T& operator[](int index);
        int size() const{return this->length;};
    private:
        Node<T> * first;
        Node<T> * last;
        int length;
};

template <typename T>
List<T>::~List() {
    while(first){
        Node<T> * pNode = first;
        first = pNode->next;
        delete pNode;
    }
}

template <typename T>
bool List<T>::contains(T& element) const{
    Node<T> *pNode = first;
    int index = length;
    while(index > 0){
    	if(pNode->data == element){
    		return true;
    	}
        pNode = pNode->next;
        index--;
    }
	return false;
}

template <typename T>
void List<T>::push_front(T data) {
    Node<T> *pNode = new Node<T>(data, first, 0);
    if(first != 0){
        first->previous = pNode;
    }
    first = pNode;
    if(last==0){
        last = pNode;
    }
    length++;
}

template <typename T>
void List<T>::push_back(T data) {
    Node<T> *pNode = new Node<T>(data, 0, last);
    if(last != 0){
        last->next = pNode;
    }
    last = pNode;
    if(first==0){
        first = pNode;
    }
    length++;
}

template <typename T>
void List<T>::pop_front(){
	if(this->length > 0){
		Node<T> *pNode = this->first;
		this->first = pNode->next;
		length--;
		delete pNode;
	}
}

template <typename T>
void List<T>::pop_back(){
	if(this->length > 0){
		Node<T> *pNode = this->last;
		this->last = pNode->previous;
		length--;
		delete pNode;
	}
}

template <typename T>
T& List<T>::operator[](int index) {
    if(index < length/2){
        Node<T> *pNode = first;
        while(index > 0){
            pNode = pNode->next;
            index--;
        }
        return pNode->data;
    }else{
        Node<T> *pNode = last;
        int count = length-1;
        while(count != index){
            pNode = pNode->previous;
            count--;
        }
        return pNode->data;
    }
}

#endif // LIST_H