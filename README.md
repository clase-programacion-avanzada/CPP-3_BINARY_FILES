# Proyecto: Manejo de Archivos Binarios en C++

## Descripción

Este proyecto demuestra el uso de archivos binarios en C++ para manejar información de cines. El objetivo principal es mostrar cómo leer y escribir datos estructurados utilizando archivos binarios, comparándolo con el manejo de archivos de texto.

## Estructura del Proyecto

### Archivos Principales

- **`Cinema.hh`**: Contiene las estructuras de datos para modelar la información del cine
- **`cinema.txt`**: Archivo de texto con datos de ejemplo de un cine
- **`0_how_binary_files_work.cpp`**: Ejemplo básico de funcionamiento de archivos binarios

### Estructuras de Datos

El proyecto utiliza tres estructuras principales definidas en `Cinema.hh`:

```cpp
struct Movie {
    char name[40];     // Nombre de la película
    char hour[6];      // Hora de la función (formato HH:MM)
};

struct Room {
    char id[10];           // Identificador de la sala
    int numberOfMovies;    // Número de películas en la sala
    Movie movies[5];       // Array de películas
};

struct Cinema {
    char id[10];           // Identificador del cine
    int numberOfRooms;     // Número de salas
    Room rooms[5];         // Array de salas
};
```

### Formato de Datos

El archivo `cinema.txt` sigue esta estructura:

```plaintext
<Cinema_id>
<Número_de_salas>
<Room_id>
<Número_de_películas>
<Nombre_película> | <Hora>
...
```

**Ejemplo:**

```plaintext
Cinema_1
3
Sala_1
2
Interstellar | 3:00 PM
Inception | 5:00 PM
```

## Características del Proyecto

### Ventajas de Archivos Binarios

1. **Eficiencia de espacio**: Los archivos binarios ocupan menos espacio que los archivos de texto
2. **Velocidad de acceso**: Lectura y escritura más rápida
3. **Preservación de tipos**: Los datos mantienen su tipo original
4. **Acceso directo**: Posibilidad de acceder a registros específicos sin leer todo el archivo

### Limitaciones y Consideraciones

- **Portabilidad**: Los archivos binarios pueden no ser compatibles entre diferentes arquitecturas
- **Legibilidad**: No son legibles por humanos sin un programa específico
- **Debugging**: Más difícil de depurar comparado con archivos de texto

## Compilación y Ejecución

### Compilar el proyecto

```bash
g++ -g 0_how_binary_files_work.cpp -o 0_how_binary_files_work
```

### Ejecutar

```bash
./0_how_binary_files_work
```

## Referencias y Recursos Adicionales

### 📖 **Documentación Oficial**

- [Binary File Handling in C++: A Beginner’s Guide](https://dev.to/alen_pythonista_bb/binary-file-handling-in-c-a-beginners-guide-148od) [Artículo]