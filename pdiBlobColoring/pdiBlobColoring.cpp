/*Algoritmo blob coloring para imagenes binarias "retorna" un tablero con las etiquetas de region y el total de etiquetas

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
#include "pdiBlobColoring.h"

//Mat regiones debe ser de 32 bits
// la manera de escribir valores > a 255 es con <int32_t>
// y asi debe estar en el codigo externo que use esta funcion
int pdiBlobColoring4Vecinos(Mat imagen, Mat regiones){
	int totalRegiones = 1;
	int i,j,t,a,b,iTabla, jTabla;
	int iMover, jMover;
	int iBuscar, jBuscar;
	int indiceA, indiceB, encontradoA=0, encontradoB=0;

	vector <vector<int> > tablaEquivalencias;

	//inicializa el tablero de regiones en ceros
	for (i = 0; i < regiones.rows; i++){
		for(j = 0; j < regiones.cols; j++){
			regiones.at<int32_t>(i,j) = 0;
		}
	}

	//caso para la primer fila
	for(i=0,j=0; j<imagen.cols; j++){
		if(j==0){
			if (imagen.at<uchar>(i,j) == 255){
				regiones.at<int32_t>(i,j) = totalRegiones;
				totalRegiones = totalRegiones + 1;
			}
		}
		else{
			if( imagen.at<uchar>(i,j)==255 && imagen.at<uchar>(i,j-1)==255 ){
				regiones.at<int32_t>(i,j) = regiones.at<int32_t>(i,j-1);
			}

			if( imagen.at<uchar>(i,j)==255 && imagen.at<uchar>(i,j-1)==0 ){
				regiones.at<int32_t>(i,j) = totalRegiones;
				totalRegiones = totalRegiones + 1;
			}

		}
	}

	//inicia el resto del tablero ignorando la primer fila
	for (i=1; i<imagen.rows; i++){
		for(j=0; j<imagen.cols;j++){

			//caso especial para la columna 0 ya que en esa posicion no hay un elemento a la izquierda
			if (j==0){
				if( imagen.at<uchar>(i,j)==255 && imagen.at<uchar>(i-1,j)==255 ){
					regiones.at<int32_t>(i,j) = regiones.at<int32_t>(i-1,j);
				}
				if( imagen.at<uchar>(i,j)==255 && imagen.at<uchar>(i-1,j)==0 ){
					regiones.at<int32_t>(i,j) = totalRegiones;
					totalRegiones = totalRegiones + 1;
				}
			}
			else{

				if (imagen.at<uchar>(i,j)==255 && imagen.at<uchar>(i,j-1)==0 && imagen.at<uchar>(i-1,j)==0){
					regiones.at<int32_t>(i,j) = totalRegiones;
					totalRegiones = totalRegiones + 1;
				}
				if(imagen.at<uchar>(i,j) == 255 && imagen.at<uchar>(i,j-1) == 0 && imagen.at<uchar>(i-1,j) == 255){
					regiones.at<int32_t>(i,j) = regiones.at<int32_t>(i-1,j);
				}
				if(imagen.at<uchar>(i,j) == 255 && imagen.at<uchar>(i,j-1) == 255 && imagen.at<uchar>(i-1,j) == 0){
					regiones.at<int32_t>(i,j) = regiones.at<int32_t>(i,j-1);
				}
				///caso de posible cambio de region
				if(imagen.at<uchar>(i,j) == 255 && imagen.at<uchar>(i,j-1) == 255 && imagen.at<uchar>(i-1,j)==255){


					if(regiones.at<int32_t>(i,j-1) != regiones.at<int32_t>(i-1,j)){
						/// Para cada a diferente de b encontrado en la asignacion de etiquetas
						a = regiones.at<int32_t>(i-1,j);
						b = regiones.at<int32_t>(i,j-1);

						if(regiones.at<int32_t>(i,j-1) < regiones.at<int32_t>(i-1,j)){
							regiones.at<int32_t>(i-1,j) = regiones.at<int32_t>(i,j-1);
						}
						else{
							regiones.at<int32_t>(i,j-1) = regiones.at<int32_t>(i-1,j);
						}


						/// buscar a y b en cada renglon de la tabla de equivalencia
						for( iTabla=0; iTabla < tablaEquivalencias.size(); iTabla++ ){
							for( jTabla=0; jTabla < tablaEquivalencias[iTabla].size(); jTabla++ ){
								///si encontado a marcarlo como encontrado y guardar la fila en la que fue encontrado
								if (buscarVector(tablaEquivalencias[iTabla], a)){
									encontradoA=1;
									indiceA=iTabla;
								}
								/// si encontrado b marcarlo como encontrado y guardar la fila en la que fue encontrado
								if(buscarVector(tablaEquivalencias[iTabla], b)){
									encontradoB=1;
									indiceB=iTabla;
								}
							}
						}

						/// si encontrado a y NO encontrado b: agregar b al mismo renglon de a en la tabla de equivalencia
						if(encontradoA==1 && encontradoB==0){
							tablaEquivalencias[indiceA].push_back(b);
						}
						/// si NO encontrado a y encontrado b: agregar a al mismo renglon de b en la tabla de equivalencia
						if(encontradoA==0 && encontradoB==1){
							tablaEquivalencias[indiceB].push_back(a);
						}
						/// si NO encontrado a y NO encontrado b: agregar a y b en un rengon nuevo
						if(encontradoA==0 && encontradoB==0){
							tablaEquivalencias.push_back(vector<int>());
							tablaEquivalencias[tablaEquivalencias.size()-1].push_back(a);
							tablaEquivalencias[tablaEquivalencias.size()-1].push_back(b);
						}

						//si se encontraron ambos insertar en A, mas adelante se unen las filas con etiquetas duplicadas
						if(encontradoA==1&&encontradoB==1){
							tablaEquivalencias[indiceA].push_back(b);
						}
						/// reiniciar la busqueda de a y b
						encontradoA=0;
						encontradoB=0;

					}
					regiones.at<int32_t>(i,j) = regiones.at<int32_t>(i,j-1);

				}

			}
		}
	}

	///Mueve los elementos duplicados a una sola fila
	for ( iTabla = 0; iTabla < tablaEquivalencias.size(); iTabla++ ){
    	for( jTabla = 0; jTabla < tablaEquivalencias[iTabla].size(); jTabla++ ){

    		// recorre el buscardor las filas 0 . . . iTabla -1
    		for( iBuscar = 0; iBuscar < iTabla; iBuscar++ ){

    			// si lo encuentra
				if ( buscarVector(tablaEquivalencias[iBuscar], tablaEquivalencias[iTabla][jTabla]) ){
					//printf("\nFue encontrado: %d En la fila %d\n", tablaEquivalencias[iTabla][jTabla], iBuscar);

					//copiar la fila donde fue encontrado el duplicado
					for( jMover = 0; jMover < tablaEquivalencias[iBuscar].size(); jMover++ ){
						tablaEquivalencias[iTabla].push_back(tablaEquivalencias[iBuscar][jMover]);
					}

					//destruir la fila donde fue encontrado el duplicado
					tablaEquivalencias[iBuscar].clear();
				}

    		}




    		// recorre el buscardor las filas iTabla + 1 . . . v1.size();
    		for( iBuscar = iTabla +1; iBuscar < tablaEquivalencias.size(); iBuscar++ ){
    			// si lo encuentra
				if ( buscarVector(tablaEquivalencias[iBuscar], tablaEquivalencias[iTabla][jTabla]) ){
					//printf("\nFue encontrado: %d En la fila %d\n", tablaEquivalencias[iTabla][jTabla], iBuscar);

					//copiar la fila donde fue encontrado el duplicado
					for( jMover = 0; jMover < tablaEquivalencias[iBuscar].size(); jMover++ ){
						tablaEquivalencias[iTabla].push_back(tablaEquivalencias[iBuscar][jMover]);
					}

					//destruir la fila donde fue encontrado el duplicado
					tablaEquivalencias[iBuscar].clear();
				}
    		}


    	}
    }

	/// ordenar cada renglon de menor a mayor en la tabla de equivalencias
	for( i=0; i < tablaEquivalencias.size(); i++ ){
		sort( tablaEquivalencias[i].begin(), tablaEquivalencias[i].end() );
	}

	/*
	printf("Contenido de la tabla de equivalencias\n");
	for( iTabla=0; iTabla < tablaEquivalencias.size(); iTabla++){
		for (jTabla=0; jTabla < tablaEquivalencias[iTabla].size(); jTabla++){
			cout <<tablaEquivalencias[iTabla][jTabla]<<"  ";
		}
		printf("\n\n");
	}
	printf("FIN Contenido de la tabla de equivalencias\n");
	*/

	// sustituye todas las regiones equivalentes
	for( iTabla=0; iTabla < tablaEquivalencias.size(); iTabla++){
		for (i=0; i<regiones.rows; i++){
			for(j=0; j<regiones.cols;j++){
				for (jTabla=1; jTabla < tablaEquivalencias[iTabla].size(); jTabla++){
					if( regiones.at<int32_t>(i,j) == tablaEquivalencias[iTabla][jTabla] ){
						//sustituye las regiones equivalentes con la etiqueta menor
						regiones.at<int32_t>(i,j) = tablaEquivalencias[iTabla][0];
					}
				}
			}
		}
	}

	return totalRegiones;
}
/*
ya que aqui se depuran las regiones etiquetadas, aqui tambien se obtiene el area, centroide y PDO
y se genera el reporte .txt
*/
// Mat imagenRGB es la imagen que se le paso a blobcoloring abierta en modo RGB
// totalColores = total de etiquetas retornada por pdiBlobColoring
//string id = nombre de la imagen sin la extencion
//int pdiColorearRegiones(Mat imagenRGB, Mat imgOriginalGris, Mat regiones, int totalColores, string id, char imgNombre[]){
void pdiColorearRegiones(Mat regiones, int totalColores, char imgNombre[]){
	//Mat imagenColoreada = imagenRGB.clone();
    
    Mat imagenColoreada(regiones.size(), CV_8UC3);//CV_8UC3 8 bits sin signo 3 canales
    
	//Mat imgCentroides = imagenRGB.clone();

	int histogramaColores[totalColores];

	int i, j;
    
    string stringNombreImagen = imgNombre;
    //int r,totalRegiones=totalColores;
	//int areaRegion = 0, sumaX = 0, sumaY = 0;
	//int promedioIntensidad = 0;
	//Point centro;
	std::vector<Vec3b> colores(totalColores);
	colores[0] = Vec3b( 0, 0, 0 );

// 	char charNombre[100]="";
// 	strcpy(charNombre, imgNombre);
// 	strcat(charNombre, " Centroide area y promedio de intensidad.txt" );
// 
// 	ofstream fs(charNombre);
	//obtiene un histograma de colores bajo la relacion de colores-#de pixeles para descartar regiones sin pixeles
	// y para obtener el area de cada region

	for( i = 0; i < totalColores; i++ ){
		histogramaColores[i] = 0;
	}

	for(i = 0; i<regiones.rows; i++){
		for(j = 0; j<regiones.cols; j++ ){
			histogramaColores[ regiones.at<int32_t>(i,j) ] = histogramaColores[ regiones.at<int32_t>(i,j) ] + 1;
		}
	}

// 	//quita las regiones con area < 15 en el histograma
// 	for( i = 0; i < totalColores; i++ ){
// 		if(histogramaColores[i] <= 15){
// 			histogramaColores[i] = 0;
// 			// y las resta del total de reiones
// 			totalRegiones = totalRegiones -1;
// 		}
// 	}
// 
// 	//quita las regiones con area < 15 en el tablero de regiones e imagen de centroides
// 	for( r = 0; r < totalColores; r++ ){
// 		for( i = 0; i < regiones.rows; i++ ){
// 			for( j = 0; j < regiones.cols; j++ ){
// 				if ( regiones.at<int32_t>(i,j) == r && histogramaColores[r] == 0 ){
// 					regiones.at<int32_t>(i,j) = 0;
// 
// 					//Vec3b &pixel = imagenColoreada.at<Vec3b>(i, j);
// 					//pixel = colores[0];
// 
// 					Vec3b &pixel2 = imgCentroides.at<Vec3b>(i, j);
// 					pixel2 = colores[0];
// 				}
// 			}
// 		}
// 	}
// 
// 	fs << "Total de regiones: ";
// 	fs << totalRegiones << endl;
    
	//para cada region obiene un color aleatorio
	for(i=1; i <= totalColores; i++){
		colores[i]=Vec3b( (rand()&255), (rand()&255), (rand()&255) );
	}



	//Colorea la imagen RGB con el color aleatorio por region
	for( i = 0; i < regiones.rows; i++ ){
		for( j = 0; j < regiones.cols; j++){
			int label = regiones.at<int32_t>(i, j);
			Vec3b &pixel = imagenColoreada.at<Vec3b>(i, j);
			pixel = colores[label];
		}
	}

// 	//Obtiene centroides y area de las regiones
// 	for( r=1; r <= totalColores; r++ ){
// 		for( i=0; i < regiones.rows; i++ ){
// 			for( j=0; j < regiones.cols; j++ ){
// 				if( r==regiones.at<int32_t>(i,j) ){
// 					sumaX = sumaX + j;
// 					sumaY = sumaY + i;
// 					areaRegion = areaRegion + 1;
// 
// 					//obtiene el promedio de intensidad
// 					promedioIntensidad = promedioIntensidad + imgOriginalGris.at<uchar>(i,j);
// 				}
// 			}
// 		}
// 		if(sumaX > 0 && sumaY > 0 && areaRegion > 0){
// 			// obtiene la coordenada del centroide de cada region
// 			sumaX = sumaX / areaRegion;
// 			sumaY = sumaY / areaRegion;
// 
// 			promedioIntensidad = promedioIntensidad / areaRegion;
// 
// 			centro.x = sumaX;
// 			centro.y = sumaY;
// 			circle(imgCentroides, centro, 3, CV_RGB(255, 69, 0), -1, 8, 0 );
// 
// 			imgCentroides.at<Vec3b>(sumaY, sumaX)[0] = 255; //B
// 			imgCentroides.at<Vec3b>(sumaY, sumaX)[1] = 255; //G
// 			imgCentroides.at<Vec3b>(sumaY, sumaX)[2] = 0; //R
// 
// 			fs << "\nEtiqueta: "<<r<<endl;
// 			fs << "Centroides ( i , j ): "<<endl;
// 			fs << "( "<<sumaY<<" , "<<sumaX<<" )"<<endl;
// 			fs << "Area: "<< areaRegion <<endl;
// 			fs << "Promedio de intensidad: "<< promedioIntensidad<<endl;
// 			//char *intChar;
// 			//sprintf(intChar, "%d",areaRegion);
// 			//putText(imgAreas, intChar, centro, FONT_HERSHEY_SCRIPT_COMPLEX, 0.25, CV_RGB(65,105,225), 2);
// 
// 
// 		}
// 		sumaX = 0;
// 		sumaY = 0;
// 		areaRegion = 0;
// 		promedioIntensidad = 0;
// 	}

	//imwrite(id + " Centroides en areas mayores a 15.tif", imgCentroides);
	//imwrite("Area por region.tif",imgAreas);
	//imshow("Regiones Coloreadas",imagenColoreada);
	imwrite(stringNombreImagen + "_RegionesColoreadas.tif",imagenColoreada);

	//fs.close();

	//return totalRegiones;
}
int buscarVector(vector<int> & vec, int n){
	int i = 0;
	while( i < vec.size() ){
		if(vec[i]==n){
			return 1;
		}
		i++;
	}
	return 0;
}
void insertarTablaDeEquivalencias(int a, int b, vector <vector<int> > &tablaEquivalencias){
	int iTabla, jTabla;
	int encontradoA = 0, encontradoB = 0;
	int indiceA, indiceB;
	/// buscar a y b en cada renglon de la tabla de equivalencia
	for( iTabla=0; iTabla < tablaEquivalencias.size(); iTabla++ ){
		for( jTabla=0; jTabla < tablaEquivalencias[iTabla].size(); jTabla++ ){
			///si encontado a marcarlo como encontrado y guardar la fila en la que fue encontrado
			if (buscarVector(tablaEquivalencias[iTabla], a)){
				encontradoA=1;
				indiceA=iTabla;
			}
			/// si encontrado b marcarlo como encontrado y guardar la fila en la que fue encontrado
			if(buscarVector(tablaEquivalencias[iTabla], b)){
				encontradoB=1;
				indiceB=iTabla;
			}
		}
	}

	/// si encontrado a y NO encontrado b: agregar b al mismo renglon de a en la tabla de equivalencia
	if(encontradoA==1 && encontradoB==0){
		tablaEquivalencias[indiceA].push_back(b);
	}
	/// si NO encontrado a y encontrado b: agregar a al mismo renglon de b en la tabla de equivalencia
	if(encontradoA==0 && encontradoB==1){
		tablaEquivalencias[indiceB].push_back(a);
	}
	/// si NO encontrado a y NO encontrado b: agregar a y b en un renglon nuevo
	if(encontradoA==0 && encontradoB==0){
		tablaEquivalencias.push_back(vector<int>());
		tablaEquivalencias[tablaEquivalencias.size()-1].push_back(a);
		tablaEquivalencias[tablaEquivalencias.size()-1].push_back(b);
	}
	//si se encontraron ambos insertar en A, mas adelante se unen las filas con etiquetas duplicadas
	if(encontradoA==1&&encontradoB==1){
		tablaEquivalencias[indiceA].push_back(b);
	}

	/// reiniciar la busqueda de a y b
	encontradoA=0;
	encontradoB=0;
}
//Mat regiones debe ser de 32 bits
// la manera de escribir valores > a 255 es con <int32_t>
// y asi debe estar en el codigo externo que use esta funcion
int pdiBlobColoring8Vecinos(Mat imagen, Mat regiones){
	int i, j, iTabla, jTabla;
	int iBuscar, jBuscar;
	int iMover, jMover;
	int totalRegiones = 1;

	vector <vector<int> > tablaEquivalencias;

	//llena el tablero con ceros
	for( i = 0; i< regiones.rows; i++){
		for( j = 0; j<regiones.cols; j++){
			regiones.at<int32_t>(i,j) = 0;
		}
	}

	//caso especial para la primera fila
	for(i=0,j=0; j<imagen.cols; j++){
		if(j==0){
			if (imagen.at<uchar>(i,j) == 255){
				regiones.at<int32_t>(i,j) = totalRegiones;
				totalRegiones = totalRegiones + 1;
			}
		}
		else{
			if( imagen.at<uchar>(i,j)==255 && imagen.at<uchar>(i,j-1)==255 ){
				regiones.at<int32_t>(i,j) = regiones.at<int32_t>(i,j-1);
			}

			if( imagen.at<uchar>(i,j)==255 && imagen.at<uchar>(i,j-1)==0 ){
				regiones.at<int32_t>(i,j) = totalRegiones;
				totalRegiones = totalRegiones + 1;
			}

		}
	}

	//continua escaneando la imagen ignorando la primera fila

	for( i = 1; i < imagen.rows; i++){
		for( j = 0; j < imagen.cols; j++){
			//caso para la columna 0 ya que no hay elemento a la izquierda
			if(j == 0){
					//si existe la esquina superior diagonal
					if( (i - 1) >=0 && (j+1)<imagen.cols){
						if(imagen.at<uchar>(i,j) == 255 && imagen.at<uchar>(i-1,j)==0 && imagen.at<uchar>(i-1,j+1)==0){
							regiones.at<int32_t>(i,j) = totalRegiones;
							totalRegiones = totalRegiones + 1;
						}
						if( imagen.at<uchar>(i,j)==255 && imagen.at<uchar>(i-1,j)==255 ){
							regiones.at<int32_t>(i,j) = regiones.at<int32_t>(i-1,j);
						}
						if( imagen.at<uchar>(i,j)==255 && imagen.at<uchar>(i-1,j+1)==255 ){
							regiones.at<int32_t>(i,j) = regiones.at<int32_t>(i-1,j+1);
						}
					}
			}
			//caso para la ultima columna ya que no hay un elemento superior derecha en diagonal
			else if( j == (imagen.cols-1) ){

				if(imagen.at<uchar>(i,j)==255&&imagen.at<uchar>(i,j-1)==0 && imagen.at<uchar>(i-1,j)==0 && imagen.at<uchar>(i-1,j-1)==0){
					regiones.at<int32_t>(i,j) = totalRegiones;
					totalRegiones = totalRegiones + 1;
				}
				if(imagen.at<uchar>(i,j)==255&&imagen.at<uchar>(i,j-1)==255 && imagen.at<uchar>(i-1,j)==0 && imagen.at<uchar>(i-1,j-1)==0){
					regiones.at<int32_t>(i,j) = regiones.at<int32_t> (i,j-1);
				}
				if(imagen.at<uchar>(i,j)==255&&imagen.at<uchar>(i,j-1)==0 && imagen.at<uchar>(i-1,j)==255 && imagen.at<uchar>(i-1,j-1)==0){
					regiones.at<int32_t>(i,j) = regiones.at<int32_t>(i-1,j);
				}
				if(imagen.at<uchar>(i,j)==255&&imagen.at<uchar>(i,j-1)==0 && imagen.at<uchar>(i-1,j)==0 && imagen.at<uchar>(i-1,j-1)==255){
					regiones.at<int32_t>(i,j) = regiones.at<int32_t>(i-1,j-1);
				}
				if(imagen.at<uchar>(i,j)==255&&imagen.at<uchar>(i,j-1)==0 && imagen.at<uchar>(i-1,j)==255 && imagen.at<uchar>(i-1,j-1)==255){
					regiones.at<int32_t>(i,j) = regiones.at<int32_t>(i-1,j);
				}
				if(imagen.at<uchar>(i,j)==255&&imagen.at<uchar>(i,j-1)==255 && imagen.at<uchar>(i-1,j)==0 && imagen.at<uchar>(i-1,j-1)==255){
					regiones.at<int32_t>(i,j) = regiones.at<int32_t>(i,j-1);
				}
				if(imagen.at<uchar>(i,j)==255&&imagen.at<uchar>(i,j-1)==255 && imagen.at<uchar>(i-1,j)==255 && imagen.at<uchar>(i-1,j-1)==255){
					regiones.at<int32_t>(i,j) = regiones.at<int32_t>(i,j-1);
				}
				if(imagen.at<uchar>(i,j)==255&&imagen.at<uchar>(i,j-1)==255 && imagen.at<uchar>(i-1,j)==255 && imagen.at<uchar>(i-1,j-1)==0){
					/*La parte de regiones equivalentes*/
					if(regiones.at<int32_t>(i,j-1) != regiones.at<int32_t>(i-1,j)){

						insertarTablaDeEquivalencias(regiones.at<int32_t>(i,j-1),regiones.at<int32_t>(i-1,j),tablaEquivalencias);

						if(regiones.at<int32_t>(i,j-1)<regiones.at<int32_t>(i-1,j)){
							regiones.at<int32_t>(i-1,j) = regiones.at<int32_t>(i,j-1);

						}
						else{
							regiones.at<int32_t>(i-1,j) = regiones.at<int32_t>(i,j-1);
						}


					}
					regiones.at<int32_t>(i,j) = regiones.at<int32_t>(i,j-1);
				}

			}

			else{

				if(imagen.at<uchar>(i,j)==255&&imagen.at<uchar>(i,j-1)==0 && imagen.at<uchar>(i-1,j)==0 && imagen.at<uchar>(i-1,j-1)==0&&imagen.at<uchar>(i-1,j+1)==0){
					regiones.at<int32_t>(i,j) = totalRegiones;
					totalRegiones = totalRegiones + 1;
				}

				if(imagen.at<uchar>(i,j)==255&&imagen.at<uchar>(i,j-1)==255 && imagen.at<uchar>(i-1,j)==0 && imagen.at<uchar>(i-1,j-1)==0&&imagen.at<uchar>(i-1,j+1)==0){
					regiones.at<int32_t>(i,j) = regiones.at<int32_t>(i,j-1);
				}
				if(imagen.at<uchar>(i,j)==255&&imagen.at<uchar>(i,j-1)==0 && imagen.at<uchar>(i-1,j)==255 && imagen.at<uchar>(i-1,j-1)==0&&imagen.at<uchar>(i-1,j+1)==0){
					regiones.at<int32_t>(i,j) = regiones.at<int32_t>(i-1,j);
				}
				if(imagen.at<uchar>(i,j)==255&&imagen.at<uchar>(i,j-1)==0 && imagen.at<uchar>(i-1,j)==0 && imagen.at<uchar>(i-1,j-1)==255&&imagen.at<uchar>(i-1,j+1)==0){
					regiones.at<int32_t>(i,j) = regiones.at<int32_t>(i-1,j-1);
				}
				if(imagen.at<uchar>(i,j)==255&&imagen.at<uchar>(i,j-1)==0 && imagen.at<uchar>(i-1,j)==0 && imagen.at<uchar>(i-1,j-1)==0&&imagen.at<uchar>(i-1,j+1)==255){
					regiones.at<int32_t>(i,j) = regiones.at<int32_t>(i-1,j+1);
				}
				if(imagen.at<uchar>(i,j)==255&&imagen.at<uchar>(i,j-1)==255 && imagen.at<uchar>(i-1,j)==0 && imagen.at<uchar>(i-1,j-1)==255&&imagen.at<uchar>(i-1,j+1)==0){
					regiones.at<int32_t>(i,j) = regiones.at<int32_t>(i,j-1);
				}
				if(imagen.at<uchar>(i,j)==255&&imagen.at<uchar>(i,j-1)==0 && imagen.at<uchar>(i-1,j)==255 && imagen.at<uchar>(i-1,j-1)==255&&imagen.at<uchar>(i-1,j+1)==0){
					regiones.at<int32_t>(i,j) = regiones.at<int32_t>(i-1,j);
				}
				if(imagen.at<uchar>(i,j)==255&&imagen.at<uchar>(i,j-1)==255 && imagen.at<uchar>(i-1,j)==255 && imagen.at<uchar>(i-1,j-1)==0&&imagen.at<uchar>(i-1,j+1)==0){
					regiones.at<int32_t>(i,j) = regiones.at<int32_t>(i,j-1);
				}
				if(imagen.at<uchar>(i,j)==255&&imagen.at<uchar>(i,j-1)==0 && imagen.at<uchar>(i-1,j)==255 && imagen.at<uchar>(i-1,j-1)==0&&imagen.at<uchar>(i-1,j+1)==255){
					regiones.at<int32_t>(i,j) = regiones.at<int32_t>(i-1,j);
				}
				if(imagen.at<uchar>(i,j)==255&&imagen.at<uchar>(i,j-1)==255 && imagen.at<uchar>(i-1,j)==255 && imagen.at<uchar>(i-1,j-1)==0&&imagen.at<uchar>(i-1,j+1)==255){
					regiones.at<int32_t>(i,j) = regiones.at<int32_t>(i,j-1);
				}
				if(imagen.at<uchar>(i,j)==255&&imagen.at<uchar>(i,j-1)==255 && imagen.at<uchar>(i-1,j)==255 && imagen.at<uchar>(i-1,j-1)==255&&imagen.at<uchar>(i-1,j+1)==0){
					regiones.at<int32_t>(i,j) = regiones.at<int32_t>(i,j-1);
				}
				if(imagen.at<uchar>(i,j)==255&&imagen.at<uchar>(i,j-1)==0 && imagen.at<uchar>(i-1,j)==255 && imagen.at<uchar>(i-1,j-1)==255&&imagen.at<uchar>(i-1,j+1)==255){
					regiones.at<int32_t>(i,j) = regiones.at<int32_t>(i-1,j);
				}
				if(imagen.at<uchar>(i,j)==255&&imagen.at<uchar>(i,j-1)==255 && imagen.at<uchar>(i-1,j)==255 && imagen.at<uchar>(i-1,j-1)==255&&imagen.at<uchar>(i-1,j+1)==255){
					/*
					if(regiones.at<int32_t>(i,j-1)!=regiones.at<int32_t>(i-1,j+1)){
						insertarTablaDeEquivalencias(regiones.at<int32_t>(i,j-1),regiones.at<int32_t>(i-1,j+1),tablaEquivalencias);
					}*/
					regiones.at<int32_t>(i,j) = regiones.at<int32_t>(i,j-1);
				}
				if(imagen.at<uchar>(i,j)==255&&imagen.at<uchar>(i,j-1)==255 && imagen.at<uchar>(i-1,j)==0 && imagen.at<uchar>(i-1,j-1)==0&&imagen.at<uchar>(i-1,j+1)==255){

					if(regiones.at<int32_t>(i,j-1)!=regiones.at<int32_t>(i-1,j+1)){

						insertarTablaDeEquivalencias(regiones.at<int32_t>(i,j-1),regiones.at<int32_t>(i-1,j+1),tablaEquivalencias);

						if(regiones.at<int32_t>(i,j-1)<regiones.at<int32_t>(i-1,j+1)){
								regiones.at<int32_t>(i-1,j+1) = regiones.at<int32_t>(i,j-1);
						}
						else{
							regiones.at<int32_t>(i,j-1) = regiones.at<int32_t>(i-1,j+1);
						}

					}
					regiones.at<int32_t>(i,j) = regiones.at<int32_t>(i,j-1);
					//Equivalencias
				}
				if(imagen.at<uchar>(i,j)==255&&imagen.at<uchar>(i,j-1)==0 && imagen.at<uchar>(i-1,j)==0 && imagen.at<uchar>(i-1,j-1)==255&&imagen.at<uchar>(i-1,j+1)==255){

					if(regiones.at<int32_t>(i-1,j-1) != regiones.at<int32_t>(i-1,j+1)){

						insertarTablaDeEquivalencias(regiones.at<int32_t>(i-1,j-1),regiones.at<int32_t>(i-1,j+1),tablaEquivalencias);

						if(regiones.at<int32_t>(i-1,j-1) < regiones.at<int32_t>(i-1,j+1)){
							regiones.at<int32_t>(i-1,j+1) = regiones.at<int32_t>(i-1,j-1);
						}
						else{
							regiones.at<int32_t>(i-1,j-1) = regiones.at<int32_t>(i-1,j+1);
						}

					}
					regiones.at<int32_t>(i,j) = regiones.at<int32_t>(i-1,j+1);
					//Equivalencias
				}
				if(imagen.at<uchar>(i,j)==255&&imagen.at<uchar>(i,j-1)==255 && imagen.at<uchar>(i-1,j)==0 && imagen.at<uchar>(i-1,j-1)==255&&imagen.at<uchar>(i-1,j+1)==255){
					if(regiones.at<int32_t>(i,j-1) != regiones.at<int32_t>(i-1,j+1)){

						insertarTablaDeEquivalencias(regiones.at<int32_t>(i,j-1), regiones.at<int32_t>(i-1,j+1),tablaEquivalencias);

						if(regiones.at<int32_t>(i,j-1) < regiones.at<int32_t>(i-1,j+1)){
							regiones.at<int32_t>(i-1,j+1) = regiones.at<int32_t>(i,j-1);
						}
						else{
							regiones.at<int32_t>(i,j-1) = regiones.at<int32_t>(i-1,j+1);
						}

					}
					regiones.at<int32_t>(i,j) = regiones.at<int32_t>(i,j-1);
					//Equivalencias
				}

			}

		}
	}


	///Mueve los elementos duplicados a una sola fila
	for ( iTabla = 0; iTabla < tablaEquivalencias.size(); iTabla++ ){
    	for( jTabla = 0; jTabla < tablaEquivalencias[iTabla].size(); jTabla++ ){

    		// recorre el buscardor las filas 0 . . . iTabla -1
    		for( iBuscar = 0; iBuscar < iTabla; iBuscar++ ){

    			// si lo encuentra
				if ( buscarVector(tablaEquivalencias[iBuscar], tablaEquivalencias[iTabla][jTabla]) ){
					//printf("\nFue encontrado: %d En la fila %d\n", tablaEquivalencias[iTabla][jTabla], iBuscar);

					//copiar la fila donde fue encontrado el duplicado
					for( jMover = 0; jMover < tablaEquivalencias[iBuscar].size(); jMover++ ){
						tablaEquivalencias[iTabla].push_back(tablaEquivalencias[iBuscar][jMover]);
					}

					//destruir la fila donde fue encontrado el duplicado
					tablaEquivalencias[iBuscar].clear();
				}

    		}




    		// recorre el buscardor las filas iTabla + 1 . . . v1.size();
    		for( iBuscar = iTabla +1; iBuscar < tablaEquivalencias.size(); iBuscar++ ){
    			// si lo encuentra
				if ( buscarVector(tablaEquivalencias[iBuscar], tablaEquivalencias[iTabla][jTabla]) ){
					//printf("\nFue encontrado: %d En la fila %d\n", tablaEquivalencias[iTabla][jTabla], iBuscar);

					//copiar la fila donde fue encontrado el duplicado
					for( jMover = 0; jMover < tablaEquivalencias[iBuscar].size(); jMover++ ){
						tablaEquivalencias[iTabla].push_back(tablaEquivalencias[iBuscar][jMover]);
					}

					//destruir la fila donde fue encontrado el duplicado
					tablaEquivalencias[iBuscar].clear();
				}
    		}


    	}
    }



	/// ordenar cada renglon de menor a mayor en la tabla de equivalencias
	for( i=0; i < tablaEquivalencias.size(); i++ ){
		sort( tablaEquivalencias[i].begin(), tablaEquivalencias[i].end() );
	}
	/*
	printf("\nContenido de la tabla de equivalencias\n");
	for( iTabla=0; iTabla < tablaEquivalencias.size(); iTabla++){
		for (jTabla=0; jTabla < tablaEquivalencias[iTabla].size(); jTabla++){
			cout <<tablaEquivalencias[iTabla][jTabla]<<"  ";
		}
		printf("\n\n");
	}
	printf("\nFIN Contenido de la tabla de equivalencias\n");
	*/

	// sustituye todas las regiones equivalentes
	for( iTabla=0; iTabla < tablaEquivalencias.size(); iTabla++){
		for (i=0; i<regiones.rows; i++){
			for(j=0; j<regiones.cols;j++){
				for (jTabla=1; jTabla < tablaEquivalencias[iTabla].size(); jTabla++){
					if( regiones.at<int32_t>(i,j) == tablaEquivalencias[iTabla][jTabla] ){
						//sustituye las regiones equivalentes con la etiqueta menor
						regiones.at<int32_t>(i,j) = tablaEquivalencias[iTabla][0];
					}
				}
			}
		}
	}

	return totalRegiones;
}
