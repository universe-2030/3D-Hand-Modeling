/*
1. ??入至少1?使用glBegin() ... glEnd()所繪製的幾?物體。
2. 使得使用者可透過鍵盤或滑鼠輸入，以glFrame控制至少??主要物體的移動
3. 利用數?glutWire*()幾?物體，繪製出至少具有三?關?的物體
利用glFrame 讓整?物體移動
使用push/pop 配合 rotate/translate/scale ，透過鍵盤輸入改變旋轉角度，旋轉關?
(Ex: 檯燈(底盤，兩?桿子，角?) )
\
>\
/ \
/
/
-------
4. 對這?具關?的物體進??段小動畫
(Ex: 仿照hw1,?定鍵盤輸入，使得物體跳躍向前，同?各關?旋轉角??相對的運動)
5. 說明文件 readme.txt須?括：(1)學號姓名(2)編譯環境(3)簡要說明你做的幾?物體、具?物體為?，以及相關操?方式
*/

#include <gltools.h>	// OpenGL toolkit
#include <glframe.h>   // Frame Class
#include <math.h>
#include <math3d.h>
#include "glm.h"
#include <iostream>
#include "Hand.h"

using namespace std;
const double R2D = 180.0 / M_PI;
const double D2R = 1 / R2D;

int			screenWidth = 1600;
int			screenHeight = 900;
GLFrame		frameCamera;
float		delta = 0;
int			cursorPos[2];
//GLfloat		whiteLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
//GLfloat		sourceLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };
//GLfloat		lightPos[] = { 0.0f, 0.0f, 0.0f, 1.0f };
bool		cameraControlMode = false;
GLFrame		hand[2];
Hand		rightHand(&hand[0]);
Hand		leftHand(&hand[1]);
int			jointIndex = 0;

//////////////////////////////////////////////////////////////////
// This function does any needed initialization on the rendering
// context.
void SetupRC()
{
	int iSphere;

	// Bluish background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glEnable(GL_DEPTH_TEST);
	// Draw everything as wire frame
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//MODEL = glmReadOBJ("hand.obj");


	//glEnable(GL_LIGHTING);
	// Setup and enable light 0
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, whiteLight);
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, sourceLight);
	//glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	//glEnable(GL_LIGHT0);

	// Enable color tracking
	//glEnable(GL_COLOR_MATERIAL);

	// Set Material properties to follow glColor values
	//glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// Randomly place the sphere inhabitants

	//for (iSphere = 0; iSphere < NUM_SPHERES; iSphere++)
	//{
	//	// Pick a random location between -20 and 20 at .1 increments
	//	float x = ((float)((rand() % 400) - 200) * 0.1f);
	//	float z = (float)((rand() % 400) - 200) * 0.1f;
	//	spheres[iSphere].SetOrigin(x, 0.0f, z);
	//}

	M3DVector3f up = { -0.614193, 0.690447, 0.382165 };
	M3DVector3f origin = { 5.12, 7.09, -5.57 };
	M3DVector3f look = { -0.51938, -0.71827, 0.4629628 };
	frameCamera.SetForwardVector(look);
	frameCamera.SetOrigin(origin);
	frameCamera.SetUpVector(up);
	frameCamera.Normalize();
}

///////////////////////////////////////////////////////////
// Draw a gridded ground
void DrawGround(void)
{
	const GLfloat fExtent = 100.0f;
	const GLfloat fStep = 0.5f;
	GLfloat y = -0.4f;
	GLfloat iLine;

	glLineWidth(1);
	glColor3ub(0,150, 150);
	glBegin(GL_LINES);
	for (iLine = -fExtent; iLine <= fExtent; iLine += fStep)
	{
		glVertex3f(iLine, y, fExtent);    // Draw Z lines
		glVertex3f(iLine, y, -fExtent);

		glVertex3f(fExtent, y, iLine); // Draw X lines
		glVertex3f(-fExtent, y, iLine);
	}
	glEnd();

	//gltDrawUnitAxes();
}

