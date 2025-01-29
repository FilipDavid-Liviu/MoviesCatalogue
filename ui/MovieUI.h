#pragma once
#include "../controller/MovieServices.h"
#include <iostream>
using namespace std;

class MovieUI {
public:
    MovieService* services;

public:
    MovieUI();

    ~MovieUI();

    void run();

    void addMovie();

    void removeMovie();

    void updateMovie();

    void printAllMovies() const;

    void printWatchlist() const;

    void deleteMovie();

    void adminMenu();
    void userMenu();
    void movieMenu();

    static void printMenuStart();
    static void printMenuAdmin();
    static void printMenuUser();
    static void printMenuMovie();

};

void normalizeName(string& name);