#ifndef MYAPPLICATION
#define MYAPPLICATION

#include <QApplication>


class MyApplication:public QApplication
{
public:
    MyApplication(int argc, char*argv[]);
    static void delay(int msecs);
};

#endif // MYAPPLICATION

