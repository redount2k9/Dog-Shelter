#include "mywindow.h"
#include <QApplication>
#include <QPushButton>
#include "Repository/Repository.h"
#include "Repository/FileRepository.h"
#include "Domain/Dog.h"
#include "UI/UI.h"
#include "Tests/Tests.h"

int main(int argc, char *argv[])
{
    FileRepository repository("in.txt");
    AdoptionList list;
    Controller controller(repository, list);
    QApplication a(argc, argv);
    MyWindow w{controller};
    w.show();


    return a.exec();
}
