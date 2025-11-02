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


class List {


    public:
    Node* loopdetect(Node* head) {
    Node* slow = head;
    Node* fast = head;

    while (fast && fast->next) { //idk
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return slow;  
    }
    return nullptr;
}

    Node* Loopstart(Node* head, Node* collide, int& x) {
    Node* ptr1 = head;
    Node* ptr2 = collide;

    x = 1;

    while (ptr1 != ptr2) 
    {
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
        x++;
    }
    return ptr1;  
}


    void removeLoop(Node* loopstart, int startpos) {
    Node* temp = loopstart;
    int lastPos = startpos;

   
    while (temp->next != loopstart) {
        temp = temp->next;
        lastPos++;
    }

    temp->next = nullptr; 
    cout << "Loop removed from Node: " << lastPos << " -> Node: " << startpos << endl;
}

    void detectAndRemoveLoop(Node* head) {
    Node* collide = loopdetect(head);

    if (!collide) 
    {
        cout << "No loop detected." << endl;
        return;
    }

    int position;
    Node* loopStart = Loopstart(head, collide, position);

    cout << "Loop starts at Node: " << position << " with value = " << loopStart->data << endl;

    removeLoop(loopStart, position);
}

};     

int main() {

    List L1;
    
    Node* head = new Node(11);
    head->next = new Node(3);
    head->next->next = new Node(8);
    head->next->next->next = new Node(2);
    head->next->next->next->next = new Node(1);

    head->next->next->next->next->next = head->next->next;

    // Detect and remove loop
    L1.detectAndRemoveLoop(head);



    return 0;
}
