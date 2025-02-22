#include <GLUT/glut.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unistd.h>

using namespace std;

struct Edge {
    float yMax, xMin, slopeInv;
};

vector<Edge> edgeTable[500];
int minY = 500, maxY = 0;
int currentY;
bool filling = false;

void drawSquare() {
    glBegin(GL_LINE_LOOP);
    glVertex2i(100, 100);
    glVertex2i(200, 100);
    glVertex2i(200, 200);
    glVertex2i(100, 200);
    glEnd();
}

void addEdge(int x1, int y1, int x2, int y2) {
    if (y1 == y2) return;
    
    if (y1 > y2) swap(x1, x2), swap(y1, y2);
    
    Edge edge;
    edge.yMax = y2;
    edge.xMin = x1;
    edge.slopeInv = (float)(x2 - x1) / (y2 - y1);
    
    edgeTable[y1].push_back(edge);
    
    minY = min(minY, y1);
    maxY = max(maxY, y2);
}

void fillSquare() {
    static vector<Edge> activeEdgeTable;
    
    if (!filling) {
        currentY = minY;
        filling = true;
        activeEdgeTable.clear();
    }
    
    if (currentY < maxY) {
        for (auto edge : edgeTable[currentY]) {
            activeEdgeTable.push_back(edge);
        }
        
        activeEdgeTable.erase(remove_if(activeEdgeTable.begin(), activeEdgeTable.end(),
            [](Edge e) { return e.yMax == currentY; }), activeEdgeTable.end());
        
        sort(activeEdgeTable.begin(), activeEdgeTable.end(), [](Edge a, Edge b) { return a.xMin < b.xMin; });
        
        glBegin(GL_LINES);
        for (size_t i = 0; i < activeEdgeTable.size(); i += 2) {
            glVertex2i(activeEdgeTable[i].xMin, currentY);
            glVertex2i(activeEdgeTable[i + 1].xMin, currentY);
        }
        glEnd();
        
        for (auto& edge : activeEdgeTable) {
            edge.xMin += edge.slopeInv;
        }
        
        currentY++;
        glutPostRedisplay();
        glutTimerFunc(50, [](int){ fillSquare(); }, 0);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    drawSquare();
    glColor3f(1.0, 0.0, 0.0);
    fillSquare();
    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 300, 0, 300);
    addEdge(100, 100, 200, 100);
    addEdge(200, 100, 200, 200);
    addEdge(200, 200, 100, 200);
    addEdge(100, 200, 100, 100);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(300, 300);
    glutCreateWindow("Scanline Fill Square");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
