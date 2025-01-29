#include "Action.h"

ActionAdd::ActionAdd(Movie& movie, FileRepository& repository) : repo(repository){
    this->addedMovie = movie;
}

ActionRemove::ActionRemove(Movie& movie, FileRepository& repo) : repo(repo){
    this->removedMovie = movie;
}

ActionUpdate::ActionUpdate(Movie& movieOld, Movie& movieNew, FileRepository& repo) : repo(repo){
    this->initialMovie = movieOld;
    this->newMovie = movieNew;
}


void ActionAdd::executeUndo(){
    this->repo.removeEl(this->addedMovie);
}
void ActionAdd::executeRedo(){
    this->repo.add(this->addedMovie);
}

void ActionRemove::executeUndo(){
    this->repo.add(this->removedMovie);
}
void ActionRemove::executeRedo(){
    this->repo.removeEl(this->removedMovie);
}
void ActionUpdate::executeUndo(){
    this->repo.replaceEl(newMovie, initialMovie);
}
void ActionUpdate::executeRedo(){
    this->repo.replaceEl(initialMovie, newMovie);
}