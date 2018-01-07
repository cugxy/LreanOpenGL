#include <GL/glut.h>

GLuint lineList;

void Initial(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glLineWidth(12.0f);
	glColor4f(0.0f, 0.6f, 1.0f, 1.0f);
	lineList = glGenLists(1);
	glNewList(lineList, GL_COMPILE);
		glBegin(GL_LINE_LOOP);
		glVertex2f(1.0f, 1.0f);
		glVertex2f(4.0f, 2.0f);
		glVertex2f(2.0f, 5.0f);
		glEnd();
	glEndList();
}

void ChangeSize(GLsizei w, GLsizei h)
{
	if (h == 0) h = 1;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		gluOrtho2D(0.0, 5.0, 0.0, 6.0 *(GLfloat)h / (GLfloat)w);
	else
		gluOrtho2D(0.0, 5.0 *(GLfloat)w / (GLfloat)h, 0.0, 6.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Displayt(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glCallList(lineList);
	glFlush();
}

void Displayw(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glCallList(lineList);
	glFlush();
}

void main(void)
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Original graphics");
	glutDisplayFunc(Displayt);
	glutReshapeFunc(ChangeSize);
	Initial();

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(300, 300);
	glutCreateWindow("Anti aliasing graphics");
	glutDisplayFunc(Displayw);
	glutReshapeFunc(ChangeSize);
	Initial();

	glutMainLoop();
}