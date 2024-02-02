#ifndef SHOW_BINARY_FILE_H
#define SHOW_BINARY_FILE_H


#include <iostream>
#include <iomanip>
#include <vector>
#include <string>


char convertNumberToChar(int number) {
    if (number < 10) {
        return static_cast<char>(number + 48);
    }
    return static_cast<char>(number + 55);
}

char getAscii(int byte) {
    if (byte >= 32 && byte <= 126) {
        return static_cast<char>(byte);
    }
    return '_';
}


// Function to render a line of output
void renderLine(int index, const std::vector<char>& bytes) {
    std::string hexContent; // String to hold the hex representation of bytes
    std::string chrContent; // String to hold the ASCII representation of bytes

    // Calculate the limit for the loop
    int limit = std::min((index + 1) * 16, static_cast<int>(bytes.size()));

    // Loop over each byte in the current line
    for (int i = index * 16; i < limit; i++) {
        int byte = bytes[i]; // Get the current byte

        // Convert the byte to a hex string
        std::stringstream hexStream;
        hexStream << std::setfill('0') << std::setw(2) << std::hex << byte;

        // Append the hex string to hexContent, only taking the last two characters
        hexContent += " " + hexStream.str().substr(hexStream.str().length() - 2);

        // Append a space and the ASCII representation of the byte to chrContent
        chrContent += " ";
        chrContent += getAscii(byte);
    }

    // Create a string of the offset in hex
    std::stringstream offsetStream;
    offsetStream << std::setfill('0') << std::setw(8) << std::hex << index * 16;

    // Print the offset and the hex and ASCII content
    std::cout << "Offset: " << offsetStream.str() << "\n";
    std::cout << "Hex: " << hexContent.substr(1) << "\n";
    std::cout << "Chr: " << chrContent << "\n\n";
}

void showBinaryFile(const std::string& fileName) {
    std::ifstream file(fileName, std::ios::binary);

    if (!file) {
        std::cout << "Could not open file " << fileName << "\n";
        return;
    }

    char byte;
    std::vector<char> bytes;

    while (file >> std::noskipws >> byte) {
        bytes.push_back(byte);
    }

    int lines = bytes.size() / 16;

    for (int i = 0; i < lines/100; i++) {
        renderLine(i, bytes);
    }

    file.close();
}

void showBlockFromMovieBinaryFile(const std::string& fileName) {
    //reads file

    std::ifstream file(fileName, std::ios::binary);

    if (!file) {
        std::cout << "Could not open file " << fileName << "\n";
        return;
    }

    char byte;
    std::vector<char> bytes;

    while (file >> std::noskipws >> byte) {
        bytes.push_back(byte);
    }

    int wrongBlocks = bytes.size() / sizeof(MovieBin2);

    if (bytes.size() < wrongBlocks * sizeof(MovieBin2)) {
        std::cerr << "Not enough data for " << wrongBlocks << " blocks" << std::endl;
        return;
    }

   
   
    
    int blocks = bytes.size() / sizeof(MovieBin);
    cout << "============ Movie Binary File ============" << endl;
    cout << "Number of blocks: " << blocks << endl; 
    
    for (int i = 0; i < blocks/8; i++) {
        cout << "Movie " << i << endl;
        cout << "id = " << ((MovieBin*)bytes.data())[i].id << endl;
        cout << "year = " << ((MovieBin*)bytes.data())[i].year << endl;
        cout << "rating = " << ((MovieBin*)bytes.data())[i].rating << endl;
        cout << "title = " << ((MovieBin*)bytes.data())[i].title << endl;
        cout << "______________________" << endl;
    }

     cout << "============ Movie Binary File with wrong order ============" << endl;
    cout << "Number of blocks: " << wrongBlocks << endl; 
    for (int i = 0; i < wrongBlocks/8; i++) {
        std::cout << "Starting iteration " << i << std::endl;
        MovieBin2 movieBin2;
        std::memcpy(&movieBin2, bytes.data() + i * sizeof(MovieBin2), sizeof(MovieBin2));
        cout << "Movie " << i << endl;
        cout << "id = " << movieBin2.id << endl;
        cout << "year = " << movieBin2.year << endl;
        cout << "rating = " << movieBin2.rating << endl;
        string title = movieBin2.title;
        cout << "title = " << title << endl;
        cout << "______________________" << endl;
        std::cout << "Ending iteration " << i << std::endl;
        
    }


    file.close();

    
}



#endif // !SHOW_BINARY_FILE_H