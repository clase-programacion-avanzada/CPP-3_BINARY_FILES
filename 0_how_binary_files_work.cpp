/*This is a cpp file that explains how binary files works*/
#include <iostream>
#include <string>
#include <cstddef> // This is for the byte type
#include <cstdint>
#include <fstream>

#include "libs/Cinema.hh"

using namespace std;

void trim(char str[]);
Cinema readCinemaFromTextFile(char fileName[]);
void printCinema(Cinema cinema);

int main() {

    /* En un archivo binario, los datos se almacenan en formato binario, 
    lo que significa que se representan como una secuencia de bytes. 
    
    Esto contrasta con los archivos de texto, 
    donde los datos se almacenan como caracteres legibles. 
    En este ejemplo, primero leeremos un archivo de texto con información sobre 
    un cine y luego lo convertiremos a un archivo binario.
    */

    // Leer el archivo de texto
    char fileName[] = "cinema.txt";

    //El arrchivo de texto está en el siguiente formato:
    // # ID del cine
    // # Cantidad de salas
    // # ID de la sala
    // # Cantidad de películas
    // # Nombre de la película | Hora de la película (HH:MM)
    cout << "Leyendo el archivo de texto: " << fileName << endl;
    Cinema cinema = readCinemaFromTextFile(fileName);

    if (cinema.numberOfRooms == 0 && cinema.id[0] == '\0') {
        cout << "No se pudo leer el cine desde el archivo de texto." << endl;
        return 1; // Salir si no se pudo leer el cine
    }
    printCinema(cinema);
    // Escribir el archivo binario
    char binaryFileName[] = "cinema.bin";
    cout << "Escribiendo el archivo binario: " << binaryFileName << endl;

    // En los archivos binarios, tenemos que especificar que queremos abrir el archivo en modo binario
    fstream writeBinaryFile(binaryFileName, ios::out | ios::binary);

    if (writeBinaryFile.fail()) {
        cout << "Error al abrir el archivo binario: " << binaryFileName << endl;
        return 1;
    }

    // En este caso, el archivo binario tendrá el siguiente formato:
    // - ID del cine (10 bytes)
    // - Cantidad de salas (1 byte)
    // - Para cada sala:
    //   - ID de la sala (10 bytes)
    //   - Cantidad de películas (1 byte)
    //   - Para cada película:
    //     - Nombre de la película (40 bytes)
    //     - Hora de la película (HH:MM) (6 bytes)

    // Para escribir los datos en el archivo binario, 
    // usamos el operador `write`, indicando cuántos bytes queremos escribir.
    writeBinaryFile.write(cinema.id, 10);
    writeBinaryFile.write(reinterpret_cast<char*>(&cinema.numberOfRooms), sizeof(cinema.numberOfRooms));

    for (int i = 0; i < cinema.numberOfRooms; i++) {
        writeBinaryFile.write(cinema.rooms[i].id, 10);
        writeBinaryFile.write(reinterpret_cast<char*>(&cinema.rooms[i].numberOfMovies), sizeof(cinema.rooms[i].numberOfMovies));

        for (int j = 0; j < cinema.rooms[i].numberOfMovies; j++) {
            writeBinaryFile.write(cinema.rooms[i].movies[j].name, 40);
            writeBinaryFile.write(cinema.rooms[i].movies[j].hour, 6);
        }
    }

    writeBinaryFile.close();

    cout << "Leyendo el archivo binario: " << binaryFileName << endl;
    // Una vez que hemos escrito los datos en el archivo binario,
    // podemos leerlos de nuevo para verificar que se han guardado correctamente.
    fstream readBinaryFile(binaryFileName, ios::in | ios::binary);
    
    if (readBinaryFile.fail()) {
        cout << "Error al abrir el archivo binario para lectura: " << binaryFileName << endl;
        return 1;
    }
    

    Cinema cinemaFromBinary;
    
    //Leer el id del cine
    readBinaryFile.read(cinemaFromBinary.id, 10);
    readBinaryFile.read(reinterpret_cast<char*>(&cinemaFromBinary.numberOfRooms), sizeof(cinemaFromBinary.numberOfRooms));

    for (int i = 0; i < static_cast<int>(cinemaFromBinary.numberOfRooms); i++) {
        readBinaryFile.read(cinemaFromBinary.rooms[i].id, 10);
        readBinaryFile.read(reinterpret_cast<char*>(&cinemaFromBinary.rooms[i].numberOfMovies), sizeof(cinemaFromBinary.rooms[i].numberOfMovies));

        for (int j = 0; j < static_cast<int>(cinemaFromBinary.rooms[i].numberOfMovies); j++) {
            readBinaryFile.read(cinemaFromBinary.rooms[i].movies[j].name, 40);
            readBinaryFile.read(cinemaFromBinary.rooms[i].movies[j].hour, 6);
        }
    }

    readBinaryFile.close();

    cout << "Cine leído desde el archivo binario:" << endl;
    printCinema(cinemaFromBinary);
    cout << endl;

    // Hay que tener cuidado al leer los datos del archivo binario,
    // ya que debemos leerlos en el mismo orden en que los escribimos,
    // con los tamaños correctos.
    fstream readBinaryFile2(binaryFileName, ios::in | ios::binary);

    if (readBinaryFile2.fail()) {
        cout << "Error al abrir el archivo binario para lectura: " << binaryFileName << endl;
        return 1;
    }

    char id[10];

    readBinaryFile2.read(id, 10);
    cout << "ID leído correctamente: " << id << endl;

    //Si cometemos el error de pensar que estamos leyendo un entero porque es un número
    int wrongReading = 0;
    readBinaryFile2.read(reinterpret_cast<char*>(&wrongReading), sizeof(int));

    cout << "Valor leído incorrectamente: " << wrongReading << endl;

    readBinaryFile2.close();

    return 0;
}

