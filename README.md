# velocistaEdu
Libreria para placa de Kit de Robot Velocista Educacion para Arduino.

El kit de velocistas incluye una placa de control para 2 motores DC que pueden integrar un pin de encoder.
Tambien se incluye una placa con 4 sensores infrarrojos para detectar una linea de 2cm en el suelo.
La libreria proporciona las funciones para inicializar los pines usados y poder leer/actuar sobre
los diferentes sensores/actuadores incluidos.

Para usar la libreria hay que poner el contenido del repositorio en la carpeta "library" del IDE Arduino
Dentro de la carpeta "examples" existen proyectos de Arduino que usan algunas de las funciones de la
libreria y se pueden usar como ejemplo.

Esta libreria tiene como dependencia la libreria EnableInterrupt, que tambien hay que incluir a la instalacion
de Arduino. Esta libreria se puede encontrar en el siguiente enlace:
https://github.com/GreyGnome/EnableInterrupt

Dentro de la carpeta "doc" se puede encontrar la documentacion de la libreria en formato doxygen.
Para generarla hay que tener instalado doxygen y generar la documentacion usando el archivo de configuracion
Doxyfile que se encuentra en dicha carpeta.

Una vez generada, ara verla hay que abrir el fichero "doc/html/index.html" en un navegador.

Se puede consultar la documentacion de la ultima version de la libreria online en la siguiente direccion
http://thar.github.io/velocistaEdu/

Para mas informacion sobre la libreria acude a la pagina de la liga de robots.
http://lnrc.es/estudiantes

