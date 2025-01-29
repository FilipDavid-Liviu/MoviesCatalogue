#include "MovieServices.h"

bool isName(const string& title, vector<Movie>& repo) {
    if (std::any_of(repo.begin(), repo.end(), [&](const auto& movie) {
        return movie.getTitle() == title;}))
        return true;
    return false;
}

MovieService::MovieService(const string& filetype){
    repository = new FileRepository{"../repository/data.txt"};
    if (filetype == "Html")
        watchlist = new HTMLRepository{"../repository/watchlist.txt"};
    else if (filetype == "Csv")
        watchlist =  new CSVRepository{"../repository/watchlist.txt"};
    else watchlist =  new FileRepository{"../repository/watchlist.txt"};
}

MovieService::~MovieService(){
    delete repository;
    delete watchlist;
}

void MovieService::addMovie(const string& title, const string& genre, const int& yearOfRelease, const int& numberOfLikes, const string& trailer) {
    if (isName(title, this->repository->getElements()))
        throw MovieServiceException(1);
    if (numberOfLikes < 0)
        throw MovieServiceException(2);
    Movie m = Movie(title, genre, yearOfRelease, numberOfLikes, trailer);
    repository->add(m);
    unique_ptr<Action> action = make_unique<ActionAdd>(m, *this->repository);
    undoStack.push(std::move(action));
    while(!redoStack.empty())
        redoStack.pop();

}

void MovieService::removeMovie(const string& title) {
    auto repo = repository->getElements();
    int index = 0;
    for (auto& movie : repo) {
        if (movie.getTitle() == title) {
            Movie m = movie;
            repository->remove(index);
            unique_ptr<Action> action = make_unique<ActionRemove>(m, *this->repository);
            undoStack.push(std::move(action));
            while(!redoStack.empty())
                redoStack.pop();
            return;
        }
        index++;
    }
    throw MovieServiceException(3);
}

void MovieService::updateMovie(const string& title, const string& genre, const int& yearOfRelease, const int& numberOfLikes, const string& trailer){
    auto repo = repository->getElements();
    int index = 0;
    for (auto& movie : repo){
        if (movie.getTitle() == title) {
            Movie mInitial = movie, mNew = Movie(title, genre, yearOfRelease, numberOfLikes, trailer);
            repository->replace(index, mNew);
            unique_ptr<Action> action = make_unique<ActionUpdate>(mInitial, mNew, *this->repository);
            undoStack.push(std::move(action));
            while(!redoStack.empty())
                redoStack.pop();
            return;
        }
        index++;
    }
    throw MovieServiceException(3);
}

Repository* MovieService::getAllMovies() const{
    return repository;
}

FileRepository* MovieService::getWatchlist() const{
    return watchlist;
}

Repository* MovieService::getGenreList(const string& genre) const {
    auto* genre_list = new Repository;
    auto repo = repository->getElements();
    for (auto& movie : repo)
        if ((int)movie.getGenre().find(genre) !=-1)
            genre_list->add(movie);
    return genre_list;
}

void MovieService::deleteMovie(const string& title) {
    auto repo = watchlist->getElements();
    int index = 0;
    for (auto& movie : repo) {
        if (movie.getTitle() == title) {
            watchlist->remove(index);
            return;
        }
        index++;
    }
    throw MovieServiceException(3);
}

void MovieService::addLike(const string& title) {
    for (int i = 0; i < repository->getLength(); i++){
        if(repository->getElements()[i].getTitle() == title){
            repository->getElements()[i].addLike();
            return;
        }
    }
}

void MovieService::addMovieWatchlist(const Movie& movie){
    if (isName(movie.getTitle(), this->watchlist->getElements()))
        throw MovieServiceException(4);
    watchlist->add(movie);
}

void MovieService::undo() {
    if (!undoStack.empty()) {
        this->undoStack.top()->executeUndo();
        this->redoStack.push(std::move(undoStack.top()));
        this->undoStack.pop();
    }
    else throw MovieServiceException(5);
}
void MovieService::redo(){
    if (!redoStack.empty()) {
        this->redoStack.top()->executeRedo();
        this->undoStack.push(std::move(redoStack.top()));
        this->redoStack.pop();
    }
    else throw MovieServiceException(6);
}