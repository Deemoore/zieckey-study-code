//#include "lines.h"
#include "polys.h"

int main( int argc, char* argv[] )
{ 
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH );
    glutInitWindowSize( 800, 800 );
    glutInitWindowPosition( 100, 100 );
    glutCreateWindow( "Chapter2" );
    init();
    glutDisplayFunc( &display );
    glutReshapeFunc( &reshape );
    glutMainLoop();

    return 0;
}