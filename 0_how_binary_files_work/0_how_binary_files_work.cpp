/*This is a cpp file that explains how binary files works*/
#include <iostream>
#include <string>
#include <cstddef> // This is for the byte type
#include <cstdint>
#include"../libs/Movie.h"
#include"../libs/MovieList.h"
#include"../libs/TextFileHandler.h"
#include"../libs/LineList.h"

using namespace std;

struct MovieBin {
    int id;
    int year;
    int rating;
    char title[100];
};

struct MovieBin2 {
    int id;
    char title[100];
    int year;
    int rating;
};

MovieBin toMovieBin(Movie movie);

bool writeFile(string fileName, MovieList movies, unsigned int mode);
MovieList readFile(string fileName, unsigned int mode);
MovieBin2 readFileWrongStruct(string fileName, unsigned int mode);

void printMovie(Movie movie);
void printMovieBin(MovieBin movieBin);


int main(){
    
    //We will use the same example as in the text file example
    // and we will read it using the TextFileHandler struct 

    //https://en.cppreference.com/w/cpp/types/byte <- This only works in C++17 and above
    
    //byte x{0b01000001};

    uint8_t value = 0b01000001;
    cout <<"======================"<< endl;
    cout << "Binary files can be seen as a sequence of bytes,\n"
    "these bytes can be interpreted as any type of data \n"
    "(int, float, char, etc). \n"
    "    i.e  \n"
    "        01000001 can be interpreted as the number 65 \n"
    "        or as the character 'A'"
        << endl<< endl;
    cout << "Binary value: 01000001"<< endl;
    cout << "interpreted as number: " << (int)value << endl;//This will print 65
    cout << "interpreted as char: " << (char)value << endl;//This will print 'A'
    cout <<"======================"<< endl << endl;
    
    cout << "The way we interpret the bytes is up to us.\n"
    "In the case of structs, the bytes are interpreted\n"
    "as the struct's attributes.\n"
    "    i.e\n"
    "        if we have a struct Movie with the following\n"
    "        attributes:\n"
    "            int id;\n"
    "            int year;\n"
    "            int rating;\n"
    "            string title;\n"
    "        and we have the following values:\n"
    "            id = 1\n"
    "            year = 2000\n"
    "            rating = 5\n"
    "            title = \"Movie 1\"\n"
    "        then the bytes would be interpreted as:\n"
    "                   | most significant byte (MSB) -> least significant byte (LSB)\n"
    "            4 bytes| 00000000 00000000 00000000 00000001| <- id\n"
    "            4 bytes| 00000000 00000000 00000111 11010000| <- year\n"
    "            4 bytes| 00000000 00000000 00000000 00000101| <- rating\n"
    "            4 bytes| 00000000 01001101 01101111 01110110 \n"
    "            4 bytes  01101001 01100101 00100000 00110001| <- title*\n"
    "\n"
    "            *Note that the string is variable in size, so\n"
    "            we need to specify the size of the string\n"
    "            in the struct. In this case we will use a\n"
    "            char array of size 100.\n"
    "        technically, we are writing the following struct \n"
    "        to the binary file:\n"
    "            struct MovieBin {\n"
    "                int id;\n"
    "                int year;\n"
    "                int rating;\n"
    "                char title[100];\n"
    "            }\n"
    "\n"
    "\n"
    "    Binary files are written in bytes, so we need to convert\n"
    "    the MovieList struct to a byte array. Also, if the struct\n"
    "    contains strings we need to convert them to char arrays;\n"
    "    the reason for this is that strings are dynamic arrays\n"
    "    and that could cause problems when reading the file."
        << endl<< endl;
    
    cout << "Let's write one movie to a binary file" << endl;
    Movie movie;
    movie.id = 1;
    movie.year = 2000;
    movie.rating = 5;
    movie.title = "Movie 1";

    MovieList movies;
    movies.add(movie);

    bool fileWasWritten = writeFile(
        "example_writing_one_movie_binary.bin", 
        movies, 
        ios::out | ios::binary);

    if (!fileWasWritten) {
        cout << "Error writing to binary file" << endl;
        return -1;
    }

    cout << "Binary file written successfully" << endl << endl;

    cout << "Now let's read the binary file using a wrong struct"
    " this struct will be\n"
    " struct MovieBin2 {\n" 
    "                int id;\n"
    "                char title[100];\n"
    "                int year;\n"
    "                int rating;\n"
    "}" << endl << endl;


    cout << "============ Movie Binary File with wrong order ============" << endl;
    MovieBin2 movieBin2 = readFileWrongStruct(
        "example_writing_one_movie_binary.bin", 
        ios::in | ios::binary);

    cout << "Movie with wrong order " << endl;
    cout << "id = " << movieBin2.id << endl;
    cout << "year = " << movieBin2.year << endl;
    cout << "rating = " << movieBin2.rating << endl;
    string title = movieBin2.title;
    cout << "title = " << title << endl;

    cout << "As you can see, the title is not correct, this is because\n"
    "the bytes are interpreted as the struct MovieBin2, which has\n"
    "the wrong order of the struct MovieBin" << endl << endl;

    cout << "The lesson is that we need to read the bytes as the struct\n"
    "we want to read, in this case, we want to read the bytes as the\n"
    "struct MovieBin, so we need to convert the bytes to a MovieBin\n"
    "struct" << endl << endl;
    

}

/*This function converts a Movie object to a MovieBin object.
 The 'movie' parameter is the Movie object to convert.*/
MovieBin toMovieBin(Movie movie) {
    MovieBin movieBin;

    movieBin.id = movie.id;
    movieBin.year = movie.year;
    movieBin.rating = movie.rating;

    // Copy the 'title' field from the Movie object to the MovieBin object.
    // Since 'title' is a C-style string (aka char array) in MovieBin and a std::string in Movie,
    // we need to use 'c_str()' to get a C-style string from the std::string,
    // and 'strcpy' to copy that C-style string into 'movieBin.title'.
    strcpy(movieBin.title, movie.title.c_str());

    return movieBin;
}



/*This function writes a list of movies to a file.
The 'fileName' parameter specifies the name of the file to write to.
The 'movies' parameter is the list of movies to write.
The 'mode' parameter specifies the mode in which to open the file. 
    By default, it's set to 'ios::out', which means the file will be opened for output.*/
bool writeFile(string fileName, MovieList movies, unsigned int mode = ios::out) {

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


MovieBin2 readFileWrongStruct(string fileName, unsigned int mode = ios::in) {
    // Create a file stream object.
    fstream file;

    cout << "Opening file " << fileName << endl;
    // Open the file with the specified mode.
    file.open(fileName, mode);

    // If the file failed to open, return an empty list.
    if (file.fail()) {
        return MovieBin2();
    }

    cout << "File opened successfully!!!" << endl << endl;


    // Create a MovieBin object to store the movie data.
    MovieBin2 movieBin;

    // While there are still movies to read...
    file.read((char*)&movieBin, sizeof(MovieBin2));
    

    cout << "Closing file" << endl;
    // Don't forget to close the file when you're done.
    file.close();

    // Return the list of movies.
    return movieBin;
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

