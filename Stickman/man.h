#pragma once
#include <GL/glut.h>  
#include "eigen.h"
#include "glCamera.h"
#include "drawItem.h"
using namespace Eigen;
using namespace std;
const int maxnxt = 20;
int time = 0;
class Box {
public:
	int len;
	double angle;
	Vector3d base, scale, rotN, color, rotP;
	Box* nxt[maxnxt];
	Box() { 
		angle = 0;
		len = 0;
		angle = 0;
		color = Vector3d(1, 1, 1);
		rotP = Vector3d(0, 0, 0);
	};
	Box(Vector3d base_, Vector3d scale_,
		Vector3d rotN_=Vector3d(0,0,0),
		Vector3d rotP_=Vector3d(0,0,0),
		double angle_=0,
		Vector3d color_ = Vector3d(1, 1, 1)) {
		angle = angle_;
		base = base_;
		scale = scale_;
		rotN = rotN_;
		len = 0;
		rotP = rotP_;
		color = color_;
	}
	void draw() {
		glPushMatrix();
			if (rotN.norm() != 0) {
				glTranslated(rotP.x(), rotP.y(), rotP.z());
				glRotated(angle, rotN.x(), rotN.y(), rotN.z());
				glTranslated(-rotP.x(), -rotP.y(), -rotP.z());
			}
			glColor3d(color.x(), color.y(), color.z());
//			cout << "base:" << base << endl;
//			cout << "color:" << color << endl;
//			cout << "scale:" << scale << endl;
			glTranslated(base.x(), base.y(), base.z());
			drawBox(Vector3d(0,0,0),scale);
			for (int i = 0; i < len; i++) {
				glPushMatrix();
//				printf("i:%d\n",i);
				nxt[i]->draw();
				glPopMatrix();
			}
		glPopMatrix();
	}
	void addNxt(Box *x) {
		nxt[len] = x;
		len++;
	}


};
class Man {
public:
	Box body;
	Man() {
		body = Box(Vector3d(1,2,5), Vector3d(1, 2, 3), Vector3d(0,0,0));
		body.color = Vector3d(0, 0, 1); 
		int angArm = sin(time/100) * 30;
		int angLeg= sin(time/100) * 10;
		Box *head = new Box(Vector3d(0,-0.5,1),Vector3d(1,1,1));
		Box *lArm = new Box(Vector3d(0,0.8,0),Vector3d(0.8,0.8,2),
				Vector3d(0,1,0),
				Vector3d(-0.5,0,0),
				angArm);
		Box *rArm = new Box(Vector3d(0,-2,0),Vector3d(0.8,0.8,2),
				Vector3d(0,-1,0),
				Vector3d(-0.5,0,0),
				angArm);
		Box *lLeg = new Box(Vector3d(0,-0.1,-3),Vector3d(0.8,0.8,2),
				Vector3d(0,-1,0),
				Vector3d(-0.5,0,0),
				angLeg);
		Box *rLeg = new Box(Vector3d(0,-1.1,-3),Vector3d(0.8,0.8,2),
				Vector3d(0,1,0),
				Vector3d(-0.5,0,0),
				angLeg);
		body.addNxt(head);
		body.addNxt(lArm);
		body.addNxt(rArm);
		body.addNxt(lLeg);
		body.addNxt(rLeg);
	}
	void draw() {
		printf("time:%d\n", time);
		int angArm = sin(time/100) * 30;
		int angLeg= sin(time/100) * 10;
		body.nxt[1]->angle = body.nxt[2]->angle = angArm;
		body.nxt[3]->angle = body.nxt[4]->angle = angLeg;
		body.draw();
	}
};
