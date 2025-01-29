#pragma once
#include "Movie.h"
#include "Repository.h"
class Action {
public:
    virtual void executeUndo() = 0;
    virtual void executeRedo() = 0;
};

class ActionAdd: public Action {
private:
    Movie addedMovie;
    FileRepository& repo;
public:
    explicit ActionAdd(Movie& movie, FileRepository& repo);
    void executeUndo() override;
    void executeRedo() override;
};

class ActionRemove: public Action {
private:
    Movie removedMovie;
    FileRepository& repo;
public:
    ActionRemove(Movie& movie, FileRepository& repo);
    void executeUndo() override;
    void executeRedo() override;
};

class ActionUpdate: public Action {
private:
    Movie initialMovie;
    Movie newMovie;
    FileRepository& repo;
public:
    ActionUpdate(Movie& movieOld, Movie& movieNew, FileRepository& repo);
    void executeUndo() override;
    void executeRedo() override;
};