#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    int n_values[] = {16, 64, 256, 1024, 4096, 16384};
    int n_size = sizeof(n_values) / sizeof(n_values[0]);
    size_t m_values[] = {1677721600, 13421772800};
    int m_size = sizeof(m_values) / sizeof(m_values[0]);

    for (int n_index = 0; n_index < n_size; ++n_index) {
        int n = n_values[n_index];

        // Initialize dynamic matrix M
        int** M = new int*[n];
        for (int i = 0; i < n; ++i) {
            M[i] = new int[n](); // Use '()' to initialize all elements to 0
        }

        for (int m_index = 0; m_index < m_size; ++m_index) {
            size_t m = m_values[m_index];

            // Start timing
            clock_t start_time = clock();

            // Perform calculations
            for (size_t i = 0; i < m; ++i) {
                int x = rand() % 100 + 1;
                int a = rand() % n;
                int b = rand() % n;
                M[a][b] += x;
            }

            // End timing
            double time_taken = double(clock() - start_time) / CLOCKS_PER_SEC;
            cout << "Time for n=" << n << " and m=" << m << ": " << time_taken << " seconds" << endl;
        }

        // Free memory
        for (int i = 0; i < n; ++i) {
            delete[] M[i];
        }
        delete[] M;
    }

    return 0;
}
