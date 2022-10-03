//
// Created by luna_ on 09/12/2020.
//

#include <limits>

#include "EigenFaces.h"



EigenFaces::EigenFaces(Matrix PCbyCol, Matrix eigenvectorsByRow, Matrix testCenteredByCol, double factor) {

    projectedTest = eigenvectorsByRow.product(std::move(testCenteredByCol), true);
    projectedTest = projectedTest.Transpose();
    trainingPC = PCbyCol.Transpose(); //Centered and by row
    this->factor = factor;
    threshold = CalculateThreshold();


}

template <typename T>
ostream &operator<<(ostream &os, const vector<T> &V)
{
    for(auto x:V)
        os << x << " ";
    os <<endl;
    return os;
}

double EigenFaces::CalculateThreshold(){

    unsigned nRows = projectedTest.GetRows();

    double inf = numeric_limits<double>::infinity();
    vector<vector<double> > distances(nRows, vector<double> (nRows, inf));

    for(unsigned i=0; i<nRows; i++){
        for(unsigned j=0; j<i; j++){
            distances[i][j] = Matrix::distance(projectedTest[i], projectedTest[j]);
        }
    }

    vector<double> rash(distances.size());
    unsigned i = 0;
    for(const vector<double>& row: distances){
        if(i==0){
            i++;
            continue;
        }
        rash[i++] = Matrix::min(row);
    }

    return Matrix::max(rash)*factor;
}

vector<int> EigenFaces::classify(){

    vector<int> predictions;  // indexes: rows of testCenteredImagesByRow, values: indexes of predicted rows of imagesPCbyRow
    predictions.clear();
    for(const vector<double>& pTest: projectedTest.data){
        int idx = argMinDistance(pTest);
        predictions.push_back(idx);
    }

    return predictions;
}




int EigenFaces::argMinDistance(const vector<double>& pTest){

    double inf = numeric_limits<double>::infinity();
    double minDistance = inf;
    int minIndex = -1;

    int i = 0;

    for(const vector<double>& img: trainingPC.data){

        double dist = Matrix::distance(pTest, img);


        if( dist < minDistance && dist < threshold){
            minDistance = dist;
            minIndex = i;
        }

        i++;

    }

    return minIndex;

}