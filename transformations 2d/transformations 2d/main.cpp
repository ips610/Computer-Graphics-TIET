#include <GLUT/glut.h>
#include <math.h>

float squareX = 0.0f;
float squareY = 0.0f;
float targetX = 0.5f;
float targetY = 0.5f;
float translationStep = 0.005f;

float angle = 0.0f;
float targetAngle = 45.0f;
float rotationStep = 0.5f;

void drawSquare() {
    glBegin(GL_QUADS);
    glVertex2f(-0.1f, -0.1f);
    glVertex2f(0.1f, -0.1f);
    glVertex2f(0.1f, 0.1f);
    glVertex2f(-0.1f, 0.1f);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Draw initial square (red)
    glColor3f(1.0f, 0.0f, 0.0f);
    drawSquare();
    
    // Draw rotated square (blue)
    glColor3f(0.0f, 0.0f, 1.0f);
    glPushMatrix();
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    drawSquare();
    glPopMatrix();
    
    // Draw translated square (yellow)
    glColor3f(1.0f, 1.0f, 0.0f);
    glPushMatrix();
    glTranslatef(squareX, squareY, 0.0f);
    drawSquare();
    glPopMatrix();
    
    glutSwapBuffers();
}

void timer(int value) {
    // Update translation
    if (squareX < targetX) squareX += translationStep;
    if (squareY < targetY) squareY += translationStep;
    
    // Update rotation
    if (angle < targetAngle) {
        angle += rotationStep;
        if (angle > targetAngle) angle = targetAngle;
    }
    
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("2D Transformations");
    
    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);
    
    glutMainLoop();
    return 0;
}
