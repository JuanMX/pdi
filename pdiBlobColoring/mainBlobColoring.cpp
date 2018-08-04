/*
MIT License

Copyright (c) 2018 JuanMX

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.


Programa principal

Compilar: g++ mainBlobColoring.cpp pdiBlobColoring.cpp pdiBlobColoring.h -o mainBlob `pkg-config --cflags --libs opencv`

Ejecutar: ./mainBlob NombreDeLaImagen.extencion NombreDeLaImagen

*/ 

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "pdiBlobColoring.h"//funcion blob coloring y colorear(colorea y cuenta las regiones)

using namespace std;
using namespace cv;

int main ( int argc, char** argv ){
    
    Mat imgBin;
    int totalEtiquetas;
    int i, j;
    
    if ( argc != 3 ){
		cout<<"Para dar una imagen de entrada es con ./NombreDelEjecutable NombreDeLaImagen.extencion NombreDeLaImagen"<< endl;
		return -1;
	}
	
	imgBin = imread(argv[1], 0); //abre gris
    
    Mat regiones(imgBin.size(), CV_32S);
    
    
    totalEtiquetas = pdiBlobColoring4Vecinos( imgBin, regiones );
    
    printf("Tablero de regiones 4 vecinos\n");
    for( i = 0; i < regiones.rows; i++){
        for( j = 0; j < regiones.cols; j++){
            if (regiones.at<int32_t>(i, j) == 0){
                printf(".");
                
            }
            else{
                printf("%d", regiones.at<int32_t>(i, j));
            }
        }
        printf("\n");
    }
    printf("Total de etiquetas: %d\n\n", totalEtiquetas);
    
    pdiColorearRegiones(regiones, totalEtiquetas, argv[2]);
    
    totalEtiquetas = pdiBlobColoring8Vecinos( imgBin, regiones );
    
//     for( i = 0; i < regiones.rows; i++){
//         for( j = 0; j < regiones.cols; j++){
//             regiones.at<int32_t>(i,j)=255;
//         }
//     }
    
    printf("Tablero de regiones 8 vecinos\n");
    for( i = 0; i < regiones.rows; i++){
        for( j = 0; j < regiones.cols; j++){
            
            if (regiones.at<int32_t>(i,j) == 0){
            
                printf(".");
            }
            else{
                printf("%d", regiones.at<int32_t>(i,j));
            }
        }
        printf("\n");
    }
    printf("Total de etiquetas: %d\n\n", totalEtiquetas);
    
    pdiColorearRegiones(regiones, totalEtiquetas, argv[2]);
    
    return 0;
}
