/*This is a cpp file that explains how binary files works*/
#include <iostream>
#include <string>
#include <cstddef> // This is for the byte type
#include <cstdint>

#include"libs/Movie.h"
#include"libs/TextFileHandler.h"
#include"libs/List.h"

using namespace std;


bool writeBinaryFile(string fileName, List<MovieBin> movies);
MovieBin2 readFileWrongStruct(string fileName, unsigned int mode);
List<MovieBin> readBinaryFile(string fileName);
void printMovie(Movie movie);
void printMovieBin(MovieBin movieBin);


int main(){
    
    string inputFileName = "example_reading.txt";
    const char delimiter = ';';

    TextFileHandler readFileHandler(inputFileName);

    List<string> lines = readFileHandler.readLines();

    List<Movie> moviesFromLines = getMoviesFromLines(lines, delimiter);

    //Writing a binary file

    string inputFileNameBinary = "binary_file_writing.bin";

    //We will use a function to write the movies to a binary file
    //Remember that the type we will be writing is MovieBin

    //The first thing to do is to convert the movies to MovieBin
    List<MovieBin> moviesBin = getMoviesBinFromMovies(moviesFromLines);

    //Then we will write the movie bins to a binary file
    cout << "Writing movies to binary file" << endl;

    //The mode should be set to ios::out | ios::binary
    bool fileWasWritten = writeBinaryFile(
        inputFileNameBinary, 
        moviesBin);
    
    if (!fileWasWritten) {
        cout << "Error writing to binary file" << endl;
        return -1;
    }

    cout << "Binary file written successfully" << endl << endl;


    //Reading a binary file

    cout << "Reading binary file" << endl;

    //We will read the binary file and print the movies.
    //Remember that if we wrote the file with MovieBin, 
    // we should read it with MovieBin

    List<MovieBin> moviesFromBinaryFile = readBinaryFile(inputFileNameBinary);
    
    //We will convert the MovieBin to Movie
    List<Movie> moviesFromBinaryFileConverted = getMoviesFromMoviesBin(moviesFromBinaryFile);

    cout << "Printing first and last movie from binary file " << endl;
    printMovie(moviesFromBinaryFileConverted.get(0));
    printMovie(moviesFromBinaryFileConverted.get(moviesFromBinaryFileConverted.size - 1));
}

/*This function writes a list of movies to a file.
The 'fileName' parameter specifies the name of the file to write to.
The 'movies' parameter is the list of movies to write.
The 'mode' parameter specifies the mode in which to open the file. 
    By default, it's set to 'ios::out', which means the file will be opened for output.*/
bool writeBinaryFile(string fileName, List<MovieBin> moviesBin) {

    // Create a file stream object.
    fstream file;

    cout << "Opening file " << fileName << endl;
    // Open the file with the specified mode.
    file.open(fileName, ios::out | ios::binary);
    
    // If the file failed to open, return false.
    if (file.fail()) {
        return false;
    }

    cout << "File opened successfully!!!" << endl << endl;

    for (int i = 0; i < moviesBin.size; i++) {
        // Convert the Movie object to a MovieBin object.
        
        MovieBin movieBin = moviesBin.get(i);
        
        file.write((char*)&movieBin, sizeof(MovieBin));
    }

    cout << "Closing file" << endl;
    // Don't forget to close the file when you're done.
    file.close();

    // If everything succeeded, return true.
    return true;


}

List<MovieBin> readBinaryFile(string fileName) {

    List<MovieBin> moviesBin;

    fstream file;

    file.open(fileName, ios::in | ios::binary);

    if (file.fail()) {
        return moviesBin;//Return an empty list
    }

    MovieBin movieBin;

    while (file.read(reinterpret_cast<char *>(&movieBin), sizeof(MovieBin))) {
        moviesBin.add(movieBin);
    }

    file.close();

    return moviesBin;
}


void printMovie(Movie movie){
    cout << "Movie block: " << endl;
    cout << "ID: " << movie.id << " ";
    cout << "Year: " << movie.year << " ";
    cout << "Rating: " << movie.rating << " " ;
    cout << "Title: " << movie.title << endl;
}



