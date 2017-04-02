#include <GL/glut.h>  
#include <iostream>
#include <cstdlib>  
#include "eigen.h"
#include "glCamera.h"
#include "man.h"
#include "drawItem.h"

int WinW = 1000, WinH = 800;	//window size
int oldx, oldy, x, y, wander, walking, moving;	//mouse motion
GLfloat wanderSpeed = 1, walkingSpeed = 1;
Eigen::Vector3d pos,target,up;
GLCamera cam;
Man man;
void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0); //black background  
	pos = Eigen::Vector3d(10,10,14);
	target = Eigen::Vector3d(0,0,0);
	up = Eigen::Vector3d(0,0,1);
	cam = GLCamera(pos, target, up);
	oldx = oldy = 0;
	wander = walking = moving = false;
	time = 0;
	man = Man();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glClearDepth(1);
	glColor3f(1.0, 1.0, 1.0); 
	glLoadIdentity(); 
	gluLookAt(cam.m_pos.x(), cam.m_pos.y(), cam.m_pos.z(), 
		cam.m_target.x(), cam.m_target.y(), cam.m_target.z(), 
		cam.m_up.x(), cam.m_up.y(), cam.m_up.z());
//	glutWireTeapot(2);
//	glutWireCube(3);
	//Draw the coordinates
	drawCoordinate();
	man.draw();
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cam.m_pos.x(), cam.m_pos.y(), cam.m_pos.z(), 
		cam.m_target.x(), cam.m_target.y(), cam.m_target.z(), 
		cam.m_up.x(), cam.m_up.y(), cam.m_up.z());
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON&&state == GLUT_DOWN)
	{
		wander = !wander;
		oldx = x;
		oldy = y;
	}
	//printf("oldx:%.5f oldy:%.5f\n", oldx, oldy);
}
void keyboard(unsigned char key, int , int )
{
	float v = wanderSpeed;
	switch (key) {
	case 27:
	case 'q':
		exit(0);
	case 's':
		cam.slide(0, 0, v, 0);
		break;
	case 'w':
		cam.slide(0, 0, -v, 0);
		break;
	case 'a':
		cam.slide(-v,0,0,0);
		break;
	case 'd':
		cam.slide(v,0,0,0);
		break;
	case 'r':
		init();
		break;
	case 'z':
		walking = !walking;
		break;
	case 'x':
		moving = !moving;
		break;
	case 32:
		int mod = glutGetModifiers();
		if (mod == (GLUT_ACTIVE_SHIFT)) 
			cam.slide(0,0,0,-v);
		else
			cam.slide(0,0,0,v);
		break;
	}
	glutPostRedisplay();

}
void passiveMotion(int x, int y)
{
	if (!wander) return;
//	printf("x:%d y:%d\n", x, y);
	GLint deltax = oldx - x;
	GLint deltay = oldy - y;
	GLfloat xAngle = 360 * (GLfloat)deltay / (GLfloat)WinH;
	GLfloat yAngle = 360 * (GLfloat)deltax / (GLfloat)WinW;
	yAngle = 360 - yAngle;
	xAngle = 360 - xAngle;
	glPushMatrix();
	glLoadIdentity();
//	printf("xangle : %f\n", xAngle);
//	printf("yangle : %f\n", yAngle);
	glRotated(xAngle, cam.u.x(), cam.u.y(), cam.u.z());
	glRotated(yAngle, cam.v.x(), cam.v.y(), cam.v.z());
	GLfloat m[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, m);
	glPopMatrix();
	Eigen::Matrix3d rot;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			rot(i, j) = m[i * 4 + j];
		}
	}
//	std::cout << "rot:\n" << rot << std::endl;
//	std::cout << "n(before):\n" << n << std::endl;
	cam.n = rot*cam.n;
//	std::cout << "n(after):\n" << n << std::endl;
	cam.m_target = Eigen::Vector3d(cam.m_pos.x() - cam.n.x(), cam.m_pos.y() - cam.n.y(), cam.m_pos.z() - cam.n.z());
	cam.upduvn();
	oldx = x;
	oldy = y;
	glutPostRedisplay();
}
void idle()
{
	if(moving||walking)
		time++;
	if (walking)
		man.body.base += Vector3d(1, 0, 0)/100*walkingSpeed;
	glutPostRedisplay();
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB| GLUT_DEPTH);
	glutInitWindowSize(WinW,WinH);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	init();
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutPassiveMotionFunc(passiveMotion);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}