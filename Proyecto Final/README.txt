Proyecto Eigenfaces. 

Recibe los argumentos que se describen a continuación y clasifica las imágenes señaladas con 
los mismos con el método APC acompañado por método de Potencia y Eigenfaces. Como resultado,
imprime en consola la clasificación de las imágenes, la matriz de confusión y la precisión. 
Donde las clases son las personas del conjunto de entrenamiento más una clase que corresponde 
a las imágenes no reconocidas. Es decir, a aquellas que superan cierto umbral asociado al método
Eigenfaces. Este último también se modula con los argumentos.


DESCRIPCIÓN:

Este programa recibe 4 enteros para entrenamiento:

    argv[1] = m     cantidad de personas

    argv[2] = n	    cantidad de fotos por persona

    argv[3] = k	    primera persona

    argv[4] = l	    primera foto (utliza personas y fotos consecutivas)

Y 4 enteros para validación:

    argv[5] = m     cantidad de personas

    argv[6] = n	    cantidad de fotos por persona

    argv[7] = k	    primera persona

    argv[8] = l	    primera foto (utliza personas y fotos consecutivas)

Finalmente, recibe:

    argv[9] = c     el número de componentes principales que se calcularán, si es cero se calcula el máximo

    argv[10] = f    y f un factor que multiplica al umbral para reconocimiento/no reconocimiento

Ejemplo: 10 5 1 1 20 5 1 2 0 0.3

10 personas de entrenamiento, 5 fotos por persona.
De la persona 1 a la 5 y de la foto 1 a la 5.

20 personas de entrenamiento, 5 fotos por persona.
De la persona 1 a la 5 y de la foto 2 a la 5.

se calcula el número máximo de componentes y el umbral se escala por 0.3

COMPILACIÓN:

Se agrega el Makefile.

Necesita del archivo Materiales que se adjunta junto con el código. 

Para la correcta compilación, en el archivo Data.pcc en el método CreateFilenames de la clase Data
se debe cambiar el string "C:\\Users\\luna_\\Documents\\Cursos\\Numeric Methods\\Tareas\\Proyecto\\Material\\s"
por la dirección de la carpeta Material.










