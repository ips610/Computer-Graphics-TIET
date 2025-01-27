#include <iostream>
#include <GLUT/glut.h> // Include GLUT library for OpenGL functionality

#define GL_SILENCE_DEPRECATION

// Define the vertices for the hut
GLfloat v[20][3] = {
    {0, 0, 0}, // R - 0
    {4, 0, 0}, // Q - 1
    {3, 3, 0}, // P - 2
    {0, 3, 0}, // O - 3
    {-3, 3, 0}, // N - 4
    {-4, 0, 0}, // M - 5
    {0, 0, 1}, // R-Z-1 - 6
    {0, 3, 1}, // O-Z-1 - 7
    {-4.5, 0, 0}, // C - 8
    {-3.5,3.5,0}, // D - 9
    {3.5, 3.5, 0}, // E - 10
    {4.5, 0, 0}, // F - 11
    {8.5, 0, 0}, // G - 12
    {8.5, -3.5, 0}, // H - 13
    {-8.5, -3.5, 0}, // A - 14
    {-8.5, 0, 0}, // B - 15
    {-4.25, -3.5, 0}, // I - 16
    {4.25, -3.5, 0}, // J - 17
    {8.5, 0, 1}, // G-Z-1 - 18
    {-8.5, 0, 1}, // B-Z-1 - 19
};

void drawCircle(GLfloat center[3], float radius, int numSegments) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(center[0], center[1], center[2]); // Center point
    
    for (int i = 0; i <= numSegments; i++) {
        float theta = 2.0f * 3.1415926f * (float)i / (float)numSegments;
        float x = radius * cosf(theta);
        float y = radius * sinf(theta);
        glVertex3f(x + center[0], y + center[1], center[2]);
    }
    
    glEnd();
}

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
    glColor3f(0.678, 0.847, 0.902);
    glBegin(GL_POLYGON);
    
    glVertex3fv(v[0]);
    glVertex3fv(v[1]);
    glVertex3fv(v[2]);
    glVertex3fv(v[3]);
    glVertex3fv(v[4]);
    glVertex3fv(v[5]);
    glVertex3fv(v[0]);
    glEnd();
    

    glColor3f(0.463, 0.663, 0.263);
    glBegin(GL_POLYGON);
    
    glVertex3fv(v[8]);
    glVertex3fv(v[9]);
    glVertex3fv(v[10]);
    glVertex3fv(v[11]);
    glVertex3fv(v[12]);
    glVertex3fv(v[13]);
    glVertex3fv(v[14]);
    glVertex3fv(v[15]);
    glVertex3fv(v[8]);
    glEnd();

    // Set color to black
    glColor3f(0.0, 0.0, 0.0);

    // Set line width (thickness)
    glLineWidth(3.0);  // Adjust this value to increase or decrease thickness

    glBegin(GL_LINES);
    glVertex3fv(v[6]); // Base middle
    glVertex3fv(v[7]); // Roof top
    glEnd();

    // Reset line width to default (optional)
    glLineWidth(1.0);
    
    // Set the color (optional)
    glColor3f(0.663f, 0.663f, 0.663f); // Dark gray color

    // Define the radius
    float radius = 1.25f; // Adjust this value to change the circle size

    // Draw the circle
    drawCircle(v[16], radius, 100);
    drawCircle(v[17], radius, 100);
    
    glColor3f(1.0f, 1.0f, 0.0f);
    radius = 0.5f;
    drawCircle(v[18], radius, 100);
    drawCircle(v[19], radius, 100);

    
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
    glutCreateWindow("Car"); // Create window with title "Hut"
    init(); // Initialize OpenGL settings
    glutDisplayFunc(display); // Register display callback function
    glutKeyboardFunc(key); // Register keyboard callback function
    glutMainLoop(); // Enter the GLUT event processing loop
    return 0;
}
