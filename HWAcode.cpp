// ===============================================================
// Computer Graphics Homework Solutions
// Copyright (C) 2022 by George Wolberg
//
// HW1a.cpp - HW1a class
//
// Written by: George Wolberg, 2022
// ===============================================================

#include "HW1a.h"

// init array of 16 vertices for letter 'P'
float Vertices[] = {
	-0.5f , -0.75f,
	-0.5f , -0.5f,
	-0.5f , -0.25f,
	-0.5f ,  0.0f,
	-0.5f ,  0.25f,
	-0.5f ,  0.5f,
	-0.25f,  0.75f,
	 0.0f ,  0.75f,
	 0.25f,  0.75f,
	 0.5f ,  0.75f,
	 0.75f,  0.5f,
	 0.75f,  0.25f,
	 0.5f ,  0.0f,
	 0.25f,  0.0f,
	 0.0f ,  0.0f,
	-0.25f,  0.0f
};

static int DrawModes[] = {
	GL_POINTS,
	GL_LINES,
	GL_LINE_STRIP,
	GL_LINE_LOOP,
	GL_TRIANGLES,
	GL_TRIANGLE_STRIP,
	GL_TRIANGLE_FAN,
	GL_QUADS,
	GL_POLYGON
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW1a::HW1a:
//
// HW1a constructor.
//
HW1a::HW1a(const QGLFormat &glf, QWidget *parent)
	: HW(glf, parent)
{
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW1a::initializeGL:
//
// Initialization routine before display loop.
// Gets called once before the first time resizeGL() or paintGL() is called.
//
void
HW1a::initializeGL()
{
	initializeGLFunctions();
	//example done in class
	glClearColor(0.0, 0.0, 0.0, 0.0);
	//set and fill background with black
	glColor3f(1.0, 1.0, 1.0);
	//fill with white
	// PUT YOUR CODE HERE
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW1a::resizeGL:
//
// Resize event handler.
// The input parameters are the window width (w) and height (h).
//
void
HW1a::resizeGL(int w, int h)
{
	// // set viewport to occupy full canvas initially 
	 glViewport(0, 0, w, h);
	 //reset the window width and height size here so that each view point is different
	 m_winW = w;
	 m_winH = h;

	// PUT YOUR CODE HERE
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW1a::paintGL:
//
// Update GL scene.
//
void
HW1a::paintGL()
{
	//I think  we need to call the resize function here so that we have a specific instance of the viewport but I don't get how
	glClear(GL_COLOR_BUFFER_BIT);

	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();

	int WidthBuffer = m_winW / 3;
	int HeightBuffer = m_winH / 3;
	int index = 0;

	for(int r = 0; r < 3; r++) {
        for(int c = 0; c < 3; c++) {
			//set the viewport
            glViewport(c * WidthBuffer, r * HeightBuffer, WidthBuffer, HeightBuffer);

			//clear the scene for this specifying viewport drawing 
			glEnable(GL_SCISSOR_TEST);
			glScissor(c * WidthBuffer, r * HeightBuffer, WidthBuffer, HeightBuffer);

			glClear(GL_COLOR_BUFFER_BIT);

			glDisable(GL_SCISSOR_TEST);

            // Reset projection
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(-1, 1, -1, 1, -1, 1);

            // Reset modelview
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
			//the above reset the positioning of the drawing in the given frame

            // Draw
            glBegin(DrawModes[index]);
            for(int l = 0; l < 31; l += 2) {
                glVertex2f(Vertices[l], Vertices[l + 1]);
            }
            glEnd();

			index++;
        }
    }

	glFlush();
	// PUT YOUR CODE HERE
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HW1a::controlPanel:
//
// Create control panel groupbox.
//
QGroupBox*
HW1a::controlPanel()
{
	// init group box
	QGroupBox *groupBox = new QGroupBox("Homework 1a");
	groupBox->setStyleSheet(GroupBoxStyle);

	return(groupBox);
}
