#include "pch.h"
#include <iostream>
#include <windows.h>
#include <gl/gl.h>
#include <glut.h>
#include <math.h>
using namespace std;

typedef float point3[3];
static GLfloat lightCamera[] = { 0.0,0.0,10.0,1.0 };
static GLfloat lightCamera2[] = { 10.0,0.0,0.0,1.0 };
static GLfloat thetaTab[] = { 0.0, 0.0, 0.0 };
static int x_pos_old = 0;
static int x_pos_old_right = 0;
static int delta_x = 0;
static GLfloat pix2angle;
static GLfloat fi = 0.0;
static GLfloat fiDeg = 0.0;
static GLfloat fi2 = 0.0;
static GLfloat fi2Deg = 0.0;
static GLfloat theta2 = 0.0;
static GLfloat theta2Deg = 0.0;
static GLint status = 0; 
static GLfloat scale = 10.0;
static int y_pos_old = 0;

static int y_pos_old_right = 0;

static int delta_y = 0;

static GLfloat theta = 0.0;
static GLfloat thetaDeg = 0.0;
static int delta_y_right = 0;
static int delta_x_right = 0;
float x(float u, float v)
{
	return (-90 * u*u*u*u*u + 225 * u*u*u*u - 270 * u*u*u + 180 * u*u - 45*u)*cos(3.14f*v);
}

float y(float u, float v)
{
	return 160 * u*u*u*u - 320 * u*u*u + 160 * u*u;
}

float z(float u, float v)
{
	return (-90 * u*u*u*u*u + 225 * u*u*u*u - 270 * u*u*u + 180 * u*u - 45*u)*sin(3.14f*v);
}

void Mouse(int btn, int state, int x, int y)
{
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		x_pos_old = x;
		y_pos_old = y;
		status = 1;
	}
	else if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		y_pos_old_right = y;
		x_pos_old_right = x;
		status = 2;
	}
	else

		status = 0;
}

void spinEgg()
{

	thetaTab[0] -= 0.5;
	if (thetaTab[0] > 360.0) thetaTab[0] -= 360.0;

	thetaTab[1] -= 0.5;
	if (thetaTab[1] > 360.0) thetaTab[1] -= 360.0;

	thetaTab[2] -= 0.5;
	if (thetaTab[2] > 360.0) thetaTab[2] -= 360.0;

	glutPostRedisplay();
}

void Egg(void)
{
	glRotated(-40.0, 1.0, 0.0, 0.0);
	const int N = 40;
	float tabx[N][N];
	float taby[N][N];
	float tabz[N][N];
	float tabu[N][N];
	float tabv[N][N];
	float u, v;
	for (int i = 0; i < N; i++)
	{
		u = (float)i / (N - 1);
		for (int j = 0; j < N; j++)
		{
			v = (float)j / (N - 1);
			tabu[i][j] = u;
			tabv[i][j] = v;
		}
	}
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			tabx[i][j] = x(tabu[i][j], tabv[i][j]);
			taby[i][j] = y(tabu[i][j], tabv[i][j]);
			
			tabz[i][j] = z(tabu[i][j], tabv[i][j]);
		}
	}

	glBegin(GL_POINTS);
	glColor3i(INT_MAX, INT_MAX, INT_MAX);
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			glVertex3f(tabx[i][j], taby[i][j]-5.0f, tabz[i][j]);
		}
	}
	glEnd();

}

void Eggmodel(void)
{
	glRotated(-40.0, 1.0, 0.0, 0.0);
	const int N = 40;
	float tabx[N][N];
	float taby[N][N];
	float tabz[N][N];
	float tabu[N][N];
	float tabv[N][N];
	float u, v;
	for (int i = 0; i < N; i++)
	{
		u = (float)i / (N - 1);
		for (int j = 0; j < N; j++)
		{
			v = (float)j / (N - 1);
			tabu[i][j] = u;
			tabv[i][j] = v;
		}
	}
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			tabx[i][j] = x(tabu[i][j], tabv[i][j]);
			taby[i][j] = y(tabu[i][j], tabv[i][j]);
			tabz[i][j] = z(tabu[i][j], tabv[i][j]);
		}
	}

	glBegin(GL_LINES);
	glColor3i(INT_MAX, INT_MAX, INT_MAX);
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			glVertex3f(tabx[i][j], taby[i][j] - 5.0f, tabz[i][j]);
			if (j < N - 1)
			{
				glVertex3f(tabx[i][j + 1], taby[i][j + 1] - 5.0f, tabz[i][j + 1]);
			}
			else
			{
				if (i<N-1)
					glVertex3f(tabx[i+1][j], taby[i+1][j] - 5.0f, tabz[i+1][j]);
				else 
					glVertex3f(tabx[i][j], taby[i][j] - 5.0f, tabz[i][j]);
			}
		}
	}
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			glVertex3f(tabx[j][i], taby[j][i] - 5.0f, tabz[j][i]);
			if (j < N - 1)
			{
				glVertex3f(tabx[j+1][i], taby[j+1][i] - 5.0f, tabz[j+1][i]);
			}
			else
			{
				if (i < N - 1)
					glVertex3f(tabx[j][i+1], taby[j][i+1] - 5.0f, tabz[j][i+1]);
				else
					glVertex3f(tabx[j][i], taby[j][i] - 5.0f, tabz[j][i]);
			}
		}
	}
	glEnd();

}

