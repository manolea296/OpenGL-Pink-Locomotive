#include "glos.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glaux.h>
#include <math.h>

const float PI = 3.1415926535f;

void myinit(void);
void CALLBACK display(void);
void CALLBACK myReshape(GLsizei w, GLsizei h);
void CALLBACK idle(void);
void CALLBACK moveLeft(void);
void CALLBACK moveRight(void);
void CALLBACK rotateCamLeft(void);
void CALLBACK rotateCamRight(void);

void drawCube(float xSize, float ySize, float zSize);
void drawCylinderWheel(float radius, float thickness, int segments);
void drawLocomotive(void);
void seteazaCuloareMaterial(GLfloat r, GLfloat g, GLfloat b);

float locoX = 0.0f;       
float cameraAngle = 0.5f; 
GLfloat lightPos[] = { 4.0f, 6.0f, 3.0f, 1.0f }; 

const float LIMITA_SOL = 8.2f;

void CALLBACK moveLeft(void) 
{
    locoX -= 0.1f;
    if (locoX < -LIMITA_SOL)
    {
        locoX = -LIMITA_SOL;
    }
}

void CALLBACK moveRight(void) 
{
    locoX += 0.1f;
    if (locoX > LIMITA_SOL) 
    {
        locoX = LIMITA_SOL;
    }
}

void CALLBACK rotateCamLeft(void) { cameraAngle -= 0.05f; }
void CALLBACK rotateCamRight(void) { cameraAngle += 0.05f; }

void CALLBACK idle(void)
{
    display();
}

void seteazaCuloareMaterial(GLfloat r, GLfloat g, GLfloat b) 
{
    GLfloat mat_ambient[] = { r * 0.3f, g * 0.3f, b * 0.3f, 1.0f };
    GLfloat mat_diffuse[] = { r, g, b, 1.0f };
    GLfloat mat_specular[] = { 0.6f, 0.6f, 0.6f, 1.0f };
    GLfloat mat_shininess[] = { 32.0f };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

void drawCube(float xSize, float ySize, float zSize) 
{
    float x = xSize / 2.0f;
    float y = ySize / 2.0f;
    float z = zSize / 2.0f;

    glBegin(GL_QUADS);
    
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-x, -y, z); glVertex3f(x, -y, z); glVertex3f(x, y, z); glVertex3f(-x, y, z);
    
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(-x, -y, -z); glVertex3f(-x, y, -z); glVertex3f(x, y, -z); glVertex3f(x, -y, -z);
    
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-x, y, -z); glVertex3f(-x, y, z); glVertex3f(x, y, z); glVertex3f(x, y, -z);
    
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(-x, -y, -z); glVertex3f(x, -y, -z); glVertex3f(x, -y, z); glVertex3f(-x, -y, z);
    
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(x, -y, -z); glVertex3f(x, y, -z); glVertex3f(x, y, z); glVertex3f(x, -y, z);
   
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-x, -y, -z); glVertex3f(-x, -y, z); glVertex3f(-x, y, z); glVertex3f(-x, y, -z);
    glEnd();
}

void drawCylinderWheel(float radius, float thickness, int segments)
{
    float hThick = thickness / 2.0f;

    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, hThick);
    for (int i = 0; i <= segments; i++)
    {
        float angle = i * 2.0f * PI / segments;
        glVertex3f(cos(angle) * radius, sin(angle) * radius, hThick);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.0f, 0.0f, -hThick);
    for (int i = 0; i <= segments; i++) 
    {
        float angle = -i * 2.0f * PI / segments;
        glVertex3f(cos(angle) * radius, sin(angle) * radius, -hThick);
    }
    glEnd();

    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= segments; i++) 
    {
        float angle = i * 2.0f * PI / segments;
        float x = cos(angle) * radius;
        float y = sin(angle) * radius;

        glNormal3f(cos(angle), sin(angle), 0.0f);
        glVertex3f(x, y, hThick);
        glVertex3f(x, y, -hThick);
    }
    glEnd();
}

