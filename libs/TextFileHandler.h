#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "LineList.h"
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

struct TextFileHandler {

    string fileName;

    TextFileHandler(string path) {
        fileName = path;
    }

    LineList readLines() {

        LineList lines;
        
        fstream file;
        
        file.open(fileName, ios::in);
        
        if (file.fail()) {
            return lines;
        }
        string line;

        while (getline(file, line)) {
            lines.add(line);
        }

        file.close();

        return lines;

    }

    bool writeLines(LineList lines, unsigned int mode = ios::out) {

        fstream file;

        file.open(fileName, mode);

        if (file.fail()) {
            return false;
        }

        for (int i = 0; i < lines.size; i++) {
            
            if(i != 0) {
                file << endl;
            }

            file << lines.get(i);
        }

        file.close();

        return true;

    }

    bool writeSingleLine(string line, unsigned int mode = ios::out | ios::app) {

        fstream file;

        file.open(fileName, mode);

        if (file.fail()) {
            return false;
        }

        file << line;

        file.close();

        return true;

    }

};




#endif /* MYHEADER_H */