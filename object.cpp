#include "object.h"
#include <qgl.h>

using namespace qglviewer;

void Object::draw() const {
    // glPushMatrix();
    // glMultMatrixd(frame.matrix());
    // glRectf(-0.01f, -0.01f, 0.01f, 0.01f);
    // glPopMatrix();


    // glPushMatrix();
    // glPointSize(2);
    // glBegin(GL_POINT);
    // // glBegin(GL_POINTS);
    // glMultMatrixd(frame.matrix());
    // glVertex3f(0.0, 0.0,0.0);
    // // glRectf(-0.01f, -0.01f, 0.01f, 0.01f);
    // glEnd();
    // glPopMatrix();

    static GLUquadric *quad = gluNewQuadric();
    glPushMatrix();
    glMultMatrixd(frame.matrix());
    glBegin(GL_POINTS);
    glVertex3d(0.0, 0.0, 0.0);
    glEnd();
    glPopMatrix();
}