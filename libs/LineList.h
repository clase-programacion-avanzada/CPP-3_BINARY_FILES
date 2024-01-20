#ifndef LINELIST_H
#define LINELIST_H

#include <string>
#include <sstream>
using namespace std;

struct LineList {
    string lines[100];
    int size;

    LineList() {
        size = 0;
    }

    void add(string line) {
        lines[size] = line;
        size++;
    }

    bool remove(int index) {

        if (index < 0 || index >= size) {
            return false;
        }

        for (int i = index; i < size - 1; i++) {
            lines[i] = lines[i + 1];
        }
        size--;

        return true;
    }

    string get(int index) {
        return lines[index];
    }

    bool contains(string line) {
        for (int i = 0; i < size; i++) {
            if (lines[i] == line) {
                return true;
            }
        }
        return false;
    }

    void clear() {
        size = 0;
    }

    LineList copy(LineList other) {
        LineList newList;
        
        for (int i = 0; i < other.size; i++) {
            newList.add(other.lines[i]);
        }

        return newList;

    }

};

LineList split(string line, char delimiter) {
        
        LineList tokenList;
        //split line into tokens
        //stringstream is a stream class to operate on strings.
        stringstream ss(line);

        //see that ss.good() is used to check if the stream is good
        //it means that it checks if the stream has not reached the end of the line
        while (ss.good()) {
            //declare a string variable to store the token
            //a token is a string separated by a delimiter
            //i.e 1;1994;90;The Shawshank Redemption
            //  the delimiter is the semicolon (;)
            //  the tokens are: 1, 1994, 90, The Shawshank Redemption
            string token;
            //getline() is used to read a string from the stream
            //getline() extracts characters from the stream until it finds the delimiter character
            //and stores them in the string object 'token'
            getline(ss, token, delimiter);

            //add token to the tokenList
            tokenList.add(token);
        }

        return tokenList;

}
#endif /* MYHEADER_H */

