namespace delfem2 {
namespace cuda{

void cuda_VecScale(
    float *hOut,
    const float *hIn,
    float scale,
    const int n);

// -------------------------------------------------------------

float cuda_Dot(
    const float *h_A,
    const float *h_B,
    unsigned int n);

// -------------------------------------------------------------


void cuda_MatMat(
    float *h_C_gpu,
    const float *h_A,
    const float *h_B,
    unsigned int WIDTH);

// -------------------------------------------------------------

void cuda_MinMax_Points3F(
    float *p_minmax,
    const float *p_XYZ,
    unsigned int np);

// -------------------------------------------------------------

void cuda_CentsMaxRad_MeshTri3F(
    float* pXYZ_cent,
    float* max_rad,
    const float *aXYZ,
    const unsigned int nXYZ,
    const unsigned int *aTri,
    const unsigned int nTri);

void cuda_MortonCode_Points3F(
    unsigned int *aMorton,
    const float *aXYZ,
    const unsigned int nXYZ);


} // cuda
} // delfem2