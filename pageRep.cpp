//==============================================================================
// pageRep.cpp - COP 4600 final project which simulates the page replacement
// algorithms and also counts page hits and faults
// By: Luis Castro
//==============================================================================
#include <iostream>
#include <cmath>
#include <deque>
using namespace std;

void FIFO(deque<int> pageQueue, int arrLength);

int main()
{
    int tempVar = 0;
    deque<int> pageRef;

    // First, let's get integers for the page references
    for (int i = 0; i < 5; i++) {
        cout << "Page " << i + 1 << ": ";
        cin  >> tempVar;
        pageRef.push_back(tempVar);
    }

    cout << "\nNumbers have been entered, here's the string: |";

    for (auto x: pageRef) {
        cout << x << "|";
    }
    cout << endl;
    FIFO(pageRef, pageRef.size());
    return 0;
}

void FIFO(deque<int> pageQueue, int arrLength)
{
    // Initialize table, set values to 0
    int table[10][3];
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 3; j++) {
            table[i][j] = 0;
        }
    }

    cout << "\nFront of Queue: " << pageQueue.front() << endl;

    int frameArray[3] = {0, 0, 0};
    int counter[3] = {0, 0, 0};

    // Adding the first pages (which are page faults)
    for (int i = 0; i < 3; i++) {
        frameArray[i] = pageQueue.front();
        pageQueue.pop_front();
        for (int j = 0; j < 3; j++) {
            table[i][j] = frameArray[j];
        }
    }

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 3; j++) {
            cout << table[i][j] << " ";
        }
        cout << endl;
    }
}