void Eggtriangle(void)
{
	float xu, xv, yu, yv, zu, zv;
	glRotated(-40.0, 1.0, 0.0, 0.0);
	const int N = 140;
	float tabx[N][N];
	float taby[N][N];
	float tabz[N][N];
	float tabu[N][N];
	float tabv[N][N];
	float u, v;
	for (int i = 0; i < N; i++)
	{
		u = (float)i / (N - 1);
		for (int j = 0; j < N; j++)
		{
			v = (float)j / (N - 1);
			tabu[i][j] = u;
			tabv[i][j] = v;
		}
	}
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			tabx[i][j] = x(tabu[i][j], tabv[i][j]);
			taby[i][j] = y(tabu[i][j], tabv[i][j]);
			tabz[i][j] = z(tabu[i][j], tabv[i][j]);
		}
	}
			glBegin(GL_TRIANGLES);
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					if(tabu[i][j]<0.5f)
					glColor3f(tabu[i][j], tabv[i][j], tabu[i][j]);
					else
					glColor3f(tabu[N-i][N-j], tabv[N-i][N-j], tabu[N-i][N-j]);
					if (j < (N - 1)&&i<(N-1))
					{
						xu = ((-450 * tabu[i][j] * tabu[i][j] * tabu[i][j] * tabu[i][j]) + (900 * tabu[i][j] * tabu[i][j] * tabu[i][j]) - (810 * tabu[i][j] * tabu[i][j]) + (360 * tabu[i][j]) - 45)*cos(3.14*tabv[i][j]);
						glVertex3f(tabx[i][j], taby[i][j] - 5.0f, tabz[i][j]);
						glVertex3f(tabx[i][j + 1], taby[i][j + 1] - 5.0f, tabz[i][j + 1]);
						glVertex3f(tabx[i+1][j], taby[i+1][j] - 5.0f, tabz[i+1][j]);
					}

				}
			}
			glEnd();
			glBegin(GL_TRIANGLES);
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					if (tabu[i][j] < 0.5f)
						glColor3f(tabu[i][j], tabv[i][j], tabu[i][j]);
					else
						glColor3f(tabu[N - i][N - j], tabv[N - i][N - j], tabu[N-i][N-j]);
					if (j < (N - 1) && i < (N - 1))
					{
						glVertex3f(tabx[i + 1][j + 1], taby[i + 1][j + 1] - 5.0f, tabz[i + 1][j + 1]);
						glVertex3f(tabx[i][j + 1], taby[i][j + 1] - 5.0f, tabz[i][j + 1]);
						glVertex3f(tabx[i + 1][j], taby[i + 1][j] - 5.0f, tabz[i + 1][j]);
					}
				}
			}
			glEnd();
}

void Eggtrianglestrip(void)
{
	glRotated(-40.0, 1.0, 0.0, 0.0);
	const int N = 40;
	float tabx[N][N];
	float taby[N][N];
	float tabz[N][N];
	float tabu[N][N];
	float tabv[N][N];
	float u, v;
	for (int i = 0; i < N; i++)
	{
		u = (float)i / (N - 1);
		for (int j = 0; j < N; j++)
		{
			v = (float)j / (N - 1);
			tabu[i][j] = u;
			tabv[i][j] = v;
		}
	}
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			tabx[i][j] = x(tabu[i][j], tabv[i][j]);
			taby[i][j] = y(tabu[i][j], tabv[i][j]);
			tabz[i][j] = z(tabu[i][j], tabv[i][j]);
		}
	}
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i < N-1; i++)
	{
				for (int j = 0; j < N; j++)
				{
					if (tabu[i][j] < 0.5f)
						glColor3f(tabu[i][j], tabv[i][j], 0.0f);
					else
						glColor3f(tabu[N - i][N - j], tabv[N - i][N - j], 0.0f);
					glVertex3f(tabx[i][j], taby[i][j] - 5.0f, tabz[i][j]);
					glVertex3f(tabx[i + 1][j], taby[i + 1][j] - 5.0f, tabz[i + 1][j]);
				}
	}
	glEnd();
}

