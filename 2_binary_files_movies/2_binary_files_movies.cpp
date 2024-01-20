#include <iostream>
#include <string>

#include "../libs/Movie.h"
#include "../libs/MovieList.h"
#include "../libs/TextFileHandler.h"
#include "../libs/LineList.h"
#include "../libs/MovieBinaryFileHandler.h"
#include "ShowBinaryFile.h"

using namespace std;

int EXIT_ERROR_CODE = -1;

void printMovie(Movie movie){
    cout << "ID: " << movie.id << endl;
    cout << "Year: " << movie.year << endl;
    cout << "Rating: " << movie.rating << endl;
    cout << "Title: " << movie.title << endl;
}

void printLines (LineList lines) {
    for (int i = 0; i < lines.size; i++){
        cout << lines.get(i) << endl;
    }
}

void printMovies(MovieList movies){
    for (int i = 0; i < movies.size; i++){
        printMovie(movies.get(i));
    }
}



int main(){
    
    cout.setf(std::ios::unitbuf);
    string inputFileName = "../example_reading.txt";
    const char delimiter = ';';

    TextFileHandler readFileHandler(inputFileName);

    LineList lines = readFileHandler.readLines();

    MovieList movies = getMoviesFromLines(lines, delimiter);
    cout << "Movies from text file: " << endl;

    //printMovies(movies);

    cout << endl;
    //Using binary files

    //We will need to write the movies to a binary file

    string inputFileNameBinary = "example_reading_binary.bin";

    MovieBinaryFileHandler binaryFileHandler(inputFileNameBinary);

    bool successfulWrite = binaryFileHandler.writeFile(movies);

    if (!successfulWrite){
        cout << "Error writing to binary file" << endl;
        return EXIT_ERROR_CODE;
    }

    cout << "Binary file written successfully" << endl;
   
    //If we see the binary file, we will see that it is not human readable
    //showBinaryFile(inputFileNameBinary);

    //We can also see the binary file in blocks,
    //each block must be the size and order of the struct MovieBin
    //In this example we have a struct MovieBin2 that has the wrong order
    // of the struct MovieBin
    showBlockFromMovieBinaryFile(inputFileNameBinary);
    //Once we have the binary file, we can read it
    cout << "== Reading binary file == " << endl;
    MovieList moviesFromBinary = binaryFileHandler.readFile();

    cout << "Movies from binary file: " << endl;
    //printMovies(moviesFromBinary);

    //We can also get a movie from the binary file
    cout << "== Getting movie from binary file == " << endl;
    Movie movieFromBinary = binaryFileHandler.getMovie(0);
    //printMovie(movieFromBinary);

    //We can also append a movie to the binary file
    cout << "== Appending movie to binary file == " << endl;
    cout << "Appending movie to binary file" << endl;
    cout << "File size before appending: " << binaryFileHandler.getFileSize() << endl;
    Movie movieToAppend;
    movieToAppend.id = 5;
    movieToAppend.year = 2000;
    movieToAppend.rating = 5;
    movieToAppend.title = "Movie 5";

    bool successfulAppend = binaryFileHandler.appendMovie(movieToAppend);

    if (!successfulAppend){
        cout << "Error appending to binary file" << endl;
        return EXIT_ERROR_CODE;
    }
    cout << "File size after appending: " << binaryFileHandler.getFileSize() << endl;
    cout << "Movie appended successfully" << endl;

    //We can also remove a movie from the binary file

    cout << "Removing movie from binary file" << endl;
    cout << "File size before removing: " << binaryFileHandler.getFileSize() << endl;

    bool successfulRemove = binaryFileHandler.removeMovie(movieToAppend);

    if (!successfulRemove){
        cout << "Error removing from binary file" << endl;
        return EXIT_ERROR_CODE;
    }

    cout << "File size after removing: " << binaryFileHandler.getFileSize() << endl;
    cout << "Movie removed successfully" << endl;
 

    return 0;
}


