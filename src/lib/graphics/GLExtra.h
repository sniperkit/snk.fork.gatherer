//
//  GLExtra.h
//  gatherer
//
//  Created by David Hirvonen on 10/8/12.
//  Copyright (c) 2012 David Hirvonen. All rights reserved.
//

#ifndef __gatherer__GLExtra__
#define __gatherer__GLExtra__

#include "graphics/gatherer_graphics.h"
#include <iostream>
#include <opencv2/core/core.hpp>

#if defined(GATHERER_ENABLE_OPENGL_DEBUG)
# define GATHERER_OPENGL_DEBUG \
      do { \
        GLenum er = glGetError(); \
        const char* errorMessage = gatherer::graphics::glErrorToString(er); \
        if (errorMessage != nullptr) { \
          std::ostringstream msg; \
          msg << errorMessage; \
          msg << " ("; \
          msg << "code:" << er; \
          msg << " file:" << __FILE__; \
          msg << " line:" << __LINE__; \
          msg << ")"; \
          throw std::runtime_error(msg.str()); \
        } \
      } \
      while (false);
#else
# define GATHERER_OPENGL_DEBUG
#endif

_GATHERER_GRAPHICS_BEGIN

void glMakeIdentityf(GLfloat m[16]);
void glOrthof(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat near, GLfloat far, GLfloat *matrix);
void glPerspectivef(GLfloat fovy, GLfloat aspect, GLfloat zNear, GLfloat zFar, GLfloat *matrix);
void glFrustumf(float l, float r, float b, float t, float n, float f, float *matrix);
cv::Mat glOrtho(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat near, GLfloat far);
cv::Mat glFrustum(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat near, GLfloat far);
void glErrorTest();
void glCheckError();

/*
 * @brief Convert integer error value to string message
 * @return nullptr - no error
 */
const char* glErrorToString(GLenum error);

// Source: dhirvonen@elucideye.com
// drishti/lib/graphics/graphics/MosaicRenderGL.cpp: R3x3To4x4
//
// Map 3x3 homography to 4x4 matrix:
//
// H00 H01 H02      H00 H01 0 H02
// H10 H11 H12  =>  H10 H11 0 H12
// H20 H21 H22       0   0  1  0
//                  H20 H21 0 H22
static void R3x3To4x4(const cv::Matx33f &R3, cv::Matx44f &R4)
{
    R4 = cv::Matx44f::eye();

    R4(0,0) = R3(0,0);
    R4(0,1) = R3(0,1);
    R4(0,3) = R3(0,2);

    R4(1,0) = R3(1,0);
    R4(1,1) = R3(1,1);
    R4(1,3) = R3(1,2);

    R4(3,0) = R3(2,0);
    R4(3,1) = R3(2,1);
    R4(3,3) = R3(2,2);
}


_GATHERER_GRAPHICS_END

#endif /* defined(__gatherer__GLExtra__) */
