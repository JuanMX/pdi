# pdi Imagen Negativa

![demo_negativa](./assets/demo_negativa.png)

Código para obtener el negativo de una imagen mediante la siguiente estrategia:

```c++
imgNegativa.at<Vec3b>(i, j)[0] = 255 - img.at<Vec3b>(i, j)[0]; //azul (B)
imgNegativa.at<Vec3b>(i, j)[1] = 255 - img.at<Vec3b>(i, j)[1]; //verde (G)
imgNegativa.at<Vec3b>(i, j)[2] = 255 - img.at<Vec3b>(i, j)[2]; //rojo (R)
```

Se compila y ejecuta con las siguientes instrucciones:

```
g++ mainImagenNegativa.cpp pdiImagenNegativa.cpp pdiImagenNegativa.h -o mainImagenNegativa `pkg-config --cflags --libs opencv`

./mainImagenNegativa nombreImagen.extencion nombreImagen
```
