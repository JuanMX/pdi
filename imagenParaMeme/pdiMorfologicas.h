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

Contiene las definicones de las operaciones morfologicas y sus aplicaciones
*/
#ifndef PDIMORFOLOGICAS_H
#define PDIMORFOLOGICAS_H

#include <cstdlib>
#include <iostream>
#include <vector>

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;
using namespace std;

/*Son las versiones generalizadas de AND OR y NOT con el fin de que despues 
se realice pdiErode y pdiDilate para imagenes en escala de grises

NOT no se usa pero se deja de todos modos*/

int pdiAND(int intensidad1, int intensidad2);
int pdiOR(int intensidad1, int intensidad2);
int pdiNOT(int intensidad, int nivelesDeIntensidad);

void pdiErode(Mat imagen);
void pdiDilate(Mat imagen);

/// Las siguientes funciones son "aplicaciones" de pdiErode y pdiDilate
void pdiContornoErode( Mat imagen, Mat imagenContorno );
void pdiContornoDilate( Mat imagen, Mat imagenContorno );
void pdiOpen(Mat imagen);
void pdiClose(Mat imagen);

void restaImagenes( Mat imagen1, Mat imagen2, Mat imagenResultado);

#endif // PDIMORFOLOGICAS_H
