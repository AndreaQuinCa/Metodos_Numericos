//
// Created by luna_ on 09/12/2020.
//

#include "Report.h"
#include <algorithm>

ostream &operator<<(ostream &os, const vector<int> &V)
{
    for(auto x:V)
        os << x << " ";
    os <<endl;
    return os;
}

Report::Report(const vector<int>& rowTestVsRowTraining, vector<int>& rowTrainingVsTrPerson, vector<int>& rowTestVsTePerson){

    this->rowTestVsTePerson = rowTestVsTePerson;

    this->rowTrainingVsTrPerson = rowTrainingVsTrPerson;


    MatchRowVsPersons(rowTestVsRowTraining, rowTrainingVsTrPerson);


    DivideTest();

    nClasses = CountPersons(rowTrainingVsTrPerson) + 1;  //nPersons of training plus 1 unknown

    CalculateConfusion();

}

void Report::DivideTest(){

    knownTestPersons.clear();
    unknownTestPersons.clear();

    for(int j: rowTestVsTePerson){
        if(FindInTraining(j)){
            knownTestPersons.insert(j);
        }
        else{
            unknownTestPersons.insert(j);
        }
    }


}

int Report::CountPersons(const vector<int>& rowTrainingVsTrPerson){

    set<int> trainingPersonsSet;

    for(int p: rowTrainingVsTrPerson){

        auto pos = trainingPersonsSet.find(p);

        if(pos==trainingPersonsSet.end()){
            trainingPersonsSet.insert(p);
            trainingPersons.push_back(p);
        }

    }

    return trainingPersons.size();

}




void Report::MatchRowVsPersons(const vector<int>& rowTestVsRowTraining, vector<int>& rowTrainingVsTrPerson){

    rowTestVsTrPerson.clear();

    for(int rowTr: rowTestVsRowTraining){
        if(rowTr>= (int)rowTrainingVsTrPerson.size()){
            cout<<"Index out of bounds in Match row Vs persons"<<endl;
            exit(-1);
        }
        if(rowTr>=0) rowTestVsTrPerson.push_back(rowTrainingVsTrPerson[rowTr]);
        else rowTestVsTrPerson.push_back(-1);
    }

}

ostream &operator<<(ostream &os, const vector<vector<int> > &M)
{
    for(const auto & row : M)
    {
        for(auto x:row)
        {
            os << x << " ";
        }
        os <<endl;
    }
    return os;
}


void Report::ReportConfusion(){

    cout<<endl;
    cout<<endl;
    cout<<"Report:"<<endl;
    cout<<endl;
    cout<<"Image classification:"<<endl;
    cout<<predictionMatrix<<endl;
    cout<<endl;
    cout<<"Confusion matrix (micro-averaged F1-score):"<<endl;
    cout<<confusionMatrix<<endl;
    cout<<endl;
    cout<<"Accuracy: "<<(confusionMatrix[0][0])*1.0/(rowTestVsTrPerson.size())*1.0<<endl;
    cout<<endl;
}


void Report::CalculateConfusion(){



    confusionMatrix = vector<vector<int> >(2, vector<int> (2, 0.0));

    CreatePredictionMatrix();

    int total = rowTestVsTrPerson.size();
    for(unsigned j=0; j<nClasses; j++){
        int TP = predictionMatrix[j][j];
        int FP = CountRow(predictionMatrix[j])-TP;
        int FN = CountCol(j, predictionMatrix)-TP;
        int TN = total-(TP+FP+FN);
        confusionMatrix[0][0] += TP;
        confusionMatrix[0][1] += FP;
        confusionMatrix[1][1] += TN;
        confusionMatrix[0][1] += FN;
    }



}

void Report::CreatePredictionMatrix(){

    predictionMatrix = vector<vector<int> >(nClasses, vector<int> (nClasses, 0.0));

    if(rowTestVsTePerson.size()!=rowTestVsTrPerson.size()){
        cout<<"Size dont match in prediction matrix"<<endl;
        exit(-1);
    }

    for(int j=0; j<trainingPersons.size(); j++){
        auto pos = knownTestPersons.find(trainingPersons[j]);
        if(pos != knownTestPersons.end()) {
            vector<unsigned> trueIdx = FindTrueIdxS(trainingPersons[j]);
            for (unsigned idx: trueIdx) {
                int predictedPerson = rowTestVsTrPerson[idx];
                if (predictedPerson >= 0) {
                    int i = FindInTrainingPersons(predictedPerson);
                    predictionMatrix[i][j] += 1;
                } else {
                    predictionMatrix[nClasses - 1][j] += 1;
                }
            }
        }
    }

    cout<<endl;
    cout<<"unknownTestPersons"<<endl;
    cout<<unknownTestPersons.size()<<endl;

    for(int u: unknownTestPersons){
        vector<unsigned> trueIdx = FindTrueIdxS(u);

        for (unsigned idx: trueIdx) {
            int predictedPerson = rowTestVsTrPerson[idx];
            if (predictedPerson >= 0) {
                int i = FindInTrainingPersons(predictedPerson);
                predictionMatrix[i][nClasses - 1] += 1;
            } else {
                predictionMatrix[nClasses - 1][nClasses - 1] += 1;
            }
        }
    }

}


bool Report::FindInTraining(unsigned val){


    bool founded = false;

    auto it = rowTrainingVsTrPerson.begin();
    if ((it= find(it, rowTrainingVsTrPerson.end(), val)) != rowTrainingVsTrPerson.end()){
        founded = true;
    }

    return founded;

}

int Report::FindInTrainingPersons(unsigned val){

    int i = -1;
    auto it = trainingPersons.begin();
    if ((it= find(it, trainingPersons.end(), val)) != trainingPersons.end()){
        i = distance(trainingPersons.begin(), it);
    }

    return i;
}

vector<unsigned> Report::FindTrueIdxS(unsigned val){

    vector<unsigned> idxS;

    auto it = rowTestVsTePerson.begin();

    while ((it= find(it, rowTestVsTePerson.end(), val)) != rowTestVsTePerson.end())
    {
        idxS.push_back(distance(rowTestVsTePerson.begin(), it));
        it++;
    }

    return idxS;

}


int Report::CountRow(const vector<int>& row){
    int sum = 0;
    for(int x: row){
        sum += x;
    }
    return sum;
}

int Report::CountCol(unsigned j, const vector<vector<int> >& matrix){
    int sum = 0;
    for(const auto & row : matrix){
        sum += row[j];
    }
    return sum;
}


