void Motion(GLsizei x, GLsizei y)
{

	delta_x = x - x_pos_old;
	delta_y = y - y_pos_old;
	x_pos_old = x;
	y_pos_old = y;
	delta_y_right = y - y_pos_old_right;
	delta_x_right = x - x_pos_old_right;
	y_pos_old_right = y;
	x_pos_old_right = x;
	glutPostRedisplay();
}

void Axes(void)
{

	point3  x_min = { -5.0, 0.0, 0.0 };
	point3  x_max = { 5.0, 0.0, 0.0 };
	point3  y_min = { 0.0, -5.0, 0.0 };
	point3  y_max = { 0.0,  5.0, 0.0 };
	point3  z_min = { 0.0, 0.0, -5.0 };
	point3  z_max = { 0.0, 0.0,  5.0 };
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3fv(x_min);
	glVertex3fv(x_max);
	glEnd();

	glColor3f(0.0f, 1.0f, 0.0f); 
	glBegin(GL_LINES); 

	glVertex3fv(y_min);
	glVertex3fv(y_max);
	glEnd();

	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);

	glVertex3fv(z_min);
	glVertex3fv(z_max);
	glEnd();

}

void RenderScene(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Czyszczenie okna aktualnym kolorem czyszcz¹cym

	glLoadIdentity();
	// Czyszczenie macierzy bie¿¹cej
	if (status == 1)
	{
		theta += (delta_x * pix2angle*3.1415926) / 180;
		fi += (delta_y * pix2angle*3.1415926) / 180;
		fiDeg += delta_y * pix2angle;
		while (fiDeg > 360)
			fiDeg -= 360;
		while (fiDeg < 0)
			fiDeg += 360;
		thetaDeg += delta_x * pix2angle;
		while (thetaDeg > 360)
			thetaDeg -= 360;
		while (thetaDeg < 0)
			thetaDeg += 360;
	}
	if (status == 2)
	{
		theta2 += (delta_x_right * pix2angle*3.1415926) / 180;
		fi2 += (delta_y_right * pix2angle*3.1415926) / 180;
		fi2Deg += delta_y_right * pix2angle;
		while (fi2Deg > 360)
			fi2Deg -= 360;
		while (fi2Deg < 0)
			fi2Deg += 360;
		theta2Deg += delta_x_right * pix2angle;
		while (theta2Deg > 360)
			theta2Deg -= 360;
		while (theta2Deg < 0)
			theta2Deg += 360;
	}
	lightCamera[0] = scale * cos(theta)*cos(fi);
	lightCamera[1] = scale * sin(fi);
	lightCamera[2] = scale * sin(theta)*cos(fi);
	lightCamera2[0] = scale * cos(theta2)*cos(fi2);
	lightCamera2[1] = scale * sin(fi2);
	lightCamera2[2] = scale * sin(theta2)*cos(fi2);
	glLightfv(GL_LIGHT0, GL_POSITION, lightCamera);
	glLightfv(GL_LIGHT1, GL_POSITION, lightCamera2);
	GLfloat light_diffuse[] = { lightCamera[0], lightCamera[1], lightCamera[2], 1.0 };
	GLfloat light_diffuse2[] = { lightCamera2[0], lightCamera2[1], lightCamera2[2], 1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse2);
	glPointSize(10);
	glBegin(GL_POINTS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex4f(-lightCamera[0],-lightCamera[2],-lightCamera[1],1.0);

	glVertex4f(-lightCamera2[0], -lightCamera2[2], -lightCamera2[1],1.0);

	glEnd();
	// Narysowanie osi przy pomocy funkcji zdefiniowanej wy¿ej
	/*glRotatef(theta[0], 1.0, 0.0, 0.0);

	glRotatef(theta[1], 0.0, 1.0, 0.0);

	glRotatef(theta[2], 0.0, 0.0, 1.0);
	*/
	Eggtriangle();
	glFlush();
	// Przekazanie poleceñ rysuj¹cych do wykonania


	glutSwapBuffers();
	//
}

void MyInit(void)
{

	// Definicja materia³u z jakiego zrobiony jest czajnik

	GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
	// wspó³czynniki ka =[kar,kag,kab] dla œwiat³a otoczenia

	GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	// wspó³czynniki kd =[kdr,kdg,kdb] œwiat³a rozproszonego

	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	// wspó³czynniki ks =[ksr,ksg,ksb] dla œwiat³a odbitego               

	GLfloat mat_shininess = { 20.0 };
	// wspó³czynnik n opisuj¹cy po³ysk powierzchni


/*************************************************************************************/
// Definicja Ÿród³a œwiat³a


	GLfloat light_position[] = { 0.0, 0.0, 10.0, 1.0 };
	// po³o¿enie Ÿród³a
	GLfloat light2_position[] = { 10.0, 0.0,0.0,1.0 };

	GLfloat light_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
	// sk³adowe intensywnoœci œwiecenia Ÿród³a œwiat³a otoczenia
	// Ia = [Iar,Iag,Iab]

	GLfloat light_diffuse[] = { 10.0, 1.0, 1.0, 1.0 };
	GLfloat light_diffuse2[] = { 1.0, 1.0, 10.0, 1.0 };
	// sk³adowe intensywnoœci œwiecenia Ÿród³a œwiat³a powoduj¹cego
	// odbicie dyfuzyjne Id = [Idr,Idg,Idb]

	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	// sk³adowe intensywnoœci œwiecenia Ÿród³a œwiat³a powoduj¹cego
	// odbicie kierunkowe Is = [Isr,Isg,Isb]

	GLfloat att_constant = { 1.0 };
	// sk³adowa sta³a ds dla modelu zmian oœwietlenia w funkcji
	// odleg³oœci od Ÿród³a

	GLfloat att_linear = { 0.05 };
	// sk³adowa liniowa dl dla modelu zmian oœwietlenia w funkcji
	// odleg³oœci od Ÿród³a

	GLfloat att_quadratic = { 0.001 };
	// sk³adowa kwadratowa dq dla modelu zmian oœwietlenia w funkcji
	// odleg³oœci od Ÿród³a

/*************************************************************************************/
// Ustawienie parametrów materia³u i Ÿród³a œwiat³a

/*************************************************************************************/
// Ustawienie patrametrów materia³u


	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);


	/*************************************************************************************/
	// Ustawienie parametrów Ÿród³a

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, att_constant);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, att_linear);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, att_quadratic);

	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse2);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, light2_position);

	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, att_constant);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, att_linear);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, att_quadratic);


	/*************************************************************************************/
	// Ustawienie opcji systemu oœwietlania sceny

	glShadeModel(GL_SMOOTH); // w³aczenie ³agodnego cieniowania
	glEnable(GL_LIGHTING);   // w³aczenie systemu oœwietlenia sceny
	glEnable(GL_LIGHT0);     // w³¹czenie Ÿród³a o numerze 0
	glEnable(GL_LIGHT1);
	glEnable(GL_DEPTH_TEST); // w³¹czenie mechanizmu z-bufora

/*************************************************************************************/
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// Kolor czyszc¹cy (wype³nienia okna) ustawiono na czarny

}

void ChangeSize(GLsizei horizontal, GLsizei vertical)
{
	pix2angle = 360.0 / (float)horizontal;
	GLfloat AspectRatio;
	if (vertical == 0)
		vertical = 1;
	glViewport(0, 0, horizontal, vertical);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();          
	AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;           
	if (horizontal <= vertical)
		glOrtho(-7.5, 7.5, -7.5 / AspectRatio, 7.5 / AspectRatio, 10.0, -10.0);
	else
		glOrtho(-7.5*AspectRatio, 7.5*AspectRatio, -7.5, 7.5, 10.0, -10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(300, 300);

	glutCreateWindow("Uk³ad wspó³rzêdnych 3-D");

	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	//glutIdleFunc(spinEgg);
	MyInit();
	// Funkcja MyInit() (zdefiniowana powy¿ej) wykonuje wszelkie
	// inicjalizacje konieczne  przed przyst¹pieniem do renderowania
	glEnable(GL_DEPTH_TEST);
	// W³¹czenie mechanizmu usuwania powierzchni niewidocznych

	glutMainLoop();
	// Funkcja uruchamia szkielet biblioteki GLUT 
}
