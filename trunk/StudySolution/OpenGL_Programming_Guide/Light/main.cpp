#include "light1.h"

int main( int argc, char* argv[] )
{ 
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH );
    glutInitWindowSize( 500, 500 );
    glutInitWindowPosition( 100, 100 );
    glutCreateWindow( "Light" );
    init();
    glutDisplayFunc( &display );
    glutReshapeFunc( &reshape );
    glutMainLoop();

    return 0;
}