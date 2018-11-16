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
void tablePrint(int tableArr[10][3]);

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
    cout << endl << endl;
    FIFO(pageRef, pageRef.size());
    return 0;
}

void tablePrint(int tableArr[10][3])
{
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 3; j++) {
            cout << tableArr[i][j] << " ";
        }
        cout << endl;
    }
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

    int frameArray[3] = {0, 0, 0};
    int counter[3] = {0, 0, 0};
    int popCount = 0;

    // Adding the first pages (which are page faults)
    for (int i = 0; i < 3; i++) {
        frameArray[i] = pageQueue.front();
        pageQueue.pop_front();
        popCount++;
        for (int j = 0; j < 3; j++) {
            table[i][j] = frameArray[j];
        }
    }

    // Adding subsequent pages
    for (int i = 0; i < popCount; i++) {
        for (int j = 0; j < 3; j++) {
            if (table[j][i] == frameArray[i]) {
                counter[i]++;
            }
        }
    }

    tablePrint(table);

    // Print counter array
    cout << "\nCounter array: ";
    for (int i = 0; i < 3; i++) {
        cout << counter[i] << " ";
    }
    cout << endl;

    // Find largest element/index in counter[] which will tell us which page to
    // replace
    int maxValue = counter[0];
    int maxIndex = 0;
    for (int i = 0; i < 3; i++) {
        if (maxValue < counter[i]) {
            maxValue = counter[i];
            maxIndex = i;
        }
    }

    cout << "Largest element: " << maxValue << endl;
    cout << "Largest index: " << maxIndex << endl;

    // Calculate which page to replace next based on info from above
    frameArray[maxIndex] = pageQueue.front();
    pageQueue.pop_front();
    popCount++;

    cout << "Frame array: ";
    for (int i = 0; i < 3; i++) {
        cout << frameArray[i] << " ";
    }

    cout << "\nRow index: " << popCount << endl;

    for (int i = 0; i < 3; i++) {
        table[popCount-1][i] = frameArray[i];
    }

    // Dealing with PAGE HITS
    for (int i = 0; i < 3; i++) {
        if (pageQueue.front() == frameArray[i]) {
            for (int j = 0; j < 3; j++) {
                table[popCount][i] == table[popCount-1][i];
            }
        }
    }
    pageQueue.pop_front();
    popCount++;
    cout << "Frame array: ";
    for (int i = 0; i < 3; i++) {
        cout << frameArray[i] << " ";
    }
}
