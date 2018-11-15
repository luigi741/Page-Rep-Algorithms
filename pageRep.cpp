//==============================================================================
// pageRep.cpp - COP 4600 final project which simulates the page replacement
// algorithms and also counts page hits and faults
// By: Luis Castro
//==============================================================================
#include <iostream>
using namespace std;

void FIFO(int arr[], int arrLength);

int main()
{
    int pageRef[10];

    // First, let's get integers for the page references
    for (int i = 0; i < 10; i++) {
        cout << "Page " << i + 1 << ": ";
        cin  >> pageRef[i];
    }

    cout << "\nNumbers have been entered, here's the string: |";

    int length = (sizeof(pageRef)/sizeof(*pageRef));

    for (int i = 0; i < length; i++) {
        cout << pageRef[i] << "|";
    }
    cout << "\n\n";

    FIFO(pageRef, length);

    return 0;
}

void FIFO(int arr[], int arrLength)
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
    // int marker = 0;

    for (int i = 0; i < 10; i++)
    {
        // Replacing the pages in the frames and then copying into the table
        for (int j = 0; j < 3; j++)
        {
            if (i < 3) {
                frameArray[i] = arr[i];
            }
            else {
                // Check for FIFO rule
                for (int x = 0; x < 3; x++) {
                    for (int y = i; y >= 0; y--) {
                        if (table[y][x] == frameArray[x]) {
                            counter[x]++;
                        }
                    }
                }
            }
            table[i][j] = frameArray[j];

            // if (marker == j) {
            //     frameArray[j] = arr[i];
            // }
            // table[i][j] = frameArray[j];

            if (i == 5) {
                cout << "Array: ";
                cout << counter[0] << " " << counter[1] << " " << counter[2] << "\n\n";
            }
        }
        // marker++;
        // if (marker >= 3) {
        //     marker %= 3;
        // }
    }

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << table[i][j] << " ";
        }
        cout << endl;
    }
}
