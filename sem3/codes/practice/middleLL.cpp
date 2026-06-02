#include <iostream>
using namespace std;

class Node {

    public:

        int data;
        Node* next;

        Node(int val) {

            data = val;
            next = NULL;
        }
};


class middleLL{

    public:
        Node* middlenode(Node* head)
        {
            Node* slow = head;
            Node* fast = head;


        while (fast != NULL && fast->next != NULL){

            slow = slow->next;
            fast = fast->next->next;
        }

        return slow;
        }
};