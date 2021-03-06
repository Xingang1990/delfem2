/*
 * Copyright (c) 2019 Nobuyuki Umetani
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <cassert>
#include <cmath>
#include <vector>
#include <complex>
#include "delfem2/vecxitrsol.h"

typedef std::complex<double> COMPLEX;
namespace dfm2 = delfem2;

// ----------------------------------------------------------------------

template <typename T>
T dfm2::Dot(
    const std::vector<T>& r_vec,
    const std::vector<T>& u_vec)
{
  assert( r_vec.size() == u_vec.size() );
  const std::size_t n = r_vec.size();
  T r = 0;
  for(unsigned int i=0;i<n;i++){ r += r_vec[i]*u_vec[i]; }
  return r;
}
template float dfm2::Dot(const std::vector<float>& r_vec, const std::vector<float>& u_vec);
template double dfm2::Dot(const std::vector<double>& r_vec, const std::vector<double>& u_vec);

namespace delfem2 {

template <>
COMPLEX Dot(
    const std::vector<COMPLEX>& va,
    const std::vector<COMPLEX>& vb)
{
  const std::size_t n = va.size();
  assert( vb.size() == n );
  double sr = 0.0, si = 0.0;
  for(unsigned int i=0;i<n;++i){
    const COMPLEX& a = va[i];
    const COMPLEX& b = vb[i];
    sr += a.real()*b.real() + a.imag()*b.imag();
    si += a.imag()*b.real() - a.real()*b.imag();
  }
  return {sr,si};
}

}

// -----------------------------

template<typename T>
T dfm2::DotX(
    const T* va,
    const T* vb,
    unsigned int n)
{
  T r = 0.0;
  for(unsigned int i=0;i<n;i++){ r += va[i]*vb[i]; }
  return r;
}
template float dfm2::DotX(const float* va, const float* vb, unsigned int n);
template double dfm2::DotX(const double* va, const double* vb, unsigned int n);

namespace delfem2 {

template <>
COMPLEX DotX
 (const COMPLEX* va,
  const COMPLEX* vb,
  unsigned int n)
{
  double sr = 0.0;
  double si = 0.0;
  for(unsigned int i=0;i<n;i++){
    const COMPLEX& a = va[i];
    const COMPLEX& b = vb[i];
    sr += a.real()*b.real() + a.imag()*b.imag();
    si += a.imag()*b.real() - a.real()*b.imag();
  }
  return {sr,si};
}

}


// -------------------------------------------------

namespace delfem2 {

// {y} = {y} + a * {x}
template <typename VAL>
void AXPY(
    VAL a,
    const std::vector<VAL> &x,
    std::vector<VAL> &y)
{
  const std::size_t n = x.size();
  assert(y.size() == n);
  for (unsigned int i = 0; i < n; i++) { y[i] += a * x[i]; }
}
template void AXPY( float a, const std::vector<float> &x, std::vector<float> &y);
template void AXPY( double a, const std::vector<double> &x, std::vector<double> &y);
template void AXPY( COMPLEX a, const std::vector<COMPLEX> &x, std::vector<COMPLEX> &y);

}

// -----------------------------------------------------------

namespace delfem2 {

// {y} = {y} + a * {x}
template <typename VAL>
void AXPY(
    VAL a,
    const VAL* x,
    VAL* y,
    unsigned int n)
{
  for(unsigned int i=0;i<n;i++){ y[i] += a*x[i]; }
}
template void AXPY(float a, const float* x, float* y, unsigned int n);
template void AXPY(double a, const double* x, double* y, unsigned int n);
template void AXPY(COMPLEX a, const COMPLEX* x, COMPLEX* y, unsigned int n);

}


// --------

template <typename VAL>
void dfm2::ScaleX(
    VAL* p0,
    VAL s,
    unsigned int n)
{
  for(unsigned int i=0;i<n;++i){ p0[i] *= s; }
}
template void dfm2::ScaleX(float* p0, float s, unsigned int n);
template void dfm2::ScaleX(double* p0, double s, unsigned int n);



// -----------------------------------------------------------



void dfm2::NormalizeX(
                      double* p0,
                      unsigned int n)
{
  const double ss = dfm2::DotX(p0,p0,n);
  ScaleX(p0,1.0/sqrt(ss),n);
}

void dfm2::OrthogonalizeToUnitVectorX(
                                      double* p1,
                                      const double* p0,
                                      unsigned int n)
{
  double d = dfm2::DotX(p0, p1, n);
  for(unsigned int i=0;i<n;++i){ p1[i] -= d*p0[i]; }
}


COMPLEX dfm2::MultSumX
(const COMPLEX* va,
 const COMPLEX* vb,
 unsigned int n)
{
  COMPLEX s(0,0);
  for(unsigned int i=0;i<n;++i){
    const COMPLEX& a = va[i];
    const COMPLEX& b = vb[i];
    s += a*b;
  }
  return s;
}

// ---------------------------------------------------------------

namespace delfem2 {

template<>
void XPlusAY
(std::vector<double> &X,
 const int nDoF,
 const std::vector<int> &aBCFlag,
 double alpha,
 const std::vector<double> &Y)
{
  for (int i = 0; i < nDoF; ++i) {
    if (aBCFlag[i] != 0) continue;
    X[i] += alpha * Y[i];
  }
}

template<>
void XPlusAY
(std::vector<std::complex<double> > &X,
 const int nDoF,
 const std::vector<int> &aBCFlag,
 std::complex<double> alpha,
 const std::vector<std::complex<double> > &Y)
{
  for (int i = 0; i < nDoF; ++i) {
    if (aBCFlag[i] != 0) continue;
    X[i] += alpha * Y[i];
  }
}

} // end namespace delfem2

// -------------------------------------

namespace delfem2 {

template<>
void setRHS_Zero
(std::vector<double> &vec_b,
 const std::vector<int> &aBCFlag,
 int iflag_nonzero)
{
  const std::size_t ndof = vec_b.size();
  for (unsigned int i = 0; i < ndof; ++i) {
    if (aBCFlag[i] == iflag_nonzero) continue;
    vec_b[i] = 0;
  }
}

template<>
void setRHS_Zero
(std::vector<COMPLEX> &vec_b,
 const std::vector<int> &aBCFlag,
 int iflag_nonzero)
{
  const int ndof = (int) vec_b.size();
  for (int i = 0; i < ndof; ++i) {
    if (aBCFlag[i] == iflag_nonzero) continue;
    vec_b[i] = 0;
  }
}

}

void dfm2::XPlusAYBZ
 (std::vector<double>& X,
  const int nDoF,
  const std::vector<int>& aBCFlag,
  double alpha,
  const std::vector<double>& Y,
  double beta,
  const std::vector<double>& Z)
{
  for(int i=0;i<nDoF;++i ){
    if( aBCFlag[i] !=0 ) continue;
    X[i] += alpha*Y[i] + beta*Z[i];
  }
}

void dfm2::XPlusAYBZCW
 (std::vector<double>& X,
  const int nDoF,
  const std::vector<int>& aBCFlag,
  double alpha,
  const std::vector<double>& Y,
  double beta,
  const std::vector<double>& Z,
  double gamma,
  const std::vector<double>& W)
{
  for(int i=0;i<nDoF;++i ){
    if( aBCFlag[i] !=0 ) continue;
    X[i] += alpha*Y[i] + beta*Z[i] + gamma*W[i];
  }
}

// -------------------------------------------------------------------



void dfm2::setRHS_MasterSlave(
                              double* vec_b,
                              int nDoF,
                              const int* aMSFlag)
{
  for(int idof=0;idof<nDoF;++idof){
    int jdof = aMSFlag[idof];
    if( jdof == -1 ) continue;
    vec_b[jdof] += vec_b[idof];
    vec_b[idof] = 0;
  }
}




void dfm2::MatVec(double* y,
                  double* A, unsigned int ncol, unsigned int nrow,
                  double* x)
{
  for(unsigned int i=0;i<ncol;++i){
    y[i] = 0;
    for(unsigned int j=0;j<nrow;++j){
      y[i] += A[i*nrow+j]*x[j];
    }
  }
}
