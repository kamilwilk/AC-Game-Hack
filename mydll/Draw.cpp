#include <stdio.h>
#include "Draw.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Engine.h"

void Draw::string(GLfloat x, GLfloat y, GLubyte r, GLubyte g, GLubyte b, GLubyte alpha, void * font, char const*const pFmtText, ...)
{
	int newLineDist;

	//Set the distance dynamically for new lines
	switch ((int)font)
	{
	case (int)GLUT_BITMAP_9_BY_15:
		newLineDist = 16;
		break;

	case (int)GLUT_BITMAP_8_BY_13:
		newLineDist = 14;
		break;

	case (int)GLUT_BITMAP_TIMES_ROMAN_10:
		newLineDist = 11;
		break;

	case (int)GLUT_BITMAP_TIMES_ROMAN_24:
		newLineDist = 25;
		break;

	case (int)GLUT_BITMAP_HELVETICA_10:
		newLineDist = 11;
		break;

	case (int)GLUT_BITMAP_HELVETICA_12:
		newLineDist = 13;
		break;

	case (int)GLUT_BITMAP_HELVETICA_18:
		newLineDist = 19;
		break;

	default:
		newLineDist = 19;
		break;
	}

	//Set our attributes
	glEnable(GL_BLEND);
	glColor4ub(r, g, b, alpha);
	glRasterPos2i(x, y);

	//Allocate memory for a temporary result string. You could probably do much less
	char *const pTemp = new char[5000];

	//Put all of the text into pTemp
	va_list vaList;
	va_start(vaList, pFmtText);
	int const TextLen = vsprintf(pTemp, pFmtText, vaList);
	va_end(vaList);

	//Draw the string
	for (signed int Counter = 0; Counter < TextLen; ++Counter)
	{
		if (pTemp[Counter] == '\n')
		{
			y += newLineDist;
			glRasterPos2i(x, y);
			continue;
		}

		glutBitmapCharacter(font, pTemp[Counter]);
	}

	//Prevent memory leaks
	delete[] pTemp;
}

void Draw::box(GLfloat x, GLfloat y, GLfloat xLen, GLfloat yLen, GLubyte r, GLubyte g, GLubyte b, GLubyte alpha)
{
	//Set our attributes
	glEnable(GL_BLEND);
	glColor4ub(r, g, b, alpha);


	//Draw our box
	glBegin(GL_QUADS);
	glVertex2f(x, y);
	glVertex2f(x + xLen, y);
	glVertex2f(x + xLen, y + yLen);
	glVertex2f(x, y + yLen);
	glEnd();
}

void Draw::boxLine(GLfloat width, GLfloat x, GLfloat y, GLfloat xLen, GLfloat yLen, GLubyte r, GLubyte g, GLubyte b, GLubyte alpha)
{
	//Grab the current line width to prevent clashes
	GLfloat glTemp[1];
	glGetFloatv(GL_LINE_WIDTH, glTemp);

	//Set our attributes
	glEnable(GL_BLEND);
	glColor4ub(r, g, b, alpha);
	glLineWidth(width);

	//Draw out box
	glBegin(GL_LINE_LOOP);
	glVertex2f(x, y);
	glVertex2f(x + xLen, y);
	glVertex2f(x + xLen, y + yLen);
	glVertex2f(x, y + yLen);
	glEnd();

	//Restore the line width
	glLineWidth(glTemp[0]);
}

void Draw::line(GLfloat width, GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLubyte r, GLubyte g, GLubyte b, GLubyte alpha)
{
	//Grab the current line width to prevent clashes
	GLfloat glTemp[1];
	glGetFloatv(GL_LINE_WIDTH, glTemp);

	//Set our attributes
	glEnable(GL_BLEND);
	glColor4ub(r, g, b, alpha);
	glLineWidth(width);

	//Draw our line
	glBegin(GL_LINES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();

	//Restore the line width
	glLineWidth(glTemp[0]);
}

void Draw::dot(GLfloat size, GLfloat x, GLfloat y, GLubyte r, GLubyte g, GLubyte b, GLubyte alpha)
{
	//Grab the current line width to prevent clashes
	GLfloat glTemp[1];
	glGetFloatv(GL_POINT_SIZE, glTemp);

	//Set our attributes
	glEnable(GL_BLEND);
	glColor4ub(r, g, b, alpha);
	glPointSize(size);

	//Draw our point
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();

	//Restore to prevent clashing
	glPointSize(glTemp[0]);
}

void Draw::init()
{
	glViewport(0, 0, *CurrentGame.w_res, *CurrentGame.h_res);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, *CurrentGame.w_res, *CurrentGame.h_res, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_BLEND);
}


