/*This is a cpp file that explains how binary files works*/
#include <iostream>
#include <string>
#include <cstddef> // This is for the byte type
#include <cstdint>

#include "libs/Movie.h"
#include "libs/TextFileHandler.h"
#include "libs/List.h"

using namespace std;


bool writeFile(string fileName, List<Movie> movies, unsigned int mode);
List<MovieBin> readFile(string fileName, unsigned int mode);
MovieBin2 readFileWrongStruct(string fileName, unsigned int mode);

void printMovie(Movie movie);
void printMovieBin(MovieBin movieBin);


int main(){
    
    
    //We will read the movies from the text file and write them to a binary file
    string inputFileName = "example_reading.txt";
    const char delimiter = ';';

    TextFileHandler readFileHandler(inputFileName);

    List<string> lines = readFileHandler.readLines();

    List<Movie> moviesFromLines = getMoviesFromLines(lines, delimiter);

    //We will write the movies to a binary file
    string inputFileNameBinary = "example_reading_binary.bin";

    cout << "Writing movies to binary file, remember mode"
    " should be set to ios::out | ios::binary" << endl << endl;
    bool fileWasWritten2 = writeFile(
        inputFileNameBinary, 
        moviesFromLines, 
        ios::out | ios::binary);

    if (!fileWasWritten2) {
        cout << "Error writing to binary file" << endl;
        return -1;
    }

    cout << "Binary file written successfully" << endl << endl;
    
    cout << "In the case of reading binary files, we need to read the bytes\n"
    "and interpret them as the struct we want to read.\n"
    "In this case, we want to read the bytes as a MovieBin struct.\n"
    "Then we need to convert the bytes to a Movie struct.\n"
    "The conversion is done by copying the bytes to the Movie struct.\n"<< endl << endl;


    //We will read the binary file and print the movies
    cout << "Reading binary file" << endl;
    List<MovieBin> moviesFromBinaryFile = readFile(inputFileNameBinary, ios::in | ios::binary);

    List<Movie> moviesFromBinaryFileConverted = getMoviesFromMoviesBin(moviesFromBinaryFile);
    cout << "Printing first and last movie from binary file " << endl;
    printMovie(moviesFromBinaryFileConverted.get(0));
    printMovie(moviesFromBinaryFileConverted.get(moviesFromBinaryFile.size - 1));


}

/*This function writes a list of movies to a file.
The 'fileName' parameter specifies the name of the file to write to.
The 'movies' parameter is the list of movies to write.
The 'mode' parameter specifies the mode in which to open the file. 
    By default, it's set to 'ios::out', which means the file will be opened for output.*/
bool writeFile(string fileName, List<Movie> movies, unsigned int mode = ios::out ) {

    // Create a file stream object.
    fstream file;

    cout << "Opening file " << fileName << endl;
    // Open the file with the specified mode.
    file.open(fileName, mode);
    
    // If the file failed to open, return false.
    if (file.fail()) {
        return false;
    }

    cout << "File opened successfully!!!" << endl << endl;

    for (int i = 0; i < movies.size; i++) {
        // Convert the Movie object to a MovieBin object.
        
        Movie movie = movies.get(i);
        MovieBin movieBin = toMovieBin(movie);

        //This is just to show the process for the first movie
        if (i == 0) {
            cout << "This process is repeated for each movie in the list" << endl;
            cout << "Writing movie: " << i << endl;
            cout << "Getting movie from list" << endl << endl;
            printMovie(movie);
            cout << "Converting movie to movie bin" << endl ;
            printMovieBin(movieBin);
            cout << "Note that the title is a char array" 
            " that means that the title will be padded with"
            " null characters '\\0'" 
            " if the title is less than 100 characters long" << endl;
            
        }
        
        
        file.write((char*)&movieBin, sizeof(MovieBin));
    }

    cout << "Closing file" << endl;
    // Don't forget to close the file when you're done.
    file.close();

    // If everything succeeded, return true.
    return true;
}

List<MovieBin> readBinaryFile(string fileName) {
    // Create a file stream object.
    fstream file;

    cout << "Opening file " << fileName << endl;
    // Open the file with the specified mode.
    file.open(fileName, ios::in | ios::binary);

    // If the file failed to open, return an empty list.
    if (file.fail()) {
        return List<MovieBin>();
    }

    cout << "File opened successfully!!!" << endl << endl;

    // Create a list to store the movies.
    List<MovieBin> movies;

    // Create a MovieBin object to store the movie data.
    MovieBin movieBin;

    
    // While there are still movies to read...
    while (file.read((char*)&movieBin, sizeof(MovieBin))) {
        
        // Add the movie to the list.
        movies.add(movieBin);
    }

    cout << "Closing file" << endl;
    // Don't forget to close the file when you're done.
    file.close();

    // Return the list of movies.
    return movies;
}

void printMovie(Movie movie){
    cout << "Movie block: " << endl;
    cout << "ID: " << movie.id << " ";
    cout << "Year: " << movie.year << " ";
    cout << "Rating: " << movie.rating << " " ;
    cout << "Title: " << movie.title << endl;
}

void printMovieBin(MovieBin movieBin) {
    cout << "MovieBin block:" << endl;
    cout << "ID: " << movieBin.id << " ";
    cout << "Year: " << movieBin.year << " ";
    cout << "Rating: " << movieBin.rating << " ";
    string arrayShowingAllChars = "";

    for (int i = 0; i < 100; i++) {
        char currentChar = movieBin.title[i];
        if (currentChar == '\0') {
            arrayShowingAllChars += "\\0";
        }
        arrayShowingAllChars += movieBin.title[i];
    }

    cout << "Title: " << arrayShowingAllChars << endl << endl;
}

