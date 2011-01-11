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
        glColor3f( 0.0f, 1.0f, 0.0f );//指定线的颜色,绿色
        // x-axis
        glVertex2f( -axislenh, 0.0f);
        glVertex2f( axislenh, 0.0f);

        // x-axis arrow
        glVertex2f( axislenh, 0.0f);
        glVertex2f( axislenh-7, 3.0f);
        glVertex2f( axislenh, 0.0f);
        glVertex2f( axislenh-7,-3.0f);


        glColor3f( 1.0f, 0.0f, 0.0f );//指定线的颜色,红色
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


    /* 一个白色的正方形，先平移再旋转 */
    glLoadIdentity();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef( 100.0f, 0.0f, 0.0f );//沿着x轴移动
    glRotatef( 45, 0.0f, 0.0f, 1.0f );//沿着z轴旋转
    drawsquare(50);


    /* 一个红色的正方形，先旋转再平移 */
    glLoadIdentity();
    glColor3f(1.0, 0.0, 0.0);
    glRotatef( 45, 0.0f, 0.0f, 1.0f );//沿着z轴旋转
    glTranslatef( 100.0f, 0.0f, 0.0f );//沿着x轴移动
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