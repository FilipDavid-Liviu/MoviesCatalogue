#include "MovieGUI.h"
void clearLayout(QLayout *layout) {
    QLayoutItem *item;
    while ((item = layout->takeAt(0)) != nullptr) {
        QWidget *widget = item->widget();
            delete widget;
        delete item;
    }
}

MovieGUI::MovieGUI() {
    this->resize(600, 400);
    this->setWindowTitle("Movies App");

    QMessageBox msgBox;
    msgBox.setWindowTitle("Open");
    msgBox.setText("How to open up the app?");
    QPushButton *adminButton = msgBox.addButton("ADMIN", QMessageBox::ActionRole);
    QPushButton *userButton = msgBox.addButton("USER", QMessageBox::ActionRole);
    msgBox.exec();

    mainLayout = new QHBoxLayout{ this };
    movieListWidget = new QListWidget{};
    this->movieListWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    this->movieListWidget->setFixedSize(500, 500);
    gridWidget = new QGridLayout{};
    mainLayout->addLayout(gridWidget);
    mainLayout->addWidget(this->movieListWidget);

    this->movieTableView = new QTableView(this);
    this->movieTableModel = new MyTableView(this);
    this->movieTableView->setModel(this->movieTableModel);
    this->movieTableView->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    this->movieTableView->setFixedSize(950, 300);
    mainLayout->addWidget(this->movieTableView);
    submitShortcut = new QShortcut(QKeySequence("Return"), this);
    backShortcut = new QShortcut(QKeySequence("Backspace"), this);
    oneShortcut = new QShortcut(QKeySequence("1"), this);
    twoShortcut = new QShortcut(QKeySequence("2"), this);
    threeShortcut = new QShortcut(QKeySequence("3"), this);
    fourShortcut = new QShortcut(QKeySequence("4"), this);

    string fileType;
    if (msgBox.clickedButton() == userButton) {
        this->resize(800, 400);
        QMessageBox msgBoxRepo;
        msgBoxRepo.setWindowTitle("Choose File Type");
        msgBoxRepo.setText("Please choose the file type:");
        QPushButton *csvButton = msgBoxRepo.addButton("CSV", QMessageBox::ActionRole);
        QPushButton *htmlButton = msgBoxRepo.addButton("HTML", QMessageBox::ActionRole);
        msgBoxRepo.exec();
        if (msgBoxRepo.clickedButton() == csvButton) {
            fileType = "Csv";
        } else if (msgBoxRepo.clickedButton() == htmlButton) {
            fileType = "Html";
        }
        services = new MovieService(fileType);
        nextShortcut = new QShortcut(QKeySequence("Space"), this);
        this->userMenu();
    } else if (msgBox.clickedButton() == adminButton) {
        fileType = "";
        services = new MovieService(fileType);
        undoShortcut = new QShortcut(QKeySequence("Ctrl+Z"), this);
        redoShortcut = new QShortcut(QKeySequence("Ctrl+Y"), this);
        QObject::connect(undoShortcut, &QShortcut::activated, this, &MovieGUI::undo);
        QObject::connect(redoShortcut, &QShortcut::activated, this, &MovieGUI::redo);
        this->adminMenu();
    }
}

