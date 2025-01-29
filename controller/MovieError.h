#pragma once
#include <iostream>
using namespace std;

class MovieServiceException : exception{
private:
    string messageError;
public:
    explicit MovieServiceException(int code){
        this->messageError = "ERROR";
        switch (code) {
            case 1:
                this->messageError += ": There is already a movie with that name!\n";
                break;
            case 2:
                this->messageError += ": The number of likes should be positive!\n";
                break;
            case 3:
                this->messageError += ": There is no movie with that name!\n";
                break;
            case 4:
                this->messageError = "Movie already in watchlist! Go watch it!\n";
                break;
            case 5:
                this->messageError = "No undo available!\n";
                break;
            case 6:
                this->messageError = "No redo available!\n";
                break;
            default:
                break;
        }
    }

    string& message(){ return messageError;}
};