// Called to draw scene
void RenderScene(void)
{
	//frameCamera.Normalize();
	//frametorus.Normalize();
	//cout << "Camera Position: (" << frameCamera.GetOriginX() << ", " << frameCamera.GetOriginY() << ", " << frameCamera.GetOriginZ() << ")" << endl;
	//M3DVector3f tmp;
	//frameCamera.GetForwardVector(tmp);
	//cout << "Camera Lookat: (" << tmp[0] << ", " << tmp[1] << ", " << tmp[2] << ")" << endl;

	// Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	
	frameCamera.ApplyCameraTransform();

	// Draw the ground
	DrawGround();
	glTranslatef(0, 1, 0);
	//??入至少1?使用glBegin() ... glEnd()所繪製的幾?物體
#pragma region PolygonObject
	glPushMatrix();
		const float vertices[8][3] = {	{ -1, -1, -1 }, 
										{ 1, -1, -1 }, 
										{ 1, 1, -1 }, 
										{ -1, 1, -1 }, 
										{ -1, -1, 1 }, 
										{ 1, -1, 1 }, 
										{ 1, 1, 1 }, 
										{ -1, 1, 1 } };
		glTranslatef(1, 0, 1);
		//glScalef(0.1, 0.1, 0.1);
		glColor3ub(255, 0, 255);

		#pragma region PolygonObject_Solid
		
		glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonOffset(.5, .5);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		//Back
		glColor3ub(0, 0, 0);
		glBegin(GL_POLYGON);
			glNormal3f(0, 0, -1);
			glVertex3fv(vertices[0]);
			glVertex3fv(vertices[1]);
			glVertex3fv(vertices[2]);
			glVertex3fv(vertices[3]);
		glEnd();

		//Front
		glColor3ub(255, 0, 255);
		glBegin(GL_POLYGON);
			glNormal3f(0, 0, 1);
			glVertex3fv(vertices[4]);
			glVertex3fv(vertices[5]);
			glVertex3fv(vertices[6]);
			glVertex3fv(vertices[7]);
		glEnd();

		//Top
		glColor3ub(0, 0, 255);
		glBegin(GL_POLYGON);
			glNormal3f(0, 1, 0);
			glVertex3fv(vertices[0]);
			glVertex3fv(vertices[1]);
			glVertex3fv(vertices[2]);
			glVertex3fv(vertices[3]);
		glEnd();

		//Bottom
		glColor3ub(255, 255, 255);
		glBegin(GL_POLYGON);
			glNormal3f(0, -1, 0);
			glVertex3fv(vertices[1]);
			glVertex3fv(vertices[0]);
			glVertex3fv(vertices[4]);
			glVertex3fv(vertices[5]);
		glEnd();

		//Left
		glColor3ub(0, 255, 0);
		glBegin(GL_POLYGON);
			glVertex3fv(vertices[0]);
			glVertex3fv(vertices[3]);
			glVertex3fv(vertices[7]);
			glVertex3fv(vertices[4]);
		glEnd();

		//Right
		glColor3ub(255, 0, 0);
		glBegin(GL_POLYGON);
			glVertex3fv(vertices[1]);
			glVertex3fv(vertices[2]);
			glVertex3fv(vertices[6]);
			glVertex3fv(vertices[5]);
		glEnd();
		glDisable(GL_POLYGON_OFFSET_FILL);
		#pragma endregion

		#pragma region PolygonObject_Wire
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glColor3ub(255, 255, 255);
		glBegin(GL_POLYGON);
		glVertex3fv(vertices[0]);
		glVertex3fv(vertices[1]);
		glVertex3fv(vertices[2]);
		glVertex3fv(vertices[3]);
		glEnd();

		//Front
		glBegin(GL_POLYGON);
		glVertex3fv(vertices[4]);
		glVertex3fv(vertices[5]);
		glVertex3fv(vertices[6]);
		glVertex3fv(vertices[7]);
		glEnd();

		//Top
		glBegin(GL_POLYGON);
		glVertex3fv(vertices[0]);
		glVertex3fv(vertices[1]);
		glVertex3fv(vertices[2]);
		glVertex3fv(vertices[3]);
		glEnd();

		//Bottom
		glBegin(GL_POLYGON);
		glVertex3fv(vertices[1]);
		glVertex3fv(vertices[0]);
		glVertex3fv(vertices[4]);
		glVertex3fv(vertices[5]);
		glEnd();

		//Left
		glBegin(GL_POLYGON);
		glVertex3fv(vertices[0]);
		glVertex3fv(vertices[3]);
		glVertex3fv(vertices[7]);
		glVertex3fv(vertices[4]);
		glEnd();

		//Right
		glBegin(GL_POLYGON);
		glVertex3fv(vertices[1]);
		glVertex3fv(vertices[2]);
		glVertex3fv(vertices[6]);
		glVertex3fv(vertices[5]);
		glEnd();
		#pragma endregion

	glPopMatrix();
#pragma endregion


	//利用數?glutWire*()幾?物體，繪製出至少具有三?關?的物體
#pragma region JointObject
	glPushMatrix();
	//glRotatef(90, 0, 0, 1);
		rightHand.Render();
	glPopMatrix();
#pragma endregion

	glPopMatrix();

	// Do the buffer Swap
	glutSwapBuffers();
}

