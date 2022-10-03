//
// Created by luna_ on 07/12/2020.
//

#ifndef EIGENFACES_PCA_H
#define EIGENFACES_PCA_H
#include "Matrix.h"


class PCA {

public:
    PCA(Matrix& data, unsigned nComponents, double precision);

    Matrix GetCovariance() { return covariance;}
    Matrix GetEigenvectors() { return eigenvectors;}
    vector<double> GetEigenvalues() { return eigenvalues;}
    Matrix GetData() { return data;}

    Matrix dataPC();

private:
    unsigned nComponents;
    Matrix covariance;
    vector<double> eigenvalues;
    Matrix eigenvectors;
    Matrix data;
     //Sample principal components

};


#endif //EIGENFACES_PCA_H
