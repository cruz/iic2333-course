# Sitio web de IIC2333 Sistemas Operativos y Redes

Este repositorio contiene el sitio web del curso. Hay dos alternativas para obtener una versión local del sitio.

### Clonar y crear localmente

`git clone git@github.com:cruz/iic2333-course.git`

Para configurar el ambiente (primera vez)

`bundle install`

En el directorio base ejecutar:

`rake build`

El sitio queda en el directorio `build`. Puedes abrir el archivo `build/index.html` en un navegador. 

Si necesitas reconstruir el sitio, ejecutar `rake build`.

### Bajar versión estática

En el repositorio hay un archivo comprimido con una versión estática del sitio (~90MB). Descomprimirlo con:

`tar zxvf build-YYYYMMDD.tar.gz`

donde `YYYYMMDD` indica la fecha de construcción. Una vez descomprimido, apuntar el navegador a `build/index.html`


