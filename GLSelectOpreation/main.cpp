#include <GL/glut.h>
#include "stdio.h"

const GLint knPickSize = 32;
int nWinWidth = 400;
int nWinHeight = 300;

void Initial(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void DrawRect(GLenum model)
{
	if (model == GL_SELECT)
		glPushName(1);
	glColor3f(1.0f, 0.0f, 0.0f);
	glRectf(60.0f, 50.0f, 150.0f, 150.0f);
	if (model == GL_SELECT)
		glPushName(1);
	glColor3f(0.0f, 1.0f, 0.0f);
	glRectf(230.0f, 50.0f, 330.0f, 150.0f);
	if (model == GL_SELECT)
		glPushName(1);
	glColor3f(0.0f, 0.0f, 1.0f);
	glRectf(140.0f, 140.0f, 240.0f, 240.0f);
}

void ProcessPicks(GLint nPicks, GLuint pickBuffer[])
{
	GLint i = 0;
	GLuint name = 0;
	GLuint *ptr = 0;
	printf("选中数目为%d个 \n", nPicks);
	ptr = pickBuffer;
	for (int i = 0; i < nPicks; ++i)
	{
		name = *ptr;
		ptr += 3;
		ptr += name - 1;
		if (name == 1)
			printf("Red");
		if (name == 2)
			printf("blue");
		if (name == 3)
			printf("green");
		++ptr;
	}
	printf("/n");
}

void ChangeSize(int w, int h)
{
	nWinWidth = w;
	nWinHeight = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, nWinWidth, 0.0, nWinHeight);
}

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	DrawRect(GL_RENDER);
	glFlush();
}

void MousePlot(GLint button, GLint action, GLint xMouse, GLint yMouse)
{
	GLuint pickBuffer[knPickSize];
	GLint nPicks;
	GLint vp[4];
	if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
	{
		glSelectBuffer(knPickSize, pickBuffer);
		glRenderMode(GL_SELECT);
		glInitNames();
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glGetIntegerv(GL_VIEWPORT, vp);
		gluPickMatrix(GLdouble(xMouse), GLdouble(vp[3] - yMouse), 10.0, 10.0, vp);
		gluOrtho2D(0.0, nWinWidth, 0.0, nWinHeight);
		DrawRect(GL_SELECT);
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glFlush();
		nPicks = glRenderMode(GL_RENDER);
		ProcessPicks(nPicks, pickBuffer);
		glutPostRedisplay();
	}
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 300);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Select ");
	glutDisplayFunc(Display);
	glutReshapeFunc(ChangeSize);
	glutMouseFunc(MousePlot);
	Initial();
	glutMainLoop();
	return 0;
}

















