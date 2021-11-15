#include "simplelangmuirprobe.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SimpleLangmuirProbe w;
    w.show();
    return a.exec();
}
