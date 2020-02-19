
#include "otsu.h"

//using namespace std;
//using namespace cv;

void histogramaNormalizado( float p_i[], float n_i[], float N , int nivelDeIntensidad ){
  int i;
  for( i = 0; i < nivelDeIntensidad; i++){
    p_i[i] = n_i[i] / N;
  }
}
/*
void verificarHistograma( float p_i[], int nivelDeIntensidad ){
  int i;
  float uno;
  for( i = 0; i < nivelDeIntensidad; i++ ){
    uno = uno + p_i[i];
  }
  printf("\nSuma de todos los valores en el histograma normalizado %f\n", uno);
  printf("La suma debe ser igual a 1\n");
}
*/
float obtenerP1k( int k, float p_i[ ] ){
  int i;
  float P1k = 0;

  for( i = 0; i <= k; i++){
    P1k = P1k + p_i[i];
  }

  return P1k;
}
float obtenermk( int k, float p_i[ ] ){
  int i;
  float mk = 0;

  for( i = 0; i <= k; i++){
    mk = mk + ( i * p_i[i] );
  }

  return mk;
}

float obtenermg( int nivelDeIntensidad, float p_i[ ] ){
  int i;
  float mg = 0;
  for( i = 0; i < nivelDeIntensidad; i++ ){
    mg = mg + ( i * p_i[i] );
  }

  return  mg;
}

float varianzaEntreClases( float P1k, float mk, float mg ){
  float varianza = 0;

  varianza = ( ( (mg*P1k) - (mk) ) * ( (mg*P1k) - (mk) ) ) / ( P1k * ( 1 - P1k ) );

  return varianza;
}

///en este metodo de obtencion del umbral optimo, si hay mas de 1 se queda con el ultimo encontrado
int obtenerUmbralOptimo(float p_i[ ], float varianza, float mg , int kInicial ,int nivelDeIntensidad){
  int k, kOtsu = kInicial;
  float P1k, mk, kResultado;
  for( k = 1; k < nivelDeIntensidad; k++ ){
    P1k = obtenerP1k( k, p_i );
    mk = obtenermk( k, p_i );
    kResultado = varianzaEntreClases( P1k, mk, mg );

    if ( kResultado > varianza ){
      varianza = kResultado;
      kOtsu=k;
    }
  }
  return kOtsu;
}

void binarizarMatriz( Mat imagen1, int kOtsu ){
  int x, y;
  for( int x = 0; x < imagen1.rows; x++ ){
    for( int y = 0; y < imagen1.cols; y++ ){
      if( imagen1.at<uchar>(x,y) < kOtsu  ){
        imagen1.at<uchar>(x,y) = 255; //para nivel de gris

//         imagen1.at<Vec3b>(x, y)[0] = 255; //azul (B)
//         imagen1.at<Vec3b>(x, y)[1] = 255; //verde (G)
//         imagen1.at<Vec3b>(x, y)[2] = 255; //rojo (R)
      }
      else {
        imagen1.at<uchar>(x,y) = 0; //para nivel de gris

//         imagen1.at<Vec3b>(x, y)[0] = 0; //azul (B)
//         imagen1.at<Vec3b>(x, y)[1] = 0; //verde (G)
//         imagen1.at<Vec3b>(x, y)[2] = 0; //rojo (R)

      }
    }
  }
}

void metodoOtsu1Umbral(Mat imagen1, int canal){

	int N; ///Numero de pixeles
	int nivelDeIntensidad = 256;
	float n_i[ nivelDeIntensidad ]; ///numero de pixeles con intensidad i
	int i, x, y;
	int kInicial = 100, kOtsu;
	float p_i[ nivelDeIntensidad ];
	float P1k = 0, mk = 0, mg = 0;
	float varianza;
	
	N = imagen1.rows * imagen1.cols;
	
	for ( i = 0; i < nivelDeIntensidad; i++ ) {
		n_i[ i ]=0;
  	}
  	
  	if ( canal > 2 || canal < 0) {
  		printf("\nEl canal de color esta fuera del rango [0-2]\nPista:\n0 -> Azul\n1 -> Verde\n2 -> Rojo\n");
  		exit(EXIT_FAILURE);
  	}

	for( int x = 0; x < imagen1.rows; x++ ){
		for( int y = 0; y < imagen1.cols; y++ ){

			n_i[ imagen1.at<uchar>(x,y) ] = n_i[ imagen1.at<uchar>(x,y) ] + 1; //para nivel de gris
			//n_i[ imagen1.at<Vec3b>(x, y)[canal] ] = n_i[ imagen1.at<Vec3b>( x, y )[ canal ] ] + 1;
		}
	}
	
	/// 1 calcula el histograma normalizado
	histogramaNormalizado( p_i, n_i, N, nivelDeIntensidad );
	/// 2 calcula las sumas comulativas P1(k)
	P1k = obtenerP1k( kInicial, p_i );
	/// 3 calcula las medias comulativas m(k)
	mk = obtenermk( kInicial, p_i );
	/// 4 calcula la intensidad media global
	mg = obtenermg( nivelDeIntensidad, p_i );
	/// 5 calcula la varianza entre clases
	varianza = varianzaEntreClases( P1k, mk, mg );
	/// 6 obtiene el umbral de otsu k*
	kOtsu = obtenerUmbralOptimo( p_i, varianza, mg , kInicial , nivelDeIntensidad );

	binarizarMatriz( imagen1, kOtsu );
}


