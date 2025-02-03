#include <iostream>
#include <GLUT/glut.h>
#include <vector>

using namespace std;

// Circle parameters
GLint centerX = 320, centerY = 240, radius = 100;
vector<pair<GLint, GLint>> circlePoints;
vector<pair<GLint, GLint>> algorithmSteps;
size_t currentStep = 0;

void plotPoint(GLint x, GLint y) {
    // Store all 8 symmetric points
    circlePoints.push_back({centerX + x, centerY + y});
    circlePoints.push_back({centerX - x, centerY + y});
    circlePoints.push_back({centerX + x, centerY - y});
    circlePoints.push_back({centerX - x, centerY - y});
    circlePoints.push_back({centerX + y, centerY + x});
    circlePoints.push_back({centerX - y, centerY + x});
    circlePoints.push_back({centerX + y, centerY - x});
    circlePoints.push_back({centerX - y, centerY - x});

    // Print the calculated point
    cout << "Plotted point: (" << x << ", " << y << ")" << endl;
}

void midpointCircle() {
    GLint x = 0;
    GLint y = radius;
    GLint p = 1 - radius;

    algorithmSteps.emplace_back(x, y);

    while(x < y) {
        x++;
        if(p < 0) {
            p += 2 * x + 1;
        } else {
            y--;
            p += 2 * (x - y) + 1;
        }
        algorithmSteps.emplace_back(x, y);
    }
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);  // Black background
    glColor3f(1.0, 1.0, 1.0);          // White drawing color
    glPointSize(2.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 640, 0, 480);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    glBegin(GL_POINTS);
    for (auto& p : circlePoints) {
        glVertex2i(p.first, p.second);
    }
    glEnd();
    
    glutSwapBuffers();
}

void timer(int value) {
    if (currentStep < algorithmSteps.size()) {
        auto [x, y] = algorithmSteps[currentStep];
        plotPoint(x, y);
        currentStep++;
        glutPostRedisplay();
        glutTimerFunc(100, timer, 0);  // 100ms delay between steps
    }
}

void key(unsigned char k, int x, int y) {
    if (k == 27) {  // ESC key
        cout << "\nPoints plotted:\n";
        for (auto& p : circlePoints) {
            cout << "(" << p.first << ", " << p.second << ")\n";
        }
        exit(0);
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Animated Midpoint Circle");
    
    init();
    midpointCircle();
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    
    return 0;
}