void objectAnimate(int i)
{
	if (i < 50)
	{
		for (int j = 0; j < 15; j++)
		{
			rightHand.setJointIndex(j);
			rightHand.fingerRotateDown();
		}
	}
	else if (i >= 50 && i<60)
	{
		hand[0].MoveForward(-0.3);
	}
	else if (i >= 60 && i < 70)
	{
		hand[0].MoveForward(0.3);
	}
	else
	{
		for (int j = 0; j < 15; j++)
		{
			rightHand.setJointIndex(j);
			rightHand.fingerRotateUp();
		}
	}

	if (++i<92)
		glutTimerFunc(5, objectAnimate, i);
}
//void bf(int i)
//{
//	/*
//	Your Implementation
//	*/
//
//	const double rad = 3.14159265359 / 180;
//	const float dist = sqrtf(pow(frameCamera.GetOriginX() - frametorus.GetOriginX(), 2) + pow(frameCamera.GetOriginZ() - frametorus.GetOriginZ(), 2));
//
//	frameCamera.RotateLocalY(1 * D2R);
//
//	frameCamera.MoveRight(-dist*sin(rad));
//
//	if ((i >= 0 && i < 90) || (i >= 270 && i < 360))
//		frameCamera.MoveForward(dist - dist*cos(rad));
//	else
//		frameCamera.MoveForward(-(dist - dist*cos(rad)));
//
//	if (i < 360)
//		glutTimerFunc(33, bf, ++i);
//
//	glutPostRedisplay();
//}

void myKeys(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'w':
			/* Your Implementation */
			//Ex:  frametorus.????
			//hand[0].MoveForward(.1f);
			if (++jointIndex > 15)
				jointIndex = 0;
			rightHand.setJointIndex(jointIndex);
			
			break;
		case 's':
			/* Your Implementation */
			//hand[0].MoveForward(-.1f);
			if (--jointIndex < 0)
				jointIndex = 15;
			rightHand.setJointIndex(jointIndex);
			
			break;
		case 'a':
			/* Your Implementation */
			//hand[0].MoveRight(.1f);
			rightHand.fingerRotateUp();
			break;
		case 'd':
			/* Your Implementation */
			//hand[0].MoveRight(-.1f);
			rightHand.fingerRotateDown();
			break;

		case 'b':
			objectAnimate(0);
			break;
		case 'p':
			cout << "Camera Position: (" << frameCamera.GetOriginX() << ", " << frameCamera.GetOriginY() << ", " << frameCamera.GetOriginZ() << ")" << endl;
			M3DVector3f tmp;
			frameCamera.GetForwardVector(tmp);
			cout << "Camera Lookat: (" << tmp[0] << ", " << tmp[1] << ", " << tmp[2] << ")" << endl;
			frameCamera.GetUpVector(tmp);
			cout << "Camera Up: (" << tmp[0] << ", " << tmp[1] << ", " << tmp[2] << ")" << endl;
			break;

		case 'r':
			M3DVector3f up = { -0.614193, 0.690447, 0.382165 };
			M3DVector3f origin = { 5.12, 7.09, -5.57 };
			M3DVector3f look = { -0.51938, -0.71827, 0.4629628 };
			frameCamera.SetForwardVector(look);
			frameCamera.SetOrigin(origin);
			frameCamera.SetUpVector(up);
			frameCamera.Normalize();
			break;

	}
	glutPostRedisplay();
}

// Respond to arrow keys by moving the camera frame of reference
void SpecialKeys(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
	{
		frameCamera.MoveForward(0.05f);
		hand[0].MoveForward(-0.05f);
	}
	if (key == GLUT_KEY_DOWN)
	{
		frameCamera.MoveForward(-0.05f);
		hand[0].MoveForward(0.05f);
	}
	if (key == GLUT_KEY_LEFT)
	{
		frameCamera.MoveRight(0.05f);
		hand[0].MoveRight(-0.05f);
		//frameCamera.RotateLocalY(0.1f);
	}
	if (key == GLUT_KEY_RIGHT)
	{
		frameCamera.MoveRight(-0.05f);
		hand[0].MoveRight(0.05f);
		//frameCamera.RotateLocalY(-0.1f);
	}
	// Refresh the Window
	glutPostRedisplay();
}

void mouseClicked(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		cameraControlMode = true;
	}
	else
	{
		cameraControlMode = false;
	}
}

