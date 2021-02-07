//
//  TestGL.cpp
//  FarscapeEngine
//
//  Created by Taner Selim on 1/29/18.
//  Copyright © 2018 Taner Selim. All rights reserved.
//

#include "TestGL.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>


void TestDraw(GLFWwindow* window)
{
    float points[12] = {
        0.5f,  0.5f,  0.0f, //0
        0.5f, -0.5f,  0.0f, //1
        -0.5f, -0.5f,  0.0f,//2
        -0.5f, 0.5f,  0.0f, //3
    };
    
    // indexes that define 2 triangles - CW rotation = 1 triangle 3 indexes
    int indices[3*2] = {
        2, 1, 0,
        0, 3, 2
    };
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_TEXTURE_2D);
    
    // VAO
    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    
    // VBO
    // points buffer
    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    const int totalArraySizeBytes = 12 * sizeof(float); // total components in all vertices (sizeof array) = 12
    glBufferData(GL_ARRAY_BUFFER, totalArraySizeBytes, points, GL_STATIC_DRAW);
    
    // specify how many points make up the vertex
    const int pointsPerVertex = 3;
    glVertexAttribPointer(0, pointsPerVertex, GL_FLOAT, GL_FALSE, 0, NULL);
    
    // element array buffer - which pixel order makes up a triangle
    GLuint eab;
    glGenBuffers(1, &eab);
    
    // Transfer the data from indices to eab
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eab);
    // indices = the order in which to draw pixels
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(indices), indices, GL_STATIC_DRAW);
    
    const char* vertex_shader =
    "#version 410\n"
    "in vec3 vp;"
    "void main() {"
    "  gl_Position = vec4(vp, 1.0);"
    "}";
    
    const char* fragment_shader =
    "#version 410\n"
    "out vec4 frag_colour;"
    "void main() {"
    "  frag_colour = vec4(0.5, 0.0, 0.5, 1.0);"
    "}";
    
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, NULL);
    glCompileShader(vs);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, NULL);
    glCompileShader(fs);
    
    GLuint shader_programme = glCreateProgram();
    glAttachShader(shader_programme, fs);
    glAttachShader(shader_programme, vs);
    glLinkProgram(shader_programme);
    
    while(!glfwWindowShouldClose(window)) {
        // wipe the drawing surface clear
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shader_programme);
        glBindVertexArray(vao);
        // draw points 0-3 from the currently bound VAO with current in-use shader
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glDrawElements( GL_TRIANGLES, // what to draw
                       6, // how many total elements from indices will form geometries (in this case GL_TRIANGLES)
                       GL_UNSIGNED_INT,
                       0); // offset to start reading indexes from
        
        // update other events like input handling
        glfwPollEvents();
        // put the stuff we've been drawing onto the display
        glfwSwapBuffers(window);
    }
}