MovieGUI::~MovieGUI() {
    delete services;
    clearLayout(gridWidget);
    delete gridWidget;
    delete mainLayout;
}
void setwidget(QWidget* a){
    a->setFixedWidth(200);
    a->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    a->setStyleSheet(
            "font-weight: bold; "
            // "font-family: Arial; "  // Uncomment to test Arial
            // "font-family: 'Times New Roman'; "  // Uncomment to test Times New Roman
            // "font-family: 'Courier New'; "  // Uncomment to test Courier New
            // "font-family: Georgia; "  // Uncomment to test Georgia
            //"font-family: Verdana; "  // Uncomment to test Verdana
            // "font-family: Tahoma; "  // Uncomment to test Tahoma
            // "font-family: 'Trebuchet MS'; "  // Uncomment to test Trebuchet MS
            // "font-family: 'Comic Sans MS'; "  // Uncomment to test Comic Sans MS
            // "font-family: Impact; "  // Uncomment to test Impact
            // "font-family: 'Lucida Console'; "  // Uncomment to test Lucida Console
            // "font-family: 'Palatino Linotype'; "  // Uncomment to test Palatino Linotype
            "font-size: 12px;"
    );
}
void MovieGUI::adminMenu() {
    this->movieListWidget->show();
    this->movieTableView->hide();
    this->populateList();
    clearLayout(gridWidget);
    this->addButton = new QPushButton{ "Add" };
    this->removeButton = new QPushButton{"Remove" };
    this->updateButton = new QPushButton{ "Update" };
    this->displayButton = new QPushButton{ "Display" };
    this->goBackButton = new QPushButton{ "Go back" };
    this->submitButton = new QPushButton{ "Submit" };
    this->undoButton = new QPushButton{ "UNDO" };
    this->redoButton = new QPushButton{ "REDO" };

    gridWidget->addWidget(this->addButton, 1, 1);
    gridWidget->addWidget(this->removeButton, 2, 1);
    gridWidget->addWidget(this->updateButton, 3, 1);
    gridWidget->addWidget(this->displayButton, 4, 1);
    gridWidget->addWidget(this->undoButton, 5, 1);
    gridWidget->addWidget(this->redoButton, 6, 1);

    setwidget(addButton);
    setwidget(removeButton);
    setwidget(updateButton);
    setwidget(displayButton);
    setwidget(undoButton);
    setwidget(redoButton);

    QObject::connect(this->addButton, &QPushButton::clicked, this, &MovieGUI::addButtonHandler);
    QObject::connect(this->removeButton, &QPushButton::clicked, this, &MovieGUI::removeButtonHandler);
    QObject::connect(this->updateButton, &QPushButton::clicked, this, &MovieGUI::updateButtonHandler);
    QObject::connect(this->displayButton, &QPushButton::clicked, this, &MovieGUI::displayHandler);
    QObject::connect(this->undoButton, &QPushButton::clicked, this, &MovieGUI::undo);
    QObject::connect(this->redoButton, &QPushButton::clicked, this, &MovieGUI::redo);

    QObject::disconnect(this->submitShortcut, &QShortcut::activated, this, &MovieGUI::submitAddHandler);
    QObject::disconnect(this->submitShortcut, &QShortcut::activated, this, &MovieGUI::submitRemoveHandler);
    QObject::disconnect(this->submitShortcut, &QShortcut::activated, this, &MovieGUI::submitUpdateHandler);
    QObject::disconnect(this->backShortcut, &QShortcut::activated, this, &MovieGUI::adminMenu);


    QObject::connect(this->oneShortcut, &QShortcut::activated, this, &MovieGUI::addButtonHandler);
    QObject::connect(this->twoShortcut, &QShortcut::activated, this, &MovieGUI::removeButtonHandler);
    QObject::connect(this->threeShortcut, &QShortcut::activated, this, &MovieGUI::updateButtonHandler);
    QObject::connect(this->fourShortcut, &QShortcut::activated, this, &MovieGUI::displayHandler);
}

void MovieGUI::undo() {
    try {
        this->services->undo();
        this->populateList();
    } catch (MovieServiceException& e) {
        QMessageBox::warning(this, "Warning", e.message().c_str());
    }
}

void MovieGUI::redo() {
    try {
        this->services->redo();
        this->populateList();
    } catch (MovieServiceException& e) {
        QMessageBox::warning(this, "Warning", e.message().c_str());
    }
}

void MovieGUI::populateList()
{
    this->movieListWidget->clear();
    for (const auto& m : this->services->getAllMovies()->getElements())
    {
        this->movieListWidget->addItem(QString::fromStdString(m.toString()));
    }
}
void MovieGUI::populateWatchList()
{
    this->movieListWidget->clear();
    for (const auto& m : this->services->getWatchlist()->getElements())
    {
        this->movieListWidget->addItem(QString::fromStdString(m.toString()));
    }
}
void MovieGUI::populateWatchList2() {
    const auto& watchlistMovies = this->services->getWatchlist()->getElements();
    this->movieTableModel->setMovies(watchlistMovies);
    this->movieTableView->resizeColumnsToContents();
}
void MovieGUI::displayHandler() {
    movieListWidget->hide();
    clearLayout(gridWidget);
    auto *moviesTextEdit = new QPlainTextEdit{this};
    moviesTextEdit->setReadOnly(true);
    moviesTextEdit->setPlainText("");

    auto repo = this->services->getAllMovies();
    for (auto& s : repo->getElements())
    {
        moviesTextEdit->appendPlainText(QString::fromStdString(s.toString()));
        moviesTextEdit->appendPlainText(QString::fromStdString("--------------------------------------------------------------\n"));
    }
    gridWidget->addWidget(moviesTextEdit, 1 , 1);
    gridWidget->addWidget(this->goBackButton, 2, 1);
    setwidget(goBackButton);

    QObject::connect(this->goBackButton, &QPushButton::clicked, this, &MovieGUI::adminMenu);

    QObject::connect(this->backShortcut, &QShortcut::activated, this, &MovieGUI::adminMenu);
    QObject::disconnect(this->oneShortcut, &QShortcut::activated, this, &MovieGUI::addButtonHandler);
    QObject::disconnect(this->twoShortcut, &QShortcut::activated, this, &MovieGUI::removeButtonHandler);
    QObject::disconnect(this->threeShortcut, &QShortcut::activated, this, &MovieGUI::updateButtonHandler);
    QObject::disconnect(this->fourShortcut, &QShortcut::activated, this, &MovieGUI::displayHandler);
}

