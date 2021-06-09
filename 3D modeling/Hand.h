#pragma once

#include <gltools.h>	// OpenGL toolkit
#include <glframe.h>   // Frame Class
#include "glm.h"

class Hand {
private:
	float armDeg;
	float armDeg_2;
	float elbowDeg;
	float shoulderDeg;
	float shoulderDeg_2;
	float shoulderDeg_3;

public:
	Hand(GLFrame* obj)
	{
		object = obj;
		object->SetOrigin(0, 0, -1);
		palm = glmReadOBJ("hand.obj");
		arm = glmReadOBJ("arm.obj");
		Lower_arm = glmReadOBJ("Lower_arm_only.obj");
		Upper_arm = glmReadOBJ("Upper_arm_only.obj");
		glmUnitize(palm);
		glmFacetNormals(palm);
		glmVertexNormals(palm, 90);
		glmUnitize(arm);
		glmFacetNormals(arm);
		glmVertexNormals(arm, 90);
		glmUnitize(Lower_arm);
		glmFacetNormals(Lower_arm);
		glmVertexNormals(Lower_arm, 90);
		glmUnitize(Upper_arm);
		glmFacetNormals(Upper_arm);
		glmVertexNormals(Upper_arm, 90);

		index = 0;// INDEX: 0~2:litte finger ; 3~5:right finger ; 6~8:middle ; 9~11: fore ; 12~13: thumb

		root[0] = 9;
		first[0] = 30;
		second[0] = 30;

		root[1] = 15;
		first[1] = 45;
		second[1] = 9;

		root[2] = 9;
		first[2] = 36;
		second[2] = 9;

		root[3] = 12;
		first[3] = 45;
		second[3] = 9;

		first[4] = 21;
		second[4] = 30;

		armDeg = 0.0;
		armDeg_2 = 0.0;
		elbowDeg = 0.0;
		shoulderDeg = 0.0;
		shoulderDeg_2 = 0.0;
		shoulderDeg_3 = 0.0;
	}

	~Hand()
	{

	}

	void setJointIndex(int num)
	{
		index = num;
	}

	void fingerRotateDown()
	{
		if (index == 12)
		{
			first[4] += 3;
			if (first[4] >= 90)
				first[4] = 90;
		}
		else if (index == 13)
		{
			second[4] += 3;
			if (second[4] >= 90)
				second[4] = 90;
		}
		else if (index == 14)
		{
			armDeg += 3;
			if (armDeg >= 84)
				armDeg = 84;
		}
		else if (index == 15)
		{
			armDeg_2 += 3;
			if (armDeg_2 >= 50)
				armDeg_2 = 50;
		}
		else if (index == 16)
		{
			elbowDeg += 3;
			if (elbowDeg >= 55)
				elbowDeg = 55;
		}
		else if (index == 17)
		{
			shoulderDeg += 3;
			if (shoulderDeg >= 70)
				shoulderDeg = 70;
		}
		else if (index == 18)
		{
			shoulderDeg_2 += 3;
			if (shoulderDeg_2 >= 70)
				shoulderDeg_2 = 70;
		}
		else if (index == 19)
		{
			shoulderDeg_3 += 3;
			if (shoulderDeg_3 >= 70)
				shoulderDeg_3 = 70;
		}
		else if (index % 3 == 0)
		{
			root[index / 3] += 3;

			if (root[index / 3]>=78)
				root[index / 3] = 78;
		}
		else if (index % 3 == 1)
		{
			first[index / 3] += 3;

			if (first[index / 3] >= 99)
				first[index / 3] = 99;
		}
		else if (index % 3 == 2)
		{
			second[index / 3] += 3;

			if (second[index / 3] >= 90)
				second[index / 3] = 90;
		}
	}

