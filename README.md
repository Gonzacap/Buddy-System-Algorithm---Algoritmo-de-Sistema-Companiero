# Buddy System Algoritm - Algoritmo de Sistema Compañero


Esta es una implementacion del algoritmo de [Sistema Compañero](https://en.wikipedia.org/wiki/Buddy_system), la cual es una simulacion de asignacion de procesos en un cierto espacio de memoria.

### Funcionamiento del algoritmo: 
Cuando se quiere guardar un proceso, se busca el _menor_ valor de 2^n mayor o igual al tamaño del proceso proceso

![ejemplo](https://www.cs.nott.ac.uk/~pszgxk/courses/g53ops/images/buddysystem.jpg)
![ejemplo arbol](https://cnx.org/resources/ad447da04e30d84c7dca683aef385f2d2b604814/graphics3.png)

### Implementacion:
Para la implementacion se creo una exructura para simular los procesos la cual guarda el tamaño y el mid del mismo.
Luego un arreglo de T-1 (siendo T el tamaño total de la memoria) donde cada espacio representa un nodo del arbol binario completo (excepto del ultimo nivel) para guardar los procesos.
El tamaño minimo de un proceso es de 2, ya que el valor 0 se usa para representar un nodo _NULL_ (espacio disponible en memoria) y el valor 1 para representar un nodo padre vacio (un nodo que no tiene un proceso pero tiene dos hijos que podrían o no tenerlo). 


No entendes algo? Necesitas ayuda??? mandame un mail: [gonzalo.october@gmail.com](mailto:gonzalo.october@gmail.com)
