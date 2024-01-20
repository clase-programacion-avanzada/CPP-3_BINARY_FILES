#ifndef MOVIE_H
#define MOVIE_H

#include <string>
#include <sstream>
#include "LineList.h"

using namespace std;

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
    
    LineList words = split(line, delimiter);

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

#endif /* MOVIE_H */