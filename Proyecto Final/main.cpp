
#include "Image.h"
#include "Data.h"
#include "PCA.h"
#include "Report.h"
#include "EigenFaces.h"



int main(int argc, char** argv) {

    //Argumentos para imágenes
    vector<int> args = vector<int>(4);
    string suffix = "_";
    for(unsigned i=1; i<5; i++){
        args[i-1] = atoi(argv[i]);
        suffix +=  argv[i];
    }

    //Lee y centra los datos de entrenamiento
    Data myData(args, true);


    //Calcula las componentes principales
    Matrix data = myData.GetData();
    myData.ClearData();
    PCA myPCA(data, atoi(argv[9]), atof(argv[10]));


    //Lee datos de validación
    args = vector<int>(4);
    string test_suffix = "_";
    for(unsigned i=5; i<=8; i++){
        args[i-5] = atoi(argv[i]);
        test_suffix +=  argv[i];
    }



    //Lee y centra los datos
    Data testData(args, true);


    //Clasifica las imágenes
    EigenFaces eigenFaces(myPCA.dataPC(), myPCA.GetEigenvectors(), testData.GetData().Transpose(), 0.25);
    vector<int> rowTestVsRowTraining = eigenFaces.classify();


    //Elabora el reporte
    vector<int> rowTestVsTePerson = testData.GetRowPerson();
    vector<int> rowTrainingVsTrPerson = myData.GetRowPerson();
    Report myReport(rowTestVsRowTraining, rowTrainingVsTrPerson, rowTestVsTePerson);
    myReport.ReportConfusion();




    return 0;
}
