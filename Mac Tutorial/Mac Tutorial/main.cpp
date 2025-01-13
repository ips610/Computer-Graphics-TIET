// main.cpp
// First Lab
// Created by Ishpuneet Singh on 13/01/25.

#include <iostream>
#include <GLUT/glut.h> // For macOS. Use <GL/glut.h> on other platforms.

#define GL_SILENCE_DEPRECATION

// Display callback
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear buffers
    glLoadIdentity(); // Reset transformations

    // Example: Draw a simple red square
    glBegin(GL_QUADS);
    glColor3f(1.0, 0.0, 0.0); // Red color
    glVertex2f(-0.5, -0.5);   // Bottom-left
    glVertex2f(0.5, -0.5);    // Bottom-right
    glVertex2f(0.5, 0.5);     // Top-right
    glVertex2f(-0.5, 0.5);    // Top-left
    glEnd();

    glutSwapBuffers(); // Swap buffers for double buffering
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); // Initialize GLUT
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // Set display mode
    glutInitWindowSize(500, 500); // Set window size
    glutCreateWindow("Simple"); // Create window with title

    // Register callback
    glutDisplayFunc(display);

    // Enter GLUT event processing loop
    glutMainLoop();

    return 0;
}
