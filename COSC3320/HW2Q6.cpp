#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

void PerformComputation(const vector<int>& data) {
    for (size_t i = 0; i < data.size(); i++) {
        int temp = data[i] * data[(i + 1) % data.size()];
    }
}

// Function to get and print system memory status
void PrintMemoryStatus(ofstream& outputFile) {
    char buffer[128];
    string result = "";
    FILE* pipe = popen("vm_stat | grep 'Pages free'", "r");

    if (!pipe) {
        cerr << "Couldn't start command." << endl;
        return;
    }
    while (fgets(buffer, sizeof buffer, pipe) != NULL) {
        result += buffer;
    }
    pclose(pipe);

    // Process and print the result
    cout << "Available Physical Memory: " << result;
    outputFile << "Available Physical Memory: " << result;
}

int main() {
    ofstream outputFile;  // Changed from fstream to ofstream
    outputFile.open("output.txt", ios::out);

    const int numCacheSizes = 15;
    double cacheSizes[numCacheSizes] = { 0.5, 0.6, 0.7, 0.8, 0.9, 0.95, 0.99, 1.0, 1.01, 1.1, 1.5, 2, 5, 10, 50 };

    for (int i = 0; i < numCacheSizes; i++) {
        double cacheSize = cacheSizes[i];
        long int dataSize = static_cast<long int>(cacheSize * 1024 * 1024); // 1M is 1024 * 1024 bytes
        int numElements = dataSize / sizeof(int);

        vector<int> data(numElements);
        for (size_t j = 0; j < data.size(); j++) {
            data[j] = rand() % 100;
        }

        PrintMemoryStatus(outputFile);

        cout << "===============================\nCache Size: " << cacheSize << "*M" << endl;
        outputFile << "===============================\nCache Size: " << cacheSize << "*M" << endl;

        clock_t startTime = clock();
        PerformComputation(data);
        double elapsedTime = static_cast<double>(clock() - startTime) / CLOCKS_PER_SEC;

        cout << "Time elapsed: " << elapsedTime << " seconds" << endl;
        outputFile << "Time elapsed: " << elapsedTime << " seconds" << endl;
    }

    outputFile.close();
    return 0;
}

