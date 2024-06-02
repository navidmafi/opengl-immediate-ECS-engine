#include <Sphere.hpp>
#include <cmath>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <GL/glu.h>

Sphere::Sphere() = default;

Sphere::~Sphere() = default;

void Sphere::render()
{
    glPushMatrix();
    glTranslatef(position.x, position.y, position.z);
    glRotatef(rotation.x, 1.0f, 0.0f, 0.0f);
    glRotatef(rotation.y, 0.0f, 1.0f, 0.0f);
    glRotatef(rotation.z, 0.0f, 0.0f, 1.0f);
    glScalef(scale.x, scale.y, scale.z);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat lightPos[] = {-1.0f, 0.0f, 0.5f, 0.0f}; // Directional light
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    GLfloat lightAmbient[] = {0.4f, 0.4f, 0.4f, 1.0f}; // Increased ambient light
    GLfloat lightDiffuse[] = {0.9f, 0.9f, 0.9f, 1.0f}; // Increased diffuse light
    GLfloat lightSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

    GLfloat matAmbient[] = {0.4f, 0.4f, 0.4f, 1.0f};
    GLfloat matDiffuse[] = {0.8f, 0.0f, 0.0f, 1.0f};
    GLfloat matSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat matShininess[] = {100.0f}; // Increase shininess value for shinier appearance
    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);

    GLUquadric *quadric = gluNewQuadric();
    gluQuadricNormals(quadric, GLU_SMOOTH);
    gluSphere(quadric, 1.0, 32, 32);
    gluDeleteQuadric(quadric);

    glDisable(GL_LIGHTING);

    glPopMatrix();
}

void Sphere::update(float deltaTime)
{
    static float animationTime = 0.0f;
    animationTime += deltaTime;
    float scaleAmount = 0.5f + 0.2f * sin(animationTime * M_PI * 0.5); // sin scale 0.5 < x < 1.0
    scale = {scaleAmount, scaleAmount, scaleAmount};
}