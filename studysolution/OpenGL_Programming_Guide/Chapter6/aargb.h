#include "common.h"

static float rotAngle = 0.0f;

void init()
{
	GLfloat values[2];
	glGetFloatv( GL_LINE_WIDTH_GRANULARITY, values );
	printf( "GL_LINE_WIDTH_GRANULARITY value is %3.1f\n",
	        values[0] );
	glGetFloatv( GL_LINE_WIDTH_RANGE, values );
	printf( "GL_LINE_WIDTH_RANGE values are %3.1f %3.1f\n",
	        values[0], values[1] );
	//glEnable( GL_LINE_SMOOTH );//启用抗锯齿功能
    glHint( GL_LINE_SMOOTH_HINT, GL_DONT_CARE );//给出抗锯齿的质量
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	glLineWidth( 20.0 );
	glClearColor( 0.0, 0.0, 0.0, 0.0 );

}


/* Draw 2 diagonal lines to form an X */
void display( void )
{
	glClear( GL_COLOR_BUFFER_BIT );
	glColor3f( 0.0, 1.0, 0.0 );
	glPushMatrix();
	glRotatef( -rotAngle, 0.0, 0.0, 0.1 );
	glBegin( GL_LINES );
	glVertex2f( -100, 100 );
	glVertex2f( 100, -100 );
	glEnd();
	glPopMatrix();
	glColor3f( 0.0, 0.0, 1.0 );
	glPushMatrix();
	glRotatef( rotAngle, 0.0, 0.0, 0.1 );
	glBegin( GL_LINES );
	glVertex2f( 100, 100 );
	glVertex2f( -100, -100 );
	glEnd();
	glPopMatrix();
	glFlush();
}
void reshape( int w, int h )
{
	glViewport( 0, 0, ( GLint ) w, ( GLint ) h );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();

	if ( w <= h )
		gluOrtho2D( -200, 200,
		            -200 * ( GLfloat )h / ( GLfloat )w, 200 * ( GLfloat )h / ( GLfloat )w );
	else
		gluOrtho2D( -200 * ( GLfloat )w / ( GLfloat )h,
		            200 * ( GLfloat )w / ( GLfloat )h, -200, 200 );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
}
void keyboard( unsigned char key, int x, int y )
{
	switch ( key )
	{
		case 'r':
		case 'R':
			rotAngle += 5;

			if ( rotAngle >= 360. )
			{
				rotAngle = 0.;
			}

			glutPostRedisplay();
			break;
        case 'y':
        case 'Y':
            rotAngle -= 5;

            if ( rotAngle <= 0. )
            {
                rotAngle = 360.;
            }

            glutPostRedisplay();
            break;
		case 27: /* Escape Key */
			exit( 0 );
			break;
		default:
			break;

	}
}
int main( int argc, char** argv )
{
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB );
	glutInitWindowSize( 800, 800 );
	glutCreateWindow( "" );
	init();
	glutReshapeFunc( reshape );
	glutKeyboardFunc( keyboard );
	glutDisplayFunc( display );
	glutMainLoop();
	return 0;
}