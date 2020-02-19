/*
MIT License

Copyright (c) 2020 JuanMX

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

Compilar: g++ mainImagenNegativa.cpp pdiImagenNegativa.cpp pdiImagenNegativa.h -o mainImagenNegativa `pkg-config --cflags --libs opencv`

Ejecutar: ./mainImagenNegativa rainbow.jpg rainbow

*/


#include <stdio.h>
#include <string>

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "pdiImagenNegativa.h" ///funciones de operaciones morfologicas

using namespace std;
using namespace cv;

int main ( int argc, char** argv ){
    Mat imgOriginal, imgNegativa;
    
    string nombreImg;
    
    if ( argc != 3 ){
		cout<<"Para dar una imagen de entrada es con ./NombreDelEjecutable NombreDeLaImagen.extencion NombreDeLaImagen"<< endl;
		return -1;
	}
    
    
    imgOriginal = imread(argv[1], 1); //abre en escala de gris pero la imagen es binaria
    nombreImg = argv[2];
    imgNegativa = imgOriginal.clone();
    
    
    if ( !imgOriginal.data || !imgNegativa.data){
		cout<<"No hay datos en la imagen"<< endl;
        cout<<"Se dio bien el nombre de la imagen ?"<< endl;
		return -1;
	}
    
    pdiImagenNegativa(imgNegativa);
    
    imwrite(nombreImg + "_Negativa.png", imgNegativa);

    return 0;
}
