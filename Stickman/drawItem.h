#pragma once
#include <GL/glut.h>  
#include "eigen.h"
#include "glCamera.h"
#include "drawItem.h"
using namespace Eigen;
using namespace std;
void drawCoordinate()
{
	glPushMatrix();
		glBegin(GL_LINES);
		glVertex3d(-9.0f, 0.0f, 0.0f);
		glVertex3d(9.0f, 0.0f, 0.0f);
		glVertex3d(0.0f, -9.0f, 0.0f);
		glVertex3d(0.0f, 9.0f, 0.0f);
		glVertex3d(0.0f, 0.0f, -9.0f);
		glVertex3d(0.0f, 0.0f, 9.0f);
		glEnd();
		glPushMatrix();
		glTranslated(9.0f, 0.0f, 0.0f);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		glutSolidCone(0.3, 0.6, 10, 10);
		glPopMatrix();
		glPushMatrix();
		glTranslated(0.0f, 9.0f, 0.0f);
		glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
		glutSolidCone(0.3, 0.6, 10, 10);
		glPopMatrix();
		glPushMatrix();
		glTranslated(0.0f, 0.0f, 9.0f);
		glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
		glutSolidCone(0.3, 0.6, 10, 10);
		glPopMatrix();
	glPopMatrix();
}
void drawCube(double xPos, double yPos, double zPos)
{
	glPushMatrix();
		glTranslated(xPos, yPos, zPos);
		glBegin(GL_POLYGON);
		glVertex3d(0.0f, 0.0f, 0.0f);  //顶面
		glVertex3d(0.0f, 0.0f, -1.0f);
		glVertex3d(-1.0f, 0.0f, -1.0f);
		glVertex3d(-1.0f, 0.0f, 0.0f);
		glVertex3d(0.0f, 0.0f, 0.0f);  //正面
		glVertex3d(-1.0f, 0.0f, 0.0f);
		glVertex3d(-1.0f, -1.0f, 0.0f);
		glVertex3d(0.0f, -1.0f, 0.0f);
		glVertex3d(0.0f, 0.0f, 0.0f);  //右面
		glVertex3d(0.0f, -1.0f, 0.0f);
		glVertex3d(0.0f, -1.0f, -1.0f);
		glVertex3d(0.0f, 0.0f, -1.0f);
		glVertex3d(-1.0f, 0.0f, 0.0f); //左面
		glVertex3d(-1.0f, 0.0f, -1.0f);
		glVertex3d(-1.0f, -1.0f, -1.0f);
		glVertex3d(-1.0f, -1.0f, 0.0f);
		glVertex3d(0.0f, -1.0f, 0.0f);  //底面
		glVertex3d(0.0f, -1.0f, -1.0f);
		glVertex3d(-1.0f, -1.0f, -1.0f);
		glVertex3d(-1.0f, -1.0f, 0.0f);
		glVertex3d(0.0f, 0.0f, -1.0f);  //背面
		glVertex3d(-1.0f, 0.0f, -1.0f);
		glVertex3d(-1.0f, -1.0f, -1.0f);
		glVertex3d(0.0f, -1.0f, -1.0f);
		glEnd();
	glPopMatrix();
}
void drawBox(double xPos, double yPos, double zPos, double xLen, double yLen, double zLen)
{
	glPushMatrix();
		glTranslated(xPos, yPos, zPos);
		glScaled(xLen, yLen, zLen);
		drawCube(0, 0, 0);
	glPopMatrix();
}
void drawBox(Vector3d Pos, Vector3d Len)
{
	drawBox(Pos.x(), Pos.y(), Pos.z(), Len.x(), Len.y(), Len.z());
}
