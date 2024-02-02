#ifndef MOVIE_H
#define MOVIE_H

#include <string>
#include <sstream>
#include "List.h"
#include "TextFileHandler.h"

using namespace std;

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

struct Movie{
    int id;
    int year;
    int rating;
    string title;

    Movie() {
        id = 0;
        year = 0;
        rating = 0;
        title = "";
    }

    bool equals(Movie other) {
        return id == other.id
            && year == other.year
            && rating == other.rating
            && title == other.title;

    }

};


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

Movie toMovie(MovieBin movieBin) {
    Movie movie;
    movie.id = movieBin.id;
    movie.year = movieBin.year;
    movie.rating = movieBin.rating;
    movie.title = movieBin.title;
    return movie;
}

MovieBin toMovieBin(Movie movie) {
    MovieBin movieBin;
    movieBin.id = movie.id;
    movieBin.year = movie.year;
    movieBin.rating = movie.rating;
    strcpy(movieBin.title, movie.title.c_str());
    return movieBin;
}
Movie getMovieFromLine (string line, char delimiter) {
    
    // This is an alternative way to split a string
    /*string word; 
    Movie aux_movie;
    stringstream str(line);

    getline( str, word, delimiter);
    aux_movie.id = stoi(word);

    getline( str, word,delimiter);
    aux_movie.year = stoi(word);

    getline( str, word,delimiter);
    aux_movie.rating = stoi(word);

    getline( str, word,delimiter);
    aux_movie.title = word;

    return aux_movie;*/
    
    List<string> words = split(line, delimiter);

    Movie aux_movie;
    aux_movie.id = stoi(words.get(0));
    aux_movie.year = stoi(words.get(1));
    aux_movie.rating = stoi(words.get(2));
    aux_movie.title = words.get(3);
    

    return aux_movie;

}

string getLineFromMovie(Movie movie, char delimiter) {
    string line = "";
    line += to_string(movie.id) + delimiter;
    line += to_string(movie.year) + delimiter;
    line += to_string(movie.rating) + delimiter;
    line += movie.title;

    return line;
}

List<Movie> getMoviesFromLines(List<string> lines, char delimiter) {

    List<Movie> movies;
    for (int i = 0; i < lines.size; i++) {
    
        Movie movie = getMovieFromLine(lines.get(i), delimiter);
        
        movies.add(movie);
    }

    return movies;
}

List<string> getLinesFromMovies(List<Movie> movies, char delimiter) {
    List<string> lines;
    for (int i = 0; i < movies.size; i++) {
        lines.add(getLineFromMovie(movies.get(i), delimiter));
    }
    return lines;
}

List<MovieBin> getMoviesBinFromMovies(List<Movie> movies) {
    List<MovieBin> moviesBin;
    for (int i = 0; i < movies.size; i++) {
        MovieBin movieBin = toMovieBin(movies.get(i));
        moviesBin.add(movieBin);
    }
    return moviesBin;
}

List<Movie> getMoviesFromMoviesBin(List<MovieBin> moviesBin) {
    List<Movie> movies;
    for (int i = 0; i < moviesBin.size; i++) {
        Movie movie = toMovie(moviesBin.get(i));
        movies.add(movie);
    }
    return movies;
}

float getAverageRating(List<Movie> movies) {
    float sum = 0;
    for (int i = 0; i < movies.size; i++) {
        sum += movies.get(i).rating;
    }
    return sum / movies.size;
}

List<Movie> moviesWithratingGreaterThan(List<Movie> movies, double rating) {
    List<Movie> newList;

    for (int i = 0; i < movies.size; i++) {
        if (movies.get(i).rating > rating) {
            newList.add(movies.get(i));
        }
    }

    return newList;
}

#endif /* MOVIE_H */