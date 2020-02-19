/*
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

Operaiones para imagenes binarias tipo AND, OR. y morfologicas tipo erode, dilate, open, close
*/

#include "pdiMorfologicas.h"

/*Son las versiones generalizadas de AND OR y NOT con el fin de que despues 
se realice pdiErode y pdiDilate para imagenes en escala de grises

NOT no se usa pero se deja de todos modos*/

int pdiAND(int intensidad1, int intensidad2){
	//AND solo regresa el minimo
	if (intensidad1 <= intensidad2){
		return intensidad1;
	}

	else{
		return intensidad2;
	}

}

int pdiOR(int intensidad1, int intensidad2){
	//OR solo regresa el maximo
	if (intensidad1 >= intensidad2){
		return intensidad1;
	}

	else{
		return intensidad2;
	}
}

int pdiNOT(int intensidad, int nivelesDeIntensidad){
	return nivelesDeIntensidad-1-intensidad;
}

/*
 Hace una erosion modificando la imagen original
 si se necesita la imagen orignal intacta puedes hacer lo siguiente:
 
 imagenOriginal = imread("ERODE.tif", 0);
 Mat imagenClonada = imagenOriginal.clone();
 pdiErode(imagenClonada);
 */
void pdiErode( Mat erosionada ){
    Mat imagen = erosionada.clone();

    int i,j;
    
    /*
     Recorre la imagen con una ventana de 3x3 llena de 255 (blanco), buscando el primer caso para el cual al hacer
     pdiAND con el correspondiente nivel de intensidad en la imagen de 0 (falso), entonces pone en el pixel central de la
     ventana de 3x3 pero correspondiente a la imagen 0 (erosiona) y continua la ventana recorriendo la imagen
     */
    
    for(i=0;i<imagen.rows;i++){
        for(j=0;j<imagen.cols;j++){
            //analiza todos los de la fila de arriba (i-1)
            if( i-1>=0 ){
                // superior izquierda
                if( j-1>=0 ){
                    if( pdiAND( 255, imagen.at<uchar>(i-1,j-1) )==0 ){
                            erosionada.at<uchar>(i,j) = 0;
                            continue;
                    }
                }
                // superior derecha
                if( j+1<imagen.cols ){
                    if( pdiAND( 255, imagen.at<uchar>(i-1,j+1) )==0 ){
                        erosionada.at<uchar>(i,j) = 0;
                        continue;
                    }
                }
                //el que esta justo arriba
                if( pdiAND( 255, imagen.at<uchar>(i-1,j) )==0 ){
                    erosionada.at<uchar>(i,j) = 0;
                    continue;
                }
            }
            //analiza los de la fila de abajo
            if( i+1 < imagen.rows ){
                //izquierda
                if( j-1>=0 ){
                    if( pdiAND( 255, imagen.at<uchar>(i+1,j-1) )==0 ){
                        erosionada.at<uchar>(i,j) = 0;
                        continue;
                    }
                }
                //derecha
                if(j+1 < imagen.cols){
                    if( pdiAND( 255, imagen.at<uchar>(i+1,j+1) )==0 ){
                        erosionada.at<uchar>(i,j) = 0;
                        continue;
                    }
                }
                // el que esta justo abajo
                if( pdiAND( 255, imagen.at<uchar>(i+1,j) )==0 ){
                    erosionada.at<uchar>(i,j) = 0;
                    continue;
                }
            }

            //analiza a los lados
            //izquierda
            if(j-1>=0){
                if( pdiAND( 255, imagen.at<uchar>(i,j-1) )==0 ){
                    erosionada.at<uchar>(i,j) = 0;
                    continue;
                }
            }
            //derecha
            if(j+1<imagen.cols){
                if( pdiAND( 255, imagen.at<uchar>(i,j+1) )==0 ){
                    erosionada.at<uchar>(i,j) = 0;
                    continue;
                }
            }
            //Analiza el pixel actual
            //Me parece que esta condicional esta demas pero igual se deja
            if( pdiAND( 255, imagen.at<uchar>(i,j) )==0){
                erosionada.at<uchar>(i,j) = 0;
                continue;
            }
        }
    }

}

/*
 Hace una dilatacion modificando la imagen original
 si se necesita la imagen orignal intacta puedes hacer lo siguiente:
 
 imagenOriginal = imread("ERODE.tif", 0);
 Mat imagenClonada = imagenOriginal.clone();
 pdiDilate(imagenClonada);
 */

