/*
 * Copyright (c) 2019 Nobuyuki Umetani
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <random>
#include "delfem2/mat3.h"

namespace dfm2 = delfem2;

// ------------------------

// t is a tmporary buffer size of 9
template <typename T>
void dfm2::Transpose_Mat3(T t[9],
                          const T a[9])
{
  t[0] = a[0];
  t[1] = a[3];
  t[2] = a[6];
  t[3] = a[1];
  t[4] = a[4];
  t[5] = a[7];
  t[6] = a[2];
  t[7] = a[5];
  t[8] = a[8];
}
template void dfm2::Transpose_Mat3(float t[], const float a[]);
template void dfm2::Transpose_Mat3(double t[], const double a[]);

// --------------------------------------

template <typename REAL>
void dfm2::Inverse_Mat3
(REAL Ainv[9],
 const REAL A[9])
{
  const REAL det =
  + A[0]*A[4]*A[8] + A[3]*A[7]*A[2] + A[6]*A[1]*A[5]
  - A[0]*A[7]*A[5] - A[6]*A[4]*A[2] - A[3]*A[1]*A[8];
  const REAL inv_det = 1.0/det;
  Ainv[0] = inv_det*(A[4]*A[8]-A[5]*A[7]);
  Ainv[1] = inv_det*(A[2]*A[7]-A[1]*A[8]);
  Ainv[2] = inv_det*(A[1]*A[5]-A[2]*A[4]);
  Ainv[3] = inv_det*(A[5]*A[6]-A[3]*A[8]);
  Ainv[4] = inv_det*(A[0]*A[8]-A[2]*A[6]);
  Ainv[5] = inv_det*(A[2]*A[3]-A[0]*A[5]);
  Ainv[6] = inv_det*(A[3]*A[7]-A[4]*A[6]);
  Ainv[7] = inv_det*(A[1]*A[6]-A[0]*A[7]);
  Ainv[8] = inv_det*(A[0]*A[4]-A[1]*A[3]);
}
template void dfm2::Inverse_Mat3(float Ainv[9], const float A[9]);
template void dfm2::Inverse_Mat3(double Ainv[9], const double A[9]);


// --------------------------------------

template <typename REAL>
void dfm2::Inverse_Mat3
 (REAL A[9])
{
  const REAL B[9] = {
    A[0],A[1],A[2],
    A[3],A[4],A[5],
    A[6],A[7],A[8] };
  const REAL det =
  + B[0]*B[4]*B[8] + B[3]*B[7]*B[2] + B[6]*B[1]*B[5]
  - B[0]*B[7]*B[5] - B[6]*B[4]*B[2] - B[3]*B[1]*B[8];
  const REAL inv_det = 1.0/det;
  A[0] = inv_det*(B[4]*B[8]-B[5]*B[7]);
  A[1] = inv_det*(B[2]*B[7]-B[1]*B[8]);
  A[2] = inv_det*(B[1]*B[5]-B[2]*B[4]);
  A[3] = inv_det*(B[5]*B[6]-B[3]*B[8]);
  A[4] = inv_det*(B[0]*B[8]-B[2]*B[6]);
  A[5] = inv_det*(B[2]*B[3]-B[0]*B[5]);
  A[6] = inv_det*(B[3]*B[7]-B[4]*B[6]);
  A[7] = inv_det*(B[1]*B[6]-B[0]*B[7]);
  A[8] = inv_det*(B[0]*B[4]-B[1]*B[3]);
}
template void dfm2::Inverse_Mat3(float Ainv[9]);
template void dfm2::Inverse_Mat3(double Ainv[9]);

// -----------------------------------

template <typename REAL>
void dfm2::Mat3_Spin(
    REAL* mat,
    const REAL* v)
{
  mat[0] =  0;     mat[1] = -v[2];   mat[2] = +v[1];
  mat[3] = +v[2];  mat[4] = 0;       mat[5] = -v[0];
  mat[6] = -v[1];  mat[7] = +v[0];   mat[8] = 0;
}
template void dfm2::Mat3_Spin(float* mat, const float* v);
template void dfm2::Mat3_Spin(double* mat, const double* v);

// ---------------------------------------------------------

template <typename REAL>
void dfm2::Mat3_Spin_ScaleAdd(
    REAL* m,
    const REAL* v,
    REAL alpha, REAL beta)
{
  m[0] = beta*m[0];
  m[1] = beta*m[1] - v[2]*alpha;
  m[2] = beta*m[2] + v[1]*alpha;
  m[3] = beta*m[3] + v[2]*alpha;
  m[4] = beta*m[4];
  m[5] = beta*m[5] - v[0]*alpha;
  m[6] = beta*m[6] - v[1]*alpha;
  m[7] = beta*m[7] + v[0]*alpha;
  m[8] = beta*m[8];
}
template void dfm2::Mat3_Spin_ScaleAdd(float* mat, const float* v, float alpha, float beta);
template void dfm2::Mat3_Spin_ScaleAdd(double* mat, const double* v, double alpha, double beta);

// ---------------------------------------------------------

template <typename REAL>
void dfm2::Mat3_Identity_ScaleAdd(
    REAL* mat,
    REAL alpha, REAL beta)
{
  mat[0] = beta*mat[0] + alpha;
  mat[1] = beta*mat[1];
  mat[2] = beta*mat[2];
  mat[3] = beta*mat[3];
  mat[4] = beta*mat[4] + alpha;
  mat[5] = beta*mat[5];
  mat[6] = beta*mat[6];
  mat[7] = beta*mat[7];
  mat[8] = beta*mat[8] + alpha;
}
template void dfm2::Mat3_Identity_ScaleAdd(float* mat, float alpha, float beta);
template void dfm2::Mat3_Identity_ScaleAdd(double* mat, double alpha, double beta);

template <typename REAL>
void dfm2::Mat3_Identity(REAL* mat,
                   REAL alpha)
{
  mat[0] = alpha;
  mat[1] = 0;
  mat[2] = 0;
  mat[3] = 0;
  mat[4] = alpha;
  mat[5] = 0;
  mat[6] = 0;
  mat[7] = 0;
  mat[8] = alpha;
}
template void dfm2::Mat3_Identity(float* mat, float alpha);
template void dfm2::Mat3_Identity(double* mat, double alpha);

// --------------------------------------------------------


template <typename T>
void dfm2::MatVec3
(T y[3],
 const T m[9], const T x[3])
{
  y[0] = m[0]*x[0] + m[1]*x[1] + m[2]*x[2];
  y[1] = m[3]*x[0] + m[4]*x[1] + m[5]*x[2];
  y[2] = m[6]*x[0] + m[7]*x[1] + m[8]*x[2];
}
template void dfm2::MatVec3(float y[3], const float m[9], const float x[3]);
template void dfm2::MatVec3(double y[3], const double m[9], const double x[3]);

// ----------------------------

template <typename T>
void dfm2::MatVec3_ScaleAdd(
    T y[3],
    const T m[9], const T x[3],
    T alpha, T beta)
{
  y[0] = beta*y[0] + alpha*(m[0]*x[0] + m[1]*x[1] + m[2]*x[2]);
  y[1] = beta*y[1] + alpha*(m[3]*x[0] + m[4]*x[1] + m[5]*x[2]);
  y[2] = beta*y[2] + alpha*(m[6]*x[0] + m[7]*x[1] + m[8]*x[2]);
}
template void dfm2::MatVec3_ScaleAdd(float y[3],
                                     const float m[9], const float x[3], float alpha, float beta);
template void dfm2::MatVec3_ScaleAdd(double y[3],
                                     const double m[9], const double x[3], double alpha, double beta);


void dfm2::VecMat3
 (double y[3],
  const double x[3], const double m[9])
{
  y[0] = m[0]*x[0] + m[3]*x[1] + m[6]*x[2];
  y[1] = m[1]*x[0] + m[4]*x[1] + m[7]*x[2];
  y[2] = m[2]*x[0] + m[5]*x[1] + m[8]*x[2];
}

void dfm2::MatTVec3(
    double y[3],
    const double m[9], const double x[3])
{
  y[0] = m[0]*x[0] + m[3]*x[1] + m[6]*x[2];
  y[1] = m[1]*x[0] + m[4]*x[1] + m[7]*x[2];
  y[2] = m[2]*x[0] + m[5]*x[1] + m[8]*x[2];
}


template <typename T>
void dfm2::MatTVec3_ScaleAdd(
    T y[3],
    const T m[9], const T x[3],
    T alpha, T beta)
{
  y[0] = beta*y[0] + alpha*(m[0]*x[0] + m[3]*x[1] + m[6]*x[2]);
  y[1] = beta*y[1] + alpha*(m[1]*x[0] + m[4]*x[1] + m[7]*x[2]);
  y[2] = beta*y[2] + alpha*(m[2]*x[0] + m[5]*x[1] + m[8]*x[2]);
}
template void dfm2::MatTVec3_ScaleAdd(float y[3], const float m[9], const float x[3], float alpha, float beta);
template void dfm2::MatTVec3_ScaleAdd(double y[3], const double m[9], const double x[3], double alpha, double beta);



void dfm2::Mat4Vec3(
    double vo[3],
    const double M[16],
    const double vi[3])
{
  vo[0] = M[0*4+0]*vi[0] + M[0*4+1]*vi[1] + M[0*4+2]*vi[2];
  vo[1] = M[1*4+0]*vi[0] + M[1*4+1]*vi[1] + M[1*4+2]*vi[2];
  vo[2] = M[2*4+0]*vi[0] + M[2*4+1]*vi[1] + M[2*4+2]*vi[2];
}

// ------------------------------------

template <typename T>
void dfm2::MatMat3
(T* C,
 const T* A, const T* B)
{
  for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
      C[i*3+j] = A[i*3+0]*B[0*3+j] + A[i*3+1]*B[1*3+j] + A[i*3+2]*B[2*3+j];
    }
  }
}
template void dfm2::MatMat3(float* C, const float* A, const float* B);
template void dfm2::MatMat3(double* C, const double* A, const double* B);

// ---------------------------------------

template <typename T>
void dfm2::MatMatT3(
    T* C,
    const T* A,
    const T* B)
{
  for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
      C[i*3+j] = A[i*3+0]*B[j*3+0] + A[i*3+1]*B[j*3+1] + A[i*3+2]*B[j*3+2];
    }
  }
}
template void dfm2::MatMatT3(float* C, const float* A, const float* B);
template void dfm2::MatMatT3(double* C, const double* A, const double* B);

// ---------------------------------------

template <typename T>
void dfm2::MatTMat3(
    T* C,
    const T* A, const T* B)
{
  for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
      C[i*3+j] = A[0*3+i]*B[0*3+j] + A[1*3+i]*B[1*3+j] + A[2*3+i]*B[2*3+j];
    }
  }
}
template void dfm2::MatTMat3(float* C, const float* A, const float* B);
template void dfm2::MatTMat3(double* C, const double* A, const double* B);

// --------------------------------------

template <typename T>
void dfm2::MatTMat3_ScaleAdd(
    T* C,
    const T* A, const T* B,
    T alpha, T beta)
{
  for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
      C[i*3+j] = beta*C[i*3+j] + alpha*(A[0*3+i]*B[0*3+j] + A[1*3+i]*B[1*3+j] + A[2*3+i]*B[2*3+j]);
    }
  }
}
template void dfm2::MatTMat3_ScaleAdd(float* C, const float* A, const float* B, float alpha, float beta);
template void dfm2::MatTMat3_ScaleAdd(double* C, const double* A, const double* B, double alpha, double beta);

// ---------------------------------------

template <typename T>
T dfm2::Det_Mat3(const T U[9])
{
  return + U[0]*U[4]*U[8] + U[3]*U[7]*U[2] + U[6]*U[1]*U[5]
  - U[0]*U[7]*U[5] - U[6]*U[4]*U[2] - U[3]*U[1]*U[8];
}
template float dfm2::Det_Mat3(const float U[9]);
template double dfm2::Det_Mat3(const double U[9]);

// ---------------------------------------

template <typename T>
T dfm2::SquareNormFrobenius_SymMat3
(const T sm[6])
{
  return sm[0]*sm[0] + sm[1]*sm[1] + sm[2]*sm[2] + 2*(sm[3]*sm[3] + sm[4]*sm[4] + sm[5]*sm[5]);
}
template float dfm2::SquareNormFrobenius_SymMat3(const float sm[6]);
template double dfm2::SquareNormFrobenius_SymMat3(const double sm[6]);

// ---------------------------------------

template <typename REAL>
void dfm2::Mat3_Rotation_Cartesian(
    REAL mat[9],
    const REAL vec[3])
{
  double sqt = vec[0]*vec[0]+vec[1]*vec[1]+vec[2]*vec[2];
  if( sqt < 1.0e-20 ){ // infinitesmal rotation approximation
    mat[0] = 1;        mat[1] = -vec[2];  mat[2] = +vec[1];
    mat[3] = +vec[2];  mat[4] = 1;        mat[5] = -vec[0];
    mat[6] = -vec[1];  mat[7] = +vec[0];  mat[8] = 1;
    return;
  }
  double t = sqrt(sqt);
  double invt = 1.0/t;
  double n[3] = { vec[0]*invt, vec[1]*invt, vec[2]*invt };
  const double c0 = cos(t);
  const double s0 = sin(t);
  mat[0*3+0] = c0        +(1-c0)*n[0]*n[0];
  mat[0*3+1] =   -n[2]*s0+(1-c0)*n[0]*n[1];
  mat[0*3+2] =   +n[1]*s0+(1-c0)*n[0]*n[2];
  mat[1*3+0] =   +n[2]*s0+(1-c0)*n[1]*n[0];
  mat[1*3+1] = c0        +(1-c0)*n[1]*n[1];
  mat[1*3+2] =   -n[0]*s0+(1-c0)*n[1]*n[2];
  mat[2*3+0] =   -n[1]*s0+(1-c0)*n[2]*n[0];
  mat[2*3+1] =   +n[0]*s0+(1-c0)*n[2]*n[1];
  mat[2*3+2] = c0        +(1-c0)*n[2]*n[2];
}
template void dfm2::Mat3_Rotation_Cartesian(float mat[9], const float vec[3]);
template void dfm2::Mat3_Rotation_Cartesian(double mat[9], const double vec[3]);


// ---------------------------------------

// compute eigen value & vector for symmmetric matrix
// sm[6] = (M_00,M_11,M_22,M_12,M_20,M_01)
// M = ULU^T
// u[9] = (U_00,U_01,U_02, U_10,U_11,U_12, U_20,U_21,U_22)
bool dfm2::eigenSym3
(double u[9], double l[3],
 const double sm[6],
 int nitr)
{
//  const double eps = 1.0e-100;
  //  double tol = 1.0e-5;
  u[0]=u[4]=u[8]=1.0;
  u[1]=u[2]=u[3]=u[5]=u[6]=u[7]=0.0;
  l[0]=l[1]=l[2]=0.0;
  double dnrm = SquareNormFrobenius_SymMat3(sm);
  if( dnrm < 1.0e-30 ){ return false; } // this matrix is too small
  const double scale = sqrt(dnrm);
  const double invscl = 1.0/scale;
  double sms[6] = {sm[0]*invscl,sm[1]*invscl,sm[2]*invscl,sm[3]*invscl,sm[4]*invscl,sm[5]*invscl};
  for(int itr=0;itr<nitr;itr++){
    const double m[6] = {sms[0],sms[1],sms[2],sms[3],sms[4],sms[5]};
    const double v[9] = {u[0],u[1],u[2], u[3],u[4],u[5], u[6],u[7],u[8] };
    const double a12 = fabs(sms[3]);
    const double a20 = fabs(sms[4]);
    const double a01 = fabs(sms[5]);
//    std::cout << a12 << " " << a20 << " " << a01 << std::endl;
//    std::cout << m[0] << " " << m[1] << " " << m[2] << " " << m[3] << " " << m[4] << " " << m[5] << std::endl;
    if( a12 >= a20 && a12 >= a01 ){ // a12 sms[3] is biggest
      const double t = 0.5*atan2(2*m[3],m[2]-m[1]);
      const double ct = cos(t);
      const double st = sin(t);
//      std::cout << "hoge0 " << m[2]-m[1] << " " << (ct*ct-st*st)*m[3]+st*ct*(m[1]-m[2]) << std::endl;
//      if( fabs(t)< eps ){ return true; }
      sms[1] = ct*ct*m[1]+st*st*m[2]-2*st*ct*m[3];
      sms[2] = ct*ct*m[2]+st*st*m[1]+2*st*ct*m[3];
      sms[3] = 0; // (ct*ct-st*st)*m[3]+st*ct*(m[1]-m[2]);
      sms[4] = st*m[5]+ct*m[4];
      sms[5] = ct*m[5]-st*m[4];
      //
      u[1] = +ct*v[1]-st*v[2];
      u[2] = +st*v[1]+ct*v[2];
      u[4] = +ct*v[4]-st*v[5];
      u[5] = +st*v[4]+ct*v[5];
      u[7] = +ct*v[7]-st*v[8];
      u[8] = +st*v[7]+ct*v[8];
    }
    else if( a20 >= a01 && a20 >= a12 ){ // a20 sms[4] is biggest
      // the above condition statement shoud pass exactly once for each iteration.
      const double t = 0.5*atan2(2*m[4],m[2]-m[0]);
      const double ct = cos(t);
      const double st = sin(t);
//      std::cout << "hoge1 " << m[2]-m[0] << "   " << (ct*ct-st*st)*m[4]+st*ct*(m[0]-m[2]) << std::endl;
//      if( fabs(t)< eps ){ return true; }
      sms[0] = ct*ct*m[0]+st*st*m[2]-2*st*ct*m[4];
      sms[2] = ct*ct*m[2]+st*st*m[0]+2*st*ct*m[4];
      sms[3] = st*m[5]+ct*m[3];
      sms[4] = 0; // (ct*ct-st*st)*m[4]+st*ct*(m[0]-m[2]);
      sms[5] = ct*m[5]-st*m[3];
      ////
      u[0] = +ct*v[0]-st*v[2];
      u[2] = +st*v[0]+ct*v[2];
      u[3] = +ct*v[3]-st*v[5];
      u[5] = +st*v[3]+ct*v[5];
      u[6] = +ct*v[6]-st*v[8];
      u[8] = +st*v[6]+ct*v[8];
    }
//    if( a01 >= a12 && a01 >= a20 ){ // a01 sms[5] is biggest
    else{ // the condition statement shoud pass exactly once for each iteration.
      const double t = 0.5*atan2(2*m[5],m[1]-m[0]);
      const double ct = cos(t);
      const double st = sin(t);
//      std::cout << "hoge2 " << m[1]-m[0] << " " << (ct*ct-st*st)*m[5]+st*ct*(m[0]-m[1]) << std::endl;
//      if( fabs(t)< eps ){ return true; }
      sms[0] = ct*ct*m[0]+st*st*m[1]-2*st*ct*m[5];
      sms[1] = ct*ct*m[1]+st*st*m[0]+2*st*ct*m[5];
      sms[3] = st*m[4]+ct*m[3];
      sms[4] = ct*m[4]-st*m[3];
      sms[5] = 0; // (ct*ct-st*st)*m[5]+st*ct*(m[0]-m[1]);
      //
      u[0] = +ct*v[0]-st*v[1];
      u[1] = +st*v[0]+ct*v[1];
      u[3] = +ct*v[3]-st*v[4];
      u[4] = +st*v[3]+ct*v[4];
      u[6] = +ct*v[6]-st*v[7];
      u[7] = +st*v[6]+ct*v[7];
    }
  }
  l[0] = scale*sms[0];
  l[1] = scale*sms[1];
  l[2] = scale*sms[2];
  return true;
}

double estimationMaxEigenValue(const double mtm[6])
{
  double maxl = 1;
  {  // estimation of maximum eigen value using Gerschgorin's circle theorem
    maxl = mtm[0] + fabs(mtm[3])+fabs(mtm[5]);
    const double tmp2 = mtm[1] + fabs(mtm[3])+fabs(mtm[4]);
    maxl = ( tmp2 > maxl ) ? tmp2 : maxl;
    const double tmp3 = mtm[2] + fabs(mtm[5])+fabs(mtm[4]);
    maxl = ( tmp3 > maxl ) ? tmp3 : maxl;
  }
  return maxl;
}

void dfm2::svd3
(double U[9], double G[3], double V[9],
 const double m[9],
 int nitr)
{
  const double mtm[6] = {
    m[0]*m[0]+m[3]*m[3]+m[6]*m[6],
    m[1]*m[1]+m[4]*m[4]+m[7]*m[7],
    m[2]*m[2]+m[5]*m[5]+m[8]*m[8],
    m[1]*m[2]+m[4]*m[5]+m[7]*m[8],
    m[2]*m[0]+m[5]*m[3]+m[8]*m[6],
    m[0]*m[1]+m[3]*m[4]+m[6]*m[7] };
  double lv[3]; eigenSym3(V,lv,
                          mtm,nitr);
  G[0] = sqrt(lv[0]);
  G[1] = sqrt(lv[1]);
  G[2] = sqrt(lv[2]);
  if( G[0]>1.e-20 && G[1]>1.e-20 && G[2]>1.e-20 ){
    const double invG[3] = { 1.0/G[0], 1.0/G[1], 1.0/G[2] };
    U[0] = (m[0]*V[0]+m[1]*V[3]+m[2]*V[6])*invG[0];
    U[1] = (m[0]*V[1]+m[1]*V[4]+m[2]*V[7])*invG[1];
    U[2] = (m[0]*V[2]+m[1]*V[5]+m[2]*V[8])*invG[2];
    U[3] = (m[3]*V[0]+m[4]*V[3]+m[5]*V[6])*invG[0];
    U[4] = (m[3]*V[1]+m[4]*V[4]+m[5]*V[7])*invG[1];
    U[5] = (m[3]*V[2]+m[4]*V[5]+m[5]*V[8])*invG[2];
    U[6] = (m[6]*V[0]+m[7]*V[3]+m[8]*V[6])*invG[0];
    U[7] = (m[6]*V[1]+m[7]*V[4]+m[8]*V[7])*invG[1];
    U[8] = (m[6]*V[2]+m[7]*V[5]+m[8]*V[8])*invG[2];
  }
  else{
    const double mmt[6] = {
      m[0]*m[0]+m[3]*m[3]+m[6]*m[6],
      m[1]*m[1]+m[4]*m[4]+m[7]*m[7],
      m[2]*m[2]+m[5]*m[5]+m[8]*m[8],
      m[3]*m[6]+m[4]*m[7]+m[5]*m[8],
      m[6]*m[0]+m[7]*m[1]+m[8]*m[2],
      m[0]*m[3]+m[1]*m[4]+m[2]*m[5] };
    double lu[3]; eigenSym3(U,lu,
                            mmt,nitr);
  }
  const double detU = Det_Mat3(U);
  if( detU < 0 ){
    U[2]=-U[2];
    U[5]=-U[5];
    U[8]=-U[8];
    G[2]=-G[2];
  }
}

void dfm2::GetRotPolarDecomp
(double R[9],
 //
 const double am[9],
 int nitr)
{
  double U[9], G[3], V[9];
  svd3(U,G,V,
       am,nitr);
  MatMatT3(R,U,V);
}


// https://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation
// row major matrix
void SetMatrix3_Quaternion(double r[], const double q[])
{
  double x2 = q[1] * q[1] * 2.0;
  double y2 = q[2] * q[2] * 2.0;
  double z2 = q[3] * q[3] * 2.0;
  double xy = q[1] * q[2] * 2.0;
  double yz = q[2] * q[3] * 2.0;
  double zx = q[3] * q[1] * 2.0;
  double xw = q[1] * q[0] * 2.0;
  double yw = q[2] * q[0] * 2.0;
  double zw = q[3] * q[0] * 2.0;
  r[0] = 1.0 - y2 - z2;
  r[1] = xy - zw;
  r[2] = zx + yw;
  r[3] = xy + zw;
  r[4] = 1.0 - z2 - x2;
  r[5] = yz - xw;
  r[6] = zx - yw;
  r[7] = yz + xw;
  r[8] = 1.0 - x2 - y2;
}

// -----------------------------------

namespace delfem2 {

template <typename T>
CMat3<T> operator* (double d, const CMat3<T>& rhs){
  CMat3<T> temp = rhs;
  temp *= d;
  return temp;
}
template CMat3<double> operator* (double d, const CMat3<double>& rhs);

template <typename T>
CMat3<T> operator* (const CMat3<T>& m, double d){
  CMat3<T> t = m;
  t *= d;
  return t;
}
template CMat3<double> operator* (const CMat3<double>& m, double d);

template <typename T>
CMat3<T> operator/ (const CMat3<T>& m, double d){
  CMat3<T> temp = m;
  temp /= d;
  return temp;
}

template <typename T>
CMat3<T> operator+ (const CMat3<T>& lhs, const CMat3<T>& rhs){
  CMat3<T> temp = lhs;
  temp += rhs;
  return temp;
}
template CMat3<double> operator+ (const CMat3<double>& lhs, const CMat3<double>& rhs);

template <typename T>
CMat3<T> operator* (const CMat3<T>& lhs, const CMat3<T>& rhs){
  return lhs.MatMat(rhs);
}
template CMat3<double> operator* (const CMat3<double>& lhs, const CMat3<double>& rhs);
  
// ------------------------------

template <typename T>
CMat3<T> operator- (const CMat3<T>& lhs, const CMat3<T>& rhs){
  CMat3<T> temp = lhs;
  temp -= rhs;
  return temp;
}
template CMat3<double> operator- (const CMat3<double>& lhs, const CMat3<double>& rhs);
  
// ------------------------------

template <typename T>
std::ostream &operator<<(std::ostream &output, const CMat3<T>& m)
{
  output.setf(std::ios::scientific);
  output << m.mat[0*3+0] << " " << m.mat[0*3+1] << " " << m.mat[0*3+2] << " ";
  output << m.mat[1*3+0] << " " << m.mat[1*3+1] << " " << m.mat[1*3+2] << " ";
  output << m.mat[2*3+0] << " " << m.mat[2*3+1] << " " << m.mat[2*3+2] << " ";
  return output;
}

template <typename T>
std::istream &operator>>(std::istream &input, CMat3<T>& m)
{
  input >> m.mat[0*3+0] >> m.mat[0*3+1] >> m.mat[0*3+2];
  input >> m.mat[1*3+0] >> m.mat[1*3+1] >> m.mat[1*3+2];
  input >> m.mat[2*3+0] >> m.mat[2*3+1] >> m.mat[2*3+2];
  return input;
}
  
}

// -------------------------------------------------------------------
  
template <typename T>
dfm2::CMat3<T>::CMat3(): mat{0.,0.,0., 0.,0.,0., 0.,0.,0.} {}
template dfm2::CMat3<double>::CMat3();
  
// ---------------------

template <typename T>
dfm2::CMat3<T>::CMat3(const T s): mat{s,0,0, 0,s,0, 0,0,s} {}

template <typename T>
dfm2::CMat3<T>::CMat3(double v00, double v01, double v02,
                      double v10, double v11, double v12,
                      double v20, double v21, double v22):
 mat{v00,v01,v02, v10,v11,v12, v20,v21,v22}
{}

template <typename T>
dfm2::CMat3<T>::CMat3(T x, T y, T z):
  mat{x,0,0, 0,y,0, 0,0,z} {}

template <typename T>
dfm2::CMat3<T>::CMat3(const T m[9]):
 mat{m[0],m[1],m[2], m[3],m[4],m[5], m[6],m[7],m[8]} {}

template <typename T>
void dfm2::CMat3<T>::MatVec(const double vec0[], double vec1[]) const
{
  ::dfm2::MatVec3(vec1, mat, vec0);
//  vec1[0] = mat[0]*vec0[0] + mat[1]*vec0[1] + mat[2]*vec0[2];
//  vec1[1] = mat[3]*vec0[0] + mat[4]*vec0[1] + mat[5]*vec0[2];
//  vec1[2] = mat[6]*vec0[0] + mat[7]*vec0[1] + mat[8]*vec0[2];
}
template void dfm2::CMat3<double>::MatVec(const double vec0[], double vec1[]) const;

template <typename T>
void dfm2::CMat3<T>::MatVecTrans(const double vec0[], double vec1[]) const
{
  vec1[0] = mat[0]*vec0[0] + mat[3]*vec0[1] + mat[6]*vec0[2];
  vec1[1] = mat[1]*vec0[0] + mat[4]*vec0[1] + mat[7]*vec0[2];
  vec1[2] = mat[2]*vec0[0] + mat[5]*vec0[1] + mat[8]*vec0[2];
}
template void dfm2::CMat3<double>::MatVecTrans(const double vec0[], double vec1[]) const;


template <typename T>
dfm2::CMat3<T> dfm2::CMat3<T>::MatMat(const CMat3<T>& mat0) const{
  CMat3 m;
  ::dfm2::MatMat3(m.mat,
                  this->mat, mat0.mat);
  /*
  for(unsigned int i=0;i<3;i++){
    for(unsigned int j=0;j<3;j++){
      m.mat[i*3+j] =
      mat[i*3+0]*mat0.mat[0*3+j]
      + mat[i*3+1]*mat0.mat[1*3+j]
      + mat[i*3+2]*mat0.mat[2*3+j];
    }
  }
   */
  return m;
}
template dfm2::CMat3<double> dfm2::CMat3<double>::MatMat(const CMat3<double>& mat0) const;
  
