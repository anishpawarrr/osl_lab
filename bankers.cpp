#include <iostream>
#include <vector>

using namespace std;

const int NUM_PROCESSES = 5;
const int NUM_RESOURCES = 3;

int available[NUM_RESOURCES] = {3, 3, 2};

int maximum[NUM_PROCESSES][NUM_RESOURCES] = {
    {7, 5, 3},
    {3, 2, 2},
    {9, 0, 2},
    {2, 2, 2},
    {4, 3, 3}
};

int allocation[NUM_PROCESSES][NUM_RESOURCES] = {
    {0, 1, 0},
    {2, 0, 0},
    {3, 0, 2},
    {2, 1, 1},
    {0, 0, 2}
};

int need[NUM_PROCESSES][NUM_RESOURCES];

bool requestResources(int processId, int request[]) {
    for (int i = 0; i < NUM_RESOURCES; ++i) {
        if (request[i] > need[processId][i] || request[i] > available[i]) {
            return false; // Requested resources exceed need or available resources
        }
    }

    // Try to allocate resources temporarily
    for (int i = 0; i < NUM_RESOURCES; ++i) {
        available[i] -= request[i];
        allocation[processId][i] += request[i];
        need[processId][i] -= request[i];
    }

    // Check if the system is still in a safe state after the resource allocation
    if (isSafe()) {
        return true; // Resources allocated successfully
    } else {
        // Roll back the allocation if it leads to an unsafe state
        for (int i = 0; i < NUM_RESOURCES; ++i) {
            available[i] += request[i];
            allocation[processId][i] -= request[i];
            need[processId][i] += request[i];
        }
        return false; // Resources cannot be allocated without leading to a deadlock
    }
}
bool isSafe() {
    vector<bool> finish(NUM_PROCESSES, false);
    int work[NUM_RESOURCES];
    for (int i = 0; i < NUM_RESOURCES; ++i) {
        work[i] = available[i];
    }

    // Calculate the initial need matrix
    for (int i = 0; i < NUM_PROCESSES; ++i) {
        for (int j = 0; j < NUM_RESOURCES; ++j) {
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }

    int completedProcesses = 0;
    while (completedProcesses < NUM_PROCESSES) {
        bool found = false;
        for (int i = 0; i < NUM_PROCESSES; ++i) {
            if (!finish[i]) {
                bool canAllocate = true;
                for (int j = 0; j < NUM_RESOURCES; ++j) {
                    if (need[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }

                if (canAllocate) {
                    for (int j = 0; j < NUM_RESOURCES; ++j) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = true;
                    found = true;
                    ++completedProcesses;
                }
            }
        }

        if (!found) {
            return false; // No process can be allocated, the system is in an unsafe state
        }
    }

    return true; // All processes were successfully allocated, the system is in a safe state
}

int main() {
    // Example: Process 1 requests resources [1, 0, 2]
    int processId = 1;
    int request[NUM_RESOURCES] = {1, 0, 2};

    if (requestResources(processId, request)) {
        cout << "Resources allocated successfully." << endl;
    } else {
        cout << "Request denied. Allocating these resources would lead to a deadlock." << endl;
    }

    return 0;
}
