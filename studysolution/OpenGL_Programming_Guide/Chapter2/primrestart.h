#pragma once

#include "common.h"

#define BUFFER_OFFSET(offset) ((GLvoid *) NULL + offset)
#define XStart -0.8
#define XEnd 0.8
#define YStart -0.8
#define YEnd 0.8
#define NumXPoints 11
#define NumYPoints 11
#define NumPoints (NumXPoints * NumYPoints)
#define NumPointsPerStrip (2*NumXPoints)
#define NumStrips (NumYPoints-1)
#define RestartIndex 0xffff

void
init()
{
	GLuint vbo, ebo;
	GLfloat *vertices;
	GLushort *indices;
	/* Set up vertex data */
	glGenBuffers( 1, &vbo );
	glBindBuffer( GL_ARRAY_BUFFER, vbo );
	glBufferData( GL_ARRAY_BUFFER, 2 * NumPoints * sizeof( GLfloat ),
	              0, GL_STATIC_DRAW );

	vertices = (GLfloat*)glMapBuffer( GL_ARRAY_BUFFER, GL_WRITE_ONLY );

	if ( vertices == 0 )
	{
		fprintf( stderr, "Unable to map vertex buffer\n" );
		//exit( EXIT_FAILURE );
	}
	else
	{
		int i, j;
		GLfloat dx = ( XEnd - XStart ) / ( NumXPoints - 1 );
		GLfloat dy = ( YEnd - YStart ) / ( NumYPoints - 1 );
		GLfloat *tmp = vertices;
		int n = 0;

		for ( j = 0; j < NumYPoints; ++j )
		{
			GLfloat y = YStart + j * dy;

			for ( i = 0; i < NumXPoints; ++i )
			{
				GLfloat x = XStart + i * dx;
				*tmp++ = x;
				*tmp++ = y;
			}
		}

		glUnmapBuffer( GL_ARRAY_BUFFER );
		glVertexPointer( 2, GL_FLOAT, 0, BUFFER_OFFSET( 0 ) );
		glEnableClientState( GL_VERTEX_ARRAY );
	}

	/* Set up index data */
	glGenBuffers( 1, &ebo );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo );
	/* We allocate an extra restart index because it simplifies
	** the element-array loop logic */
	glBufferData( GL_ELEMENT_ARRAY_BUFFER,
	              NumStrips*( NumPointsPerStrip + 1 )*sizeof( GLushort ),
	              0, GL_STATIC_DRAW );
	indices = glMapBuffer( GL_ELEMENT_ARRAY_BUFFER,
	                       GL_WRITE_ONLY );

	if ( indices == 0 )
	{
		fprintf( stderr, "Unable to map index buffer\n" );
		//exit( EXIT_FAILURE );
	}
	else
	{
		int i, j;
		GLushort *index = indices;

		for ( j = 0; j < NumStrips; ++j )
		{
			GLushort bottomRow = j * NumYPoints;
			GLushort topRow = bottomRow + NumYPoints;

			for ( i = 0; i < NumXPoints; ++i )
			{
				*index++ = topRow + i;
				*index++ = bottomRow + i;
			}

			*index++ = RestartIndex;
		}

		glUnmapBuffer( GL_ELEMENT_ARRAY_BUFFER );
	}

	glPrimitiveRestartIndex( RestartIndex );
	glEnable( GL_PRIMITIVE_RESTART );
}


void
display()
{
	int i, start;
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glColor3f( 1, 1, 1 );
	glDrawElements( GL_TRIANGLE_STRIP,
	                NumStrips*( NumPointsPerStrip + 1 ),
	                GL_UNSIGNED_SHORT, BUFFER_OFFSET( 0 ) );
	glutSwapBuffers();
}



void reshape( int width, int height )
{
    if ( height == 0 ) // Prevent A Divide By Zero By
    {
        height = 1; // Making Height Equal One
    }

    glViewport( 0, 0, width, height ); // Reset The Current Viewport

    //投影矩阵负责为我们的场景增加透视功能，意味着越远的东西看起来越小。
    glMatrixMode( GL_PROJECTION );				// 选择投影矩阵
    glLoadIdentity();							// 重置投影矩阵

    // 设置视口的大小
    gluPerspective( 45.0f, ( GLfloat )width / ( GLfloat )height, 0.1f, 100.0f );

    //模型观察矩阵负责存放了我们的物体信息
    glMatrixMode( GL_MODELVIEW );						// 选择模型观察矩阵
    glLoadIdentity();
};

