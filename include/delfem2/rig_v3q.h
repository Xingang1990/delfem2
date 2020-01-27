/*
 * Copyright (c) 2019 Nobuyuki Umetani
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */


#ifndef DFM2_RIG_V3Q_H
#define DFM2_RIG_V3Q_H

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <cassert>

#include "delfem2/vec3.h"

namespace delfem2 {

class CRigBone
{
public:
    CRigBone(){
      for(int i=0;i<16;++i){ invBindMat[i]=0.0; }
      invBindMat[ 0] = 1.0;
      invBindMat[ 5] = 1.0;
      invBindMat[10] = 1.0;
      invBindMat[15] = 1.0;
      //
      scale = 1;
      rot[0] = 1;
      rot[1] = 0;
      rot[2] = 0;
      rot[3] = 0;
      trans[0] = 0;
      trans[1] = 0;
      trans[2] = 0;
      ibone_parent = -1;
    }
  delfem2::CVec3d Pos() const{
    return delfem2::CVec3d(Mat[3],Mat[7],Mat[11]);
  }
  void SetRotationBryant(double rx, double ry, double rz);
  void SetTranslation(double tx, double ty, double tz);
  int PickHandler(const delfem2::CVec3d& org,
                  const delfem2::CVec3d& dir,
                  double rad_handlr,
                  double tol) const;
  void AffineJoint(const double a[16]) const;
public:
  std::string name;
  int ibone_parent;
  /////
  double invBindMat[16];
  double Mat[16];
  //////
  double rot[4]; // rotation of the joint from parent joint (quaternion w,x,y,z)
  double trans[3]; // position of the joint position from parent joint
  double scale; // scale
};


void UpdateBoneRotTrans(std::vector<CRigBone>& aBone);

void PickBone(int& ibone_selected,
              int& ielem_selected,
              const std::vector<CRigBone>& aBone,
              const delfem2::CVec3d& src,
              const delfem2::CVec3d& dir,
              double rad_hndlr,
              double tol);


// ----------------------------------

void UpdateRigSkin(double* aXYZ,
                   const double* aXYZ0,
                   unsigned int nXYZ,
                   const unsigned int* aTri,
                   unsigned int nTri,
                   const std::vector<CRigBone>& aBone,
                   const double* aRigWeight,
                   const unsigned int* aRigJoint);

// ------------------------------------

class CChannel_BioVisionHierarchy
{
public:
  CChannel_BioVisionHierarchy(int ib, int ia, bool br){
    this->ibone = ib;
    this->iaxis = ia;
    this->isrot = br;
  }
public:
  int ibone;
  int iaxis;
  bool isrot;
};

void Read_BioVisionHierarchy(std::vector<CRigBone>& aBone,
                             std::vector<CChannel_BioVisionHierarchy>& aChannelInfo,
                             int& nframe,
                             std::vector<double>& aChannelValue,
                             const std::string& path_bvh);

void SetPose_BioVisionHierarchy(std::vector<CRigBone>& aBone,
                                const std::vector<CChannel_BioVisionHierarchy>& aChannelInfo,
                                const double *aVal);



} // namespace delfem2

#endif // #define DFM2_RIG_V3Q_H

