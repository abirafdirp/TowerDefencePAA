#ifndef MYAPPLICATION
#define MYAPPLICATION

#include <QApplication>
#include "Game.h"

class MyApplication:public QApplication
{
public:
    MyApplication(int argc, char*argv[]);
};

#endif // MYAPPLICATION

