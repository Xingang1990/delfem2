/*
 * Copyright (c) 2019 Nobuyuki Umetani
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */


#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cassert>
#include <cstdlib>

#if defined(__APPLE__) && defined(__MACH__) // Mac
  #include <OpenGL/gl.h>
#elif defined(_WIN32) // windows
  #include <windows.h>
  #include <GL/gl.h>
#else // linux
  #include <GL/gl.h>
#endif

#include "delfem2/opengl/gl_tex.h"

namespace dfm2 = delfem2;

// ------------------------

void dfm2::opengl::CTexture::LoadTex()
{
  if( id_tex == 0 ){
    ::glGenTextures(1, &id_tex);
  }
  glBindTexture(GL_TEXTURE_2D, id_tex);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
  glPixelStorei(GL_UNPACK_ALIGNMENT,1);
  assert(  aRGB.size() == w*h*3 );
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
               w, h, 0, GL_RGB, GL_UNSIGNED_BYTE,
               aRGB.data() );
  glBindTexture(GL_TEXTURE_2D, 0);
}


void dfm2::opengl::CTexture::Draw(){
  if( id_tex == 0 ){ return; }
  ::glEnable(GL_TEXTURE_2D);
  ::glDisable(GL_LIGHTING);
  ::glBindTexture(GL_TEXTURE_2D, id_tex);
  ::glColor3d(1,1,1);
  ::glBegin(GL_QUADS);
  ::glTexCoord2d(0.0, 0.0); ::glVertex3d(min_x,min_y,0);
  ::glTexCoord2d(1.0, 0.0); ::glVertex3d(max_x,min_y,0);
  ::glTexCoord2d(1.0, 1.0); ::glVertex3d(max_x,max_y,0);
  ::glTexCoord2d(0.0, 1.0); ::glVertex3d(min_x,max_y,0);
  ::glEnd();
  ::glBindTexture(GL_TEXTURE_2D, 0);
  ::glDisable(GL_TEXTURE_2D);
}


// --------------------------------------------------

void dfm2::opengl::SaveImage(
    const std::string& path)
{
  static unsigned int inum = 0;
  int viewport[4];
  glGetIntegerv(GL_VIEWPORT, viewport);
  void* image = malloc(3*viewport[2]*viewport[3]);
  glPixelStorei(GL_PACK_ALIGNMENT, 1);
  glReadPixels(0, 0, viewport[2], viewport[3], GL_RGB, GL_UNSIGNED_BYTE, image);
  unsigned int width = viewport[2];
  unsigned int height = viewport[3];
  std::ofstream fout;
  //  //  fname << "out";
  fout.open(path.c_str(), std::ios::out);
  fout<<"P3\n";
  fout<<width<<" "<<height<<"\n";
  fout<<"255\n";
  //  fout << "255\n";
  //  fout << "255\n";
  char* img = (char*)image;
  for (unsigned int ih = 0; ih<height; ih++){
    for (unsigned int iw = 0; iw<width; iw++){
      unsigned int i = (height-1-ih)*width+iw;
      int r = (unsigned char)img[i*3+0];
      int g = (unsigned char)img[i*3+1];
      int b = (unsigned char)img[i*3+2];
      fout<<r<<" "<<g<<" "<<b<<"\n";
      //    std::cout << i << " " << r << " "<< g << " "<< b << std::endl;
    }
  }
  fout.close();
  //  if( inum >= 700 ) abort();
  //  if( inum >= 400 ) abort();
  if (inum>=600) abort();
  inum++;
}

int dfm2::opengl::SetTexture_RGB(
    unsigned int w, unsigned int h,
    const std::vector<unsigned char>& image)
{
  glEnable(GL_TEXTURE_2D);
  GLuint m_texName = 0;
  glGenTextures(1 , &m_texName);
  glBindTexture(GL_TEXTURE_2D , m_texName);
  glTexImage2D(GL_TEXTURE_2D , 0 , GL_RGB , w, h,
               0 , GL_RGB , GL_UNSIGNED_BYTE , image.data() );
  
  return (int)m_texName;
}

GLuint dfm2::opengl::LoadTexture
(const unsigned char* image,
 const int width, const int height, const int bpp)
{
  GLuint id_tex; glGenTextures(1, &id_tex);
  glBindTexture(GL_TEXTURE_2D, id_tex);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  if( bpp == 3 ){
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)width, (GLsizei)height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
  }
  if( bpp == 4 ){
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)width, (GLsizei)height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
  }
  return id_tex;
};

/*
void DrawTextureBackground
(const GLuint tex,
 const int imgWidth,
 const int imgHeight,
 const int winWidth,
 const int winHeight)
{
  double imgAsp = (double)imgWidth/imgHeight;
  double winAsp = (double)winWidth/winHeight;
  /////
  glPushAttrib(GL_TRANSFORM_BIT|GL_CURRENT_BIT|GL_ENABLE_BIT);
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  
  if (winAsp>imgAsp){
    double imgWidth2 = imgHeight*winAsp;
    gluOrtho2D(
               -0.5*imgWidth2,+0.5*imgWidth2,
               -0.5*imgHeight,+0.5*imgHeight);
  }
  else{
    double imgHeight2 = (double)imgWidth/winAsp;
    gluOrtho2D(
               -0.5*imgWidth, +0.5*imgWidth,
               -0.5*imgHeight2, +0.5*imgHeight2);
  }
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
  
  glDisable(GL_LIGHTING);
  glDisable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);
  
  glBindTexture(GL_TEXTURE_2D, tex);
  
  glColor3f(1.0f, 1.0f, 1.0f);
  glBegin(GL_QUADS);
  glTexCoord2i(0, 0); glVertex2d(-0.5*imgWidth, -0.5*imgHeight);
  glTexCoord2i(1, 0); glVertex2d(+0.5*imgWidth, -0.5*imgHeight);
  glTexCoord2i(1, 1); glVertex2d(+0.5*imgWidth, +0.5*imgHeight);
  glTexCoord2i(0, 1); glVertex2d(-0.5*imgWidth, +0.5*imgHeight);
  glEnd();
  
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  
  glPopAttrib();
}
 */

// use it for GLSL shader drawing
void DrawRectangle_FullCanvas()
{
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
  
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  
  glDisable(GL_LIGHTING);
  glDisable(GL_DEPTH_TEST);
  
  glBegin(GL_QUADS);
  glVertex2d(-1, -1);
  glVertex2d(+1, -1);
  glVertex2d(+1, +1);
  glVertex2d(-1, +1);
  glEnd();
  
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  
  glPopAttrib();
}


void dfm2::opengl::CTexManager::Clear(){
  for(auto & itex : aTexInfo){
    unsigned int id_tex_gl = itex.id_tex_gl;
    if( glIsTexture(id_tex_gl) ){
      ::glDeleteTextures(1, &id_tex_gl);
    }
  }
  aTexInfo.clear();
}

void dfm2::opengl::CTexManager::BindTexturePath(const std::string& path) const {
  for(const auto & itex : aTexInfo){
    if( itex.full_path != path ) continue;
    glBindTexture(GL_TEXTURE_2D, itex.id_tex_gl );
    glEnable(GL_TEXTURE_2D);
  }
}
