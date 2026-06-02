#include <iostream>
using namespace std;


class Node {

    public:

        int val;
        Node* next;

        Node(int data) {

            val = data;
            next = nullptr;
        }
};

class reverseLL {

    public:

        Node* reverselist(Node* head){

            Node* prev = NULL;
            Node* curr = head;
            Node* next = NULL;

            while(curr != NULL){

                next = curr->next;
                curr->next = prev;

                prev = curr;
                curr = next;
            }
            return prev;

        }
};


int main(){

    return 0;
}
