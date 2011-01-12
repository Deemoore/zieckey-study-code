#include <qapplication.h>
#include "cmainwidget.h"

int main( int argc, char ** argv )
{
    QApplication a( argc, argv );
    CMainWidget w;
    w.show();
    a.connect( &a, SIGNAL( lastWindowClosed() ), &a, SLOT( quit() ) );
    return a.exec();
}
