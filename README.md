# PDI - Procesamiento digital de imágenes

Son pequeños programas relacionados a [*procesamiento digital de imágenes*](https://en.wikipedia.org/wiki/Digital_image_processing) (PDI).

No es código que quiera reemplazar a software sofisticado y existente como [OpenCV](https://opencv.org/) o [PIL](http://www.pythonware.com/products/pil/), en cambio tienen propósitos académicos, una manera de mostrar como se escribe en código algoritmos pertenecientes a tareas de PDI.

Las funciones codificadas empiezan con `pdi` por ejemplo `pdiBlobColoring4Vecinos`.

En este código se usó [OpenCV](https://opencv.org/) y [C++](https://gcc.gnu.org/).

## Descripción breve de los algoritmos codificados

`pdiBlobColoring`

También conocido como [*conected component labeling*](https://en.wikipedia.org/wiki/Connected-component_labeling), consiste en detectar regiones conectadas en imágenes binarias.

`pdiHistograma`

Crea un *array* que representa un [histograma de imagen](https://en.wikipedia.org/wiki/Image_histogram).

`pdiMorfologicas`

Contienen las [operaiones morfológicas:]( https://en.wikipedia.org/wiki/Mathematical_morphology ) erosión (`pdiErode`) y dilatación (`pdiDilate`) para imágenes binarias, además de usos para ambas operaciones como [*Open*](https://en.wikipedia.org/wiki/Opening_(morphology)), [*Close*](https://en.wikipedia.org/wiki/Closing_(morphology)) y obtener el contorno.