// --------------------------------

template <typename T>
dfm2::CMat3<T> dfm2::CMat3<T>::MatMatTrans(const CMat3<T>& mat0) const
{
  CMat3 m;
  for(unsigned int i=0;i<3;i++){
    for(unsigned int j=0;j<3;j++){
      m.mat[i*3+j] =
      + mat[0*3+i]*mat0.mat[0*3+j]
      + mat[1*3+i]*mat0.mat[1*3+j]
      + mat[2*3+i]*mat0.mat[2*3+j];
    }
  }
  return m;
}

template <typename T>
dfm2::CMat3<T> dfm2::CMat3<T>::Inverse() const
{
  CMat3 mi = *this;
  mi.SetInverse();
  return mi;
}
template dfm2::CMat3<double> dfm2::CMat3<double>::Inverse() const;

// ------------------------------------------------------------------

template <typename T>
void dfm2::CMat3<T>::SetInverse()
{
  ::dfm2::Inverse_Mat3(mat);
  /*
  const double det = this->Det();
  const double inv_det = 1.0/det;
  double t[9]; for(int i=0;i<9;i++){ t[i] = this->mat[i]; }
  mat[0] = inv_det*(t[4]*t[8]-t[5]*t[7]);
  mat[1] = inv_det*(t[2]*t[7]-t[1]*t[8]);
  mat[2] = inv_det*(t[1]*t[5]-t[2]*t[4]);
  mat[3] = inv_det*(t[5]*t[6]-t[3]*t[8]);
  mat[4] = inv_det*(t[0]*t[8]-t[2]*t[6]);
  mat[5] = inv_det*(t[2]*t[3]-t[0]*t[5]);
  mat[6] = inv_det*(t[3]*t[7]-t[4]*t[6]);
  mat[7] = inv_det*(t[1]*t[6]-t[0]*t[7]);
  mat[8] = inv_det*(t[0]*t[4]-t[1]*t[3]);
   */
}
template void dfm2::CMat3<double>::SetInverse();
template void dfm2::CMat3<float>::SetInverse();



