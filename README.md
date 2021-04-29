# Consideraraciones Importates para el Corrector

- Todos los tests funcionan.
- Se implementó un pequeño fragmento de código para ampliar el stack a 24MB si esque su tamaño es inferior.
- Para ejecutar con Valgrind se debe especificar un stack mayor, mediante el tag `--main-stacksize=67108864` (para 64MB) por ejemplo.
- Hice pruebas en WSL2 y Ubuntu 18.04 Nativo y en WSL2 a veces el sistema operativo hacía `kill` de mi proceso en los tests de la imagen `campus.png` con el filtro delta, presumiblemente por uso excesivo de memoria. En Ubuntu 18.04 nativo no tuve problemas.
- Valgrind no corre con los tests hard (también ocurre un `kill` por parte del OS), sin embargo hasta los test medium sí en donde no arroja ningún leak ni error, por lo que es escalable y teorizable que no existen problemas de memoria en los tests hard.
- Los tiempos de ejecución, en el peor de los casos de la imagen `campus.png` en WSL son 11 segundos, sin embargo en Ubuntu 18.04 nativo el tiempo no supera los 5 segundos.
- Para todas estas consideraciones, el programa fue ejecutado en un computador Intel Core i5 7200U con 16GB de memoria RAM, tanto en WSL2 como en Ubuntu 18.04 Nativo.

## Requerimientos
Debes tener instalada la librería `libpng` para poder leer las imágenes cómo matrices.  
Esta la puedes instalar con el comando:
```sudo apt install libpng-dev```

## Compilar y ejecutar
Compilar:
```make```

Ejecutar:
```./filters <input.png> <output.png> <tipo_de_filtro> <A G | D>```

## Ejemplos:
Filtrar nodos con area mayor a 100 pixeles y grisáceo mayor a 50:
```./filters tests/img1 out.png area 100 50```

Filtrar nodos con delta menor a 0.25:
```./filters tests/img1 out.png delta 0.25```
