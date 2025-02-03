#include <iostream>
#include <GLUT/glut.h>
#include <vector>
#include <cmath>
using namespace std;

vector<pair<int, int>> linePoints;
size_t currentPoint = 0;

#define GL_SILENCE_DEPRECATION

int custom_round(float n) {
    return (n > 0.0) ? floor(n + 0.5) : ceil(n - 0.5);
}

void drawPoint(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void DDALine(int x0, int y0, int x1, int y1) {
    cout << "DDA Algorithm Points:" << endl;
    linePoints.clear();
    
    int dx = x1 - x0;
    int dy = y1 - y0;
    int steps = max(abs(dx), abs(dy));
    
    float xIncrement = dx / (float)steps;
    float yIncrement = dy / (float)steps;
    
    float x = x0, y = y0;
    
    for (int i = 0; i <= steps; i++) {
        int roundedX = custom_round(x);
        int roundedY = custom_round(y);
        linePoints.emplace_back(roundedX, roundedY);
        cout << "(" << roundedX << ", " << roundedY << ")" << endl;
        x += xIncrement;
        y += yIncrement;
    }
}

void BresenhamLine(int x0, int y0, int x1, int y1) {
    cout << "Bresenham Algorithm Points:" << endl;
    linePoints.clear();
    
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx - dy;

    while (true) {
        linePoints.emplace_back(x0, y0);
        cout << "(" << x0 << ", " << y0 << ")" << endl;
        if (x0 == x1 && y0 == y1) break;
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glViewport(0, 0, 800, 800);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-20, 20, -20, 20, -20, 20);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Draw points in red (bold)
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(8.0);
    
    for (size_t i = 0; i <= currentPoint && i < linePoints.size(); ++i) {
        drawPoint(linePoints[i].first, linePoints[i].second);
    }

    // Draw connecting line in white
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_STRIP);
    for (size_t i = 0; i <= currentPoint && i < linePoints.size(); ++i) {
        glVertex2i(linePoints[i].first, linePoints[i].second);
    }
    glEnd();

    glutSwapBuffers();
}

void timer(int value) {
    if (currentPoint < linePoints.size()) {
        currentPoint++;
        glutPostRedisplay();
        glutTimerFunc(500, timer, 0); // 100ms delay
    }
}

void key(unsigned char key, int x, int y) {
    if (key == 27) exit(0);
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Line Drawing Algorithms");
    init();
    
    // Choose one of these lines:
//    DDALine(2, 1, 10, 6);
     BresenhamLine(2, 1, 10, 6);
    
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return 0;
}
