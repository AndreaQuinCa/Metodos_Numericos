//
// Created by luna_ on 07/12/2020.
//

#include "PCA.h"
#include "Linear.h"
#include "Statistics.h"

PCA::PCA(Matrix& data, unsigned nComponents, double precision){

    this->data = data;
    this->nComponents = nComponents;

    //Calculates covariance matrix
    covariance = Statistics::covariance(data);

    //Calculates principal eigenpairs
    if(nComponents==0){
        nComponents = covariance.GetRows();
    }

    cout<<"Number of PC: "<<nComponents<<endl;
    cout<<endl;
    pair<Matrix, vector<double> > results = Linear::nEigenPower(covariance, nComponents, precision);
    eigenvectors = results.first;
    eigenvalues = results.second;

    //Calculates true eigenvectors
    this->data = data.Transpose();
    vector<vector<double> > finalEigenvectors;
    for(const vector<double>& e: eigenvectors.data){
        finalEigenvectors.push_back((this->data).product(e));
    }
    Matrix final(finalEigenvectors);
    eigenvectors = final;


}

//    if(true){
//        //Escribe los eigenvalores
//    string filename = "EigenValues"+suffix;
//    Matrix::WriteVector(myPCA.GetEigenvalues(), filename+".txt", false, false);
//    //Escribe el primer eigenvector
//    filename = "EigenVec"+suffix;
//    Matrix::WriteVector((myPCA.GetEigenvectors())[0], filename+".txt", false, false);
//    }



Matrix PCA::dataPC(){
    //Obtains sample principal components, i.e. original data projected
    Matrix dataPC = eigenvectors.product((this->data), true);
    return dataPC;
}

