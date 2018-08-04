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
*/

#ifndef PDI_HISTOGRAMA_H
#define PDI_HISTOGRAMA_H

#include <stdio.h>
#include <iostream>
#include <string>

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

//obtiene el histograma para imagenes en escala de grises
void pdiHistograma(int histograma[], Mat imagen, int nivelesDeIntensidad);

//funciona bien para graficar histogramas [0-255]
//supone que gnuplot (un programa por terminal para graficar) esta instalado
//NO es una libreria de gnuplot. Lo que hace es comunicarse con el programa a travez de un apuntador de tipo Pipe
// n_i[] es el histograma, id [] es el nombre de la imagen sin extencion a la que se le obtuvo el histograma
void gnuplotear( int n_i[ ], int nivelDeIntensidad, char id []);

#endif
