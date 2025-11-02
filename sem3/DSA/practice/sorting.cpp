// ---------- BUBBLE SORT ----------
void bubbleSort() {
    if (head == NULL)
        return;

    bool swapped;
    Node* ptr1;
    Node* lptr = NULL;

    do {
        swapped = false;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if (ptr1->data > ptr1->next->data) {
                int temp = ptr1->data;
                ptr1->data = ptr1->next->data;
                ptr1->next->data = temp;
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

// ---------- SELECTION SORT ----------
void selectionSort() {
    if (head == NULL)
        return;

    Node* current = head;

    while (current != NULL) {
        Node* minNode = current;
        Node* nextNode = current->next;

        while (nextNode != NULL) {
            if (nextNode->data < minNode->data)
                minNode = nextNode;
            nextNode = nextNode->next;
        }

        if (minNode != current) {
            int temp = current->data;
            current->data = minNode->data;
            minNode->data = temp;
        }

        current = current->next;
    }
}

// ---------- INSERTION SORT ----------
void insertionSort() {
    if (head == NULL || head->next == NULL)
        return;

    Node* sorted = NULL;
    Node* current = head;

    while (current != NULL) {
        Node* nextNode = current->next;
        sortedInsert(sorted, current);
        current = nextNode;
    }

    head = sorted;
}

// Helper for Insertion Sort
void sortedInsert(Node*& sorted, Node* newNode) {
    if (sorted == NULL || newNode->data <= sorted->data) {
        newNode->next = sorted;
        sorted = newNode;
    } else {
        Node* temp = sorted;
        while (temp->next != NULL && temp->next->data < newNode->data)
            temp = temp->next;

        newNode->next = temp->next;
        temp->next = newNode;
    }
}
