#pragma once
#include "QAbstractTableModel"
#include "Movie.h"
#include <vector>
class MyTableView :public QAbstractTableModel {
    Q_OBJECT
public:
    explicit MyTableView(QObject *parent = nullptr);
    void setMovies(const std::vector<Movie>& movies);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private:
    std::vector<Movie> movies;
};

