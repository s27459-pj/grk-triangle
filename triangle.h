#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <GL/glew.h>

#include "program.h"

class Triangle{
 public:
    void Initialize();
    ~Triangle();
    void Draw(const Program & program);
 private:
    GLuint vao_;
    GLuint vertex_buffer_;
    GLuint color_buffer_;
};

#endif // TRIANGLE_H
