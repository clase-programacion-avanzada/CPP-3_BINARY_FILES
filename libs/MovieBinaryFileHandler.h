#ifndef MOVIE_BINARY_FILE_HANDLER_H
#define MOVIE_BINARY_FILE_HANDLER_H

#include "MovieList.h"
#include "Movie.h"
#include <fstream>
#include <filesystem>

using namespace std;

struct MovieBin2 {
    
    char title[100];
    int id;
    int year;
    int rating;
    

    MovieBin2() {
        id = 0;
        year = 0;
        rating = 0;
        strcpy(title, "");
    }

    bool equals(MovieBin2 other) {
        return id == other.id
                && year == other.year
                && rating == other.rating
                && strcmp(title, other.title) == 0;

    }
};


struct MovieBin {
    int id;
    int year;
    int rating;
    char title[100];

    MovieBin() {
        id = 0;
        year = 0;
        rating = 0;
        strcpy(title, "");
    }

    bool equals(MovieBin other) {
        return id == other.id
                && year == other.year
                && rating == other.rating
                && strcmp(title, other.title) == 0;

    }
};

MovieBin toMovieBin(Movie movie) {
    MovieBin movieBin;
    movieBin.id = movie.id;
    movieBin.year = movie.year;
    movieBin.rating = movie.rating;
    strcpy(movieBin.title, movie.title.c_str());
    return movieBin;
}

Movie toMovie(MovieBin movieBin) {
    Movie movie;
    movie.id = movieBin.id;
    movie.year = movieBin.year;
    movie.rating = movieBin.rating;
    movie.title = movieBin.title;
    return movie;
}

struct MovieBinaryFileHandler {

    string fileName;

    MovieBinaryFileHandler(string path) {
        fileName = path;
    }

    MovieList readFile() {

        MovieList movies;

        fstream file;

        file.open(fileName, ios::in | ios::binary);

        if (file.fail()) {
            return movies;
        }

        MovieBin auxMovieBin;

        while (file.read((char*) &auxMovieBin, sizeof (MovieBin))) {
            Movie auxMovie = toMovie(auxMovieBin);
            movies.add(auxMovie);
        }
        
        file.close();

        return movies;

    }

    bool writeFile(MovieList movies, unsigned int mode = ios::out | ios::binary) {

        fstream file;

        file.open(fileName, mode);

        if (file.fail()) {
            return false;
        }

        for (int i = 0; i < movies.size; i++) {
            MovieBin movieBin = toMovieBin(movies.movies[i]);
            file.write((char*) &movieBin, sizeof (MovieBin));
        }

        file.close();

        return true;

    }

    bool appendMovie(Movie movie) {

        fstream file;

        file.open(fileName, ios::out | ios::binary | ios::app);

        if (file.fail()) {
            return false;
        }
        MovieBin movieBin = toMovieBin(movie);
        file.write((char*) &movieBin, sizeof (MovieBin));

        file.close();

        return true;

    }

    bool removeMovie(Movie movie) {

        MovieList movies = readFile();

        for (int i = 0; i < movies.size; i++) {
            if (movies.movies[i].equals(movie)) {
                movies.remove(i);
                return writeFile(movies);
            }
        }

        return false;

    }

    Movie getMovie(int index) {
        
        if (index < 0 || index >= readFile().size) {
            return Movie();
        }

        MovieList movies = readFile();
        return movies.get(index);
    }

    int getFileSize() {
        fstream file;

        file.open(fileName, ios::in | ios::binary);

        if (file.fail()) {
            return -1;
        }

        file.seekg(0, ios::end);
        int fileSize = file.tellg();

        file.close();

        return fileSize;
    }

};



#endif /* MOVIE_BINARY_FILE_HANDLER_H */