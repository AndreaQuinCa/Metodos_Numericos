//
// Created by luna_ on 09/12/2020.
//

#ifndef EIGENFACES_REPORT_H
#define EIGENFACES_REPORT_H


#include "Matrix.h"

class Report {

public:
    Report(const vector<int>& rowTestVsRowTraining, vector<int>& rowTrainingVsTrPerson, vector<int>& rowTestVsTePerson);

    void ReportConfusion();

    void WriteImages(Matrix centeredTrainingData, vector<double> trainingMeans, Matrix centeredTestData, vector<double> testMeans);


private:
    vector<vector<int> > confusionMatrix;
    vector<vector<int> > predictionMatrix;

    vector<int> rowTestVsTrPerson;
    vector<int> rowTestVsTePerson;
    vector<int> rowTrainingVsTrPerson;

    vector<int> trainingPersons;
    set<int> knownTestPersons;
    set<int> unknownTestPersons;

    int nClasses;

    friend ostream &operator<<(ostream &os, const vector<vector<int> > &M);
    friend ostream &operator<<(ostream &os, const vector<int> &V);

    void CalculateConfusion();

    void MatchRowVsPersons(const vector<int>& rowTestVsRowTraining, vector<int>& rowTrainingVsTrPerson);

    void CreatePredictionMatrix();

    int CountPersons(const vector<int>& rowTestVsTePerson);

    static int CountRow(const vector<int>& row);

    static int CountCol(unsigned int j, const vector<vector<int> >& matrix);


    vector<vector<double> > imagePredictions(Matrix centeredTrainingData, vector<double> means); //indexes rows test & vector preddicted image

    vector<vector<double> > originalTest(Matrix centeredTestData, vector<double> means); //indexes rows test & vector test image

    void writeImages(vector<vector<double> > predictedImages, vector<vector<double> > trueImages,  string prefix);


    void DivideTest();

    vector<unsigned int> FindTrueIdxS(unsigned int val);

    bool FindInTraining(unsigned int val);

    int FindInTrainingPersons(unsigned int val);
};


#endif //EIGENFACES_REPORT_H
