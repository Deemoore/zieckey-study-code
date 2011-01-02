// UnitAxes.c
// Draws a lit representation of the orientation of the unit axes
// Richard S. Wright Jr.
// OpenGL SuperBible

#include "GLTools.h"
#include <stdio.h>

///////////////////////////////////////////////////////////////////
// Draw the unit axis. A small white sphere represents the origin
// and the three axes are colored Red, Green, and Blue, which 
// corresponds to positive X, Y, and Z respectively. Each axis has
// an arrow on the end, and normals are provided should the axes
// be lit. These are all built using the quadric shapes. For best
// results, put this in a display list.
void gltDrawUnitAxes(void)
	{
	GLUquadricObj *pObj;	// Temporary, used for quadrics

	// Measurements
	float fAxisRadius = 0.025f;
	float fAxisHeight = 1.0f;
	float fArrowRadius = 0.06f;
	float fArrowHeight = 0.1f;

	// Setup the quadric object
	pObj = gluNewQuadric();
	gluQuadricDrawStyle(pObj, GLU_FILL);
	gluQuadricNormals(pObj, GLU_SMOOTH);
	gluQuadricOrientation(pObj, GLU_OUTSIDE);
	gluQuadricTexture(pObj, GLU_FALSE);

	///////////////////////////////////////////////////////
	// Draw the blue Z axis first, with arrowed head
	glColor3f(0.0f, 0.0f, 1.0f);
	gluCylinder(pObj, fAxisRadius, fAxisRadius, fAxisHeight, 10, 1);
	glPushMatrix();
		glTranslatef(0.0f, 0.0f, 1.0f);
		glPopMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);
    glPushMatrix();
	gluCylinder(pObj, fAxisRadius, fAxisRadius, fAxisHeight, 10, 1);
    glTranslatef(0.0f, 0.0f, 1.0f);
    glPopMatrix();
    glColor3f(0.0f, 1.0f, 0.0f);
    glPushMatrix();
    gluCylinder(pObj, fAxisRadius, fAxisRadius, fAxisHeight, 10, 1);
    glPopMatrix();

	///////////////////////////////////////////////////////
	// Draw the Red X axis 2nd, with arrowed head
   
	////////////////////////////////////////////////////////
	// White Sphere at origin

	// Delete the quadric
	gluDeleteQuadric(pObj);
	}
