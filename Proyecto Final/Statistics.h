//
// Created by luna_ on 06/12/2020.
//

#ifndef EIGENFACES_STATISTICS_H
#define EIGENFACES_STATISTICS_H

#include <bits/stdc++.h>
#include "Matrix.h"
using namespace std;

class Statistics{
public:
    static vector<double> means(Matrix, bool byCol);
    static Matrix covariance(Matrix data);


private:
    Statistics()=default;

};

#endif //EIGENFACES_STATISTICS_H
