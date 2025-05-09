#include <iostream>
#include <vector>
#include <omp.h>
#include <climits>
#include <cstdlib>

using namespace std;

void minimum(const vector<int>& array) {
    int min = INT_MAX;
    double start = omp_get_wtime();
    for (int i = 0; i < array.size(); i++) {
        if (array[i] < min) {
            min = array[i];
        }
    }
    double end = omp_get_wtime();
    cout << "Minimum Element: " << min << endl;
    cout << "Time Taken: " << (end - start) << " seconds" << endl;

    int min_ele = INT_MAX;
    start = omp_get_wtime();
    #pragma omp parallel for reduction(min:min_ele)
    for (int i = 0; i < array.size(); i++) {
        if (array[i] < min_ele) {
            min_ele = array[i];
        }
    }
    end = omp_get_wtime();
    cout << "Minimum Element (Parallel Reduction): " << min_ele << endl;
    cout << "Time Taken: " << (end - start) << " seconds" << endl;
}

void maximum(const vector<int>& array) {
    int max = INT_MIN;
    double start = omp_get_wtime();
    for (int i = 0; i < array.size(); i++) {
        if (array[i] > max) {
            max = array[i];
        }
    }
    double end = omp_get_wtime();
    cout << "Maximum Element: " << max << endl;
    cout << "Time Taken: " << (end - start) << " seconds" << endl;

    int max_ele = INT_MIN;
    start = omp_get_wtime();
    #pragma omp parallel for reduction(max:max_ele)
    for (int i = 0; i < array.size(); i++) {
        if (array[i] > max_ele) {
            max_ele = array[i];
        }
    }
    end = omp_get_wtime();
    cout << "Maximum Element (Parallel Reduction): " << max_ele << endl;
    cout << "Time Taken: " << (end - start) << " seconds" << endl;
}

void sum(const vector<int>& array) {
    int total = 0;
    double start = omp_get_wtime();
    for (int i = 0; i < array.size(); i++) {
        total += array[i];
    }
    double end = omp_get_wtime();
    cout << "Summation: " << total << endl;
    cout << "Time Taken: " << (end - start) << " seconds" << endl;

    total = 0;
    start = omp_get_wtime();
    #pragma omp parallel for reduction(+:total)
    for (int i = 0; i < array.size(); i++) {
        total += array[i];
    }
    end = omp_get_wtime();
    cout << "Summation (Parallel Reduction): " << total << endl;
    cout << "Time Taken: " << (end - start) << " seconds" << endl;
}

void average(const vector<int>& array) {
    float avg = 0.0f;
    double start = omp_get_wtime();
    for (int i = 0; i < array.size(); i++) {
        avg += array[i];
    }
    double end = omp_get_wtime();
    cout << "Average: " << avg / array.size() << endl;
    cout << "Time Taken: " << (end - start) << " seconds" << endl;

    avg = 0;
    start = omp_get_wtime();
    #pragma omp parallel for reduction(+:avg)
    for (int i = 0; i < array.size(); i++) {
        avg += array[i];
    }
    end = omp_get_wtime();
    cout << "Average (Parallel Reduction): " << avg / array.size() << endl;
    cout << "Time Taken: " << (end - start) << " seconds" << endl;
}

int main() {
    int N;
    cout << "Enter number of elements in array: ";
    cin >> N;

    vector<int> array(N);
    srand(time(0));
    for (int i = 0; i < N; i++) {
        array[i] = rand() % 1000;
    }

    minimum(array);
    maximum(array);
    sum(array);
    average(array);

    return 0;
}
