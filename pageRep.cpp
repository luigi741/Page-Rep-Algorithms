//==============================================================================
// pageRep.cpp - COP 4600 final project which simulates the page replacement
// algorithms and also counts page hits and faults
// By: Luis Castro
//==============================================================================
#include <iostream>
#include <cmath>
#include <deque>
using namespace std;

void tablePrint(int tableArr[10][3]);
void FIFO(deque<int> pageQueue, int arrLength);
void OPT(deque<int> pageQueue, int arrLength);

int main()
{
    int tempVar = 0;
    deque<int> pageRef;

    // First, let's get integers for the page references
    cout << endl;
    for (int i = 0; i < 7; i++) {
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
    cout << endl;
}

void FIFO(deque<int> pageQueue, int arrLength)
{
    // Initialize variables and arrays we will need
    int frameArray[3] = {0, 0, 0};
    int counter[3] = {0, 0, 0};
    int popCount = 0;
    int pageHit = 0;
    int pageFault = 0;

    // Initialize table, set values to 0
    int table[10][3];
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 3; j++) {
            table[i][j] = 0;
        }
    }

    // Adding the first pages (which are page faults)
    for (int i = 0; i < 3; i++) {
        frameArray[i] = pageQueue.front();
        pageQueue.pop_front();
        popCount++;
        for (int j = 0; j < 3; j++) {
            table[i][j] = frameArray[j];
        }
    }

    cout << "Before while loop" << endl;
    tablePrint(table);

    // Adding subsequent pages
    int loopCount = 0;
    while (!pageQueue.empty())
    {
        loopCount++;

        // This loop increments counter[] array to see which page has been in
        // frames the longest
        for (int i = 0; i < popCount; i++) {
            for (int j = 0; j < 3; j++) {
                if (table[i][j] == frameArray[i]) {
                    counter[i]++;
                }
            }
        }

        cout << "Counter Array: ";
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

        // Calculate which page to replace next based on info from above
        frameArray[maxIndex] = pageQueue.front();
        pageQueue.pop_front();
        popCount++;

        cout << "Inserting in row: " << popCount-1 << endl;
        for (int i = 0; i < 3; i++) {
            table[popCount-1][i] = frameArray[i];
        }

        cout << "Pop count: " << popCount << endl;
        cout << "Inside while loop" << endl;
        tablePrint(table);

        // Dealing with PAGE HITS
        for (int i = 0; i < 3; i++) {
            if (pageQueue.front() == frameArray[i]) {
                for (int j = 0; j < 3; j++) {
                    table[popCount-1][i] == table[popCount-2][i];
                }
            }
        }
    }
    cout << "After while loop" << endl;
    tablePrint(table);
}

void OPT(deque<int> pageQueue, int arrLength)
{

}
