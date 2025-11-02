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

class detectcycle {

    public:
        bool hascycle(Node* head){

            Node* slow = head;
            Node* fast = head;

        while (fast != NULL && fast->next != NULL)
        {
            slow = slow->next;
            fast = fast->next->next;

            if(slow==fast){
                return true;
            }
        }
        return false;

        // code for removing cycle

        // slow = head;
        // Node* prev = NULL;
        // while(slow != fast){
        //slow = slow->next;
        // prev = fast; this is for removing the loop
        //fast = fast->next;
        //}
        // prev->next = NULL; removes cycle
        // return slow;(returned starting point of our loop)
        }
};
