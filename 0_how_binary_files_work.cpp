/*This is a cpp file that explains how binary files works*/
#include <iostream>
#include <string>
#include <cstddef> // This is for the byte type
#include <cstdint>
#include <fstream>

#include "libs/Cinema.hh"

using namespace std;

void trim(char str[]);

int main() {

    /* En un archivo binario, los datos se almacenan en formato binario, 
    lo que significa que se representan como una secuencia de bytes. 
    
    Esto contrasta con los archivos de texto, 
    donde los datos se almacenan como caracteres legibles. 
    En este ejemplo, primero leeremos un archivo de texto con información sobre 
    un cine y luego lo convertiremos a un archivo binario.
    */

    // Leer el archivo de texto
    string fileName = "cinema.txt";

    //El arrchivo de texto está en el siguiente formato:
    // # ID del cine
    // # Cantidad de salas
    // # ID de la sala
    // # Cantidad de películas
    // # Nombre de la película | Hora de la película (HH:MM)

    fstream textFile(fileName);

    if (textFile.fail()) {
        cout << "Error al abrir el archivo de texto: " << fileName << endl;
        return 1;
    }

    Cinema cinema;
    textFile >> cinema.id;
    textFile >> cinema.numberOfRooms;

    for (int i = 0; i < cinema.numberOfRooms; i++) {
        textFile >> cinema.rooms[i].id;
        textFile >> cinema.rooms[i].numberOfMovies;

        for (int j = 0; j < cinema.rooms[i].numberOfMovies; j++) {

            char movieName[40];
            char movieHour[7];

            textFile.ignore(); // Ignorar el salto de línea anterior
            textFile.getline(movieName, 40, '|');
            textFile.getline(movieHour, 7);

            trim(movieName);
            trim(movieHour);
            
            
            strncpy(cinema.rooms[i].movies[j].name, movieName, 40);
            strncpy(cinema.rooms[i].movies[j].hour, movieHour, 6);

            // Asegurarse de que el último carácter sea nulo
            cinema.rooms[i].movies[j].name[39] = '\0';
            cinema.rooms[i].movies[j].hour[5] = '\0';

            
        }
        cout << "Sala " << cinema.rooms[i].id << " tiene " 
             << cinema.rooms[i].numberOfMovies << " películas." << endl;
    }

    textFile.close();

    // Escribir el archivo binario
    string binaryFileName = "cinema.bin";

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
    //   - Cantidad dse películas (1 byte)
    //   - Para cada película:
    //     - Nombre de la película (40 bytes)
    //     - Hora de la película (HH:MM) (6 bytes)

    // Para escribir los datos en el archivo binario, 
    // usamos el operador `write`, indicando cuántos bytes queremos escribir.



    writeBinaryFile.close();

    // Una vez que hemos escrito los datos en el archivo binario,
    // podemos leerlos de nuevo para verificar que se han guardado correctamente.
    fstream readBinaryFile(binaryFileName, ios::in | ios::binary);
    
    if (readBinaryFile.fail()) {
        cout << "Error al abrir el archivo binario para lectura: " << binaryFileName << endl;
        return 1;
    }

    Cinema cinemaFromBinary;

    readBinaryFile.close();

    // Hay que tener cuidado al leer los datos del archivo binario,
    // ya que debemos leerlos en el mismo orden en que los escribimos,
    // con los tamaños correctos.
    fstream readBinaryFile2(binaryFileName, ios::in | ios::binary);

    if (readBinaryFile2.fail()) {
        cout << "Error al abrir el archivo binario para lectura: " << binaryFileName << endl;
        return 1;
    }

    int wrongReading = 0;

    readBinaryFile2.read(reinterpret_cast<char*>(&wrongReading), sizeof(int));

    cout << "Valor leído incorrectamente: " << wrongReading << endl;

    readBinaryFile2.close();

    return 0;
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
