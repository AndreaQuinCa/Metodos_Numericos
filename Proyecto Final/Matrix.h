//
// Created by luna_ on 06/12/2020.
//

#ifndef EIGENFACES_MATRIX_H
#define EIGENFACES_MATRIX_H

#include <bits/stdc++.h>
using namespace std;

class Matrix{
public:
    explicit Matrix(const string& filename);
    Matrix()=default;
    Matrix(unsigned nRows, unsigned nCols);
    explicit Matrix(vector<vector<double> > data);

    static void ReadVector(vector<double> &V, const string& filename);
    void Write(const string& filename, bool flag_append);
    void WriteDiagonal(const string& filename, bool flag_append);



    void product(double a);
    Matrix product(Matrix B, bool byRight);
    vector<double> product(vector<double> vec);
    Matrix TransposeProduct(bool byRight);


    Matrix Transpose();
    void AddRow(const vector<double>& vec);
    void SubtractVector(vector<double>& b, bool byColumn);


    void SetRows(unsigned nRows) {this->nRows=nRows;}
    void SetCols(unsigned nCols) {this->nCols=nCols;}
    unsigned GetRows() const{return nRows;}
    unsigned GetCols() const{return nCols;}



    friend ostream &operator<<(ostream &os, const Matrix &M);
    vector<double>& operator[](unsigned);
    friend double operator*(const vector<double>&a, const vector<double>&b);
    friend Matrix operator*(Matrix, Matrix);


    vector<vector<double> > data;


    static void WriteVector(const vector<double> &V, const string& filename, bool flag_append, bool dimensions);
    static double distance(const vector<double>& a, const vector<double>& b);
    static double min(const vector<double>& v);
    static double max(const vector<double>& v);


private:

    unsigned nRows{};
    unsigned nCols{};


};


#endif //EIGENFACES_MATRIX_H
