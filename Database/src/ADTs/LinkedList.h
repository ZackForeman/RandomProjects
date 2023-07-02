#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

using namespace std;

namespace LinkedList{
    template <typename T>

    class Node{
        T data;
        Node<T>* next = nullptr;

        public:
            Node(T current){
                data = current;
            }
            void setNext(Node<T>* current){
                next = current;
            }
            Node* getNext(){
                return next;
            }
            T getData(){
                return data;
            }
    };

    template <typename T>

    class LinkedList{
        private:
            Node<T>* root = nullptr;
            int size = 0; 

        public:
            void add(T data){
                Node<T>* newNode = new Node<T>(data);
                if(root == nullptr){
                    root = newNode;
                }
                else{
                    Node<T>* start = root;

                    while(start->getNext() != nullptr){
                        start = start->getNext();
                    }
                    start->setNext(newNode);
                }
                size++;
            }
            void printList(){
                Node<T>* start = root;
                for(int i = 0; i < size; i++){
                    cout << start->getData() << endl;
                    start = start->getNext();
                }

            }

            T index(int index){
                Node<T>* start = root;
                for(int i = 0; i < index; i++){
                    start = start->getNext();
                }
                return start.getData();
            }
    };
}

#endif