template <typename T>
void dfm2::CMat3<T>::SetSymetric(const double sm[6])
{
  mat[0] = sm[0];
  mat[1] = sm[5];
  mat[2] = sm[4];
  mat[3] = sm[5];
  mat[4] = sm[1];
  mat[5] = sm[3];
  mat[6] = sm[4];
  mat[7] = sm[3];
  mat[8] = sm[2];
}
template void dfm2::CMat3<float>::SetSymetric(const double sm[6]);
template void dfm2::CMat3<double>::SetSymetric(const double sm[6]);

// --------------------------------

template <typename T>
void dfm2::CMat3<T>::SetZero()
{
  for(double & i : mat){ i = 0.0; }
}
template void dfm2::CMat3<double>::SetZero();
  
// --------------------

namespace delfem2 {

template<>
void CMat3<double>::SetRandom() {
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_real_distribution<double> score(-50.0, 50.0);
  for (double &v : mat) {
    v = score(mt);
  }
}

}

// -----------------------------------------

template <typename T>
void dfm2::CMat3<T>::SetRotMatrix_Cartesian(const double vec[])
{
  double sqt = vec[0]*vec[0]+vec[1]*vec[1]+vec[2]*vec[2];
  if( sqt < 1.0e-20 ){ // infinitesmal rotation approximation
    mat[0] = 1;        mat[1] = -vec[2];  mat[2] = +vec[1];
    mat[3] = +vec[2];  mat[4] = 1;        mat[5] = -vec[0];
    mat[6] = -vec[1];  mat[7] = +vec[0];  mat[8] = 1;
    return;
  }
  double t = sqrt(sqt);
  double invt = 1.0/t;
  double n[3] = { vec[0]*invt, vec[1]*invt, vec[2]*invt };
  const double c0 = cos(t);
  const double s0 = sin(t);
  mat[0*3+0] = c0        +(1-c0)*n[0]*n[0];
  mat[0*3+1] =   -n[2]*s0+(1-c0)*n[0]*n[1];
  mat[0*3+2] =   +n[1]*s0+(1-c0)*n[0]*n[2];
  mat[1*3+0] =   +n[2]*s0+(1-c0)*n[1]*n[0];
  mat[1*3+1] = c0        +(1-c0)*n[1]*n[1];
  mat[1*3+2] =   -n[0]*s0+(1-c0)*n[1]*n[2];
  mat[2*3+0] =   -n[1]*s0+(1-c0)*n[2]*n[0];
  mat[2*3+1] =   +n[0]*s0+(1-c0)*n[2]*n[1];
  mat[2*3+2] = c0        +(1-c0)*n[2]*n[2];
}
template void dfm2::CMat3<double>::SetRotMatrix_Cartesian(const double vec[]);
  
