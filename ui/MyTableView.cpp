#include "MyTableView.h"

MyTableView::MyTableView(QObject *parent) : QAbstractTableModel(parent) {}

void MyTableView::setMovies(const std::vector<Movie>& movies) {
    beginResetModel();
    this->movies = movies;
    endResetModel();
}

int MyTableView::rowCount(const QModelIndex& parent) const {
    return movies.size();
}

int MyTableView::columnCount(const QModelIndex& parent) const {
    return 5;
}

QVariant MyTableView::data(const QModelIndex& index, int role) const {
    if (role != Qt::DisplayRole && role != Qt::EditRole)
        return {};

    const Movie movie = movies.at(index.row());

    switch (index.column()) {
        case 0: return QString::fromStdString(movie.getTitle());
        case 1: return QString::fromStdString(movie.getGenre());
        case 2: return movie.getYearOfRelease();
        case 3: return movie.getNumberOfLikes();
        case 4: return QString::fromStdString(movie.getTrailer());
        default: return {};
    }
}

QVariant MyTableView::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole)
        return {};

    if (orientation == Qt::Horizontal) {
        switch (section) {
            case 0: return "Title";
            case 1: return "Genre";
            case 2: return "Release Year";
            case 3: return "Likes";
            case 4: return "Trailer Link";
            default: return {};
        }
    }
    return {};
}