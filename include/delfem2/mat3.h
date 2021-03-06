/*
 * Copyright (c) 2019 Nobuyuki Umetani
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

/**
 * @file 3x3 matrix class (CMat3) and functions
 */


#ifndef DFM2_MAT3_H
#define DFM2_MAT3_H

#include <vector>
#include <cassert>
#include <cmath>
#include <iostream>
#include <limits> // using NaN Check

#define NEARLY_ZERO 1.e-16

// -----------------------------

namespace delfem2 {

/**
 * @func Set spin 3x3 matrix (skew asymetric matrix)
 * @tparam REAL float and double
 * @param mat pointer of 3x3 matrix
 * @param v ponter of 3 vector
 */
template <typename REAL>
void Mat3_Spin(
    REAL* mat,
    const REAL* v);

template <typename REAL>
void Mat3_Spin_ScaleAdd(
    REAL* mat,
    const REAL* v,
    REAL alpha, REAL beta);


template <typename REAL>
void Mat3_Identity(
    REAL* mat,
    REAL alpha);

template <typename REAL>
void Mat3_Identity_ScaleAdd(
    REAL* mat,
    REAL alpha=1, REAL beta=0);

template <typename T>
void Transpose_Mat3(T At[],
                    const T A[]);

template <typename REAL>
void Inverse_Mat3(REAL Ainv[],
                  const REAL A[]);

template <typename REAL>
void Inverse_Mat3(REAL Ainv[9]);

template <typename T>
void MatMat3(T* UL,
             const T* U, const T* L);
  
template <typename T>
void MatMatT3(
    T* ULUt,
    const T* UL,
    const T* U);
  
/**
 * @func product of a transposed 3x3 matrix and another 3x3 matrix.
 * [C] = [A]^T[B}
 * @details row major data structure
 */
template <typename T>
void MatTMat3(
    T* C,
    const T* A, const T* B);

/**
 * @func adding scaled product of a transposed 3x3 matrix and another 3x3 matrix.
 * [C] = alpha * [A]^T[B} + beta* [C]
 * @details row major data structure
 */
template <typename T>
void MatTMat3_ScaleAdd(
    T* C,
    const T* A, const T* B,
    T alpha, T beta);


template <typename T>
T Det_Mat3(const T U[9]);
  
template <typename T>
T SquareNormFrobenius_SymMat3(const T sm[6]);

template <typename REAL>
void Mat3_Rotation_Cartesian(
    REAL mat[9],
    const REAL vec[3]);

/**
 * @func compute eigen value & vector for symmmetric matrix
 * @details
 * sm[6] = (M_00,M_11,M_22,M_12,M_20,M_01)
 * M = ULU^T
 * u[9] = (U_00,U_01,U_02, U_10,U_11,U_12, U_20,U_21,U_22)
 */
bool eigenSym3(double u[9], double l[3],
               const double sm[6],
               int nitr);

void svd3(double U[9], double G[3], double V[9],
          const double m[9],
          int nitr);

void GetRotPolarDecomp(double R[9],
                       const double am[9],
                       int nitr);

// ------------------------------------------------

void MatTVec3(
    double y[3],
    const double m[9], const double x[3]);

/**
 * @func {y} = beta*{y} + alpha*[M]^T{x}
 */
template <typename T>
void MatTVec3_ScaleAdd(
    T y[3],
    const T m[9], const T x[3],
    T alpha, T beta);

/**
 * @func matrix vector product for 3x3 matrix {y} := [m]{x}
 */
template <typename T>
void MatVec3(T y[3],
             const T m[9], const T x[3]);

template <typename T>
void MatVec3_ScaleAdd(T y[3],
                      const T m[9], const T x[3],
                      T alpha, T beta);

void VecMat3(double y[3],
             const double x[3], const double m[9]);
void Mat4Vec3(double vo[3],
              const double M[16],
              const double vi[3]);

// -------------------------------

template <typename T>
void MatVec4(T v[4],
    const T A[16],
    const T x[4]);

template <typename T>
void MatMat4(
    T* C,
    const T* A,
    const T* B);


template <typename REAL>
void Mat4_Identity(
    REAL A[16]);
  
template <typename REAL>
void Mat4_AffineScale(
    REAL A[16],
    REAL s);
  
template <typename REAL>
void Mat4_AffineTranslation(
    REAL A[16],
    REAL dx, REAL dy, REAL dz);

template <typename T>
void Mat4_AffineRotationRodriguez(
    T A[16],
    T dx, T dy, T dz);

template <typename T>
void Vec3_AffMat3Vec3Projection(
    T y0[3],
    const T a[16],
    const T x0[3]);

/**
 * @func multiply rotation affine matrix from left to an affine matrix in 3D
 * @details the ritation is parmeterized with a rodriguez angle
 */
template <typename REAL>
void Rotate_Mat4AffineRodriguez(
    REAL A[16],
    const REAL v[3]);

/**
 * @func multiply translation affine matrix from left to an affine matrix in 3D
 */
template <typename REAL>
void Translate_Mat4Affine(
    REAL A[16],
    const REAL v[3]);



// --------------------------------
  
template <typename T>
class CMat3; // this pre-definition is needed for following functions

template <typename T>
CMat3<T> operator+ (const CMat3<T>& lhs, const CMat3<T>& rhs);

template <typename T>
CMat3<T> operator- (const CMat3<T>& lhs, const CMat3<T>& rhs);

template <typename T>
CMat3<T> operator* (double d, const CMat3<T>& rhs);

template <typename T>
CMat3<T> operator* (const CMat3<T>& m, double d);
  
template <typename T>
CMat3<T> operator* (const CMat3<T>& lhs, const CMat3<T>& rhs);

template <typename T>
CMat3<T> operator/ (const CMat3<T>& m, double d);

template <typename T>
std::ostream &operator<<(std::ostream &output, const CMat3<T>& m);
  
template <typename T>
std::istream &operator>>(std::istream &output, CMat3<T>& m);

static inline bool myIsNAN_Matrix3(double d){ return !(d > d-1); }

/**
 * @class class of 3x3 matrix
 */
template <typename REAL>
class CMat3
{
public:
  CMat3();
  CMat3(const REAL s);
  CMat3(double v00, double v01, double v02,
           double v10, double v11, double v12,
           double v20, double v21, double v22);
  CMat3(REAL x, REAL y, REAL z);
  CMat3(const REAL m[9]);
  // ---------------
  REAL* data() { return mat; }
  const REAL* data() const { return mat; }
  // ---------------
  void GetElements(double m[9]) const { for(unsigned int i=0;i<9;i++){ m[i]=mat[i]; } }
  void AffineMatrixTrans(double m[16]) const {
    m[0*4+0] = mat[0];  m[1*4+0] = mat[1];  m[2*4+0] = mat[2];  m[3*4+0] = 0;
    m[0*4+1] = mat[3];  m[1*4+1] = mat[4];  m[2*4+1] = mat[5];  m[3*4+1] = 0;
    m[0*4+2] = mat[6];  m[1*4+2] = mat[7];  m[2*4+2] = mat[8];  m[3*4+2] = 0;
    m[0*4+3] = 0;       m[1*4+3] = 0;       m[2*4+3] = 0;       m[3*4+3] = 1;
  }
  double Get(int i, int j) const { return mat[i*3+j]; }
  void CopyValueToPtr(REAL* ptr) const {
    for(int i=0;i<9;++i){ ptr[i] = mat[i]; }
  }
  // ---------------
//  CVector3 MatVec(const CVector3& vec0) const;
  void MatVec(const double vec0[], double vec1[]) const;
  void MatVecTrans(const double vec0[], double vec1[]) const;
//  CVector3 MatVecTrans(const CVector3& vec0) const;
  CMat3 MatMat(const CMat3& mat0) const;
  CMat3 MatMatTrans(const CMat3& mat0) const;
  // ----------------
  CMat3 Sym() const{
    CMat3 m;
    for(unsigned int i=0;i<3;i++){
    for(unsigned int j=0;j<3;j++){
      m.mat[i*3+j] = (mat[i*3+j]+mat[j*3+i])*0.5;
    }
    }
    return m;
  }
  inline const CMat3 operator-() const{ return (*this)*(-1.0); }
  inline const CMat3 operator+() const{ return (*this); }
  inline CMat3& operator+=(const CMat3& rhs){
    for(unsigned int i=0;i<9;i++){ mat[i] += rhs.mat[i]; }
		return *this;
	}  
  inline CMat3& operator-=(const CMat3& rhs){
    for(unsigned int i=0;i<9;i++){ mat[i] -= rhs.mat[i]; }
		return *this;
	}    
	inline CMat3& operator*=(double d){
    for(unsigned int i=0;i<9;i++){ mat[i] *= d; }
		return *this;
	}
	inline CMat3& operator/=(double d){
    double invd = 1.0/d;
    for(unsigned int i=0;i<9;i++){ mat[i] *= invd; }
		return *this;
	}
  inline double operator[](int i) const{
    return this->mat[i];
  }  
  inline double& operator()(int i, int j){
    return this->mat[i*3+j];
  }
  // -------------------------
  CMat3 Inverse() const;
  // -------------------------
  void SetInverse();
  void SetSymetric(const double sm[6]);
  void SetZero();
  void SetRandom();
  void SetRotMatrix_Cartesian(const double vec[]);
  void SetRotMatrix_Cartesian(double x, double y, double z);
  void SetRotMatrix_Rodrigues(const double vec[]);
  void SetRotMatrix_CRV(const double crv[]);
  void SetRotMatrix_Quaternion(const double quat[]);
  void SetRotMatrix_BryantAngle(double rx, double ry, double rz);
  void SetIdentity(double scale = 1);
  // ------------------------
  void GetCRV_RotMatrix(double crv[]) const;
  void GetQuat_RotMatrix(double quat[]) const;
  // ------------------------
  CMat3 Trans() const {
    CMat3 m;
    m.mat[0] = mat[0]; m.mat[1] = mat[3]; m.mat[2] = mat[6];
    m.mat[3] = mat[1]; m.mat[4] = mat[4]; m.mat[5] = mat[7];
    m.mat[6] = mat[2]; m.mat[7] = mat[5]; m.mat[8] = mat[8];    
    return m;
  }
  bool isNaN() const{
    double s=mat[0]+mat[1]+mat[2]+mat[3]+mat[4]+mat[5]+mat[6]+mat[7]+mat[8];
    return myIsNAN_Matrix3( s ) != 0;
  }
  double Det() const {
    return
    + mat[0]*mat[4]*mat[8] + mat[3]*mat[7]*mat[2] + mat[6]*mat[1]*mat[5]
    - mat[0]*mat[7]*mat[5] - mat[6]*mat[4]*mat[2] - mat[3]*mat[1]*mat[8];
  }
  double SqNorm_Frobenius() const {
    double s = 0.0;
    for(int i=0;i<9;++i){
      s += mat[i]*mat[i];
    }
    return s;
  }
  double Trace() const {
    return mat[0]+mat[4]+mat[8];
  }
  double SecondInvarint() const {
    const CMat3& m2 = (*this)*(*this);
    const double tr = this->Trace();
    return 0.5*(tr*tr-m2.Trace());
  }
  void Print() const {
    std::cout << mat[0] << " " << mat[1] << " " << mat[2] << std::endl;
    std::cout << mat[3] << " " << mat[4] << " " << mat[5] << std::endl;
    std::cout << mat[6] << " " << mat[7] << " " << mat[8] << std::endl;
  }
  void PolerDecomp(CMat3& R, int nitr) const{
    GetRotPolarDecomp(R.mat,
                      mat, nitr);
  }
  // --------------------
  // static functions
  static CMat3 Identity(double scale = 1){
    CMat3 m;
    m.SetIdentity(scale);
    return m;
  }
  static CMat3 Zero(){
    CMat3 m;
    m.SetZero();
    return m;
  }

public:
  REAL mat[9];
};

using CMat3d = CMat3<double>;
using CMat3f = CMat3<float>;

template <typename T>
CMat3<T> Mat3_Identity(T alpha){
  CMat3<T> m;
  Mat3_Identity(m.mat, alpha);
  return m;
}

}

#endif
