#include<GL/freeglut.h>
#include<GL/gl.h>
#include<math.h>

void getpixel(int x,int y, float interiorcolor[3]){
    glReadPixels(x,y,1,1,GL_RGB,GL_FLOAT, interiorcolor);
}

void putmypixel(int x, int y, float fillcolor[3]){
    glColor3f(0,0,0);
    glColor3fv(fillcolor);
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
    glFlush();
}

void boundaryfill(int x, int y, float fillcolor[3], float boundarycolor[3]){
    float interiorcolor[3];
    getpixel(x,y,interiorcolor);
    if((interiorcolor[0]!=boundarycolor[0]||interiorcolor[1]!=boundarycolor[1]|| interiorcolor[2]!=boundarycolor[2])&&(interiorcolor[0]!=fillcolor[0]||interiorcolor[1]!=fillcolor[1]|| interiorcolor[2]!=fillcolor[2])){
        putmypixel(x,y, fillcolor);
        boundaryfill(x+1, y, fillcolor, boundarycolor);
        boundaryfill(x-1, y, fillcolor, boundarycolor);
        boundaryfill(x, y+1, fillcolor, boundarycolor);
        boundaryfill(x, y-1, fillcolor, boundarycolor);
    }

}

void fillcolor(int x,int y){
    glPointSize(2);
    glBegin(GL_LINES);
    glVertex2i(-50,-50);
    glVertex2i(50,-50);

    glVertex2i(50,-50);
    glVertex2i(50,50);

    glVertex2i(50,50);
    glVertex2i(-50,50);

    glVertex2i(-50,50);
     glVertex2i(-50,-50);

    glEnd();
    glFlush();
    float fillcolor[3]={1.0,0.0,0.0};
    float boundarycolor[3]={0.0,0.0,0.0};
    boundaryfill(x,y,fillcolor, boundarycolor);
}

void putpixel(int x,int y){
    glColor3f(0,0,0);
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
    glFlush();
}

void drawcircle(int xshift, int yshift, int r){
    int x=0;
    int y=r;
    int p=3-(2*r);

    while(x<=y){
        putpixel(x+xshift,y+yshift);
        putpixel(x+xshift,-y+yshift);
        putpixel(-x+xshift,y+yshift);
        putpixel(-x+xshift,-y+yshift);
        putpixel(y+xshift,x+yshift);
        putpixel(-y+xshift,x+yshift);
        putpixel(-y+xshift,-x+yshift);
        putpixel(y+xshift,-x+yshift);
        if(p<0){
            x=x+1;
            p=p+(4*x)+6;
        }else{
            x=x+1;
            y=y-1;
            p=p+(4*(x-y))+10;
        }
        //putpixel(x,y);
    }
}

void renderfunction(){
    glClearColor(1,1,1,0);
    glClear(GL_COLOR_BUFFER_BIT);
    gluOrtho2D(-700,700,-500,500);

    glColor3f(0,0,0);


    drawcircle(0,0,150);
    fillcolor(0,0);

}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(1400,1000);
    glutInitWindowPosition(100,100);
    glutCreateWindow("circle");
    glutDisplayFunc(renderfunction);
    glutMainLoop();
    return 1;
}
