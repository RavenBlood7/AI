#include <QCoreApplication>
#include "competative_lvqi.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    a.exec();

    //assuming algorithm is 0
    LVQI* lvqi = new Competative_LVQI("train.data", 3, "test.data", 5);
    lvqi->train();
    cout << lvqi->toString();
    lvqi->toFile("output.file");

    return 0;
}
