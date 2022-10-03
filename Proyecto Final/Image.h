//
// Created by luna_ on 06/12/2020.
//

#ifndef EIGENFACES_IMAGE_H
#define EIGENFACES_IMAGE_H

#include <cstring>
#include <bits/stdc++.h>

using namespace std;

class Image{

public:
    //Constructores y destructores
    explicit Image(const string& filename);
    Image(vector<double>& pixels, unsigned nRows, unsigned nCols);
    ~Image() = default;

    //Métodos
    void write(const string& filename);
    void write(const string& prefix, const string& suffix);
    void InvertImage();
    unsigned GetSize(){return nRows*nCols;}

private:
    unsigned nRows;
    unsigned nCols;
    vector<double> pixels; //Matriz de pixeles
    pair<double, double> MinMax();
    void NormalizeImage();

friend class Data;

};

#endif //EIGENFACES_IMAGE_H
