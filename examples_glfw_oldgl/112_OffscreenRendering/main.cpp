/*
 * Copyright (c) 2019 Nobuyuki Umetani
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <iostream>
#include <cmath>
#include "delfem2/mshio.h"
#include "delfem2/mshmisc.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "delfem2/opengl/glfw_viewer.hpp"
#include "delfem2/opengl/glold_funcs.h"
#include "delfem2/opengl/glold_color.h"
#include "delfem2/opengl/glold_v23.h"
#include "delfem2/opengl/glold_smplr.h"

namespace dfm2 = delfem2;

// ------------------------------------------------------

double cur_time = 0.0;
dfm2::opengl::CGPUSamplerDrawer sampler;
bool is_animation = true;
bool is_depth = false;
std::vector<double> aXYZ;
std::vector<unsigned int> aTri;

// ------------------------------------------------------

void Draw(){
  ::glRotated(+cur_time, 1,0,0);
  dfm2::opengl::DrawMeshTri3D_FaceNorm(aXYZ,aTri);
  ::glRotated(-cur_time, 1,0,0);
}

void myGlutDisplay()
{
  dfm2::opengl::DrawBackground( dfm2::CColor(0.2,0.7,0.7) );
//  ::glDisable(GL_LIGHTING);
  ::glEnable(GL_LIGHTING);
  
  ::glColor3d(1,1,1);
  Draw();

  glPointSize(3);
  float mMV[16]; glGetFloatv(GL_MODELVIEW, mMV);
  float mP[16]; glGetFloatv(GL_PROJECTION, mP);
  sampler.Draw();
}

void myGlutIdle(){
  if(is_animation){
    sampler.Start();
    ::glDisable(GL_LIGHTING);
    ::glColor3d(1,1,1);
    ::glEnable(GL_LIGHTING);
    Draw();
    sampler.End();
    sampler.GetDepth();
    cur_time += 1;
  }
}

int main(int argc,char* argv[])
{
  dfm2::Read_Obj(std::string(PATH_INPUT_DIR)+"/bunny_1k.obj",
    aXYZ,aTri);
  dfm2::Normalize_Points3D(aXYZ,1.0);
  
  int nres = 256;
  double elen = 0.01;
  sampler.Init(nres, nres);
  sampler.SetCoord(elen, 4.0,
                   dfm2::CVec3(-nres*elen*0.5,nres*elen*0.5,-2).stlvec(),
                   dfm2::CVec3(0,0,-1).stlvec(),
                   dfm2::CVec3(1,0,0).stlvec() );
  sampler.SetPointColor(1, 0, 0);
  sampler.draw_len_axis = 1.0;
  
  // --------------
  dfm2::opengl::CViewer_GLFW viewer;
  viewer.Init_oldGL();
  viewer.nav.camera.view_height = 2.0;
  viewer.nav.camera.camera_rot_mode = dfm2::CAMERA_ROT_TBALL;
  viewer.nav.camera.Rot_Camera(+0.2, -0.2);
  if(!gladLoadGL()) {     // glad: load all OpenGL function pointers
    printf("Something went wrong in loading OpenGL functions!\n");
    exit(-1);
  }

  dfm2::opengl::setSomeLighting();
  ::glEnable(GL_DEPTH_TEST);
  
  sampler.InitGL(); // move the sampled image to a texture

  cur_time = 0.0;
  while (!glfwWindowShouldClose(viewer.window))
  {
    cur_time += 0.1;
    myGlutIdle();
    // ----
    viewer.DrawBegin_oldGL();
    myGlutDisplay();
    glfwSwapBuffers(viewer.window);
    glfwPollEvents();
  }
  glfwDestroyWindow(viewer.window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}