void MovieGUI::addButtonHandler() {
    clearLayout(gridWidget);
    auto* titleLabel = new QLabel{"Title" };
    this->titleEdit = new QLineEdit{};
    auto* genreLabel = new QLabel{"Genre" };
    this->genreEdit = new QLineEdit{};
    auto* yearLabel = new QLabel{"Year of Release" };
    this->yearEdit = new QLineEdit{};
    auto* likesLabel = new QLabel{"Number of Likes" };
    this->likesEdit = new QLineEdit{};
    auto* trailerLabel = new QLabel{ "Trailer" };
    this->trailerEdit = new QLineEdit{};
    setwidget(titleLabel);
    setwidget(genreLabel);
    setwidget(yearLabel);
    setwidget(likesLabel);
    setwidget(trailerLabel);

    gridWidget->addWidget(titleLabel, 0, 0);
    gridWidget->addWidget(this->titleEdit, 0, 1);
    gridWidget->addWidget(genreLabel, 1, 0);
    gridWidget->addWidget(this->genreEdit, 1, 1);
    gridWidget->addWidget(yearLabel, 2, 0);
    gridWidget->addWidget(this->yearEdit, 2, 1);
    gridWidget->addWidget(likesLabel, 3, 0);
    gridWidget->addWidget(this->likesEdit, 3, 1);
    gridWidget->addWidget(trailerLabel, 4, 0);
    gridWidget->addWidget(this->trailerEdit, 4, 1);


    gridWidget->addWidget(this->submitButton, 5, 0);
    gridWidget->addWidget(this->goBackButton, 5, 1);


    setwidget(submitButton);
    setwidget(goBackButton);

    QObject::connect(this->goBackButton, &QPushButton::clicked, this, &MovieGUI::adminMenu);
    QObject::connect(this->submitButton, &QPushButton::clicked, this, &MovieGUI::submitAddHandler);

    QObject::connect(this->submitShortcut, &QShortcut::activated, this, &MovieGUI::submitAddHandler);
    QObject::connect(this->backShortcut, &QShortcut::activated, this, &MovieGUI::adminMenu);
    QObject::disconnect(this->oneShortcut, &QShortcut::activated, this, &MovieGUI::addButtonHandler);
    QObject::disconnect(this->twoShortcut, &QShortcut::activated, this, &MovieGUI::removeButtonHandler);
    QObject::disconnect(this->threeShortcut, &QShortcut::activated, this, &MovieGUI::updateButtonHandler);
    QObject::disconnect(this->fourShortcut, &QShortcut::activated, this, &MovieGUI::displayHandler);

}

void MovieGUI::removeButtonHandler() {
    clearLayout(gridWidget);
    auto* titleLabel = new QLabel{"Title" };
    this->titleEdit = new QLineEdit{};
    setwidget(titleLabel);

    gridWidget->addWidget(titleLabel, 0, 0);
    gridWidget->addWidget(this->titleEdit, 0, 1);


    gridWidget->addWidget(this->submitButton, 5, 0);
    gridWidget->addWidget(this->goBackButton, 5, 1);


    setwidget(submitButton);
    setwidget(goBackButton);

    QObject::connect(this->goBackButton, &QPushButton::clicked, this, &MovieGUI::adminMenu);
    QObject::connect(this->submitButton, &QPushButton::clicked, this, &MovieGUI::submitRemoveHandler);

    QObject::connect(this->submitShortcut, &QShortcut::activated, this, &MovieGUI::submitRemoveHandler);
    QObject::connect(this->backShortcut, &QShortcut::activated, this, &MovieGUI::adminMenu);
    QObject::disconnect(this->oneShortcut, &QShortcut::activated, this, &MovieGUI::addButtonHandler);
    QObject::disconnect(this->twoShortcut, &QShortcut::activated, this, &MovieGUI::removeButtonHandler);
    QObject::disconnect(this->threeShortcut, &QShortcut::activated, this, &MovieGUI::updateButtonHandler);
    QObject::disconnect(this->fourShortcut, &QShortcut::activated, this, &MovieGUI::displayHandler);

}

