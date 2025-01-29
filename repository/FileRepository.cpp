#include "Repository.h"

FileRepository::FileRepository(std::string _filename) : filename {std::move(_filename)}
{
    this->readFromFile();
}

FileRepository::~FileRepository(){
    this->writeToFile();
}

void FileRepository::readFromFile() {
    ifstream fin(this->filename);
    Movie movie;

    while (fin >> movie) {
        this->add(movie);
    }

    fin.close();
}

void FileRepository::writeToFile() {
    ofstream fout(this->filename);
    for (const Movie& movie : this->elements)
        fout << movie;
    fout.close();
}

void FileRepository::writeToUserFile(string& name_file){}

string replaceCommas(string& str) {
    for (char& i : str){
        if (i == ',')
            i = ' ';
    }
    return str;
}

void openCSVFile(const std::string& filename) {
    string command = "start excel \"" + filename + "\"";
    system(command.c_str());
}

void openHTMLFile(const std::string& filename) {
    string command = "start firefox \"" + filename + "\"";
    system(command.c_str());
}

void CSVRepository::writeToUserFile(string& name_file) {
    name_file = "../" + name_file + ".csv";
    ofstream fout(name_file);
    for (const Movie& movie : this->elements){
        string title = movie.getTitle(), genre = movie.getGenre();
        fout << replaceCommas(title) << "," << replaceCommas(genre) << ","
             << movie.getYearOfRelease() << "," << movie.getNumberOfLikes() << "," << movie.getTrailer()<<"\n";
    }
    fout.close();
    openCSVFile(name_file);
}

CSVRepository::CSVRepository(std::string filename) : FileRepository(std::move(filename)) {}

HTMLRepository::HTMLRepository(string filename) : FileRepository(std::move(filename)) {}

void HTMLRepository::writeToUserFile(string& name_file) {
    name_file = "../" + name_file + ".html";
    ofstream fout(name_file);
    fout << "<!DOCTYPE html>\n<html>\n<head>\n<title>Movie List</title>\n";
    fout << "<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\">\n";
    fout << "</head>\n<body>\n";

    fout << "<table border=\"1\">\n";
    fout << "<tr class=\"table_head\"><td>Title</td>\n<td>Genre</td>\n<td>Year</td>\n<td>Likes</td>\n<td>Trailer</td>\n</tr>\n";
    for (Movie& movie : this->elements) {
        fout << "<tr>\n";
        fout << "<td>" << movie.getTitle() << "</td>\n";
        fout << "<td>" << movie.getGenre() << "</td>\n";
        fout << "<td>" << movie.getYearOfRelease() << "</td>\n";
        fout << "<td>" << movie.getNumberOfLikes() << "</td>\n";
        fout << "<td><a href=\"" << movie.getTrailer() << "\">Trailer</a></td>\n";
        fout << "</tr>\n";
    }
    fout << "</table>\n";

    fout << "</body>\n</html>";

    fout.close();
    openHTMLFile(name_file);
}