// -------------------------------

template <typename T>
void dfm2::CMat3<T>::SetRotMatrix_Cartesian(double x, double y, double z){
  const double vec[3] = { x, y, z };
  this->SetRotMatrix_Cartesian(vec);
}
template void dfm2::CMat3<double>::SetRotMatrix_Cartesian(double x, double y, double z);
  
// ----------------------------------

template <typename T>
void dfm2::CMat3<T>::SetRotMatrix_Rodrigues(const double vec[])
{
  const double sqlen = vec[0]*vec[0]+vec[1]*vec[1]+vec[2]*vec[2];
  const double tmp1 = 1.0/(1+0.25*sqlen);
  mat[0] = 1+tmp1*(       +0.5*vec[0]*vec[0]-0.5*sqlen);
  mat[1] =  +tmp1*(-vec[2]+0.5*vec[0]*vec[1]          );
  mat[2] =  +tmp1*(+vec[1]+0.5*vec[0]*vec[2]          );
  mat[3] =  +tmp1*(+vec[2]+0.5*vec[1]*vec[0]          );
  mat[4] = 1+tmp1*(       +0.5*vec[1]*vec[1]-0.5*sqlen);
  mat[5] =  +tmp1*(-vec[0]+0.5*vec[1]*vec[2]          );
  mat[6] =  +tmp1*(-vec[1]+0.5*vec[2]*vec[0]          );
  mat[7] =  +tmp1*(+vec[0]+0.5*vec[2]*vec[1]          );
  mat[8] = 1+tmp1*(       +0.5*vec[2]*vec[2]-0.5*sqlen);
}