Cinema readCinemaFromTextFile(char fileName[]) {
    fstream textFile(fileName);
    Cinema cinema;

    if (textFile.fail()) {
        cout << "Error al abrir el archivo de texto: " << fileName << endl;
        return cinema; // Cinema va a estar vacío porque el constructor inicializa todo en cero
    }

   char buffer[256]; // Un buffer para leer líneas completas

    // Leer ID del cine
    textFile.getline(cinema.id, 10); // el primer dato es el id y no contiene espacios (Cinema_1)

    // Leer cantidad de salas
    textFile.getline(buffer, 256);
    cinema.numberOfRooms = atoi(buffer); // atoi convierte "3"

    for (int i = 0; i < cinema.numberOfRooms; i++) {
        textFile.getline(cinema.rooms[i].id, 10); // el primer dato es el id y no contiene espacios (Sala_1)
        textFile.getline(buffer, 256);
        cinema.rooms[i].numberOfMovies = atoi(buffer); // atoi convierte "2" a 2

        for (int j = 0; j < cinema.rooms[i].numberOfMovies; j++) {

            char movieName[40] = {};
            char movieHour[7] = {};

            textFile.getline(movieName, 40, '|'); // Hay que separar el nombre de la película del horario 
                                                    // usando el delimitador '|' (Interestellar)
            textFile.getline(movieHour, 7); // Hay que separar la hora de la película del nombre 
                                              // en este caso, usar el delimitador no va a cambiar el 
                                              // comportamiento de getline, ya que termina en un salto de línea (13:00)
            trim(movieName);// Eliminar espacios en blanco
            trim(movieHour);// Eliminar espacios en blanco

            strncpy(cinema.rooms[i].movies[j].name, movieName, 40); // Copiar el nombre de la película en la estructura del cine
            strncpy(cinema.rooms[i].movies[j].hour, movieHour, 6); // Copiar la hora de la película en la estructura del cine

            // Asegurarse de que el último carácter sea nulo
            cinema.rooms[i].movies[j].name[39] = '\0';
            cinema.rooms[i].movies[j].hour[5] = '\0';
        }
        
    }

    textFile.close();

    return cinema;
}

void printCinema(Cinema cinema) {
    cout << "Cine: " << cinema.id << endl;
    cout << "Número de salas: " << static_cast<int>(cinema.numberOfRooms) << endl;

    for (int i = 0; i < static_cast<int>(cinema.numberOfRooms); i++) {
        cout << "  Sala " << cinema.rooms[i].id << " tiene " 
             << static_cast<int>(cinema.rooms[i].numberOfMovies) << " películas." << endl;

        for (int j = 0; j < static_cast<int>(cinema.rooms[i].numberOfMovies); j++) {
            cout << "    Película: " << cinema.rooms[i].movies[j].name << " a las " 
                 << cinema.rooms[i].movies[j].hour << endl;
        }
    }
}

// Eliminar espacios al inicio y final (trim)
void trim(char str[]) {
    int start = 0;
    int end = strlen(str) - 1;

    // Eliminar espacios al inicio
    while (str[start] == ' ' && start <= end) {
        start++;
    }

    // Eliminar espacios al final
    while (str[end] == ' ' && end >= start) {
        end--;
    }

    // Mover el contenido hacia el inicio del arreglo
    for (int i = start; i <= end; i++) {
        str[i - start] = str[i];
    }
    
    // Agregar el terminador nulo al final
    str[end - start + 1] = '\0';
}
