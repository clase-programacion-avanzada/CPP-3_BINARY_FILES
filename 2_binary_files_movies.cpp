#include <iostream>
#include <string>

#include "libs/Movie.h"
#include "libs/TextFileHandler.h"
#include "libs/ShowBinaryFile.h"
#include "libs/BinaryFileHandler.h"

using namespace std;

int EXIT_ERROR_CODE = -1;

void printMovie(Movie movie){
    cout << "ID: " << movie.id << endl;
    cout << "Year: " << movie.year << endl;
    cout << "Rating: " << movie.rating << endl;
    cout << "Title: " << movie.title << endl;
}

void printLines (List<string> lines) {
    for (int i = 0; i < lines.size; i++){
        cout << lines.get(i) << endl;
    }
}

void printMovies(List<Movie> movies){
    for (int i = 0; i < movies.size/8; i++){
        printMovie(movies.get(i));
        cout << endl;
    }
}



int main(){
    
    cout.setf(std::ios::unitbuf);
    string inputFileName = "example_reading.txt";
    const char delimiter = ';';

    TextFileHandler readFileHandler(inputFileName);

    List<string> lines = readFileHandler.readLines();

    List<Movie> movies = getMoviesFromLines(lines, delimiter);

    List<MovieBin> moviesBin = getMoviesBinFromMovies(movies);

    cout << "Movies from text file: " << endl;

    //printMovies(movies);

    cout << endl;
    //Using binary files

    //We will need to write the movies to a binary file

    string inputFileNameBinary = "example_reading_binary.bin";

    BinaryFileHandler<MovieBin> binaryFileHandler(inputFileNameBinary);

    bool successfulWrite = binaryFileHandler.writeBinaryFile(moviesBin);

    if (!successfulWrite){
        cout << "Error writing to binary file" << endl;
        return EXIT_ERROR_CODE;
    }

    cout << "Binary file written successfully" << endl;
   
    //If we see the binary file, we will see that it is not human readable
    showBinaryFile(inputFileNameBinary);

    //We can also see the binary file in blocks,
    //each block must be the size and order of the struct MovieBin
    //In this example we have a struct MovieBin2 that has the wrong order
    // of the struct MovieBin
    showBlockFromMovieBinaryFile(inputFileNameBinary);
    //Once we have the binary file, we can read it
    cout << endl << "== Reading binary file == " << endl;
    List<MovieBin> moviesFromBinary = binaryFileHandler.readBinaryFile();

    List<Movie> moviesFromBinaryConverted = getMoviesFromMoviesBin(moviesFromBinary);

    cout << "Movies from binary file: " << endl << endl;
    printMovies(moviesFromBinaryConverted);

    //We can also get a movie from the binary file

    cout << endl << "== Getting movie from binary file == " << endl;
    MovieBin movieBinFromBinary = binaryFileHandler.getElementFromFile(85);
    Movie movieFromBinary = toMovie(movieBinFromBinary);
    printMovie(movieFromBinary);

    //We can also append a movie to the binary file
    cout << endl << "== Appending movie to binary file == " << endl;
    cout << "Appending movie to binary file" << endl;
    cout << "File size before appending: " << binaryFileHandler.getFileSize() << endl;
    
    Movie movieToAppend;
    movieToAppend.id = 5;
    movieToAppend.year = 2000;
    movieToAppend.rating = 5;
    movieToAppend.title = "Movie 5";

    cout << "Movie to append: " << endl << endl ;
    printMovie(movieToAppend);

    MovieBin movieToAppendBin = toMovieBin(movieToAppend);

    bool successfulAppend = binaryFileHandler.appendElementToFile(movieToAppendBin);

    if (!successfulAppend){
        cout << "Error appending to binary file" << endl;
        return EXIT_ERROR_CODE;
    }
    cout << endl << "Movie appended successfully" << endl;
    cout << "File size after appending: " << binaryFileHandler.getFileSize() << endl;
    

    //We can also remove a movie from the binary file

    cout << endl << "Removing movie from binary file" << endl;
    cout << "File size before removing: " << binaryFileHandler.getFileSize() << endl;

    bool successfulRemove = binaryFileHandler.removeElementFromFile(2);

    if (!successfulRemove){
        cout << "Error removing from binary file" << endl;
        return EXIT_ERROR_CODE;
    }

    cout << endl << "Movie removed successfully" << endl;
    cout << "File size after removing: " << binaryFileHandler.getFileSize() << endl;
    
 

    return 0;
}


