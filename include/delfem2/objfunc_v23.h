/*
 * Copyright (c) 2019 Nobuyuki Umetani
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */


#ifndef OBJFUNC_v23_h
#define OBJFUNC_v23_h

#include <vector>
#include "delfem2/mat3.h"
#include "delfem2/vec3.h"

namespace delfem2 {

void PBD_Pre3D(
    std::vector<double>& aXYZt,
    double dt,
    const double gravity[3],
    const std::vector<double>& aXYZ,
    const std::vector<double>& aUVW,
    const std::vector<int>& aBCFlag);

void PBD_Post(
    std::vector<double>& aXYZ,
    std::vector<double>& aUVW,
    double dt,
    const std::vector<double>& aXYZt,
    const std::vector<int>& aBCFlag);

void PBD_Update_Const3_Point3_Dim3(
    std::vector<double>& aXYZt,
    const double m[3],
    const double C[3],
    const double dCdp[3][9],
    const int aIP[3]);

void PBD_Update_Const3(
    double* aXYZt,
    const int np,
    const int ndim,
    const double* m,
    const double* C,
    const double* dCdp,
    const int* aIP);

void PBD_ConstProj_Rigid2D(
    double* aXYt,
    double stiffness,
    const unsigned int *clstr_ind, unsigned int nclstr_ind,
    const unsigned int *clstr, unsigned int nclstr0,
    const double* aXY0, unsigned int nXY0);

void PBD_ConstProj_Rigid3D(
    double* aXYZt,
    double stiffness,
    const int* clstr_ind, int nclstr_ind,
    const int* clstr,     int nclstr0,
    const double* aXYZ0,   int nXYZ0);

void PBD_CdC_TriStrain2D3D(
    double C[3],
    double dCdp[3][9],
    const double P[3][2], // (in) undeformed triangle vertex positions
    const double p[3][3]); // (in) deformed triangle vertex positions

void PBD_ConstraintProjection_DistanceTri2D3D(
    double C[3],
    double dCdp[3][9],
    const double P[3][2], // (in) undeformed triangle vertex positions
    const double p[3][3]); // (in) deformed triangle vertex positions

void PBD_ConstraintProjection_EnergyStVK(
    double& C,
    double dCdp[9],
    const double P[3][2], // (in) undeformed triangle vertex positions
    const double p[3][3], // (in) deformed triangle vertex positions)
    const double lambda,
    const double myu);

void PBD_ConstraintProjection_DistanceTet(
    double C[6],
    double dCdp[6][12],
    const double P[4][3], // (in) undeformed triangle vertex positions
    const double p[4][3]); // (in) deformed triangle vertex positions

void PBD_CdC_QuadBend(
    double C[3],
    double dCdp[3][12],
    const double P[4][3],
    const double p[4][3]);

void PBD_Seam(
    double* aXYZt,
    unsigned int nXYZ,
    const unsigned int* aLine,
    unsigned int nline);

void WdWddW_MIPS(
    double& E, double dE[3][3], double ddE[3][3][3][3],
    const double c[3][3],
    const double C[3][3]);
  
/**
 * @brief energy W and its derivative dW and second derivative ddW
 * where W = a^T R(dn) b(theta)
 */
void RodFrameTrans(CVec3d frm[3],
                   const CVec3d& S0,
                   const CVec3d& V01,
                   const CVec3d& du,
                   double dtheta);

void DiffFrameRod(CMat3d dF_dv[3], // first-order derivative
                  CVec3d dF_dt[3],
                  //
                  double l01,
                  const CVec3d Frm[3]);

/**
 * @brief energy W and its derivative dW and second derivative ddW
 * where W = a^T R(dn) b(theta)
 */
void DifDifFrameRod(CMat3d& ddW_ddv,
                    CVec3d& ddW_dvdt, // second-order derrivative
                    double& ddW_dtt,
                    //
                    unsigned int iaxis,
                    double l01,
                    const CVec3d& Q,
                    const CVec3d Frm[3]);

void AddDiff_DotFrames(CVec3d dV_dP[3],
                       double dV_dt[2],
                       //
                       double c,
                       unsigned int i,
                       unsigned int j,
                       const CVec3d Frm0[3],
                       const CVec3d Frm1[3],
                       const CMat3d dF0_dv[3],
                       const CVec3d dF0_dt[3],
                       const CMat3d dF1_dv[3],
                       const CVec3d dF1_dt[3]);

void AddDiffDiff_DotFrames(CMat3d ddV_ddP[3][3],
                           CVec3d ddV_dtdP[2][3],
                           double ddV_ddt[2][2],
                           //
                           double c,
                           unsigned int i,
                           unsigned int j,
                           const CVec3d P[3],
                           const CVec3d F0[3],
                           const CVec3d F1[3],
                           const CMat3d dF0_dv[3],
                           const CVec3d dF0_dt[3],
                           const CMat3d dF1_dv[3],
                           const CVec3d dF1_dt[3]);

double WdWddW_DotFrame(CVec3d dV_dP[3],
                       double dV_dt[2],
                       CMat3d ddV_ddP[3][3],
                       CVec3d ddV_dtdP[2][3],
                       double ddV_ddt[2][2],
                       //
                       const CVec3d P[3],
                       const CVec3d S[2],
                       const double off[3]);

double WdWddW_Rod(CVec3d dV_dP[3],
                  double dV_dt[2],
                  CMat3d ddV_ddP[3][3],
                  CVec3d ddV_dtdP[2][3],
                  double ddV_ddt[2][2],
                  //
                  const CVec3d P[3],
                  const CVec3d S[2],
                  const double off[3],
                  bool is_exact);

double WdWddW_SquareLengthLineseg3D(CVec3d dW_dP[2],
                                    CMat3d ddW_ddP[2][2],
                                    //
                                    const CVec3d P[2],
                                    double L0);

}

#endif /* pbd_v23_h */