int rotateCount = 0;
void mouseMotion(int x, int y)
{
	y = screenHeight - y;
	if (cameraControlMode)
	{
		if (x - cursorPos[0] > 2)
			frameCamera.MoveRight(0.1f);
		else if (x - cursorPos[0] < -2)
			frameCamera.MoveRight(-0.1f);



		//cout << "Camera Up: (" << tmp[0] << ", " << tmp[1] << ", " << tmp[2] << ")" << endl;
		if (y - cursorPos[1] > 2 && rotateCount > -30)
		{

			rotateCount--;
			frameCamera.RotateLocalX(-3 * D2R);
			const float dist = sqrtf(pow(frameCamera.GetOriginX() - hand[0].GetOriginX(), 2) +
									 pow(frameCamera.GetOriginY() - hand[0].GetOriginY(), 2) +
									 pow(frameCamera.GetOriginZ() - hand[0].GetOriginZ(), 2));
			frameCamera.MoveUp(-dist*sin(3 * D2R));
			frameCamera.MoveForward(-(dist - dist*cosf(3 * D2R)));

		}
		else if (y - cursorPos[1] < -2 && rotateCount < 30)
		{

			rotateCount++;
			frameCamera.RotateLocalX(3 * D2R);
			const float dist = sqrtf(pow(frameCamera.GetOriginX() - hand[0].GetOriginX(), 2) +
									 pow(frameCamera.GetOriginY() - hand[0].GetOriginY(), 2) +
									 pow(frameCamera.GetOriginZ() - hand[0].GetOriginZ(), 2));
			frameCamera.MoveUp(dist*sin(3 * D2R));
			frameCamera.MoveForward(dist - dist*cosf(3 * D2R));
		}

	}
	M3DVector3f camera;
	M3DVector3f object;
	frameCamera.GetOrigin(camera);
	hand[0].GetOrigin(object);
	M3DVector3f look = { object[0] - camera[0], object[1] - camera[1], object[2] - camera[2] };
	frameCamera.SetForwardVector(look);
	frameCamera.Normalize();

	cursorPos[0] = x;
	cursorPos[1] = y;

	float* temp = new float[3];
	frameCamera.GetOrigin(temp);
	std::cout << temp[0] << " " << temp[1] << " " << temp[2] << std::endl;
	frameCamera.GetForwardVector(temp);
	std::cout << temp[0] << " " << temp[1] << " " << temp[2] << std::endl;
	frameCamera.GetUpVector(temp);
	std::cout << temp[0] << " " << temp[1] << " " << temp[2] << std::endl << std::endl;

	//cout << "Cursor: " << cursorPos[0] << "," << cursorPos[1] << endl;
}

void mouseScroll(int button, int dir, int x, int y)
{
	if (dir > 0)
		frameCamera.MoveForward(0.2f);
	else
		frameCamera.MoveForward(-0.2f);
}

///////////////////////////////////////////////////////////
// Called by GLUT library when idle (window not being
// resized or moved)
void TimerFunction(int value)
{
	// Redraw the scene with new coordinates
	glutPostRedisplay();
	glutTimerFunc(3, TimerFunction, 1);
}

void ChangeSize(int w, int h)
{
	GLfloat fAspect;

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;
	screenWidth = w;
	screenHeight = h;

	glViewport(0, 0, screenWidth, screenHeight);

	fAspect = (GLfloat)screenWidth / (GLfloat)screenHeight;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set the clipping volume
	gluPerspective(70.0f, fAspect, 0.1f, 50.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glEnable(GL_MULTISAMPLE);
	glHint(GL_MULTISAMPLE_FILTER_HINT_NV, GL_NICEST);
	glutInitWindowSize(1024, 768);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("OpenGL 3D Model Demo");
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	glutKeyboardFunc(myKeys);
	glutSpecialFunc(SpecialKeys);

	//mouse control
	glutMouseFunc(mouseClicked);
	glutMouseWheelFunc(mouseScroll);
	glutMotionFunc(mouseMotion);

	cout << "操?說明：" << endl;
	cout << "\t相機操?：" << endl;
	cout << "\t\t鍵盤左右鍵：相機與物體同?向左或向右移動" << endl;
	cout << "\t\t鍵盤上下鍵：相機與物體同?向前或向後移動" << endl;
	cout << "\t\t鍵盤R鍵：??相機" << endl;
	cout << "\t\t壓著 滑鼠左或右鍵 並拖曳：相機對準關?物體做環繞" << endl;
	cout << "\t\t滑鼠滾輪：相機向前或向後移動" << endl << endl;
	cout << "\t關?操?：" << endl;
	cout << "\t\t鍵盤W鍵：下??關?" << endl;
	cout << "\t\t鍵盤S鍵：上??關?" << endl;
	cout << "\t\t鍵盤A鍵：關?向上旋轉" << endl;
	cout << "\t\t鍵盤D鍵：關?向下旋轉" << endl;
	cout << "\t\t鍵盤B鍵：物件動畫" << endl;

	SetupRC();
	glutTimerFunc(33, TimerFunction, 1);

	glutMainLoop();

	return 0;
}
