#include <iostream>
#include <GLUT/glut.h> // Include GLUT library for OpenGL functionality

#define GL_SILENCE_DEPRECATION

// Define the vertices for the hut
GLfloat v[10][3] = {
    {-10, 10, 0},
    {0, 10, 0},
    {-5, 15, 0},
    {12, 15, 0},
    {18, 10, 0},
    {-5, 10, 0},
    {-10, -8, 0},
    {0, -8, 0},
    {18, -8, 0}
};



void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0); // Set background color to black
    glViewport(0, 0, 800, 800); // Set larger viewport size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-20, 20, -20, 20, -20, 20); // Adjust orthographic projection
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); // Set model view matrix to identity
    
    glEnable(GL_LIGHT0); // Enable light source 0
//    glDisable(GL_LIGHTING);  Enable lighting
    glEnable(GL_DEPTH_TEST); // Enable depth testing
}

void display() {
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers


//    glBegin(GL_LINES);
//    glVertex3fv(v[0]);
//    glVertex3fv(v[1]);
//    glEnd();
//    glBegin(GL_LINES);
//    glVertex3fv(v[1]);
//    glVertex3fv(v[2]);
//    glEnd();
//    glBegin(GL_LINES);
//    glVertex3fv(v[0]);
//    glVertex3fv(v[2]);
//    glEnd();
//    
//
//    
//    glBegin(GL_LINES);
//    glVertex3fv(v[2]); // Base middle
//    glVertex3fv(v[3]); // Roof top
//    glEnd();
//    glBegin(GL_LINES);
//    glVertex3fv(v[1]); // Base right
//    glVertex3fv(v[4]); // Roof right
//    glEnd();
//    glBegin(GL_LINES);
//    glVertex3fv(v[3]); // Roof left
//    glVertex3fv(v[4]); // Roof top
//    glEnd();
//    glBegin(GL_LINES);
//    glVertex3fv(v[0]); // Roof top
//    glVertex3fv(v[6]); // Roof right
//    glEnd();
//    glBegin(GL_LINES);
//    glVertex3fv(v[1]); // Roof left
//    glVertex3fv(v[7]); // Wall left bottom
//    glEnd();
//    glBegin(GL_LINES);
//    glVertex3fv(v[6]); // Roof right
//    glVertex3fv(v[7]); // Wall right bottom
//    glEnd();
//    glBegin(GL_LINES);
//    glVertex3fv(v[8]); // Wall left bottom
//    glVertex3fv(v[7]); // Wall right bottom
//    glEnd();
//    glBegin(GL_LINES);
//    glVertex3fv(v[8]); // Wall left bottom
//    glVertex3fv(v[4]); // Wall right bottom
//    glEnd();
    
    
    glColor3f(1.0, 0, 0);
    glBegin(GL_POLYGON);
    
    glVertex3fv(v[0]); // First vertex
    glVertex3fv(v[1]); // Second vertex
    glVertex3fv(v[2]); // Third vertex
    glEnd();
    
    glColor3f(1.0, 1.0, 0);
    glBegin(GL_POLYGON);
    
    glVertex3fv(v[2]);
    glVertex3fv(v[3]);
    glVertex3fv(v[4]);
    glVertex3fv(v[1]);
    
    glEnd();
    
    glColor3f(0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    
    glVertex3fv(v[0]);
    glVertex3fv(v[1]);
    glVertex3fv(v[7]);
    glVertex3fv(v[6]);
    
    glEnd();
    
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    
    glVertex3fv(v[7]);
    glVertex3fv(v[8]);
    glVertex3fv(v[4]);
    glVertex3fv(v[1]);
    
    glEnd();
    
    glutSwapBuffers(); // Swap front and back buffers
}

void key(unsigned char key, int x, int y) {
    if (key == 27) // Exit the program when 'Esc' key is pressed
        exit(0);
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv); // Initialize GLUT
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Set display mode
    glutInitWindowSize(800, 800); // Set larger window size
    glutCreateWindow("Hut"); // Create window with title "Hut"
    init(); // Initialize OpenGL settings
    glutDisplayFunc(display); // Register display callback function
    glutKeyboardFunc(key); // Register keyboard callback function
    glutMainLoop(); // Enter the GLUT event processing loop
    return 0;
}
