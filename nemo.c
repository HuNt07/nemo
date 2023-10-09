#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
#include<unistd.h>
#include <emscripten.h>
#define pi 3.142857
// HELLO LET ME GUIDE U THROUGH THIS
int s_width;
int s_height;
int x_eyes_1=0,x_eyes_2=0,y_eyes_1=0,y_eyes_2=0;
int  m1=0,m2=0;
int mousex,mousey;
int key_pressed;
//This function decides the position of eyes based on the pointer position
void mouse_pointer(int x,int y){
mousex=x;
mousey=y;
x_eyes_1=20*cos(atan2(x-(s_width/2-100),y-(s_height/2-75)));
x_eyes_2=20*cos(atan2(x-(s_width/2+100),y-(s_height/2-75)));
y_eyes_1=20*sin(atan2(x-(s_width/2-100),y-(s_height/2-75)));
y_eyes_2=20*sin(atan2(x-(s_width/2+100),y-(s_height/2-75)));
glutPostRedisplay();
}
//This function takes care of the key presses
void keyboard(unsigned char key,int x,int y){
  key_pressed=key;
  printf("%d %c\n",key,key);
  glutPostRedisplay();
}
//This function helps to set things up
void myInit (void)
{
    // making background color black as first
    // 3 arguments all are 0.0
    glClearColor(0.0, 0.0, 0.0, 1.0);
    s_width=glutGet(GLUT_SCREEN_WIDTH);
    s_height=glutGet(GLUT_SCREEN_HEIGHT);
    glColor3f(1.0, 1.0, 0.0);
    // sets breadth of picture boundary
    glPointSize(10.5);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f,glutGet(GLUT_SCREEN_WIDTH),glutGet(GLUT_SCREEN_HEIGHT),0.0f,0.0f,1.0f);
}

void display (void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    glColor3f(1.0,1.0,0.0);
    float x, y, i;
  if(key_pressed==98||key_pressed==99){
  x_eyes_1=x_eyes_2=y_eyes_1=y_eyes_2=0;
  }
//here starts the dreadzone of the for loops it sounds like a book name :)))
// i have written a lot for for loops for basically the very similar tasks
// i am not proud of it 
    
    // iterate y up to 2*pi, i.e., 360 degree
    // with small increment in angle as
    // glVertex2i just draws a point on specified co-ordinate
//This draws the base emoji outline
   for ( i = 0; i < (2*pi); i += 0.01)
    {
        // let 200 is radius of circle and as,
        // circle is defined as x=r*cos(i) and y=r*sin(i)
        x =s_width/2  + 220 * cos(i);
        y =s_height/2 + 220 * sin(i);
        glVertex2i(x, y);
    }
// this is draws the eyes which follow the mouse pointer
   for (i = 0; i < (2*pi); i += 0.01)
    {
        // let 200 is radius of circle and as,
        // circle is defined as x=r*cos(i) and y=r*sin(i)
        x =-x_eyes_1+s_width/2-100+(10*cos(i));
        y =y_eyes_1+s_height/2-75+(10 * sin(i));
        float z=-x_eyes_2+(s_width/2)+100+((10*cos(i)));
        float w=y_eyes_2+(s_height/2)-75+(10*sin(i));
        glVertex2i(z,w);
        glVertex2i(x,y);
    }
// this is the center of the eye 
// its drawn seperately for some reason
    glVertex2i(-x_eyes_1+s_width/2-100,y_eyes_1+s_height/2-75);
    glVertex2i(-x_eyes_2+s_width/2+100,y_eyes_2+s_height/2-75);
//this are the various reactions to the key_pressed
    switch(key_pressed){
// this is happy
    case 104:
    for (float j=0.75; j<2.35; j+= 0.01){
        // let 200 is radius of circle and as,
        // circle is defined as x=r*cos(i) and y=r*sin(i)
        float a= s_width/2+(125  *  cos(j));
        float b= s_height/2+(125 * sin(j));
        glVertex2i(a,b);
        }
        break;
// this is sad    
    case 115:
    for (float j=-0.75; j>-2.35; j-= 0.01){
        // let 200 is radius of circle and as,
        // circle is defined as x=r*cos(i) and y=r*sin(i)
        float a= s_width/2+(125  *  cos(j));
        float b= s_height/2+175+(125 * sin(j));
        glVertex2i(a,b);
        }
        break;
//this is blush    
    case 98:
    for(float j=0.75; j<2.35; j+= 0.01){
        // let 200 is radius of circle and as,
        // circle is defined as x=r*cos(i) and y=r*sin(i)
        float a= s_width/2+( 125  *  cos(j));
        float b= s_height/2+(125 * sin(j));
        glVertex2i(a,b);
        }
    for (i = 0; i < (2*pi); i += 0.01){
        // let 200 is radius of circle and as,
        // circle is defined as x=r*cos(i) and y=r*sin(i)
        for(float e=6;e<30;e+=0.01){
        x=s_width/2-125+(e*cos(i));
        y=s_height/2+25+(e* sin(i));
        float z=(s_width/2)+125+((e*cos(i)));
        float w=(s_height/2)+25+(e*sin(i));
       glColor4f(1.0,0.0,0.0,0.3);
        glVertex2i(z,w);
        glVertex2i(x,y);}
        }
    break;
// this is cry
   case 99:
    for (float j=-0.75; j>-2.35; j-= 0.01){
        // let 200 is radius of circle and as,
        // circle is defined as x=r*cos(i) and y=r*sin(i)
        float a= s_width/2+(125  *  cos(j));
        float b= s_height/2+175+(125 * sin(j));
        glVertex2i(a,b);
     }
   glColor3f(0.0,1.0,1.0);
   for (i = 0; i < (2*pi); i += 0.01)
    {
        // let 200 is radius of circle and as,
        // circle is defined as x=r*cos(i) and y=r*sin(i)
        for(int j=75;j>50;j--){
        x =s_width/2-100+(5*cos(i));
        y =s_height/2-j+8+(5* sin(i));
        float z=(s_width/2)+100+((5*cos(i)));
        float w=(s_height/2)-j+8+(5*sin(i));
        glVertex2i(z,w);
        glVertex2i(x,y);
        }
    }
   break;
// this is astonished maybe
   case 111:
      for ( i = 0; i < (2*pi); i += 0.01)
    {
        // let 200 is radius of circle and as,
        // circle is defined as x=r*cos(i) and y=r*sin(i)
        x =s_width/2  + 20 * cos(i);
        y =s_height/2+150 + 20 * sin(i);
        glVertex2i(x, y);
    }
   default:
    for(float j=s_width/2-75;j<s_width/2+75;j+=0.01){
    float p=j;
    float q=s_height/2+75;
    glVertex2i(p,q);
    }
   }
    glEnd();
    glFlush();
}

EMSCRIPTEN_KEEPALIVE
void registerKeyboardCallback()
{
    glutKeyboardFunc(keyboard);
}
int main (int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    // giving window size in X- and Y- direction
    glutInitWindowSize(glutGet(GLUT_SCREEN_WIDTH),glutGet(GLUT_SCREEN_HEIGHT));
    glutInitWindowPosition(0, 0);
    // Giving name to window
    glutCreateWindow("Emo-Interactive Emoji");
    myInit();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutPassiveMotionFunc(mouse_pointer);
    glutMainLoop();
}