void pdiDilate( Mat dilatada ){
	Mat imagen = dilatada.clone();
	int i,j;
    
    /*
     Recorre la imagen con una ventana de 3x3 llena de 0 (negro), buscando el primer caso para el cual al hacer
     pdiOR con el correspondiente nivel de intensidad en la imagen de 255 (verdadero), 
     entonces pone en el pixel central de la ventana de 3x3 pero correspondiente a la imagen 255 (dilata) y continua la ventana recorriendo la imagen
     */
    
    for(i=0;i<imagen.rows;i++){
        for(j=0;j<imagen.cols;j++){
            //analiza todos los de la fila de arriba (i-1)
            if( i-1>=0 ){
                // superior izquierda
                if( j-1>=0 ){
                    if( pdiOR( 0, imagen.at<uchar>(i-1,j-1) )==255 ){
                            dilatada.at<uchar>(i,j) = 255;
                            continue;
                    }
                }
                // superior derecha
                if( j+1<imagen.cols ){
                    if( pdiOR( 0, imagen.at<uchar>(i-1,j+1) )==255 ){
                        dilatada.at<uchar>(i,j) = 255;
                        continue;
                    }
                }
                //el que esta justo arriba
                if( pdiOR( 0, imagen.at<uchar>(i-1,j) )==255 ){
                    dilatada.at<uchar>(i,j) = 255;
                    continue;
                }
            }
            //analiza los de la fila de abajo
            if( i+1 < imagen.rows ){
                //izquierda
                if( j-1>=0 ){
                    if( pdiOR( 0, imagen.at<uchar>(i+1,j-1) )==255 ){
                        dilatada.at<uchar>(i,j) = 255;
                        continue;
                    }
                }
                //derecha
                if(j+1 < imagen.cols){
                    if( pdiOR( 0, imagen.at<uchar>(i+1,j+1) )==255 ){
                        dilatada.at<uchar>(i,j) = 255;
                        continue;
                    }
                }
                // el que esta justo abajo
                if( pdiOR( 0, imagen.at<uchar>(i+1,j) )==255 ){
                    dilatada.at<uchar>(i,j) = 255;
                    continue;
                }
            }

            //analiza a los lados
            //izquierda
            if(j-1>=0){
                if( pdiOR( 0, imagen.at<uchar>(i,j-1) )==255 ){
                    dilatada.at<uchar>(i,j) = 255;
                    continue;
                }
            }
            //derecha
            if(j+1<imagen.cols){
                if( pdiOR( 0, imagen.at<uchar>(i,j+1) )==255 ){
                    dilatada.at<uchar>(i,j) = 255;
                    continue;
                }
            }
            //Analiza el pixel actual
            //Me parece que esta condicional esta demas pero igual se deja
            if( pdiOR( 0, imagen.at<uchar>(i,j) )==255){
                dilatada.at<uchar>(i,j) = 255;
                continue;
            }
        }
    }
}

/// Las siguientes funciones son "aplicaciones" de pdiErode y pdiDilate

void pdiContornoErode( Mat imagen, Mat imagenContorno ){

	Mat imagenErode = imagen.clone();
    
	pdiErode( imagenErode );

	restaImagenes( imagen, imagenErode, imagenContorno);/// A imagen le resta imagenErode
}

void pdiContornoDilate( Mat imagen, Mat imagenContorno ){

	Mat imagenDilate = imagen.clone();
    
	pdiDilate( imagenDilate );

	restaImagenes( imagenDilate, imagen, imagenContorno);/// A imagenDilate le resta imagen
}

void pdiOpen(Mat imagen){
    
    pdiErode( imagen );
    pdiDilate( imagen );
}

void pdiClose(Mat imagen){
    
    pdiDilate( imagen );
    pdiErode( imagen );
}

/// A imagen1 le resta imagen2
void restaImagenes( Mat imagen1, Mat imagen2, Mat imagenResultado ){
	int i,j;

	/// A imagen1 le resta imagen2
	for( i=0; i < imagenResultado.rows; i++){
		for( j=0; j < imagenResultado.cols; j++ ){
			imagenResultado.at<uchar>(i , j) = imagen1.at<uchar>( i, j ) - imagen2.at<uchar>( i, j );
		}
	}
}
