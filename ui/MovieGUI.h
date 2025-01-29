#include "../controller/MovieServices.h"
#include <qwidget.h>
#include <qlistwidget.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qlabel.h>
#include <QPlainTextEdit>
#include "MovieUI.h"
#include <QMessageBox>
#include <QShortcut>
#include <QTableView>
#include "MyTableView.h"
class MovieGUI: public QWidget
{
private:
    MovieService* services;
    QHBoxLayout* mainLayout;
    QGridLayout* gridWidget;
    QLineEdit* titleEdit;
    QLineEdit* genreEdit;
    QLineEdit* yearEdit;
    QLineEdit* likesEdit;
    QLineEdit* trailerEdit;

    QPushButton* addButton;
    QPushButton* removeButton;
    QPushButton* updateButton;
    QPushButton* displayButton;
    QPushButton* submitButton;
    QPushButton* goBackButton;
    QPushButton* searchButton;
    QPushButton* nextButton;
    QPushButton* exitButton;
    QPushButton* redoButton;
    QPushButton* undoButton;
    int currentIndex;
    Repository* movies;
    QListWidget* movieListWidget;

    QShortcut* undoShortcut;
    QShortcut* redoShortcut;

    QTableView* movieTableView;
    MyTableView* movieTableModel;

    QShortcut* submitShortcut;
    QShortcut* backShortcut;
    QShortcut* oneShortcut;
    QShortcut* twoShortcut;
    QShortcut* threeShortcut;
    QShortcut* fourShortcut;
    QShortcut* nextShortcut;

public:
    MovieGUI();
    ~MovieGUI();

private:
    void adminMenu();
    void displayHandler();
    void addButtonHandler();
    void removeButtonHandler();
    void updateButtonHandler();
    void submitAddHandler();
    void submitRemoveHandler();
    void submitUpdateHandler();

    void userMenu();
    void displayUserHandler();
    void deleteButtonHandler();
    void submitDeleteHandler();
    void searchHandler();
    void submitSearchHandler();
    void addUserHandler();
    void nextUserHandler();
    void movieMenu();

    void undo();
    void redo();
    void populateList();
    void populateWatchList();
    void populateWatchList2();

};


