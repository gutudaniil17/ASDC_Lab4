//
// Created by Gutu on 09.05.2023.
//
#include <iostream>
#include <vector>
#include <string>
using namespace std;
class MultiArray{
    vector<pair<int,int>> indices;
    vector<int> data;
    int size;
    int dimension;
public:
    int getSize() {
        return size;
    }

    int getDimension()
    {
        return dimension;
    }
    int calculateSize(vector<pair<int, int>> ranges)
    {
        int size = 1;
        for (auto& x : ranges) {
            size *= (x.second - x.first + 1);
        }
        data.resize(size);
        for (int i = 0; i < size; i++) {
            data[i] = i;
        }
        return size;
    }
    MultiArray(vector<pair<int, int>>& ranges, int dimension){
    size=calculateSize(ranges);
    indices=ranges;
    this->dimension=dimension;
    }
    int directAccess(vector<int> indices)
    {
        int index = indices[dimension - 1] - this->indices[dimension - 1].first;
        int product = 1;
        for (int i = dimension - 2; i >= 0; i--) {
            index += (indices[i] - this->indices[i].first) * product;
            product *= (this->indices[i + 1].second - this->indices[i + 1].first + 1);
        }
        return data[index];
    }
    int accessAyleaf(vector<int> indices)
    {
        int index = indices[0] - this->indices[0].first;
        for (int i = 1; i < dimension; i++) {
            int product = 1;
            for (int j = 0; j < i; j++) {
                product *= (this->indices[j + 1].second - this->indices[j + 1].first + 1);
            }
            index += (indices[i] - this->indices[i].first) * product;
        }
        return data[index];
    }
    void getDefingVectors(int index, vector<int>& rowVector, vector<int>& colVector) {
        int product = 1;
        for (int i = dimension - 1; i >= 0; i--) {
            rowVector[i] = (index / product) % (this->indices[i].second - this->indices[i].first + 1) + this->indices[i].first;
            product *= (this->indices[i].second - this->indices[i].first + 1);
        }
        product = 1;
        for (int i = 0; i < dimension; i++) {
            colVector[i] = (index / product) % (this->indices[i].second - this->indices[i].first + 1) + this->indices[i].first;
            product *= (this->indices[i].second - this->indices[i].first + 1);
        }
    }

};