void MovieGUI::updateButtonHandler() {
    clearLayout(gridWidget);
    auto* titleLabel = new QLabel{"Title" };
    this->titleEdit = new QLineEdit{};
    auto* genreLabel = new QLabel{"New Genre" };
    this->genreEdit = new QLineEdit{};
    auto* yearLabel = new QLabel{"New Year of Release" };
    this->yearEdit = new QLineEdit{};
    auto* likesLabel = new QLabel{"New Number of Likes" };
    this->likesEdit = new QLineEdit{};
    auto* trailerLabel = new QLabel{ "New Trailer" };
    this->trailerEdit = new QLineEdit{};
    setwidget(titleLabel);
    setwidget(genreLabel);
    setwidget(yearLabel);
    setwidget(likesLabel);
    setwidget(trailerLabel);

    gridWidget->addWidget(titleLabel, 0, 0);
    gridWidget->addWidget(this->titleEdit, 0, 1);
    gridWidget->addWidget(genreLabel, 1, 0);
    gridWidget->addWidget(this->genreEdit, 1, 1);
    gridWidget->addWidget(yearLabel, 2, 0);
    gridWidget->addWidget(this->yearEdit, 2, 1);
    gridWidget->addWidget(likesLabel, 3, 0);
    gridWidget->addWidget(this->likesEdit, 3, 1);
    gridWidget->addWidget(trailerLabel, 4, 0);
    gridWidget->addWidget(this->trailerEdit, 4, 1);


    gridWidget->addWidget(this->submitButton, 5, 0);
    gridWidget->addWidget(this->goBackButton, 5, 1);


    setwidget(submitButton);
    setwidget(goBackButton);

    QObject::connect(this->goBackButton, &QPushButton::clicked, this, &MovieGUI::adminMenu);
    QObject::connect(this->submitButton, &QPushButton::clicked, this, &MovieGUI::submitUpdateHandler);

    QObject::connect(this->submitShortcut, &QShortcut::activated, this, &MovieGUI::submitUpdateHandler);
    QObject::connect(this->backShortcut, &QShortcut::activated, this, &MovieGUI::adminMenu);
    QObject::disconnect(this->oneShortcut, &QShortcut::activated, this, &MovieGUI::addButtonHandler);
    QObject::disconnect(this->twoShortcut, &QShortcut::activated, this, &MovieGUI::removeButtonHandler);
    QObject::disconnect(this->threeShortcut, &QShortcut::activated, this, &MovieGUI::updateButtonHandler);
    QObject::disconnect(this->fourShortcut, &QShortcut::activated, this, &MovieGUI::displayHandler);

}
void MovieGUI::submitAddHandler() {
    string title = titleEdit->text().toStdString();
    string genre = genreEdit->text().toStdString();
    int year = yearEdit->text().toInt();
    int likes = likesEdit->text().toInt();
    string trailer = trailerEdit->text().toStdString();

    normalizeName(title);
    normalizeName(genre);

    try {
        services->addMovie(title, genre, year, likes, trailer);
        this->populateList();
        QMessageBox::information(this, "Success", "Movie added successfully.");
    } catch (MovieServiceException& e) {
        QMessageBox::warning(this, "Error", e.message().c_str());
    }
}

void MovieGUI::submitRemoveHandler() {
    string title = titleEdit->text().toStdString();
    normalizeName(title);
    try {
        services->removeMovie(title);
        this->populateList();
        QMessageBox::information(this, "Success", "Movie removed successfully.");
    } catch (MovieServiceException& e) {
        QMessageBox::warning(this, "Error", e.message().c_str());
    }
}

void MovieGUI::submitUpdateHandler() {
    string title = titleEdit->text().toStdString();
    string genre = genreEdit->text().toStdString();
    int year = yearEdit->text().toInt();
    int likes = likesEdit->text().toInt();
    string trailer = trailerEdit->text().toStdString();

    normalizeName(title);
    normalizeName(genre);

    try {
        services->updateMovie(title, genre, year, likes, trailer);
        this->populateList();
        QMessageBox::information(this, "Success", "Movie updated successfully.");
    } catch (MovieServiceException& e) {
        QMessageBox::warning(this, "Error", e.message().c_str());
    }
}