template <typename T>
void dfm2::CMat3<T>::SetRotMatrix_CRV(const double crv[])
{
  const double c0 = 0.125*( 16.0 - crv[0]*crv[0] - crv[1]*crv[1] - crv[2]*crv[2] );
  const double tmp = 1.0/( (4.0-c0)*(4.0-c0) );
  mat[0*3+0] = tmp*( (c0*c0+8*c0-16) + 2*crv[0]*crv[0] );
  mat[0*3+1] = tmp*(                   2*crv[0]*crv[1] - 2*c0*crv[2] );
  mat[0*3+2] = tmp*(                   2*crv[0]*crv[2] + 2*c0*crv[1] );
  mat[1*3+0] = tmp*(                   2*crv[1]*crv[0] + 2*c0*crv[2] );
  mat[1*3+1] = tmp*( (c0*c0+8*c0-16) + 2*crv[1]*crv[1] );
  mat[1*3+2] = tmp*(                   2*crv[1]*crv[2] - 2*c0*crv[0] );
  mat[2*3+0] = tmp*(                   2*crv[2]*crv[0] - 2*c0*crv[1] );
  mat[2*3+1] = tmp*(                   2*crv[2]*crv[1] + 2*c0*crv[0] );
  mat[2*3+2] = tmp*( (c0*c0+8*c0-16) + 2*crv[2]*crv[2] );
}

