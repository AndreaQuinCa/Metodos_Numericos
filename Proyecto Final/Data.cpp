//
// Created by luna_ on 06/12/2020.
//

#include "Data.h"

#include "Image.h"


Data::Data(const string& filename, bool center){
    Matrix data(filename);
    this->data = data;
    if(center){
        CenterData();
    }
}

Data::Data(vector<int> selectedImages, bool center){

    //Contruye los nombres de los archivos
    CreateFilenames(selectedImages);

    //Lee las dimensiones de la primera imagen
    pair<int, int> RowsCols = ReadImageDims();
    if(RowsCols.first<=0 || RowsCols.second<=0)exit(-1);

    //Carga los archivos y verifica que todas las imágenes tengan la misma dimensión
    //Cada imagen correponde a una fila de la matriz data
    if(!ReadFiles(RowsCols))exit(-1);

    if(filenames.size()!=rowPerson.size()){
        cout<<"Not all files were open"<<endl;
        exit(-1);
    }

    data.SetRows(filenames.size());
    data.SetCols(RowsCols.second*RowsCols.first);

    //Quita la media a cada fila (a cada imagen)
    if(center){
        CenterData();
    }
}

void Data::CenterData(){
    means = Statistics::means(data, false);
    data.SubtractVector(means, false);
}

bool Data::ReadFiles(pair<int, int> RowsCols){
    unsigned ImageRows = RowsCols.first;
    unsigned ImageCols = RowsCols.second;
    for(auto & filename : filenames){
        Image image(filename);
        if(ImageRows!=image.nRows || ImageCols!=image.nCols){
            cout<<"Images of different sizes"<<endl;
            return false;
        }
        data.AddRow(image.pixels);
    }
    return true;
}
pair<int, int> Data::ReadImageDims(){
    for(auto & filename : filenames){
        Image image(filename);
        return make_pair(image.nRows, image.nCols);
    }
    cout<<"No filenames"<<endl;
    return make_pair(-1, -1);
}

void Data::CreateFilenames(vector<int> selectedImages){


    filenames.clear();
    const string folder = "C:\\Users\\luna_\\Documents\\Cursos\\Numeric Methods\\Tareas\\Proyecto\\Material\\s";
    const string doubleSlash = "\\";
    const string type = ".pgm";
    for(int person=selectedImages[2]; person<selectedImages[0]+selectedImages[2]; person++){
        for(int image=selectedImages[3]; image<selectedImages[1]+selectedImages[3]; image++){
            rowPerson.push_back(person-1);
            string filePath = folder+to_string(person)+doubleSlash+to_string(image)+type;
            filenames.push_back(filePath);
        }
    }

}