void MovieGUI::userMenu() {
    this->movieListWidget->hide();
    this->movieTableView->show();
    this->populateWatchList2();
    clearLayout(gridWidget);

    this->searchButton = new QPushButton{ "Search" };
    this->removeButton = new QPushButton{"Delete" };
    this->displayButton = new QPushButton{ "Display Watchlist" };
    this->goBackButton = new QPushButton{ "Go back" };
    this->submitButton = new QPushButton{ "Submit" };

    gridWidget->addWidget(this->searchButton, 1, 1);
    gridWidget->addWidget(this->removeButton, 2, 1);
    gridWidget->addWidget(this->displayButton, 3, 1);

    setwidget(searchButton);
    setwidget(removeButton);
    setwidget(displayButton);
    setwidget(submitButton);

    QObject::connect(this->searchButton, &QPushButton::clicked, this, &MovieGUI::searchHandler);
    QObject::connect(this->removeButton, &QPushButton::clicked, this, &MovieGUI::deleteButtonHandler);
    QObject::connect(this->displayButton, &QPushButton::clicked, this, &MovieGUI::displayUserHandler);

    QObject::disconnect(this->submitShortcut, &QShortcut::activated, this, &MovieGUI::submitSearchHandler);
    QObject::disconnect(this->submitShortcut, &QShortcut::activated, this, &MovieGUI::submitDeleteHandler);
    QObject::disconnect(this->submitShortcut, &QShortcut::activated, this, &MovieGUI::addUserHandler);
    QObject::disconnect(this->backShortcut, &QShortcut::activated, this, &MovieGUI::userMenu);
    QObject::disconnect(this->nextShortcut, &QShortcut::activated, this, &MovieGUI::nextUserHandler);
    QObject::connect(this->oneShortcut, &QShortcut::activated, this, &MovieGUI::searchHandler);
    QObject::connect(this->twoShortcut, &QShortcut::activated, this, &MovieGUI::deleteButtonHandler);
    QObject::connect(this->threeShortcut, &QShortcut::activated, this, &MovieGUI::displayUserHandler);
}

void MovieGUI::displayUserHandler() {
    string file = "movie_watchlist";
    services->getWatchlist()->writeToUserFile(file);
}

void MovieGUI::deleteButtonHandler()
{
    clearLayout(gridWidget);
    auto* titleLabel = new QLabel{"Title" };
    this->titleEdit = new QLineEdit{};
    setwidget(titleLabel);

    gridWidget->addWidget(titleLabel, 0, 0);
    gridWidget->addWidget(this->titleEdit, 0, 1);


    gridWidget->addWidget(this->submitButton, 5, 0);
    gridWidget->addWidget(this->goBackButton, 5, 1);


    setwidget(submitButton);
    setwidget(goBackButton);

    QObject::connect(this->goBackButton, &QPushButton::clicked, this, &MovieGUI::userMenu);
    QObject::connect(this->submitButton, &QPushButton::clicked, this, &MovieGUI::submitDeleteHandler);

    QObject::connect(this->submitShortcut, &QShortcut::activated, this, &MovieGUI::submitDeleteHandler);
    QObject::connect(this->backShortcut, &QShortcut::activated, this, &MovieGUI::userMenu);
    QObject::disconnect(this->oneShortcut, &QShortcut::activated, this, &MovieGUI::searchHandler);
    QObject::disconnect(this->twoShortcut, &QShortcut::activated, this, &MovieGUI::deleteButtonHandler);
    QObject::disconnect(this->threeShortcut, &QShortcut::activated, this, &MovieGUI::displayUserHandler);
}

void MovieGUI::submitDeleteHandler() {
    string title = titleEdit->text().toStdString();
    normalizeName(title);
    try{
        services->deleteMovie(title);
        QMessageBox msgBox;
        msgBox.setWindowTitle("Like");
        msgBox.setText("Did you like the movie?");
        QPushButton *yButton = msgBox.addButton("Yes", QMessageBox::ActionRole);
        msgBox.addButton("No", QMessageBox::ActionRole);
        msgBox.exec();

        if (msgBox.clickedButton() == yButton)
            services->addLike(title);
        this->userMenu();
    } catch (MovieServiceException& e) {
    QMessageBox::warning(this, "Error", e.message().c_str());
    }
}