template <typename T>
void dfm2::CMat3<T>::SetRotMatrix_Quaternion(const double quat[]){
  SetMatrix3_Quaternion(mat, quat);
}
template void dfm2::CMat3<double>::SetRotMatrix_Quaternion(const double quat[]);

template <typename T>
void dfm2::CMat3<T>::SetRotMatrix_BryantAngle(double rx, double ry, double rz)
{
  CMat3 mx; double rvx[3] = {rx,0,0}; mx.SetRotMatrix_Cartesian(rvx);
  CMat3 my; double rvy[3] = {0,ry,0}; my.SetRotMatrix_Cartesian(rvy);
  CMat3 mz; double rvz[3] = {0,0,rz}; mz.SetRotMatrix_Cartesian(rvz);
  CMat3 m = mz;
  m = m.MatMat(my);
  m = m.MatMat(mx);
  *this = m;
}

template <typename T>
void dfm2::CMat3<T>::GetQuat_RotMatrix(double quat[]) const{
  const double smat[16] = {
    1+mat[0*3+0]+mat[1*3+1]+mat[2*3+2],
    mat[2*3+1]-mat[1*3+2],
    mat[0*3+2]-mat[2*3+0],
    mat[1*3+0]-mat[0*3+1],
    mat[2*3+1]-mat[1*3+2],
    1+mat[0*3+0]-mat[1*3+1]-mat[2*3+2],
    mat[0*3+1]+mat[1*3+0],
    mat[0*3+2]+mat[2*3+0],
    mat[0*3+2]-mat[2*3+0],
    mat[1*3+0]+mat[0*3+1],
    1-mat[0*3+0]+mat[1*3+1]-mat[2*3+2],
    mat[1*3+2]+mat[2*3+1],
    mat[1*3+0]-mat[0*3+1],
    mat[0*3+2]+mat[2*3+0],
    mat[1*3+2]+mat[2*3+1],
    1-mat[0*3+0]-mat[1*3+1]+mat[2*3+2],
  };
  
  unsigned int imax;
  imax = ( smat[0   *4+   0] > smat[1*4+1] ) ? 0    : 1;
  imax = ( smat[imax*4+imax] > smat[2*4+2] ) ? imax : 2;
  imax = ( smat[imax*4+imax] > smat[3*4+3] ) ? imax : 3;
  
  quat[imax] = 0.5*sqrt(smat[imax*4+imax]);
  for(unsigned int k=0;k<4;k++){
    if( k==imax ) continue;
    quat[k] = smat[imax*4+k]*0.25/quat[imax];
  }
}
template void dfm2::CMat3<double>::GetQuat_RotMatrix(double quat[]) const;

