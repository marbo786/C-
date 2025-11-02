#include <iostream> 
using namespace std;

class Stack {
private:
    int* arr;                   // Pointer to dynamically allocate array for our stack
    int topIndex;
    int maxsize;

public:
    Stack(int size) {
        maxsize = size;
        arr = new int[maxsize];
        topIndex = -1;
    }

    void push(int val) {
        if (topIndex < maxsize - 1) 
        {
            arr[++topIndex] = val;
        } else 
        {
            cout << "Error: STACK OVERFLOW" << endl;
        }
    }

    void pop() {
        if (!isEmpty()) 
        {
            topIndex--;
        }
    }

    int top() {
        if (!isEmpty()) {
            return arr[topIndex];
        }
        return -1;
    }

    bool isEmpty() {
        return topIndex == -1;
    }
};

class Queue {
private:
    int* arr;
    int capacity;
    int frontIndex; 
    int backIndex;  
    int count;                              // Number of elements in the queue since this is a circular one

public:
    Queue(int size) {
        capacity = size;
        arr = new int[capacity];
        frontIndex = 0;
        backIndex = 0;
        count = 0;
    }

    void enqueue(int val) {
        if (count < capacity) {
            arr[backIndex] = val;
            backIndex = (backIndex + 1) % capacity; 
            count++;
        } else {
            cout << "Error: Queue overflow" << endl;
        }
    }

    void dequeue() {
        if (!isEmpty()) {
            frontIndex = (frontIndex + 1) % capacity;
            count--;
        }
    }

    int front() {
        if (!isEmpty()) {
            return arr[frontIndex];
        }
        return -1;
    }

    bool isEmpty() {
        return count == 0;
    }
};

int findbestholdingtrack(Stack** holdingTracks, int k, int currentCar, int n) {

    int bestFitIndex = -1;
    int minTopValue = n + 1;                    // no car number should be greater than n so mintop
    int firstEmptyIndex = -1;

    for (int i = 0; i < k; ++i) {
        if (holdingTracks[i]->isEmpty()) 
        {
            if (firstEmptyIndex == -1) 
            {
                firstEmptyIndex = i;
                }
        } else 
        {
            int topCar = holdingTracks[i]->top();

            if (topCar > currentCar) {             //Checks if we can legally place our currentCar on this track (the car on top must be larger).
                if (topCar < minTopValue) 
                {
                    minTopValue = topCar;
                    bestFitIndex = i;
                    }
            }
        }
    }

    if (bestFitIndex != -1) {
        return bestFitIndex;
    }

    if (firstEmptyIndex != -1) {
        return firstEmptyIndex;
    }
     return -1;
}

void rearrangeCars(Queue& inputTrack, Stack** holdingTracks, int k, int n) {
    int nextCarNeeded = 1;

    while (nextCarNeeded <= n) {
        bool movedACar = true;

        while (movedACar) 
        {
            movedACar = false;

            for (int i = 0; i < k; ++i) {
                if (!holdingTracks[i]->isEmpty() && holdingTracks[i]->top() == nextCarNeeded) 
                {
                    int car = holdingTracks[i]->top();
                    holdingTracks[i]->pop();
                    
                    cout << "Move:Car " << car << " from holding track " << (i + 1) << " to output track" << endl;
                    
                    nextCarNeeded++;
                    movedACar = true;
                    break; 
                }
            }
        }

        if (inputTrack.isEmpty()) {
            if (nextCarNeeded <= n) {
                cout << "\n Cannot complete arrangement. Input is empty and car is stuck" << endl;
            }
            break;
        }

        int currentCar = inputTrack.front();

        if (currentCar == nextCarNeeded) {                     // Case 1: Car goes directly to output

            inputTrack.dequeue();                            
            
            cout << "Move: Car " << currentCar << " from Input Track to Output Track" << endl;
            nextCarNeeded++;

        } else                                               // Case 2: Car goes to a holding track
        {
                                                             
            int targetTrack = findbestholdingtrack(holdingTracks, k, currentCar, n);

            if (targetTrack == -1) {
                cout << "\nCannot complete arrangement. No suitable holding track for car " << currentCar << endl;
                break;
            } else 
            {
                inputTrack.dequeue();
                holdingTracks[targetTrack]->push(currentCar);
                cout << "Move: Car " << currentCar << " from input track to holding track " << (targetTrack + 1) << endl;
            }
        }
    } 

    if (nextCarNeeded > n) {
        cout << "\nArrangement complete. All cars are sorted on the output track" << endl;
    }
}


int main() {
    int n,k; 
   

    cout << "Enter the number of railroad cars (n): ";
    cin >> n;
    cout << "Enter the number of holding tracks (k): ";
    cin >> k;

    Queue inputTrack(n);
    
    Stack** holdingTracks = new Stack*[k];
    for (int i = 0; i < k; ++i) {
        holdingTracks[i] = new Stack(n);
    }

    cout << "Enter the car arrangement on the input track from front to back: " << endl;

    for (int i = 0; i < n; ++i) {
        int carNum;
        cin >> carNum;
        inputTrack.enqueue(carNum);
    }

    rearrangeCars(inputTrack, holdingTracks, k, n);

    for (int i = 0; i < k; ++i) {               // clearing memory
        delete holdingTracks[i];
    }

    delete[] holdingTracks;

    return 0;
}