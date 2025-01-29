#include "Repository.h"

int Repository::getLength() const {
    return (int)elements.size();
}
vector<Movie>& Repository::getElements(){
    return elements;
}
void Repository::add(const Movie& element) {
    elements.push_back(element);
}
void Repository::remove(int index) {
    if (index < 0 || index >= this->getLength()) {
        return;
    }
    elements.erase(elements.begin() + index);
}
void Repository::replace(int index, const Movie& element) {
    if (index < 0 || index >= this->getLength()) {
        return;
    }
    elements[index] = element;
}
Repository::~Repository() = default;
Repository::Repository() = default;


void Repository::removeEl(const Movie& element) {
    int index = 0;
    while (index < this->getLength()) {
        if (this->elements[index].getTitle() == element.getTitle()){
            elements.erase(elements.begin() + index);
            return;
        }
        index++;
    }
}

void Repository::replaceEl(const Movie& what, const Movie& element) {
    int index = 0;
    while (index < this->getLength()) {
        if (this->elements[index].getTitle() == what.getTitle()){
            elements[index] = element;
            return;
        }
        index++;
    }
}