#include <qapplication.h>
#include "cmaindialog.h"

int main( int argc, char ** argv )
{
    QApplication a( argc, argv );
    CMainDialog w;
    w.show();
    a.connect( &a, SIGNAL( lastWindowClosed() ), &a, SLOT( quit() ) );
    return a.exec();
}
