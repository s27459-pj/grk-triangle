#include "window.h"

#include <iostream>
#include <cstdlib>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "glerror.h"

Window::Window(const char * title, int width, int height){
    title_ = title;
    width_ = width;
    height_ = height;
}

void Window::Initialize(int major_gl_version, int minor_gl_version){

    InitGlfwOrDie(major_gl_version, minor_gl_version);
    InitGlewOrDie();


    std::cout << "OpenGL initialized: OpenGL version: " << glGetString(GL_VERSION) << " GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    InitModels();
    InitPrograms();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

}

void Window::InitGlfwOrDie(int major_gl_version, int minor_gl_version){
    if ( !glfwInit() ) {
        std::cerr << "ERROR: Could not initialize GLFW" << std::endl;
        exit(EXIT_FAILURE);
    }


    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major_gl_version);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor_gl_version);
#ifdef DEBUG
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif
    window_ = glfwCreateWindow(width_, height_, title_, nullptr, nullptr);
    if (!window_){
        std::cerr << "ERROR: Could not create a new rendering window" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window_);
}

void Window::InitGlewOrDie(){
    GLenum glew_init_result;
    glewExperimental = GL_TRUE;
    glew_init_result = glewInit();

    if (GLEW_OK != glew_init_result) {
        std::cerr << "Glew ERROR: " << glewGetErrorString(glew_init_result) << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
#ifdef DEBUG
    if(glDebugMessageCallback){
        std::cout << "Register OpenGL debug callback " << std::endl;
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback((GLDEBUGPROC) OpenglCallbackFunction, NULL);
        GLuint unused_ids = 0;
        glDebugMessageControl(GL_DONT_CARE,
            GL_DONT_CARE,
            GL_DONT_CARE,
            0,
            &unused_ids,
            GL_FALSE);
    }
    else
        std::cout << "glDebugMessageCallback not available" << std::endl;
#endif

}

void Window::InitModels(){
    triangle_.Initialize();
}

void Window::InitPrograms(){
    program_.Initialize();
}

void Window::Resize(int new_width, int new_height){
    width_ = new_width;
    height_ = new_height;
    glViewport(0, 0, width_, height_);
}

void Window::KeyEvent(int key, int /*scancode*/, int action, int /*mods*/){
    if(action == GLFW_RELEASE){
        switch (key){
            case GLFW_KEY_ESCAPE:
                glfwSetWindowShouldClose(window_, GLFW_TRUE);
            break;
            default:
            break;
        }
    }
}

void Window::Run(void){
    while (!glfwWindowShouldClose(window_)){
        glClear(GL_COLOR_BUFFER_BIT /*| GL_DEPTH_BUFFER_BIT*/);
        triangle_.Draw(program_);
        glfwSwapBuffers(window_);
        glfwWaitEvents();
    }

}
