// Name:
// Quarter, Year:
// Lab:
//
// This file is to be modified by the student.
// main.cpp
////////////////////////////////////////////////////////////
#ifndef __APPLE__
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif

#include <vector>
#include <cstdio>
#include <math.h>
#include "vec.h"
#include <iostream>

using namespace std;
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;

struct Point{
    float x;
    float y;
};

vector<Point> control_points;



float factorial(int n){
    if (n == 0) 
        return 1;

    float a = static_cast<float>(n);
    for (int i = n - 1; i > 0; --i)
        a *= i;
    return a;
}

float combination(int n, int k){
    return factorial(n) / ( factorial(k) * factorial(n - k) );
}

float polynomial(int n, int k, float t){
    return combination(n, k) * pow(t, k) * pow(1 - t, n - k);
}

void coefficients(float* c, int n, float t){
    for (int i = 0; i < n; ++i)
        c[i] = polynomial(n, i, t);
}

void GL_render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();

    glBegin(GL_LINE_STRIP);
    glColor3f(1.0f,0.0f,0.0f);

    // TODO: just for example, you will need to change this.
    for (unsigned i = 0; i < control_points.size(); i ++){
        // glVertex2f(control_points.at(i).x,control_points.at(i).y);

        for (float t = 0; t <= 1; t += 0.01){
            Point p;

            p.x = control_points.at(i).x * polynomial(control_points.size(),i,t);
            p.y = control_points.at(i).y * polynomial(control_points.size(),i,t);

            }
            glVertex2f(p.x, p.y);
    }

    glEnd();
    glFlush();
}

void GL_mouse(int button,int state,int x,int y)
{
    y=WINDOW_HEIGHT-y;
    GLdouble mv_mat[16];
    GLdouble proj_mat[16];
    GLint vp_mat[4];
    glGetDoublev(GL_MODELVIEW_MATRIX,mv_mat);
    glGetDoublev(GL_PROJECTION_MATRIX,proj_mat);
    glGetIntegerv(GL_VIEWPORT,vp_mat);

    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
        double px,py,dummy_z; // we don't care about the z-value but need something to pass in
        gluUnProject(x,y,0,mv_mat,proj_mat,vp_mat,&px,&py,&dummy_z);
        // TODO: the mouse click coordinates are (px,py).
        Point newPoint;
        newPoint.x = px;
        newPoint.y = py;
        control_points.push_back(newPoint);

        glutPostRedisplay();
    }
}

//Initializes OpenGL attributes
void GLInit(int* argc, char** argv)
{
    glutInit(argc, argv);
    //glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    //glMatrixMode(GL_PROJECTION_MATRIX);
    //glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -1, 1);
    glutCreateWindow("CS 130 - <Insert Name Here>");
    glutDisplayFunc(GL_render);
    glutMouseFunc(GL_mouse);
}

int main(int argc, char** argv)
{
    GLInit(&argc, argv);
    glutMainLoop();
    return 0;
}
