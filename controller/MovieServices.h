#pragma once
#include "../repository/Repository.h"
#include "../domain/Movie.h"
#include "MovieError.h"
#include "Action.h"
#include <stack>
#include <memory>
class MovieService {
private:
    FileRepository* repository;
    FileRepository* watchlist;
    stack<unique_ptr<Action>> undoStack;
    stack<unique_ptr<Action>> redoStack;

public:
    explicit MovieService(const string& filetype);

    ~MovieService();

    void addMovie(const string& title, const string& genre, const int& yearOfRelease, const int& numberOfLikes, const string& trailer);

    void removeMovie(const string& title);

    void updateMovie(const string& title, const string& genre, const int& yearOfRelease, const int& numberOfLikes, const string& trailer);

    Repository* getAllMovies() const;

    FileRepository* getWatchlist() const;

    Repository* getGenreList(const string& genre) const;

    void deleteMovie(const string& title);

    void addLike(const string& title);

    void addMovieWatchlist(const Movie& movie);

    void undo();
    void redo();

};

bool isName(const string& title, vector<Movie>& repo);
