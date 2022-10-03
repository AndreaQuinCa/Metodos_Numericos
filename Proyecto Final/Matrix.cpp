//
// Created by luna_ on 06/12/2020.
//
#include <limits>
#include "Matrix.h"

//Constructores
Matrix::Matrix(unsigned nRows, unsigned nCols){
    data.assign(nRows, vector<double> (nCols, 0.0));
    this->nRows = nRows;
    this->nCols = nCols;
}

Matrix::Matrix(vector<vector<double> > data){
    this->data = data;
    nRows = data.size();
    nCols = data[0].size();
}

Matrix::Matrix(const string& filename)
{
    std::ifstream readFile(filename);
    if(!readFile.is_open()){
        cout<<"Cannot open file in Matrix"<<endl;
        exit(-1);
    }
    int n,m;
    readFile >>n>>m;
    nRows = n;
    nCols = m;
    data.assign(n, vector<double> (m, 0.0));
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            readFile >> data[i][j];
        }
    }
    readFile.close();
}

//Lectura escritura

void Matrix::ReadVector(vector<double> &V, const string& filename)
{
    std::ifstream readFile(filename);
    int n,m;
    readFile >>n >> m;
    V.assign(n, 0.0);
    for(int i = 0; i < n; i++)
    {
        readFile >> V[i];
    }
    readFile.close();
}

void Matrix::Write(const string& filename, bool flag_append)
{
    std::fstream out;
    if(flag_append)
        out.open(filename,fstream::app|fstream::out);
    else
        out.open(filename,std::ios::out);
    out << (int)nRows << " " << (int)nCols <<endl;
    for(int i = 0; i < nRows; i++)
    {
        for(int j = 0; j < data[i].size(); j++)
            out <<data[i][j]<< " ";
        out << endl;
    }
    out.close();
}

void Matrix::WriteDiagonal(const string& filename, bool flag_append)
{
    std::fstream out;
    if(flag_append)
        out.open(filename,fstream::app|fstream::out);
    else
        out.open(filename,std::ios::out);
    out << (int)nRows << " " << 1 <<endl;
    for(int i = 0; i < nRows ; i++)
        out <<data[i][i]<< endl;
    out.close();
}

void Matrix::WriteVector(const vector<double> &V, const string& filename, bool flag_append,  bool dimensions)
{
    std::fstream out;
    if(flag_append)
        out.open(filename,fstream::app|fstream::out );
    else
        out.open(filename,std::ios::out);
    if(dimensions) out << (int)V.size() << " 1 "<<endl;
    for(double i : V)
        out <<i<< endl;
    out.close();

}

//Sobrecarga de operadores

ostream &operator<<(ostream &os, const Matrix &M)
{
    for(int i = 0; i < M.GetRows(); i++)
    {
        for(auto x:M.data[i])
        {
            os << x << " ";
        }
        os <<endl;
    }
    return os;
}


vector<double>& Matrix::operator[](unsigned idx){
    if(idx>nRows){
        cout<<"Matrix index out of bounds"<<endl;
        exit(-1);
    }
    return data[idx];
}

double operator*(const vector<double>&a, const vector<double>&b){
    if(a.size()!=b.size()){
        cout<<"Different dimensions in vector product."<<endl;
        exit(-1);
    }
    if(a.empty()){
        cout<<"Vectors in vector product are empty."<<endl;
        exit(-1);
    }
    double p = 0;
    for(unsigned i=0; i<a.size(); i++){
        p += a[i]*b[i];
    }
    return p;
}



//Operaciones aritméticas

void Matrix::product(double a){
    for(unsigned i=0; i<nRows; i++){
        for(unsigned j=0; j<=nRows; j++){
            data[i][j] *=  a;
        }
    }
}

Matrix Matrix::TransposeProduct(bool byRight){
    /*Creates the matrix M*M^t*/
    Matrix MMT(nRows, nRows);
    for(unsigned i=0; i<nRows; i++){
        vector<double> row_i = data[i];
        for(unsigned k=0; k<=i; k++){
            MMT[i][k] =  row_i*data[k]; //Dot produc between row_i and row_k
            MMT[k][i] = MMT[i][k];
        }
    }
    return MMT;
}

Matrix Matrix::Transpose(){
    Matrix T(nCols, nRows);
    for(unsigned i=0; i<nRows; i++){
        for(unsigned j=0; j<nCols; j++){
            T[j][i] =  data[i][j];
        }
    }
    return T;

}

void Matrix::AddRow(const vector<double>& vec){
    data.push_back(vec);
}

void Matrix::SubtractVector(vector<double>& b, bool byColumn){

    if(byColumn && b.size()!=nCols) {
        cout<<"Wrong dimension in subtracted vector"<<endl;
        return;
    }
    if(byColumn){
        for(unsigned i=0; i<nRows; i++){
            for(unsigned j=0; j<nCols; j++){
                data[i][j] -= b[j];
            }
        }
    }
    else if(b.size()!=nRows) {
        cout<<"Wrong dimension in subtracted vector"<<endl;
        return;
    }
    if(!byColumn){
        for(unsigned i=0; i<nRows; i++){
            for(unsigned j=0; j<nCols; j++){
                data[i][j] -= b[i];
            }
        }
    }
}



vector<double> Matrix::product(vector<double> vec){
    /*Regresa el producto de la matriz mat con el vector vec*/
    if(vec.size()!=nCols){
        cout<<"The product matrix X vector its not well defined"<<endl;
        exit(-1);
    }
    vector<double> result = vector<double>(nRows);
    double row_sum;
    for(int i=0; i<nRows; i++){
        row_sum = 0.0;
        for(int j=0; j<nCols; j++){
            row_sum += data[i][j]*vec[j];
        }
        result[i] = row_sum;
    }

    return result;
}

Matrix Matrix::product(Matrix B, bool byRight){

    if(nCols!=B.GetRows()){
        cout<<"The matrix product its not well defined"<<endl;
        exit(-1);
    }

    Matrix C(nRows, B.GetCols());
    for(unsigned i=0; i<nRows; i++){
        for(unsigned k=0; k<nCols; k++){
            for(unsigned j=0; j<B.GetCols(); j++){
                C[i][j] += data[i][k]*B[k][j];
            }
        }
    }
    return C;
}

double Matrix::distance(const vector<double>& a, const vector<double>& b){
    if(a.size()!=b.size()){
        cout<<"Distance between vectors of different dimensions"<<endl;
        exit(-1);
    }
    double dist = 0;
    for(unsigned i=0; i<a.size(); i++){
        dist += (a[i]-b[i])*(a[i]-b[i]);
    }

    return sqrt(dist);
}
double Matrix::min(const vector<double>& v){

    double inf = numeric_limits<double>::infinity();
    double min = inf;

    for(double x: v){

        if(x<min) min = x;

    }

    if(min==inf)
        cout<<"Min equal infinity"<<endl;

    return min;
}

double Matrix::max(const vector<double>& v){

    double inf = numeric_limits<double>::infinity();
    double max = -inf;

    for(double x: v){

        if(x>max) max = x;

    }

    if(max==-inf)
        cout<<"Max equal negative infinity"<<endl;

    return max;
}





