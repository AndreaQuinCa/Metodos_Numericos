//
// Created by luna_ on 06/12/2020.
//

#ifndef EIGENFACES_DATA_H
#define EIGENFACES_DATA_H

#include "Matrix.h"
#include "Statistics.h"
using namespace std;

class Data{
public:
    Data(vector<int> selectedImages, bool center);
    Data(const string& filename, bool center);

    Matrix GetData() const {return data;}
    void ClearData() { data.data.clear();}
    vector<int> GetRowPerson() {return rowPerson;}

    void CenterData();


private:
    Matrix data;
    vector<int> rowPerson;
    vector<string> filenames;
    vector<double> means;

    pair<int, int> ReadImageDims();
    bool ReadFiles(pair<int, int> RowsCols);
    void CreateFilenames(vector<int> selectedImages);


};

#endif //EIGENFACES_DATA_H
