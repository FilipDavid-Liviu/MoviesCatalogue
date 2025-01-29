#pragma once
#include <vector>
#include <algorithm>
#include <fstream>
#include "../domain/Movie.h"
class Repository {
protected:
    vector<Movie> elements;

public:
    Repository();

    ~Repository();

    int getLength() const;

    vector<Movie>& getElements();

    void add(const Movie& element);

    void remove(int index);

    void removeEl(const Movie& element);

    void replace(int index, const Movie& element);

    void replaceEl(const Movie& what, const Movie& element);

};


class FileRepository: public Repository{
private:
    void readFromFile();

    void writeToFile();
protected:
    string filename;

public:
    explicit FileRepository(std::string filename);

    ~FileRepository();

    virtual void writeToUserFile(string& name_file);

};

class CSVRepository: public FileRepository{
public:
    explicit CSVRepository(std::string filename);
    void writeToUserFile(string& name_file) override;

};

class HTMLRepository: public FileRepository{
public:
    explicit HTMLRepository(std::string filename);
    void writeToUserFile(string& name_file) override;

};