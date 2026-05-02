// ===============================================================
// Computer Graphics Homework Solutions
// Copyright (C) 2022 by George Wolberg
//
// HW4b.cpp - HW4b class
//
// Written by: George Wolberg, 2022
// ===============================================================

#include "HW4b.h"


#define PII		3.1415926535897931160E0
#define PI2		6.2831853071795862320E0
#define PI_2		1.5707963267948965580E0
#define DEGtoRAD	0.0174532927777777777E0
#define RADtoDEG	57.295778666661658617E0


HW4b::HW4b(const QGLFormat &glf, QWidget *parent) : HW(glf, parent)
{
	m_timer = new QTimer(this);
	connect(m_timer, SIGNAL(timeout()), this, SLOT(timeOut()));
	m_midlight[0] = .8f; 
	m_midlight[1] = .8f; 
	m_midlight[2] = .8f; 
	m_midlight[3] = .8f;

	m_gray[0]     = .5f; 
	m_gray[1]     = .5f; 
	m_gray[2]     = .5f; 
	m_gray[3]     = .5f;

	m_light_pos[0] = 8.0f; 
	m_light_pos[1] = 8.0f; 
	m_light_pos[2] = 8.0f; 
	m_light_pos[3] = 8.0f;
}


void
HW4b::initializeGL()
{
	glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
	glColor3f   (1.0f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glDepthRange(0.01f, 1000.0f);

	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, m_light_pos);
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  m_midlight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, m_midlight);
	glEnable(GL_NORMALIZE);

	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	m_time = 0;
	m_timer->start(5);
}


void
HW4b::resizeGL(int w, int h)
{
	m_winW = w;
	m_winH = h;

	double fovy   = 45;
	double aspect = 1.0;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	m_projection.setToIdentity();
	m_projection.perspective(fovy, aspect*w/h, 0.01f, 1000.0f);
	glMultMatrixf(m_projection.constData());
	glViewport(0, 0, w, h);
	glMatrixMode(GL_MODELVIEW);
}


void
HW4b::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLfloat m[16] = {0};

	float timescale = 0.5;
	float height = .8+2*(1+sin(m_time*DEGtoRAD*timescale));
	float s1 = 2 - fabs(sin(m_time*DEGtoRAD*timescale));
	float s2 = 1.2 / s1;

	GLfloat nlp[4], r = m_light_pos[0];
	float angle = m_time*.01;
	nlp[1] = m_light_pos[1];
	nlp[0] = r*cos(angle*DEGtoRAD);
	nlp[2] = r*sin(angle*DEGtoRAD);
	nlp[3] = 1.0;

	// init projection matrix with identity matrix and a non-zero m[7] entry
	// based on light position component
	// PUT YOUR CODE HERE
	m[0]  = 1.0f;  m[4]  = -nlp[0]/nlp[1]; m[8]  = 0.0f;  m[12] = 0.0f;
	m[1]  = 0.0f;  m[5]  = 0.0f;           m[9]  = 0.0f;  m[13] = 0.0f;
	m[2]  = 0.0f;  m[6]  = -nlp[2]/nlp[1]; m[10] = 1.0f;  m[14] = 0.0f;
	m[3]  = 0.0f;  m[7]  = -1.0f/nlp[1];  m[11] = 0.0f;  m[15] = 1.0f;

	// setup camera view
	glLoadIdentity();

	vec3 eye(10.0f, 30.0f, 40.0f);
	vec3 origin(0.0f, 0.0f, 0.0f);
	vec3 dir = (origin - eye).normalized();
	vec3 worldUp = vec3(0.0f, 1.0f, 0.0f);
	vec3 right   = vec3::crossProduct(dir, worldUp).normalized();
	vec3 up      = vec3::crossProduct(right, dir).normalized();
	m_cameraView.setToIdentity();
	m_cameraView.lookAt(eye, origin, up);
	glMultMatrixf(m_cameraView.constData());

	// update the position of light0
	// PUT YOUR CODE HERE
	glLightfv(GL_LIGHT0, GL_POSITION, nlp);

	// enable lighting and color material
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMaterialf(GL_FRONT, GL_SHININESS, 32.f);
	glMaterialfv(GL_FRONT, GL_SPECULAR, m_gray);

	// draw the translated/scaled sphere object
	// PUT YOUR CODE HERE
	glPushMatrix();
		glTranslatef(0.0f, height, 0.0f);
		glScalef(s2, s1, s2);
		glColor3f(0.8f, 0.5f, 0.1f);
		drawSphere(32, 32);
	glPopMatrix();

	// disable lighting
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_LIGHTING);

	// draw the xz floor first so shadow draws on top of it
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(1.0f, 1.0f);
	glColor4f(.5f, .5f, .5f, 1);
	glBegin(GL_QUADS);
	float w = 25;
	glVertex3f(-w, 0.0f, -w);
	glVertex3f( w, 0.0f, -w);
	glVertex3f( w, 0.0f,  w);
	glVertex3f(-w, 0.0f,  w);
	glEnd();
	glDisable(GL_POLYGON_OFFSET_FILL);

	// draw object's shadow (projected onto the xz plane)
	// PUT YOUR CODE HERE
	glDepthMask(GL_FALSE);
	glPushMatrix();
		glColor4f(0.1f, 0.1f, 0.1f, 0.8f);
		glMultMatrixf(m);
		glTranslatef(0.0f, height, 0.0f);
		glScalef(s2, s1, s2);
		drawSphere(32, 32);
	glPopMatrix();
	glDepthMask(GL_TRUE);

	// draw the light source
	// PUT YOUR CODE HERE
	glPushMatrix();
		glTranslatef(nlp[0], nlp[1], nlp[2]);
		glColor3f(1.0f, 1.0f, 0.0f);
		glScalef(0.2f, 0.2f, 0.2f);
		drawSphere(8, 8);
	glPopMatrix();

	glFlush();
}


QGroupBox*
HW4b::controlPanel()
{
	QGroupBox *groupBox = new QGroupBox("Homework 4b");
	groupBox->setStyleSheet(GroupBoxStyle);
	return(groupBox);
}


void 
HW4b::drawSphere(int lats, int longs)
{
	// PUT YOUR CODE HERE
	for(int i = 0; i <= lats; i++) {
		double lat0 = M_PI * (-0.5 + (double)(i - 1) / lats);
		double z0   = sin(lat0);
		double zr0  = cos(lat0);

		double lat1 = M_PI * (-0.5 + (double)i / lats);
		double z1   = sin(lat1);
		double zr1  = cos(lat1);

		glBegin(GL_QUAD_STRIP);
		for(int j = 0; j <= longs; j++) {
			double lng = 2.0 * M_PI * (double)(j - 1) / longs;
			double x   = cos(lng);
			double y   = sin(lng);

			glNormal3d(x * zr0, y * zr0, z0);
			glVertex3d(x * zr0, y * zr0, z0);
			glNormal3d(x * zr1, y * zr1, z1);
			glVertex3d(x * zr1, y * zr1, z1);
		}
		glEnd();
	}
}


void
HW4b::timeOut() 
{
	m_timer->stop();
	m_time += 3.0f;
	updateGL();
	m_timer->start(5);
}