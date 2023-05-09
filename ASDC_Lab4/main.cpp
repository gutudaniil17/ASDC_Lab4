#include <iostream>
#include <vector>
#include <chrono>
#include "MultiArray.cpp"

using namespace std;

int main()
{
    const int DIMENSION = 4;
    vector<pair<int, int>> intervals = {
            {5,2 },
            {-3, 6},
            {5, 8},
            {-4,-9}
    };
    cout << "Intervals:\n";

    for (auto& x : intervals) {
        cout << x.first << "\t" << x.second << endl;
    }

    MultiArray array(intervals, DIMENSION);
    vector<int> rowVector(array.getDimension()), colVector(array.getDimension());

    auto startTime = chrono::high_resolution_clock::now();
    cout << array.directAccess({5,-3,5,-4}) << endl;
    auto endTime = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::microseconds>(endTime - startTime);

    cout << "Direct access execution time = " << duration.count() << " microseconds" << endl;

    startTime = chrono::high_resolution_clock::now();
    cout << array.accessAyleaf({5,-3,5,-4}) << endl;
    endTime = chrono::high_resolution_clock::now();

    duration = chrono::duration_cast<chrono::microseconds>(endTime - startTime);

    cout << "Ayleaf access execution time = " << duration.count() << " microseconds" << endl;

    startTime = chrono::high_resolution_clock::now();
    array.getDefingVectors(1000, rowVector, colVector);
    endTime = chrono::high_resolution_clock::now();

    auto durationDefining = chrono::duration_cast<chrono::nanoseconds>(endTime - startTime);
    cout << "Defining vectors method execution time = " << durationDefining.count() << " nanoseconds" << endl;

    return 0;
}