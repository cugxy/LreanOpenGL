#include <GL/glut.h>

void Initial(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-10.0f, 10.0f, -10.0f, 10.0f);
}

void Triangle(GLsizei model)
{
	if (1 == model)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLES);
		glVertex2f(0.0f, 0.0f);
		glVertex2f(5.0f, -5.0f);
		glVertex2f(-5.0f, -5.0f);
	glEnd();
}

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glViewport(0, 0, 200, 200);
	Triangle(1);

	glColor3f(1.0, 0.0, 0.0);
	glViewport(200, 0, 200, 200);
	Triangle(2);

	glFlush();
}

void main(void)
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 200);
	glutCreateWindow("Multi Viewer");
	Initial();
	glutDisplayFunc(Display);
	glutMainLoop();
}