void MovieGUI::searchHandler(){
    movieListWidget->hide();
    clearLayout(gridWidget);
    auto* genreLabel = new QLabel{"Genre" };
    this->genreEdit = new QLineEdit{};
    setwidget(genreLabel);

    gridWidget->addWidget(genreLabel, 0, 0);
    gridWidget->addWidget(this->genreEdit, 0, 1);


    gridWidget->addWidget(this->submitButton, 5, 0);
    gridWidget->addWidget(this->goBackButton, 5, 1);


    setwidget(submitButton);
    setwidget(goBackButton);

    QObject::connect(this->goBackButton, &QPushButton::clicked, this, &MovieGUI::userMenu);
    QObject::connect(this->submitButton, &QPushButton::clicked, this, &MovieGUI::submitSearchHandler);

    QObject::connect(this->submitShortcut, &QShortcut::activated, this, &MovieGUI::submitSearchHandler);
    QObject::connect(this->backShortcut, &QShortcut::activated, this, &MovieGUI::userMenu);
    QObject::disconnect(this->oneShortcut, &QShortcut::activated, this, &MovieGUI::searchHandler);
    QObject::disconnect(this->twoShortcut, &QShortcut::activated, this, &MovieGUI::deleteButtonHandler);
    QObject::disconnect(this->threeShortcut, &QShortcut::activated, this, &MovieGUI::displayUserHandler);
}

void MovieGUI::submitSearchHandler() {
    string genre = genreEdit->text().toStdString();
    normalizeName(genre);
    movies = services->getGenreList(genre);
    if (movies->getLength() == 0){
        QMessageBox::warning(this, "Warning", "No such genre in the database");
    }
    else{
        currentIndex = 0;
        this->movieMenu();
    }
}

void MovieGUI::movieMenu() {
    clearLayout(gridWidget);
    auto *moviesTextEdit = new QPlainTextEdit{this};
    moviesTextEdit->setReadOnly(true);
    moviesTextEdit->setPlainText(QString::fromStdString(movies->getElements()[currentIndex].toString()));
    gridWidget->addWidget(moviesTextEdit, 0, 1);
    //string command = "start firefox \"" + movies->getElements()[currentIndex].getTrailer() + "\"";
    //system(command.c_str());
    this->nextButton = new QPushButton{ "Next" };
    this->addButton = new QPushButton{ "Add" };
    this->exitButton = new QPushButton{ "Exit" };
    gridWidget->addWidget(nextButton, 2, 1);
    gridWidget->addWidget(addButton, 1, 1);
    gridWidget->addWidget(exitButton, 3, 1);
    setwidget(nextButton);
    setwidget(addButton);
    setwidget(exitButton);
    QObject::connect(this->addButton, &QPushButton::clicked, this, &MovieGUI::addUserHandler);
    QObject::connect(this->nextButton, &QPushButton::clicked, this, &MovieGUI::nextUserHandler);
    QObject::connect(this->exitButton, &QPushButton::clicked, this, &MovieGUI::userMenu);

    QObject::disconnect(this->submitShortcut, &QShortcut::activated, this, &MovieGUI::submitSearchHandler);
    QObject::disconnect(this->submitShortcut, &QShortcut::activated, this, &MovieGUI::addUserHandler);
    QObject::disconnect(this->nextShortcut, &QShortcut::activated, this, &MovieGUI::nextUserHandler);
    QObject::disconnect(this->backShortcut, &QShortcut::activated, this, &MovieGUI::userMenu);
    QObject::connect(this->submitShortcut, &QShortcut::activated, this, &MovieGUI::addUserHandler);
    QObject::connect(this->nextShortcut, &QShortcut::activated, this, &MovieGUI::nextUserHandler);
    QObject::connect(this->backShortcut, &QShortcut::activated, this, &MovieGUI::userMenu);
}

void MovieGUI::addUserHandler() {
    try {
        services->addMovieWatchlist(movies->getElements()[currentIndex]);
        this->populateWatchList2();
    } catch (MovieServiceException& e) {
        QMessageBox::warning(this, "Warning", e.message().c_str());
    }
    currentIndex = (currentIndex + 1) % movies->getLength();
    movieMenu();
}

void MovieGUI::nextUserHandler() {
    currentIndex = (currentIndex + 1) % movies->getLength();
    movieMenu();
}