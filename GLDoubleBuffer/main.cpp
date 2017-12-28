#include <gl\glut.h>
int nPointNum = 0;
int x1 = 0;
int x2 = 0;
int y1 = 0;
int y2 = 0;
int winWidth = 400;
int winHight = 300;

void Initial(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void changeSize(int w, int h)
{
	winWidth = w;
	winHight = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, winWidth, 0.0, winHight);
}

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 0.0f);
	if (nPointNum >= 1)
	{
		glBegin(GL_LINES);
			glVertex2i(x1, y1);
			glVertex2i(x2, y2);
		glEnd();
	}
	glutSwapBuffers();
}

void MosePlot(GLint button, GLint action, GLint xMouse, GLint yMouse)
{
	if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
	{
		if (nPointNum == 0 || nPointNum == 2)
		{
			nPointNum = 1;
			x1 = xMouse;
			y1 = winHight - yMouse;
		}
		else
		{
			nPointNum = 2;
			x2 = xMouse;
			y2 = winHight = yMouse;
			glutPostRedisplay();
		} 
	}
	if (button == GLUT_RIGHT_BUTTON && action == GLUT_DOWN)
	{
		nPointNum = 0;
		glutPostRedisplay();
	}
}

void PassiveMouseMove(GLint xMouse, GLint yMouse)
{
	if (nPointNum == 1)
	{
		x2 = xMouse;
		y2 = winHight - yMouse;
		glutPostRedisplay();
	}
}


int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(400, 300);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("ÏðÆ¤½î¼¼Êõ");
	glutDisplayFunc(Display);
	glutReshapeFunc(changeSize);
	glutMouseFunc(MosePlot);
	glutPassiveMotionFunc(PassiveMouseMove);
	Initial();
	glutMainLoop();
	return 0;
}
