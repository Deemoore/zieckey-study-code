#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>

#include <stdio.h>

#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glut32.lib")

void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

void drawsquare( int width )
{
    glRecti( -width/2, -width/2, width/2, width/2 );
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    //draw axis
    {
        const float axislen = 300.0f;
        const float axislenh = axislen/2;
        glBegin(GL_LINES);
        glColor3f( 0.0f, 1.0f, 0.0f );//ָ���ߵ���ɫ,��ɫ
        // x-axis
        glVertex2f( -axislenh, 0.0f);
        glVertex2f( axislenh, 0.0f);

        // x-axis arrow
        glVertex2f( axislenh, 0.0f);
        glVertex2f( axislenh-7, 3.0f);
        glVertex2f( axislenh, 0.0f);
        glVertex2f( axislenh-7,-3.0f);


        glColor3f( 1.0f, 0.0f, 0.0f );//ָ���ߵ���ɫ,��ɫ
        // y-axis
        glVertex2f( 0.0f, -axislenh);
        glVertex2f( 0.0f, axislenh);
        glVertex2f( 0.0f, axislenh);
        glVertex2f( 3.0f, axislenh-7);
        glVertex2f( 0.0f, axislenh);
        glVertex2f( -3.0f, axislenh-7);
        glEnd();
    }

    glMatrixMode( GL_MODELVIEW );
    glPushMatrix();


    /* һ����ɫ�������Σ���ƽ������ת */
    glLoadIdentity();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef( 100.0f, 0.0f, 0.0f );//����x���ƶ�
    glRotatef( 45, 0.0f, 0.0f, 1.0f );//����z����ת
    drawsquare(50);


    /* һ����ɫ�������Σ�����ת��ƽ�� */
    glLoadIdentity();
    glColor3f(1.0, 0.0, 0.0);
    glRotatef( 45, 0.0f, 0.0f, 1.0f );//����z����ת
    glTranslatef( 100.0f, 0.0f, 0.0f );//����x���ƶ�
    drawsquare(50);

    glPopMatrix();
    glFlush();
}

void reshape( int w, int h )
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-(GLdouble) w/2, (GLdouble) w/2, -(GLdouble) h/2, (GLdouble) h/2);
};

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