#ifndef GLERROR_H
#define GLERROR_H

#include <GL/glew.h>


void GLAPIENTRY 
OpenglCallbackFunction(
//   unsigned int source, unsigned int type, unsigned int id, unsigned int severity, int length, const char* message, const void* userParam)
  
  
				  GLenum source,
                                       GLenum type,
                                       GLuint id,
                                       GLenum severity,
                                       GLsizei length,
                                       const GLchar* message,
                                       void* userParam);
#endif // GLERROR_H
