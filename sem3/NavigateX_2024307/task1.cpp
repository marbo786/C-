#include <iostream>
using namespace std;

int findMaximumValue(int array[], int size) {
    int maximum = array[0];
    for (int i = 1; i < size; i++) {
        if (array[i] > maximum) {
            maximum = array[i];
        }
    }
    return maximum;
}

void performCountingSort(int array[], int size, int exponent) {
    int sortedArray[size];
    int frequency[10] = {0};

    for (int i = 0; i < size; i++) {
        int digit = (array[i] / exponent) % 10;
        frequency[digit]++;
    }

    for (int i = 1; i < 10; i++) {
        frequency[i] += frequency[i - 1];
    }

    for (int i = size - 1; i >= 0; i--) {
        int digit = (array[i] / exponent) % 10;
        sortedArray[frequency[digit] - 1] = array[i];
        frequency[digit]--;
    }

    for (int i = 0; i < size; i++) {
        array[i] = sortedArray[i];
    }
}

void performRadixSort(int array[], int size) {
    int maximumValue = findMaximumValue(array, size);

    for (int exp = 1; maximumValue / exp > 0; exp = exp * 10) {
        performCountingSort(array, size, exp);
    }
}

void printArray(int array[], int size) {
    for (int i = 0; i < size; i++) {
        cout << array[i] << " ";
    }
    cout << endl;
}

int main() {
    int numberOfElements;
    cout << "Enter number of elements: ";
    cin >> numberOfElements;

    int dataArray[numberOfElements];
    cout << "Enter elements:\n";
    for (int i = 0; i < numberOfElements; i++) {
        cin >> dataArray[i];
    }

    performRadixSort(dataArray, numberOfElements);

    cout << "Sorted Array:\n";
    printArray(dataArray, numberOfElements);

    return 0;
}