void drawLocomotive() 
{
    seteazaCuloareMaterial(1.0f, 0.078f, 0.576f);

    glPushMatrix();
    glTranslatef(locoX, 0.2f, 0.0f);
    drawCube(2.5f, 0.8f, 1.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(locoX - 0.8f, 0.7f, 0.0f);
    drawCube(0.9f, 1.2f, 1.0f);
    glPopMatrix();

    seteazaCuloareMaterial(0.5f, 0.8f, 1.0f);

    glPushMatrix(); glTranslatef(locoX - 0.8f, 0.8f, 0.51f); drawCube(0.4f, 0.4f, 0.01f); glPopMatrix();
    glPushMatrix(); glTranslatef(locoX - 0.8f, 0.8f, -0.51f); drawCube(0.4f, 0.4f, 0.01f); glPopMatrix();
    glPushMatrix(); glTranslatef(locoX - 0.34f, 0.8f, 0.0f); drawCube(0.01f, 0.4f, 0.6f); glPopMatrix();

    seteazaCuloareMaterial(1.0f, 0.078f, 0.576f);

    glPushMatrix();
    glTranslatef(locoX + 1.3f, 0.3f, 0.0f);
    drawCube(0.1f, 0.2f, 0.4f);
    glPopMatrix();

    seteazaCuloareMaterial(1.0f, 0.9f, 0.5f);
    glPushMatrix();
    glTranslatef(locoX + 1.36f, 0.3f, 0.0f);
    drawCube(0.04f, 0.15f, 0.2f);
    glPopMatrix();

    seteazaCuloareMaterial(0.15f, 0.15f, 0.15f);
    glPushMatrix();
    glTranslatef(locoX + 0.8f, 0.8f, 0.0f);
    drawCube(0.3f, 0.6f, 0.3f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(locoX + 1.4f, -0.3f, 0.0f);
    drawCube(0.3f, 0.3f, 0.9f);
    glPopMatrix();

    float wheelX[] = { -0.6f, 0.6f };
    float wheelZ[] = { -0.52f, 0.52f };

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++) 
        {
            seteazaCuloareMaterial(0.15f, 0.15f, 0.15f);
            glPushMatrix();
            glTranslatef(locoX + wheelX[i], -0.3f, wheelZ[j]);
            drawCylinderWheel(0.3f, 0.1f, 30);
            glPopMatrix();

            seteazaCuloareMaterial(1.0f, 0.078f, 0.576f);
            glPushMatrix();
            glTranslatef(locoX + wheelX[i], -0.3f, wheelZ[j] + (wheelZ[j] > 0 ? 0.051f : -0.051f));
            drawCylinderWheel(0.13f, 0.01f, 20);
            glPopMatrix();
        }
    }
}

void myinit(void) 
{
    glClearColor(0.2f, 0.3f, 0.4f, 1.0f); 
    glShadeModel(GL_SMOOTH);               
    glEnable(GL_DEPTH_TEST);             

    GLfloat ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
    GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat specularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);

    glEnable(GL_LIGHTING);                
    glEnable(GL_LIGHT0);                  
}

void CALLBACK display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    float camX = sin(cameraAngle) * 10.0f;
    float camZ = cos(cameraAngle) * 10.0f;
    gluLookAt(camX, 4.0f, camZ, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    seteazaCuloareMaterial(0.5f, 0.5f, 0.5f);

    glPushMatrix();
    glTranslatef(0.0f, -1.0f, 0.0f);
    drawCube(20.0f, 0.02f, 20.0f);
    glPopMatrix();

    glPushMatrix();
    float groundY = -0.98f;
    float shadowMat[16] =
    {
        lightPos[1], 0, 0, 0,
        -lightPos[0], 0, -lightPos[2], -1,
        0, 0, lightPos[1], 0,
        0, groundY * lightPos[1], 0, lightPos[1]
    };
    glMultMatrixf(shadowMat);
    glDisable(GL_LIGHTING); 
    glColor3f(0.12f, 0.12f, 0.12f); 
    drawLocomotive();
    glEnable(GL_LIGHTING);
    glPopMatrix();

    drawLocomotive();

    auxSwapBuffers();
}

void CALLBACK myReshape(GLsizei w, GLsizei h) {
    if (!h) return;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) 
{
    auxInitDisplayMode(AUX_DOUBLE | AUX_RGB | AUX_DEPTH);
    auxInitPosition(100, 100, 1024, 768);
    auxInitWindow(L"Proiect Final: Locomotiva Roz cu Roti Rotunde");

    myinit();

    auxKeyFunc('a', moveLeft);
    auxKeyFunc('A', moveLeft);
    auxKeyFunc('d', moveRight);
    auxKeyFunc('D', moveRight);

    auxKeyFunc(AUX_LEFT, rotateCamLeft);
    auxKeyFunc(AUX_RIGHT, rotateCamRight);

    auxReshapeFunc(myReshape);
    auxIdleFunc(idle);

    auxMainLoop(display);
    return(0);
}