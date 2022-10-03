//
// Created by luna_ on 06/12/2020.
//

#include "Image.h"


#include <fstream>
#include <iterator>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

void Image::InvertImage(){
    /*Invierte la escala de grises*/
    for(unsigned idx=0; idx<(nRows)*(nCols); idx++){
        pixels[idx] = 255 - (pixels)[idx];
    }
}


Image::Image(const string& filename){

    //Abre y revisa que el archivo se haya encontrado
    ifstream input(filename, ios::binary);
    if (!input.is_open()){
        cout << "Could not open file"<< endl;
    }

    //Revisa si es un archivo tipo PGM leyendo los primeros dos bytes
    string buffer;
    getline(input, buffer);
    if(buffer!="P5"){
        perror("Its not a PGM-P5 file");
        input.close();
    }

    //Omite los comentarios
    getline(input, buffer);
    while(buffer[0]=='#'){
        getline(input, buffer);
    }

    //Lee dimensiones
    stringstream ss(buffer);
    string dim;
    getline(ss, dim, ' ');
    nCols = atoi(dim.c_str());
    getline(ss, dim, ' ');
    nRows = atoi(dim.c_str());

    //Lee máximo valor de la escala de grises (usualmente 255)
    int max_scale;
    getline(input, buffer);
    max_scale = atoi(buffer.c_str());
    if(max_scale!=255){
        cout<< "PGM max value = " << max_scale << endl;
    }

    //Lectura de datos
    vector<double> temp(istreambuf_iterator<char>(input), {});
    pixels = temp;

    //Cierra el archivo
    input.close();

}

Image::Image(vector<double>& pixels, unsigned nRows, unsigned nCols){
    this->pixels = pixels;
    this->nRows = nRows;
    this->nCols = nCols;
}

pair<double, double> Image::MinMax(){

    pair<double, double> minMax;
    minMax.first = DBL_MAX;
    minMax.second = -DBL_MAX;

    for(double pixel : pixels){
        if(minMax.first >pixel){
            minMax.first = pixel;
        }
        if(minMax.second<pixel){
            minMax.second = pixel;
        }
    }

    return minMax;
}

void Image::NormalizeImage(){
    /*Recibe una matriz y la normaliza para que tenga sólo valores
    en la escala de grises*/
    pair<double, double> minMax;
    for(double & pixel : pixels){
            pixel = 255*(pixel-minMax.first)/(minMax.second-minMax.first);
    }

}

void Image::write(const string& prefix, const string& middle){
    string filename = prefix+middle+".pgm";
    write(filename);
}

void Image::write(const string& filename){

    //Abre y revisa que el archivo se haya encontrado
    ofstream myFile;
    myFile.open(filename, ios::binary);
    if (!myFile.is_open()){
        cout << "Cannot open file"<< endl;
    }

    //Escribe el encabezado del formato P2
    myFile<<"P5\n";
    myFile<<nCols<<" "<<nRows<<endl;
    myFile<<255<<endl;

    //Escribe los colores de los pixeles
    for(double & pixel : pixels){
        myFile.write((char*) &pixel, sizeof(unsigned char));
    }


    //Cierra el archivo
    myFile.close();

}

