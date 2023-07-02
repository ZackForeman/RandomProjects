#include <iostream>

using namespace std;

namespace BinaryTree{

    class BinaryTree{
        Node * root;
        public:


    };

    class Node{
        int key;
        void * data;
        Node * left;
        Node * right;
        public:
            Node * getLeft(){
                return left;
            } 
            Node * getRight(){
                return left;
            }
            void * getData(){
                return data;
            } 
            void * getKey(){
                return data;
            } 
            void setLeft(Node * newLeft){
                left = newLeft;
            } 
            void setRight(Node * newRight){
                right = newRight;
            }
            int compareTo(Node x){
                return 0;
            } 
    };
}

