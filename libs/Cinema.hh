#ifndef CINEMA_HH
#define CINEMA_HH


// Struct to represent a movie showing

struct Movie {
    char name[40];
    char hour[6]; // Format HH:MM
};

// Struct to represent a room in the cinema

struct Room {
    char id[10];

    uint8_t numberOfMovies;
    Movie movies[5];
};

// Struct to represent a cinema
struct Cinema {
    char id[10];

    uint8_t numberOfRooms;
    Room rooms[5];
};

#endif // CINEMA_HH
