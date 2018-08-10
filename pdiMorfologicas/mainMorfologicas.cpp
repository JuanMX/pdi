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

Compilar: g++ mainMorfologicas.cpp pdiMorfologicas.cpp pdiMorfologicas.h -o mainMorfologicas `pkg-config --cflags --libs opencv`

Ejecutar: ./mainMorfologicas ERODE_Binaria.tif DILATE_Binaria.tif ERODE DILATE

*/

#include <stdio.h>
#include <string>

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "pdiMorfologicas.h" ///funciones de operaciones morfologicas

using namespace std;
using namespace cv;

int main ( int argc, char** argv ){
    Mat imgErode, imgDilate, imgErode2, imgDilate2;
    
    string nombreImgErode, nombreImgDilate;
    
    if ( argc != 5 ){
		cout<<"Para dar una imagen de entrada es con ./NombreDelEjecutable NombreDeLaImagen.extencion NombreDeLaImagen"<< endl;
		return -1;
	}
    
    
    imgErode = imread(argv[1], 0); //abre en escala de gris pero la imagen es binaria
    imgDilate = imread(argv[2], 0); //abre en escala de gris pero la imagen es binaria
    imgErode2 = imgErode.clone();
    imgDilate2 = imgDilate.clone();
    nombreImgErode = argv[3];
    nombreImgDilate = argv[4];
    
    Mat imgContornoErode(imgErode.size(), CV_8U);
    Mat imgContornoDilate(imgDilate.size(), CV_8U);
    
    if ( !imgErode.data || !imgDilate.data){
		cout<<"No hay datos en la imagen"<< endl;
        cout<<"Se dio bien el nombre de la imagen ?"<< endl;
		return -1;
	}
    
    //Erosiona 2 veces
    pdiErode(imgErode);
    pdiErode(imgErode);
    
    //Dilata 3 veces
    pdiDilate(imgDilate);
    pdiDilate(imgDilate);
    pdiDilate(imgDilate);
    
    //Obtiene el contorno con erosion y resta de imagenes
    pdiContornoErode( imgErode2, imgContornoErode );
    //Obtiene el contorno con dilatacion y resta de imagenes
    pdiContornoDilate( imgDilate2, imgContornoDilate );
    
//     pdiOpen(imgDilate);
//     pdiOpen(imgDilate);
//     
//     pdiClose(imgErode);
//     pdiClose(imgErode);
    
    imwrite(nombreImgErode + "_Erode.tif", imgErode);
    imwrite(nombreImgDilate + "_Dilate.tif", imgDilate);
    imwrite(nombreImgErode + "_ContornoErode.tif", imgContornoErode);
    imwrite(nombreImgDilate + "_ContornoDilate.tif", imgContornoDilate);
    
    return 0;
}
