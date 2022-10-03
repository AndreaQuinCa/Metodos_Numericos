//
// Created by luna_ on 09/12/2020.
//

#ifndef EIGENFACES_EIGENFACES_H
#define EIGENFACES_EIGENFACES_H

#include <bits/stdc++.h>
#include "Matrix.h"

class EigenFaces {
public:

    EigenFaces(Matrix PCbyCol, Matrix eigenvectorsByRow, Matrix testCenteredByCol, double factor);
    vector<int> classify();


private:

    Matrix trainingPC; //by row
    Matrix projectedTest; //by row
    double threshold;
    double factor;



    int argMinDistance(const vector<double>& pImg);
    double CalculateThreshold();

    template <typename T>
    friend ostream &operator<<(ostream &os, const vector<T> &V);
};


#endif //EIGENFACES_EIGENFACES_H
