#include "StdAfx.h"
#include "Sphere.h"


Sphere::Sphere(void)
{
}


Sphere::~Sphere(void)
{
}

void CALLBACK Sphere::resize(int width,int height)
{
   glViewport(0,0,width,height);
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   glOrtho(-5,5, -5,5, 2,12);   
   gluLookAt( 0,0,5, 0,0,0, 0,1,0 );
   glMatrixMode( GL_MODELVIEW );
}    
void CALLBACK Sphere::display(void)
{
   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glPushMatrix();       // сохраняем текущие координаты
     glTranslated(1.4,0,0);  // сдвигаемся по оси Х на единицу 
     glColor3d(0,1,0);
//     auxSolidSphere(0.5); // рисуем сферу в (1,0,0)  в абсолютных координатах
     glPopMatrix();  // возвращаемся к старой системе координат
//     auxSwapBuffers();
}