	void fingerRotateUp()
	{
		if (index == 12)
		{
			first[4] -= 3;
			
			if (first[4] <= 0)
				first[4] = 0;
		}
		else if (index == 13)
		{
			second[4] -= 3;

			if (second[4] <= -30)
				second[4] = -30;
		}
		else if (index == 14)
		{
			armDeg -= 3;

			if (armDeg <= -45)
				armDeg = -45;
		}
		else if (index == 15)
		{
			armDeg_2 -= 3;

			if (armDeg_2 <= -45)
				armDeg_2 = -45;
		}
		else if (index == 16)
		{
			elbowDeg -= 3;
			if (elbowDeg <= -60)
				elbowDeg = -60;
		}
		else if (index == 17)
		{
			shoulderDeg -= 3;
			if (shoulderDeg <= -45)
				shoulderDeg = -45;
		}
		else if (index == 18)
		{
			shoulderDeg_2 -= 3;
			if (shoulderDeg_2 <= -45)
				shoulderDeg_2 = -45;
		}
		else if (index == 19)
		{
			shoulderDeg_3 -= 3;
			if (shoulderDeg_3 <= -45)
				shoulderDeg_3 = -45;
		}
		else if (index % 3 == 0)
		{
			root[index / 3] -= 3;

			if (root[index / 3] <= -60)
				root[index / 3] = -60;
		}
		else if (index % 3 == 1)
		{
			first[index / 3] -= 3;

			if (first[index / 3] <= 0)
				first[index / 3] = 0;
		}
		else if (index % 3 == 2)
		{
			second[index / 3] -= 3;
			if (second[index / 3] <= -45)
				second[index / 3] = -45;
		}
	}

	//type1: vertical ; type2 : armRotate
	void plamRotate(int rotateType) {
		if (index != 16)
			return;
	}

