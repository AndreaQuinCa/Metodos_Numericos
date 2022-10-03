//
// Created by luna_ on 06/12/2020.
//

#include "Statistics.h"


vector<double> Statistics::means(Matrix matrix, bool byCol){

    if(byCol){
        vector<double> means = vector<double>(matrix.GetCols(), 0);
        for(unsigned i=0; i<matrix.GetRows(); i++){
            for(unsigned j=0; j<matrix.GetCols(); j++){
                means[j] += matrix.data[i][j];
            }
        }
        double rows = (double) matrix.GetRows()*1.0;
        for(unsigned j=0; j<matrix.GetCols(); j++){
            means[j] /= rows;
        }
        return means;
    }
    else{
        vector<double> means = vector<double>(matrix.GetRows(), 0);
        for(unsigned i=0; i<matrix.GetRows(); i++){
            for(unsigned j=0; j<matrix.GetCols(); j++){
                means[i] += matrix.data[i][j];
            }
        }
        double cols = (double) matrix.GetCols()*1.0;
        for(unsigned i=0; i<matrix.GetRows(); i++){
            means[i]/= cols;
        }
        return means;
    }


}
Matrix Statistics::covariance(Matrix data){
    Matrix covariance = data.TransposeProduct(true);
    covariance.product(1.0/(data.GetCols()-1));
    return covariance;
}

