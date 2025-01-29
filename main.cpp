#include "./ui/MovieUI.h"
#include "./ui/MovieGUI.h"
#include <QtWidgets/QApplication>

using namespace std;
int main(int argc, char** argv) {

    QApplication a(argc, argv);
    MovieGUI gui;
    gui.show();
    return QApplication::exec();
    //MovieUI ui;
    //ui.run();
    //return 0;
}