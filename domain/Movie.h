#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Movie {
    private:
    string title;
    string genre;
    int yearOfRelease;
    int numberOfLikes;
    string trailer;
    
    public:
    Movie();

    Movie(string _title, string _genre, int _yearOfRelease, int _numberOfLikes, string _trailer);

    const string& getTitle() const;

    const string& getGenre() const;

    const int& getYearOfRelease() const;

    const int& getNumberOfLikes() const;

    const string& getTrailer() const;

    void addLike();

    string toString() const;

    friend std::istream& operator>>(std::istream& is, Movie& s);
    friend std::ostream& operator<<(std::ostream& os, const Movie& s);
};

