//
// Created by luna_ on 07/12/2020.
//

#ifndef EIGENFACES_LINEAR_H
#define EIGENFACES_LINEAR_H

#include <bits/stdc++.h>
#include "Matrix.h"
using namespace std;

class Linear{


public:
    static pair<Matrix, vector<double> > nEigenPower(Matrix& mat, int nSol, double precision);

    static int normalize(vector<double> &vec);


private:


    static void ProductMatVec(Matrix &mat, vector<double> &vec, vector<double> &prod);

    static void OrthogonalizeVector(Matrix &eig_vecs, vector<double> &vec, int nprev_eigs);

    static double DotProduct(vector<double> &vec1, vector<double> &vec2);

    Linear() = default;



};

#endif //EIGENFACES_LINEAR_H