template <typename T>
void dfm2::CMat3<T>::GetCRV_RotMatrix(double crv[]) const{
  double eparam2[4];
  this->GetQuat_RotMatrix(eparam2);
  crv[0] = 4*eparam2[1]/(1+eparam2[0]);
  crv[1] = 4*eparam2[2]/(1+eparam2[0]);
  crv[2] = 4*eparam2[3]/(1+eparam2[0]);
}

template <typename T>
void dfm2::CMat3<T>::SetIdentity(double scale)
{
  mat[0] = scale; mat[1] = 0;     mat[2] = 0;
  mat[3] = 0;     mat[4] = scale; mat[5] = 0;
  mat[6] = 0;     mat[7] = 0;     mat[8] = scale;
}
template void dfm2::CMat3<double>::SetIdentity(double scale);
template void dfm2::CMat3<float>::SetIdentity(double scale);

// 3x3 matrix
// -------------------------------------------------------------------------------------------
// 4x4 matrix

template <typename T>
void dfm2::MatVec4
(T v[4],
 const T A[16],
 const T x[4])
{
  v[0] = A[0*4+0]*x[0] + A[0*4+1]*x[1] + A[0*4+2]*x[2] + A[0*4+3]*x[3];
  v[1] = A[1*4+0]*x[0] + A[1*4+1]*x[1] + A[1*4+2]*x[2] + A[1*4+3]*x[3];
  v[2] = A[2*4+0]*x[0] + A[2*4+1]*x[1] + A[2*4+2]*x[2] + A[2*4+3]*x[3];
  v[3] = A[3*4+0]*x[0] + A[3*4+1]*x[1] + A[3*4+2]*x[2] + A[3*4+3]*x[3];
}
template void dfm2::MatVec4(float v[4], const float A[16], const float x[4]);
template void dfm2::MatVec4(double v[4], const double A[16], const double x[4]);
  

