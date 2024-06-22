#include <GL/freeglut.h>
#include <GL/gl.h>
#include <math.h>

void SetPixel(int x, int y)
{
    glColor3f(0,0,0);
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
}

void dda(int xs, int ys, int xe, int ye)
{
    float dx, dy, steps;
    float xinc, yinc, x, y;

    dx = xe - xs;
    dy = ye - ys;

    if(abs(dx) > abs(dy))
    {
        steps = abs(dx);
    }
    else
    {
        steps = abs(dy);
    }

    xinc = dx/steps;
    yinc = dy/steps;

    x=xs;
    y=ys;

    SetPixel(round(x), round(y));
    for(int i=0; i<steps; i++)
    {
        x = x + xinc;
        y = y + yinc;
        SetPixel(round(x), round(y));
    }
}


void renderFunction()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0,0.0);
    gluOrtho2D(0,700,0,500);
    glBegin(GL_LINES);

//front
    dda(175, 350, 175, 280);
    dda(215, 280, 215, 350);
    dda(175, 350, 215, 350);
    dda(175, 280, 215, 280);

//window
    dda(185, 295, 205, 295);
    dda(205, 295, 205, 325);
    dda(205, 325, 185, 325);
    dda(185, 325, 185, 295);

//rest of the house
    dda(215, 280, 300, 305);
    dda(165, 330, 195, 390);
    dda(225, 330, 195, 390);
    dda(225, 330, 310, 355);

    dda(195, 390, 280, 415);
    dda(280, 415, 310, 355);
    dda(300, 305, 300, 353);
    dda(165, 330, 175, 335);
    dda(249, 290, 249, 325);
    dda(266, 295, 266, 330);
    dda(266, 330, 249, 325);



    glEnd();
    glFlush();
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(700,500);
    glutInitWindowPosition(100,100);
    glutCreateWindow("OpenGL - house using dda");
    glutDisplayFunc(renderFunction);
    glutMainLoop();
    return 0;
}
