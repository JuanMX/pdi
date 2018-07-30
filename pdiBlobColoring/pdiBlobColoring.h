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

#ifndef PDIBLOBCOLORING_H
#define PDIBLOBCOLORING_H

#include <cstdlib>
#include <iostream>
#include <vector>
#include <iomanip>
#include <stdio.h>
#include <algorithm>
#include <fstream>
#include <cstring>
#include <string>
#include <opencv2/opencv.hpp>

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;
using namespace std;

//Mat regiones debe ser de 32 bits
// la manera de escribir valores > a 255 es con <int32_t>
// y asi debe estar en el codigo externo que use este metodo
int pdiBlobColoring4Vecinos (Mat imagen, Mat regiones);
void pdiColorearRegiones(Mat regiones, int totalColores, char imgNombre[]);
int buscarVector(vector<int> & vec, int n);
void insertarTablaDeEquivalencias(int a, int b, vector <vector<int> > &tablaEquivalencias);
int pdiBlobColoring8Vecinos(Mat imagen, Mat regiones);


#endif