template <typename T>
void dfm2::MatMat4
(T* C,
 const T* A, const T* B)
{
  for(int i=0;i<4;i++){
    for(int j=0;j<4;j++){
      C[i*4+j] = A[i*4+0]*B[0*4+j] + A[i*4+1]*B[1*4+j] + A[i*4+2]*B[2*4+j] + A[i*4+3]*B[3*4+j];
    }
  }
}
template void dfm2::MatMat4(float* C, const float* A, const float* B);
template void dfm2::MatMat4(double* C, const double* A, const double* B);

  
// ---------------------------

template <typename T>
void dfm2::Vec3_AffMat3Vec3Projection
(T y0[3],
 const T a[16],
 const T x0[3])
{
  const T x1[4] = {x0[0], x0[1], x0[2], 1.0};
  T y1[4]; MatVec4(y1,a,x1);
  y0[0] = y1[0]/y1[3];
  y0[1] = y1[1]/y1[3];
  y0[2] = y1[2]/y1[3];
}
template void dfm2::Vec3_AffMat3Vec3Projection(float y0[3], const float a[16], const float x0[3]);
template void dfm2::Vec3_AffMat3Vec3Projection(double y0[3], const double a[16], const double x0[3]);

  
// ----------------------

template <typename T>
void dfm2::Mat4_AffineScale
(T A[16],
 T s)
{
  for(int i=0;i<16;++i){ A[i] = 0.0; }
  A[0*4+0] = s;
  A[1*4+1] = s;
  A[2*4+2] = s;
  A[3*4+3] = 1.0;
}
template void dfm2::Mat4_AffineScale(float A[16], float s);
template void dfm2::Mat4_AffineScale(double A[16], double s);
  
// ------------------------

template <typename T>
void dfm2::Mat4_AffineTranslation
(T A[16],
 T dx, T dy, T dz)
{
  for(auto i=0;i<16;++i){ A[i] = 0.0; }
  for(int i=0;i<4;++i){ A[i*4+i] = 1.0; }
  A[0*4+3] = dx;
  A[1*4+3] = dy;
  A[2*4+3] = dz;
}
template void dfm2::Mat4_AffineTranslation(float A[16],  float dx, float dy, float dz);
template void dfm2::Mat4_AffineTranslation(double A[16],  double dx, double dy, double dz);
  
// --------------------------

template <typename T>
void dfm2::Mat4_AffineRotationRodriguez
(T A[16],
 T dx, T dy, T dz)
{
  for(int i=0;i<16;++i){ A[i] = 0.0; }
  //
  const double sqlen = dx*dx+dy*dy+dz*dz;
  const double tmp1 = 1.0/(1+0.25*sqlen);
  A[0*4+0] = 1+tmp1*(+0.5*dx*dx-0.5*sqlen);
  A[0*4+1] =  +tmp1*(-dz+0.5*dx*dy);
  A[0*4+2] =  +tmp1*(+dy+0.5*dx*dz);
  A[0*4+3] = 0.0;
  //
  A[1*4+0] =  +tmp1*(+dz+0.5*dy*dx);
  A[1*4+1] = 1+tmp1*(+0.5*dy*dy-0.5*sqlen);
  A[1*4+2] =  +tmp1*(-dx+0.5*dy*dz);
  A[1*4+3] = 0.0;
  //
  A[2*4+0] =  +tmp1*(-dy+0.5*dz*dx);
  A[2*4+1] =  +tmp1*(+dx+0.5*dz*dy);
  A[2*4+2] = 1+tmp1*(+0.5*dz*dz-0.5*sqlen);
  A[2*4+3] = 0.0;
  //
  A[3*4+0] = 0.0;
  A[3*4+1] = 0.0;
  A[3*4+2] = 0.0;
  A[3*4+3] = 1.0;
}
template void dfm2::Mat4_AffineRotationRodriguez(float A[16],
                                                 float dx, float dy, float dz);
template void dfm2::Mat4_AffineRotationRodriguez(double A[16],
                                                 double dx, double dy, double dz);

// ------------------------------------------------

template <typename REAL>
void dfm2::Mat4_Identity(
    REAL A[16])
{
  for(int i=0;i<16;++i){ A[i] = 0; }
  A[0*4+0] = 1;
  A[1*4+1] = 1;
  A[2*4+2] = 1;
  A[3*4+3] = 1;
}
template void dfm2::Mat4_Identity(float A[16]);
template void dfm2::Mat4_Identity(double A[16]);

  
// ------------------------------------------------
  
template <typename REAL>
void dfm2::Rotate_Mat4AffineRodriguez(
    REAL A[16],
    const REAL V[3])
{
  REAL B[16];
  Mat4_AffineRotationRodriguez(B,
                               V[0],V[1],V[2]);
  REAL C[16];
  MatMat4(C,B,A);
  
  for(int i=0;i<16;++i){ A[i] = C[i]; }
}
template void dfm2::Rotate_Mat4AffineRodriguez(float A[16], const float V[3]);
template void dfm2::Rotate_Mat4AffineRodriguez(double A[16], const double V[3]);
  
  
template <typename REAL>
void dfm2::Translate_Mat4Affine(
    REAL A[16],
    const REAL V[3])
{
  A[0*4+3] += V[0];
  A[1*4+3] += V[1];
  A[2*4+3] += V[2];
}
template void dfm2::Translate_Mat4Affine(float A[16], const float V[3]);
template void dfm2::Translate_Mat4Affine(double A[16], const double V[3]);

