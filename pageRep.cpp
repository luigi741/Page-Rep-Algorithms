//==============================================================================
// pageRep.cpp - COP 4600 final project which simulates the page replacement
// algorithms and also counts page hits and faults
// By: Luis Castro
//==============================================================================
#include <iostream>
#include <cmath>
#include <deque>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

// Function prototypes
void tablePrint(int tableArr[10][3]);
void FIFO(deque<int> pageQueue, int arrLength);
void OPT(deque<int> pageQueue, int arrLength);
void LRU(deque<int> pageQueue, int arrLength, int frameSize);
void LFU(deque<int> pageQueue, int arrLength, int frameSize);

// Constants
const int frameSize = 3;

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
    // FIFO(pageRef, pageRef.size());
    // OPT(pageRef, pageRef.size());
    // LRU(pageRef, pageRef.size(), frameSize);
    LFU(pageRef, pageRef.size(), frameSize);
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

        for (int i = 0; i < 3; i++) {
            table[popCount-1][i] = frameArray[i];
        }

        // Dealing with PAGE HITS
        for (int i = 0; i < 3; i++) {
            if (pageQueue.front() == frameArray[i]) {
                for (int j = 0; j < 3; j++) {
                    table[popCount-1][i] == table[popCount-2][i];
                }
            }
        }
    }
    tablePrint(table);
}

void OPT(deque<int> pageQueue, int arrLength)
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

    int loopCount = 0;
    int indexOPT[3] = {-1, -1, -1};

    while (!pageQueue.empty())
    {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < pageQueue.size(); j++) {
                if (frameArray[i] == pageQueue[j]) {
                    counter[i]++;

                    // Mark the last index of the page in the reference string that
                    // matches the current page frames
                    indexOPT[i] = j;
                }
            }
        }

        int markIndex = -1;
        for (int i = 0; i < 3; i++) {
            // Marking index if there are two frames that don't have a match in the
            // page reference
            if (counter[i] == 0) {
                markIndex = i;
                break;
            }
        }

        // Dealing with PAGE HITS
        int frameCounter = 0;
        for (int i = 0; i < frameSize; i++) {
            if (frameArray[i] == pageQueue.front()) {
                frameCounter++;
            }
        }

        // Only insert if the page ref. is not already in the frames
        if (frameCounter == 0) {
            frameArray[markIndex] = pageQueue.front();
            pageQueue.pop_front();
        }
        else if (frameCounter > 0) {
            pageQueue.pop_front();
        }
        popCount++;

        // Update the page table
        for (int i = 0; i < frameSize; i++) {
            table[popCount-1][i] = frameArray[i];
        }
    }

    tablePrint(table);
}

void LRU(deque<int> pageQueue, int arrLength, int frameSize)
{
    // Store a local copy of the page reference string
    deque<int> tempQueue (arrLength);
    for (int i = 0; i < pageQueue.size(); i++) {
        tempQueue.at(i) = pageQueue.at(i);
    }

    // Initialize variables and arrays we will need
    int frameArray[frameSize] = {0, 0, 0};
    int counter[frameSize] = {0, 0, 0};
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

    while (!pageQueue.empty())
    {
        // Remove LRU element in the frame array
        int repVar = 0;
        int repIndex = -1;
        repVar = tempQueue.at(popCount-frameSize);
        for (int i = 0; i < frameSize; i++) {
            if (frameArray[i] == repVar) {
                repIndex = i;
            }
        }

        // Dealing with PAGE HITS
        int frameCounter = 0;
        for (int i = 0; i < frameSize; i++) {
            if (frameArray[i] == pageQueue.front()) {
                frameCounter++;
            }
        }

        if (frameCounter == 0) {
            frameArray[repIndex] = pageQueue.front();
            pageQueue.pop_front();
        }
        else if (frameCounter > 0) {
            pageQueue.pop_front();
        }
        popCount++;

        // Update the page table
        for (int i = 0; i < frameSize; i++) {
            table[popCount-1][i] = frameArray[i];
        }
    }

    tablePrint(table);
}

void LFU(deque<int> pageQueue, int arrLength, int frameSize)
{
    // Store a local copy of the page reference string
    deque<int> tempQueue (arrLength);
    for (int i = 0; i < pageQueue.size(); i++) {
        tempQueue.at(i) = pageQueue.at(i);
    }

    // Scan the reference string, get the number of unique entries
    set<int> refString(tempQueue.begin(), tempQueue.end());
    vector<int> unique(refString.begin(), refString.end());

    cout << "\nUnique entries: " << refString.size() << endl;
    for (int i = 0; i < unique.size(); i++) {
        cout << unique[i] << " ";
    }

    // Get frequency of each unique entry
    vector<int> pageFreq (unique.size());
    for (int i = 0; i < unique.size(); i++) {

    }
}
