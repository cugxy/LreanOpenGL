#include <GL/glut.h>

static GLsizei iMode = 1;
static GLfloat fXRot = 0.0;
static GLfloat fYRot = 0.0;

GLUquadricObj *obj = 0;

void Initial(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	obj = gluNewQuadric();
	gluQuadricDrawStyle(obj, GLU_LINE);
}

void ChangeSize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.5f, 1.5f, -1.5f, 1.5f);
}

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(fXRot, 1.0f, 0.0f, 0.0f);
	glRotatef(fYRot, 0.0f, 1.0f, 0.0f);
	switch (iMode)
	{
	case 1:
		glutWireTetrahedron(); break;
	case 2:
		glutSolidTetrahedron(); break;
	case 3:
		glutWireOctahedron(); break;
	case 4:
		glutSolidOctahedron(); break;
	case 5:
		glutWireSphere(1.0f, 15, 15); break;
	case 6:
		glutSolidSphere(1.0f, 15, 15); break;
	case 7:
		glutWireTeapot(1.0f); break;
	case 8:
		glutSolidTeapot(1.0f); break;
	case 9:
		gluSphere(obj, 1.0f, 15, 15); break;
	case 10:
		gluCylinder(obj, 1.0f, 0.0f, 1.0f, 15, 15); break;
	case 11:
		gluPartialDisk(obj, 0.3f, 0.8f, 15, 15, 30.0f, 260.0f); break;
	default:
		break;
	}
	glFlush();
}

void ProcessMenu(int value)
{
	iMode = value;
	glutPostRedisplay();
}

void SpecialKeys(int key, int x, int y)
{
	if (GLUT_KEY_UP == key) fXRot -= 5.0f;
	if (GLUT_KEY_DOWN == key) fXRot += 5.0f;
	if (GLUT_KEY_LEFT == key) fYRot -= 5.0f;
	if (GLUT_KEY_RIGHT == key) fYRot += 5.0f;
	if (fXRot > 356.0f) fXRot = 0.0f;
	if (fYRot > 356.0f) fYRot = 0.0f;
	if (fXRot < -1.0f) fXRot = 355.0;
	if (fYRot < -1.0f ) fYRot = 355.0;
	glutPostRedisplay();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Draw Graphics");

	int nGlutPolyMenu = glutCreateMenu(ProcessMenu);
	glutAddMenuEntry("Wire Tetrahedron", 1);
	glutAddMenuEntry("Solid Tetrahedron", 2);
	glutAddMenuEntry("Wire Octahedron", 3);
	glutAddMenuEntry("Solid Octahedron", 4);
	
	int nGlutCurveMenu = glutCreateMenu(ProcessMenu);
	glutAddMenuEntry("Wire Sphere", 5);
	glutAddMenuEntry("Solid Sphere", 6);
	glutAddMenuEntry("Wire Teapot", 7);
	glutAddMenuEntry("Solid Teapot", 8);

	int nGluCurveMenu = glutCreateMenu(ProcessMenu);
	glutAddMenuEntry("gluSphere", 9);
	glutAddMenuEntry("gluCylinder", 10);
	glutAddMenuEntry("gluPartialDisk", 11);
	 
	int nMainMenu = glutCreateMenu(ProcessMenu);
	glutAddSubMenu("GLUT poly", nGlutPolyMenu);
	glutAddSubMenu("GLUT Sphere", nGlutCurveMenu);
	glutAddSubMenu("GLU polygon", nGluCurveMenu);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutDisplayFunc(Display);
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(SpecialKeys);
	Initial();
	glutMainLoop();
	return 0;
}