	void Render()
	{
		glPushMatrix();
		glLineWidth(2);
		object->ApplyActorTransform();
		glTranslatef(0, 1, 0);

		#pragma region Upper_arm_joint
				glLineWidth(2);
				glTranslatef(-0.85, 6.05, 9.55);

				(index == 17) || (index == 18) || (index == 19)
						? glColor3ub(255, 255, 0) : glColor3ub(255, 0, 0);
				glutWireSphere(0.9, 50, 50);

				glRotatef(shoulderDeg, 1, 0, 0);
				glRotatef(shoulderDeg_2, 0, 1, 0);
				glRotatef(shoulderDeg_3, 0, 0, 1);

				glTranslatef(0.85, -6.05, -9.55);
		#pragma endregion

		#pragma region Upper_arm
			glLineWidth(2);
				glScalef(3, 3, 3);
				glTranslatef(-0.2, 1.2, 3.25);
				glRotatef(180, 1, 0, 0);
				glRotatef(90, 0, 0, 1);

				glColor3ub(0, 200, 0); glmDraw(Upper_arm, GL_SMOOTH);

				glRotatef(-90, 0, 0, 1);
				glRotatef(-180, 1, 0, 0);
				glTranslatef(0.2, -1.2, -3.25);
				glScalef(0.33, 0.33, 0.33);

			// glColor3ub(0, 200, 0); glmDraw(Upper_arm, GL_SMOOTH);
		#pragma endregion

		#pragma region Lower_arm_joint
				glLineWidth(2);
				glTranslatef(-0.5, 1.05, 10.05);
				glRotatef(elbowDeg, 1, 0, 0);

				index == 16 ? glColor3ub(255, 255, 0) : glColor3ub(255, 0, 0);
				glutWireSphere(0.9, 50, 50);

				glTranslatef(0.5, -1.05, -10.05);
		#pragma endregion

		#pragma region Lower_arm
			glLineWidth(2);
				glScalef(12, 12, 12);
				//glRotatef(-90, 0, 0, 1);
				glTranslatef(-0.025, 0.09, 0.65);
				glRotatef(30, 0, 1, 0);
				glRotatef(90, 1, 0, 0);

				glColor3ub(0, 200, 0); glmDraw(Lower_arm, GL_SMOOTH);

				glRotatef(-90, 1, 0, 0);
				glRotatef(-30, 0, 1, 0);
				glTranslatef(0.025, -0.09, -0.65);
				glScalef(0.084, 0.084, 0.084);
		#pragma endregion

		glTranslatef(0, 0.2, 0);
		glRotatef(-90, 0, 0, 1);
		
		#pragma region Palm
			glLineWidth(1);
				glScalef(1.5, 1.5, -1.5);
				glTranslatef(0, 0, -3.2);
				
				(index == 14) || (index == 15)
					? glColor3ub(255, 255, 0) : glColor3ub(255, 0, 0);
				glutWireSphere(0.5, 50, 50);

				glRotatef(armDeg, 1, 0, 0);
				glRotatef(armDeg_2, 0, 1, 0);

				glTranslatef(0, 0, 0.5);
				glColor3ub(0, 200, 0); glmDraw(palm, GL_SMOOTH);

				glLineWidth(2);
				glTranslatef(0.08, 0, -0.6);				
				glScalef(2.0 / 3.0, 2.0 / 3.0, -2.0 / 3.0);
				glTranslatef(-0.1, 0, -4.5);

		#pragma endregion

		#pragma region litteFinger
				glPushMatrix();
				glTranslatef(1, -0.2, 1.1);
				glScalef(1.2, 1.2, 1.2);
				glRotatef(-33, 0, 1, 0);
				glTranslatef(0.95, 0.15, -0.45);

				//glColor3ub(255, 255, 255); glutWireSphere(0.15, 10, 10);
				//glColor3ub(255, 255, 255); glutWireCylinder(0.15, 0.35, 10, 10);
				//glTranslatef(0, 0, 0.35);

				//glColor3ub(255, 0, 0); glutWireSphere(0.15, 20, 20);
				////glRotatef(20, 1, 0, 0);
				//glColor3ub(255, 255, 255); glutWireCylinder(0.15, 0.45, 10, 10);
				//glTranslatef(0, 0, 0.45);

				//glColor3ub(255, 0, 0); glutWireSphere(0.15, 20, 20);
				////glRotatef(20, 1, 0, 0);
				//glColor3ub(255, 255, 255); glutWireCylinder(0.15, 0.6, 10, 10);
				//glTranslatef(0, 0, 0.6);

				//glColor3ub(255, 0, 0); glutWireSphere(0.2, 30, 30);
				glTranslatef(0, 0, 0.35 + 0.45 + 0.6);
				glScalef(1, 1, -1);

				glRotatef(root[0], 1, 0, 0);
				index == 0 ? glColor3ub(255, 255, 0) : glColor3ub(255, 0, 0); glutWireSphere(0.2, 40, 40);
				glColor3ub(255, 255, 255); glutWireCylinder(0.15, 0.6, 10, 10);
				glTranslatef(0, 0, 0.6);

				glRotatef(first[0], 1, 0, 0);
				index == 1 ? glColor3ub(255, 255, 0) : glColor3ub(255, 0, 0); glutWireSphere(0.15, 40, 40);
				glColor3ub(255, 255, 255); glutWireCylinder(0.15, 0.45, 10, 10);
				glTranslatef(0, 0, 0.45);

				glRotatef(second[0], 1, 0, 0);
				index == 2 ? glColor3ub(255, 255, 0) : glColor3ub(255, 0, 0); glutWireSphere(0.15, 40, 40);
				glColor3ub(255, 255, 255); glutWireCylinder(0.15, 0.35, 10, 10);
				glTranslatef(0, 0, 0.35);

				glColor3ub(255, 255, 255); glutWireSphere(0.15, 10, 10);
				glPopMatrix();
		#pragma endregion

		#pragma region rightFinger 
				//µL¦W?
				glPushMatrix();
				glTranslatef(0.5, -0.1, 0.4);

				glScalef(1.2, 1.2, 1.2);
				glRotatef(-9, 0, 1, 0);
				glTranslatef(0.4, 0.35, -0.5);

				//glColor3ub(255, 255, 255); glutWireSphere(0.2, 10, 10);
				//glColor3ub(255, 255, 255); glutWireCylinder(0.2, 0.4, 10, 10);
				//glTranslatef(0, 0, 0.4);

				//glColor3ub(255, 0, 0); glutWireSphere(0.2, 20, 20);
				////glRotatef(20, 1, 0, 0);
				//glColor3ub(255, 255, 255); glutWireCylinder(0.2, 0.7, 10, 10);
				//glTranslatef(0, 0, 0.7);

				//glColor3ub(255, 0, 0); glutWireSphere(0.2, 20, 20);
				////glRotatef(20, 1, 0, 0);
				//glColor3ub(255, 255, 255); glutWireCylinder(0.2, 1.1, 10, 10);
				//glTranslatef(0, 0, 1.1);

				//glColor3ub(255, 0, 0); glutWireSphere(0.25, 30, 30);
				glTranslatef(0, 0, 0.4 + 0.7 + 1.1);
				glScalef(1, 1, -1);

				glRotatef(root[1], 1, 0, 0);
				index == 3 ? glColor3ub(255, 255, 0) : glColor3ub(255, 0, 0); glutWireSphere(0.25, 40, 40);
				glColor3ub(255, 255, 255); glutWireCylinder(0.2, 1.1, 10, 10);
				glTranslatef(0, 0, 1.1);

				glRotatef(first[1], 1, 0, 0);
				index == 4 ? glColor3ub(255, 255, 0) : glColor3ub(255, 0, 0); glutWireSphere(0.2, 40, 40);
				glColor3ub(255, 255, 255); glutWireCylinder(0.2, 0.7, 10, 10);
				glTranslatef(0, 0, 0.7);

				glRotatef(second[1], 1, 0, 0);
				index == 5 ? glColor3ub(255, 255, 0) : glColor3ub(255, 0, 0); glutWireSphere(0.2, 40, 40);
				glColor3ub(255, 255, 255); glutWireCylinder(0.2, 0.4, 10, 10);
				glTranslatef(0, 0, 0.4);

				glColor3ub(255, 255, 255); glutWireSphere(0.2, 10, 10);
				glPopMatrix();
		#pragma endregion

		#pragma region middleFinger
				glPushMatrix();
				glScalef(1.2, 1.2, 1.2);
				glTranslatef(0.07, 0.35, -0.4);
				//glColor3ub(255, 255, 255); glutWireSphere(0.2, 10, 10);
				//glColor3ub(255, 255, 255); glutWireCylinder(0.2, 0.5, 10, 10);
				//glTranslatef(0, 0, 0.5);

				//glColor3ub(255, 0, 0); glutWireSphere(0.2, 20, 20);
				////glRotatef(20, 1, 0, 0);
				//glColor3ub(255, 255, 255); glutWireCylinder(0.2, 0.7, 10, 10);
				//glTranslatef(0, 0, 0.7);

				//glColor3ub(255, 0, 0); glutWireSphere(0.2, 20, 20);
				////glRotatef(20, 1, 0, 0);
				//glColor3ub(255, 255, 255); glutWireCylinder(0.2, 1.3, 10, 10);
				//glTranslatef(0, 0, 1.3);

				//glColor3ub(255, 0, 0); glutWireSphere(0.25, 30, 30);
				glTranslatef(0, 0, 2.5);
				glScalef(1, 1, -1);

				glRotatef(root[2], 1, 0, 0);
				index == 6 ? glColor3ub(255, 255, 0) : glColor3ub(255, 0, 0); glutWireSphere(0.25, 30, 30);
				glColor3ub(255, 255, 255); glutWireCylinder(0.2, 1.3, 10, 10);
				glTranslatef(0, 0, 1.3);

				glRotatef(first[2], 1, 0, 0);
				index == 7 ? glColor3ub(255, 255, 0) : glColor3ub(255, 0, 0); glutWireSphere(0.2, 40, 40);
				glColor3ub(255, 255, 255); glutWireCylinder(0.2, 0.7, 10, 10);
				glTranslatef(0, 0, 0.7);

				glRotatef(second[2], 1, 0, 0);
				index == 8 ? glColor3ub(255, 255, 0) : glColor3ub(255, 0, 0); glutWireSphere(0.2, 40, 40);
				glColor3ub(255, 255, 255); glutWireCylinder(0.2, 0.5, 10, 10);
				glTranslatef(0, 0, 0.5);

				glColor3ub(255, 255, 255); glutWireSphere(0.2, 10, 10);

				glPopMatrix();
		#pragma endregion

		#pragma region foreFinger
				glPushMatrix();
				glTranslatef(-0.5, -0.1, 0.4);
				glScalef(1.2, 1.2, 1.2);
				glRotatef(12, 0, 1, 0);
				glTranslatef(-0.4, 0.5, -0.4);


				//glColor3ub(255, 255, 255); glutWireSphere(0.2, 10, 10);
				//glColor3ub(255, 255, 255); glutWireCylinder(0.2, 0.5, 10, 10);
				//glTranslatef(0, 0, 0.5);

				//glColor3ub(255, 0, 0); glutWireSphere(0.2, 20, 20);
				////glRotatef(20, 1, 0, 0);
				//glColor3ub(255, 255, 255); glutWireCylinder(0.2, 0.55, 10, 10);
				//glTranslatef(0, 0, 0.55);

				//glColor3ub(255, 0, 0); glutWireSphere(0.2, 20, 20);
				////glRotatef(20, 1, 0, 0);
				//glColor3ub(255, 255, 255); glutWireCylinder(0.2, 1.1, 10, 10);
				//glTranslatef(0, 0, 1.1);

				//glColor3ub(255, 0, 0); glutWireSphere(0.25, 30, 30);
				glTranslatef(0, 0, 0.5 + 0.55 + 1.1);
				glScalef(1, 1, -1);

				glRotatef(root[3], 1, 0, 0);
				index == 9 ? glColor3ub(255, 255, 0) : glColor3ub(255, 0, 0); glutWireSphere(0.25, 30, 30);
				glColor3ub(255, 255, 255); glutWireCylinder(0.2, 1.1, 10, 10);
				glTranslatef(0, 0, 1.1);

				glRotatef(first[3], 1, 0, 0);
				index == 10 ? glColor3ub(255, 255, 0) : glColor3ub(255, 0, 0); glutWireSphere(0.2, 30, 30);
				glColor3ub(255, 255, 255); glutWireCylinder(0.2, 0.55, 10, 10);
				glTranslatef(0, 0, 0.55);

				glRotatef(second[3], 1, 0, 0);
				index == 11 ? glColor3ub(255, 255, 0) : glColor3ub(255, 0, 0); glutWireSphere(0.2, 30, 30);
				glColor3ub(255, 255, 255); glutWireCylinder(0.2, 0.5, 10, 10);
				glTranslatef(0, 0, 0.5);

				glColor3ub(255, 255, 255); glutWireSphere(0.2, 10, 10);
				glPopMatrix();
		#pragma endregion

		#pragma region Thumb
				glPushMatrix();
				glTranslatef(-1.1, -0.1, 1.7);

				glScalef(1.2, 1.2, 1.2);
				glRotatef(60, 0, 1, 0);
				glTranslatef(-1.35, -0.05, -0.6);

				//glColor3ub(255, 255, 255); glutWireSphere(0.25, 10, 10);
				//glColor3ub(255, 255, 255); glutWireCylinder(0.25, 0.5, 10, 10);
				//glTranslatef(0, 0, 0.4);

				//glColor3ub(255, 0, 0); glutWireSphere(0.25, 20, 20);
				////glRotatef(20, 1, 0, 0);
				//glColor3ub(255, 255, 255); glutWireCylinder(0.25, 0.7, 10, 10);
				//glTranslatef(0, 0, 0.7);

				//glColor3ub(255, 0, 0); glutWireSphere(0.3, 30, 30);

				glTranslatef(0, 0, 0.5 + 0.7);
				glScalef(1, 1, -1);

				glRotatef(first[4], 1, 0, 0);
				index == 12 ? glColor3ub(255, 255, 0) : glColor3ub(255, 0, 0); glutWireSphere(0.3, 30, 30);
				glColor3ub(255, 255, 255); glutWireCylinder(0.25, 0.7, 10, 10);
				glTranslatef(0, 0, 0.7);

				glRotatef(second[4], 1, 0, 0);
				index == 13 ? glColor3ub(255, 255, 0) : glColor3ub(255, 0, 0); glutWireSphere(0.25, 20, 20);
				glColor3ub(255, 255, 255); glutWireCylinder(0.25, 0.5, 10, 10);
				glTranslatef(0, 0, 0.5);

				glColor3ub(255, 255, 255); glutWireSphere(0.25, 10, 10);
				glPopMatrix();
		#pragma endregion

		glPopMatrix();
	}

private:
	GLFrame* object;
	GLMmodel* palm;
	GLMmodel* arm;
	GLMmodel* Lower_arm;
	GLMmodel* Upper_arm;
	float root[4];
	float first[5];
	float second[5];

	int index;
};