//
// Created by luna_ on 07/12/2020.
//
#include <cstdlib>
#include "Linear.h"
#include <cstdio>
#include <ctime>

int Linear::normalize(vector<double>& vec){
    /*Recibe un vector y su dimensión y lo devuelve normalizado*/
    double norm = 0.0;
    for(int row=0; row<vec.size(); row++){
        norm += vec[row]*vec[row];
    }
    norm = sqrt(norm);
    if(norm == 0)
        return 1;
    for(double & row : vec){
        row = row/norm;
    }
    return 0;
}

void Linear::ProductMatVec(Matrix& mat, vector<double>& vec, vector<double>& prod){
    /*Realiza el producto de la matriz cuadrada mat con el vector vec
    y lo guarda en prod. nrows es el numero renglones de vec*/
    double row_sum = 0.0;
    for(int row=0; row<vec.size(); row++){
        row_sum = 0.0;
        for(int col=0; col<vec.size(); col++){
            row_sum += mat[row][col]*vec[col];
        }
        prod[row] = row_sum;
    }
}

void Linear::OrthogonalizeVector(Matrix& eig_vecs, vector<double>& vec, int nprev_eigs){
    /*Realiza deflación en vec respecto a los primeros nprev_eigs
    eigenvectores guardados en la matriz eig_vecs (un eigenvector por fila)*/
    vector<double> proy = vector<double>(nprev_eigs);
    for(int prev=0; prev<nprev_eigs; prev++){
        //Se encuentra la proyección de vec en el prev-ésimo eigenvector
        for(int row=0; row<vec.size(); row++){
            proy[prev] += eig_vecs[prev][row]*vec[row];
        }

    }
    //Se restan las contribiciones de los eigenvectores en vec
    for(int prev=0; prev<nprev_eigs; prev++){
        for(int row=0; row<vec.size(); row++){
            vec[row] = vec[row] - proy[prev]*eig_vecs[prev][row];
        }
    }

}

double Linear::DotProduct(vector<double>& vec1, vector<double>& vec2){
    double dot_p = 0.0;
    for(int row=0; row<vec1.size(); row++){
        dot_p += vec1[row]*vec2[row];
    }
    return dot_p;
}


pair<Matrix, vector<double> > Linear::nEigenPower(Matrix& mat, int nSol, double precision){
    /*Recibe una matriz simétrica mat, su número de filas nrows,
    escribe en archivos de param_ptr, a los nSol eigenvalores más grandes de la matriz y a sus
    vectores correspondientes, sólo se asegura que sean estimaciones correctas si todos son distintos */
    srand ((unsigned) time(0));


    int nrows = mat.GetRows();
    vector<double> sol_vals = vector<double>(nSol); //Vector de eigenvalores
    Matrix sol_vecs(nSol, nrows); //Matriz de eigenvectores (un eigenvector por fila)
    vector<double> vv = vector<double>(nrows); //Vector inicial
    vector<double> vn = vector<double>(nrows); //Siguiente estimación



    double tolerance = 5.0*pow(10.0,-precision); //tolerancia basada en la precisión establecida
    int ite;
    int max_ite = 3000;
    double eig_val;
    double nxt_val;
    double dif;
    int save_max = 0;




    //Ciclo para encontrar los nSol mayores eigenvalores y eigenvectores
    for(int sol=0; sol<nSol; sol++){
        ite = 1;
        eig_val = 0.0;
        nxt_val = 0.0;
        dif = tolerance +10.0;
        int max = 1;
        int min = -1;

        //Vector inicial aleatorio
        for(int i=0; i<nrows; i++){
            int r = rand()%(max-min + 1) + min;
            vv[i] = (double)r;
        }



        //Método de potencia
        while( dif>tolerance && ite < max_ite){

            //Deflación a vector inicial
            OrthogonalizeVector(sol_vecs, vv, sol);

            //Normaliza al vector inicial
            normalize(vv);

            //Realiza el producto de vector anterior vv con la matriz y se guarda en vn
            ProductMatVec(mat, vv, vn);

            //Calcula la siguiente estimación del eigenvalor
            nxt_val = DotProduct(vn, vv); //no se divide entre DotProduct(vv, vv, nrows) porque es 1

            //Actualiza al vector inicial
            vector<double> tmp;
            tmp = vv;
            vv= vn;
            vn = tmp;

            //Guarda la distancia para detectar convergencia
            dif = fabs(eig_val-nxt_val);

            //Actualiza a la estimación de eigenvalor
            eig_val = nxt_val;

            ite ++;
        }

        //Descarta si no convergio algún eigenvector
        if(ite == max_ite){
            printf("Power method did not converge in solution s = %d\n", sol+1);
            break;
        }
//        else{
//            cout<<"Power method founded eigenval["<<sol+1<<"] = "<<eig_val<<endl;
//        }
        if(ite> save_max){
            save_max = ite;
        }

        //Guarda el eigenvalor
        sol_vals[sol] = eig_val;


        //Guarda el eigenvector asociado
        normalize(vv);
        for(int col=0; col<nrows; col++){
            sol_vecs[sol][col] = vv[col];
        }


    }

    //Imprime los eigenvalores
    cout<<endl;
    printf("Max number of iterations in Power Method n = %d\n", save_max);
    cout<<endl;


    //Escribe los resultados

    return make_pair(sol_vecs, sol_vals);

}


