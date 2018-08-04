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
#include "pdiHistograma.h"

//obtiene el histograma para imagenes en escala de grises
void pdiHistograma(int histograma[], Mat imagen, int nivelesDeIntensidad){
    int i, j;

    //llena el histograma de ceros
    for (i=0; i<nivelesDeIntensidad; i++){
        histograma[i]=0;
    }

    //obtiene el histograma
    for (i=0; i < imagen.rows; i++){
        for(j=0; j < imagen.cols; j++){
            histograma[ imagen.at<uchar>(i,j) ] =  histograma[ imagen.at<uchar>(i,j) ] + 1;
        }
    }
}

//funciona bien para graficar histogramas [0-255]
//supone que gnuplot (un programa por terminal para graficar) esta instalado
//NO es una libreria de gnuplot. Lo que hace es comunicarse con el programa a travez de un apuntador de tipo Pipe
// n_i[] es el histograma, id [] es el nombre de la imagen sin extencion la que se le obtuvo el histograma
void gnuplotear( int n_i[ ], int nivelDeIntensidad, char id []){
    int i;
    FILE * Pipe = popen ( "gnuplot -persist", "w" );

    fprintf( Pipe," set title 'Histograma de %s en niveles de gris' \n", id );
    fprintf( Pipe," set xlabel 'Niveles de intensidad'\n" );
    fprintf( Pipe," set ylabel 'Cantidad de pixeles'\n" );
    fprintf( Pipe," set xtics (0,63,127,191,255)\n");
    fprintf( Pipe," set grid\n" );
    fprintf( Pipe," set terminal png\n");
    fprintf( Pipe," set output ' %s_Histograma.png'\n", id );
    fprintf( Pipe,"plot [0:255]'-' with boxes linecolor rgb 'blue' title 'Pixeles con intensidad gris'\n");

    for ( i = 0; i < nivelDeIntensidad; i++ ){
        fprintf( Pipe, "%d %d\n", i, n_i[ i ] );
    }
    
    fprintf( Pipe, "e\n" );
    
    fprintf(Pipe, "exit\n" );
    fclose( Pipe );
}

/*
 void gnuplotear( int n_i[ ], int nivelDeIntensidad, int T, char id []){
  int i;
  FILE * Pipe = popen ( "gnuplot -persist", "w" );

	fprintf( Pipe," set title 'Histograma de %s en niveles de gris' \n", id );
	fprintf( Pipe," set xlabel 'Niveles de intensidad'\n" );
	fprintf( Pipe," set ylabel 'Cantidad de pixeles'\n" );
  fprintf( Pipe," set xtics (0,63,127,191,255, %d)\n", T );
	fprintf( Pipe," set grid\n" );
  fprintf( Pipe, " set terminal png\n");
  fprintf( Pipe, " set output ' %s Histograma.png'\n", id );
	fprintf( Pipe, "plot [0:255]'-' with boxes linecolor rgb 'blue' title 'Pixeles con intensidad gris', '-' with boxes linecolor rgb 'red' title 'Threshold: %d' \n", T );

	for ( i = 0; i < nivelDeIntensidad; i++ ){
	   fprintf( Pipe, "%d %d\n", i, n_i[ i ] );
	}
	fprintf( Pipe, "e\n" );
  fprintf( Pipe, "%d %d\n", T, n_i[ T ] );
  fprintf( Pipe, "e\n" );
  fprintf(Pipe, "exit\n" );
	fclose( Pipe );
}
 */
