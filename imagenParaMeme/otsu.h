#ifndef OTSU_H
#define OTSU_H

#include <stdio.h>
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;
/// Calcula el histograma normalizado
void histogramaNormalizado( float p_i[ ], float n_i[ ], float N ,int nivelDeIntensidad );
/// Muestra las sumas del histograma que deben ser = 1
//void verificarHistograma( float p_i[ ], int nivelDeIntensidad );
/// Calcula las sumas comulativas P1(k)
float obtenerP1k( int k, float p_i[ ] );
/// Calcula las medias comulativas m(k)
float obtenermk( int k, float p_i[ ] );
/// Calcula la intensidad media global mg
float obtenermg( int nivelDeIntensidad, float p_i[ ] );
/// Calcula la varianza entre clases
float varianzaEntreClases( float P1k, float mk, float mg );
/// Calcula el umbral de Otsu k*
int obtenerUmbralOptimo(float p_i[ ], float varianza, float mg , int kInicial ,int nivelDeIntensidad);
/// Binariza la matriz BGR
void binarizarMatriz( Mat imagen1, int kOtsu );
///Esta funcion llama a las funciones de arriba que son los pasos que realiza el metodo de otsu
void metodoOtsu1Umbral(Mat imagenORiginal, int canal);

#endif //OTSU_H
