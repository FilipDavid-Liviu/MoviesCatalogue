#include <sstream>
#include "Movie.h"


Movie::Movie()
    : yearOfRelease(0), numberOfLikes(0) {
    title = "";
    genre = "";
    trailer = "";
}

Movie::Movie(string _title, string _genre, int _yearOfRelease, int _numberOfLikes, string _trailer)
    : title(std::move(_title)), genre(std::move(_genre)),
    yearOfRelease(_yearOfRelease), numberOfLikes(_numberOfLikes), trailer(std::move(_trailer)){}

const string& Movie::getTitle() const {
    return title;
}

const string& Movie::getGenre() const {
    return genre;
}

const int& Movie::getYearOfRelease() const {
    return yearOfRelease;
}

const int& Movie::getNumberOfLikes() const {
    return numberOfLikes;
}

const string& Movie::getTrailer() const {
    return trailer;
}

void Movie::addLike() {
    numberOfLikes++;
}

string Movie::toString() const {
    string movieString;
    movieString += "Title: " + string(title) + "\n";
    movieString += "Genre: " + string(genre) + "\n";
    movieString += "Year of Release: " + to_string(yearOfRelease) + "\n";
    movieString += "Number of Likes: " + to_string(numberOfLikes) + "\n";
    movieString += "Trailer: " + string(trailer) + "\n";
    return movieString;
}

vector<string> tokenize(const string& str, char delimiter)
{
    vector <string> result;
    stringstream ss(str);
    string token;
    while (getline(ss, token, delimiter))
        result.push_back(token);

    return result;
}

istream & operator>>(istream & is, Movie& s)
{
    string line;
    getline(is, line);

    vector<string> tokens = tokenize(line, ';');
    if (tokens.size() != 5)
        return is;

    s.title = tokens[0];
    s.genre = tokens[1];
    s.yearOfRelease = stoi(tokens[2]);
    s.numberOfLikes = stoi(tokens[3]);
    s.trailer = tokens[4];

    return is;
}

ostream & operator<<(ostream & os, const Movie& movie)
{
    os << movie.title << ";" << movie.genre << ";" << movie.yearOfRelease << ";" << movie.numberOfLikes << ";" << movie.trailer << "\n";
    return os;
}