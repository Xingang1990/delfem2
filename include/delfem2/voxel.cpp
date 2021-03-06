/*
 * Copyright (c) 2019 Nobuyuki Umetani
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */


#include "delfem2/vec3.h"
#include "delfem2/voxel.h"

namespace dfm2 = delfem2;

const unsigned int noelElemFace_Vox[6][4] = {
  { 0, 4, 6, 2 }, // -x
  { 1, 3, 7, 5 }, // +x
  { 0, 1, 5, 4 }, // -y
  { 2, 6, 7, 3 }, // +y
  { 0, 2, 3, 1 }, // -z
  { 4, 5, 7, 6 } }; // +z

const dfm2::CVec3d normalHexFace[6] = {
  dfm2::CVec3d(-1, 0, 0),
  dfm2::CVec3d(+1, 0, 0),
  dfm2::CVec3d( 0,-1, 0),
  dfm2::CVec3d( 0,+1, 0),
  dfm2::CVec3d( 0, 0,-1),
  dfm2::CVec3d( 0, 0,+1)
};

bool dfm2::IsInclude_AABB(const int aabb[8], int igvx, int igvy, int igvz)
{
  if( igvx < aabb[0] || igvx >= aabb[1] ){ return false; }
  if( igvy < aabb[2] || igvy >= aabb[3] ){ return false; }
  if( igvz < aabb[4] || igvz >= aabb[5] ){ return false; }
  return true;
}

void dfm2::Add_AABB(int aabb[8], int ivx, int ivy, int ivz)
{
  const int ipx0 = ivx+0;  const int ipx1 = ivx+1;
  const int ipy0 = ivy+0;  const int ipy1 = ivy+1;
  const int ipz0 = ivz+0;  const int ipz1 = ivz+1;
  if( aabb[0]>aabb[1] ){
    aabb[0] = ipx0;  aabb[1] = ipx1;
    aabb[2] = ipy0;  aabb[3] = ipy1;
    aabb[4] = ipz0;  aabb[5] = ipz1;
  }
  else{
    if( ipx0 < aabb[0] ){ aabb[0] = ipx0; }
    if( ipx1 > aabb[1] ){ aabb[1] = ipx1; }
    if( ipy0 < aabb[2] ){ aabb[2] = ipy0; }
    if( ipy1 > aabb[3] ){ aabb[3] = ipy1; }
    if( ipz0 < aabb[4] ){ aabb[4] = ipz0; }
    if( ipz1 > aabb[5] ){ aabb[5] = ipz1; }
  }
}


void dfm2::MeshQuad3D_VoxelGrid
(std::vector<double>& aXYZ, std::vector<unsigned int>& aQuad,
 int ndivx, int ndivy, int ndivz,
 int ioffx, int ioffy, int ioffz,
 const std::vector<int>& aIsVox)
{
  aQuad.clear();
  aXYZ.clear();
  //////
  const int mdivx = ndivx+1;
  const int mdivy = ndivy+1;
  const int mdivz = ndivz+1;
  for(int igpx=0;igpx<mdivx;++igpx){
    for(int igpy=0;igpy<mdivy;++igpy){
      for(int igpz=0;igpz<mdivz;++igpz){
        aXYZ.push_back( igpx+ioffx );
        aXYZ.push_back( igpy+ioffy );
        aXYZ.push_back( igpz+ioffz );
      }
    }
  }
  //////
  assert( (int)aIsVox.size() == ndivx*ndivy*ndivz );
  for(int igvx=0;igvx<ndivx;++igvx){
    for(int igvy=0;igvy<ndivy;++igvy){
      for(int igvz=0;igvz<ndivz;++igvz){
        const int ivoxel = igvx*(ndivy*ndivz)+igvy*ndivz+igvz;
        assert( ivoxel < (int)aIsVox.size() );
        if( aIsVox[ivoxel] == 0 ){ continue; }
        /////
        int aIGP_Vox[8] = {0,0,0,0, 0,0,0,0};
        {
          aIGP_Vox[0] = (igvx+0)*(mdivy*mdivz)+(igvy+0)*mdivz+(igvz+0);
          aIGP_Vox[1] = (igvx+1)*(mdivy*mdivz)+(igvy+0)*mdivz+(igvz+0);
          aIGP_Vox[2] = (igvx+0)*(mdivy*mdivz)+(igvy+1)*mdivz+(igvz+0);
          aIGP_Vox[3] = (igvx+1)*(mdivy*mdivz)+(igvy+1)*mdivz+(igvz+0);
          aIGP_Vox[4] = (igvx+0)*(mdivy*mdivz)+(igvy+0)*mdivz+(igvz+1);
          aIGP_Vox[5] = (igvx+1)*(mdivy*mdivz)+(igvy+0)*mdivz+(igvz+1);
          aIGP_Vox[6] = (igvx+0)*(mdivy*mdivz)+(igvy+1)*mdivz+(igvz+1);
          aIGP_Vox[7] = (igvx+1)*(mdivy*mdivz)+(igvy+1)*mdivz+(igvz+1);
        }
        for(int iface=0;iface<6;++iface){
          const int jgv0 = Adj_Grid(ivoxel, iface, ndivx, ndivy, ndivz);
          if( jgv0 >= 0 ){
            assert( jgv0 < (int)aIsVox.size() );
            if( aIsVox[jgv0] == 1 ){ continue; } // facing to adjacent voxel -> no outward face.
          }
          /////
          const int aIGP0 = aIGP_Vox[ noelElemFace_Vox[iface][0] ];
          const int aIGP1 = aIGP_Vox[ noelElemFace_Vox[iface][1] ];
          const int aIGP2 = aIGP_Vox[ noelElemFace_Vox[iface][2] ];
          const int aIGP3 = aIGP_Vox[ noelElemFace_Vox[iface][3] ];
          aQuad.push_back(aIGP0);
          aQuad.push_back(aIGP1);
          aQuad.push_back(aIGP2);
          aQuad.push_back(aIGP3);
        }
      }
    }
  }
}

void dfm2::MeshHex3D_VoxelGrid
(std::vector<double>& aXYZ, std::vector<int>& aHex,
 int ndivx, int ndivy, int ndivz,
 int ioffx, int ioffy, int ioffz,
 const std::vector<int>& aIsVox)
{
  aHex.clear();
  aXYZ.clear();
  //////
  const int mdivx = ndivx+1;
  const int mdivy = ndivy+1;
  const int mdivz = ndivz+1;
  for(int igpx=0;igpx<mdivx;++igpx){
    for(int igpy=0;igpy<mdivy;++igpy){
      for(int igpz=0;igpz<mdivz;++igpz){
        aXYZ.push_back( igpx+ioffx );
        aXYZ.push_back( igpy+ioffy );
        aXYZ.push_back( igpz+ioffz );
      }
    }
  }
  //////
  assert( (int)aIsVox.size() == ndivx*ndivy*ndivz );
  for(int igvx=0;igvx<ndivx;++igvx){
    for(int igvy=0;igvy<ndivy;++igvy){
      for(int igvz=0;igvz<ndivz;++igvz){
        const int ivoxel = igvx*(ndivy*ndivz)+igvy*ndivz+igvz;
        assert( ivoxel < (int)aIsVox.size() );
        if( aIsVox[ivoxel] == 0 ){ continue; }
        /////
        int aIGP_Hex[8] = {0,0,0,0, 0,0,0,0};
        {
          aIGP_Hex[0] = (igvx+0)*(mdivy*mdivz)+(igvy+0)*mdivz+(igvz+0);
          aIGP_Hex[1] = (igvx+1)*(mdivy*mdivz)+(igvy+0)*mdivz+(igvz+0);
          aIGP_Hex[2] = (igvx+1)*(mdivy*mdivz)+(igvy+1)*mdivz+(igvz+0);
          aIGP_Hex[3] = (igvx+0)*(mdivy*mdivz)+(igvy+1)*mdivz+(igvz+0);
          aIGP_Hex[4] = (igvx+0)*(mdivy*mdivz)+(igvy+0)*mdivz+(igvz+1);
          aIGP_Hex[5] = (igvx+1)*(mdivy*mdivz)+(igvy+0)*mdivz+(igvz+1);
          aIGP_Hex[6] = (igvx+1)*(mdivy*mdivz)+(igvy+1)*mdivz+(igvz+1);
          aIGP_Hex[7] = (igvx+0)*(mdivy*mdivz)+(igvy+1)*mdivz+(igvz+1);
        }
        aHex.push_back(aIGP_Hex[0]);
        aHex.push_back(aIGP_Hex[1]);
        aHex.push_back(aIGP_Hex[2]);
        aHex.push_back(aIGP_Hex[3]);
        aHex.push_back(aIGP_Hex[4]);
        aHex.push_back(aIGP_Hex[5]);
        aHex.push_back(aIGP_Hex[6]);
        aHex.push_back(aIGP_Hex[7]);
      }
    }
  }
}



void dfm2::MeshTet3D_VoxelGrid
(std::vector<double>& aXYZ, std::vector<int>& aTet,
 int ndivx, int ndivy, int ndivz,
 int ioffx, int ioffy, int ioffz,
 const std::vector<int>& aIsVox)
{
  aTet.clear();
  aXYZ.clear();
  //////
  const int mdivx = ndivx+1;
  const int mdivy = ndivy+1;
  const int mdivz = ndivz+1;
  for(int igpx=0;igpx<mdivx;++igpx){
    for(int igpy=0;igpy<mdivy;++igpy){
      for(int igpz=0;igpz<mdivz;++igpz){
        aXYZ.push_back( igpx+ioffx );
        aXYZ.push_back( igpy+ioffy );
        aXYZ.push_back( igpz+ioffz );
      }
    }
  }
  //////
  assert( (int)aIsVox.size() == ndivx*ndivy*ndivz );
  for(int igvx=0;igvx<ndivx;++igvx){
    for(int igvy=0;igvy<ndivy;++igvy){
      for(int igvz=0;igvz<ndivz;++igvz){
        const int ivoxel = igvx*(ndivy*ndivz)+igvy*ndivz+igvz;
        assert( ivoxel < (int)aIsVox.size() );
        if( aIsVox[ivoxel] == 0 ){ continue; }
        /////
        int aIP[8] = {0,0,0,0, 0,0,0,0};
        {
          aIP[0] = (igvx+0)*(mdivy*mdivz)+(igvy+0)*mdivz+(igvz+0);
          aIP[1] = (igvx+1)*(mdivy*mdivz)+(igvy+0)*mdivz+(igvz+0);
          aIP[2] = (igvx+1)*(mdivy*mdivz)+(igvy+1)*mdivz+(igvz+0);
          aIP[3] = (igvx+0)*(mdivy*mdivz)+(igvy+1)*mdivz+(igvz+0);
          aIP[4] = (igvx+0)*(mdivy*mdivz)+(igvy+0)*mdivz+(igvz+1);
          aIP[5] = (igvx+1)*(mdivy*mdivz)+(igvy+0)*mdivz+(igvz+1);
          aIP[6] = (igvx+1)*(mdivy*mdivz)+(igvy+1)*mdivz+(igvz+1);
          aIP[7] = (igvx+0)*(mdivy*mdivz)+(igvy+1)*mdivz+(igvz+1);
        }
        aTet.push_back(aIP[0]);
        aTet.push_back(aIP[1]);
        aTet.push_back(aIP[2]);
        aTet.push_back(aIP[6]);
        ////
        aTet.push_back(aIP[0]);
        aTet.push_back(aIP[1]);
        aTet.push_back(aIP[6]);
        aTet.push_back(aIP[5]);
        ////
        aTet.push_back(aIP[0]);
        aTet.push_back(aIP[4]);
        aTet.push_back(aIP[5]);
        aTet.push_back(aIP[6]);
        ////
        aTet.push_back(aIP[0]);
        aTet.push_back(aIP[2]);
        aTet.push_back(aIP[3]);
        aTet.push_back(aIP[6]);
        ////
        aTet.push_back(aIP[0]);
        aTet.push_back(aIP[3]);
        aTet.push_back(aIP[7]);
        aTet.push_back(aIP[6]);
        ////
        aTet.push_back(aIP[0]);
        aTet.push_back(aIP[4]);
        aTet.push_back(aIP[6]);
        aTet.push_back(aIP[7]);
      }
    }
  }
}

int dfm2::Adj_Grid
(int igridvox, int iface,
 int ndivx, int ndivy, int ndivz)
{
  int ivx0 = igridvox/(ndivy*ndivz);
  int ivy0 = (igridvox-ivx0*(ndivy*ndivz))/ndivz;
  int ivz0 = igridvox-ivx0*(ndivy*ndivz)-ivy0*ndivz;
  if( iface == 0 ){ ivx0 -= 1; }
  if( iface == 1 ){ ivx0 += 1; }
  if( iface == 2 ){ ivy0 -= 1; }
  if( iface == 3 ){ ivy0 += 1; }
  if( iface == 4 ){ ivz0 -= 1; }
  if( iface == 5 ){ ivz0 += 1; }
  if( ivx0 < 0 || ivx0 >= ndivx ){ return -1; }
  if( ivy0 < 0 || ivy0 >= ndivy ){ return -1; }
  if( ivz0 < 0 || ivz0 >= ndivz ){ return -1; }
  int igv1 = ivx0*(ndivy*ndivz)+ivy0*ndivz+ivz0;
  assert( igv1 >= 0 && igv1 < ndivx*ndivy*ndivz );
  return igv1;
}

// ---------------------------------------------------------------------

void dfm2::Pick_CubeGrid
(int& icube_pic, int& iface_pic,
 const double src_pic_[3], const double dir_pic_[3],
 double elen,
 const double org_[3],
 const std::vector<CCubeGrid>& aCube)
{
  dfm2::CVec3d dir_pic(dir_pic_), org(org_), src_pic(src_pic_);
  // // -----------------------------------
  icube_pic = -1;
  double depth_min = 0;
  for(std::size_t ivox=0;ivox<aCube.size();++ivox){
    if( !aCube[ivox].is_active ) continue;
    int ih = aCube[ivox].ivx;
    int jh = aCube[ivox].ivy;
    int kh = aCube[ivox].ivz;
    dfm2::CVec3d cnt =  org + elen*dfm2::CVec3d(ih+0.5,jh+0.5,kh+0.5);
    {
      dfm2::CVec3d q = nearest_Line_Point(cnt, src_pic, dir_pic);
      if( (q-cnt).Length() > elen  ) continue;
    }
    dfm2::CVec3d aP[8] = {
      org + elen*dfm2::CVec3d(ih+0,jh+0,kh+0),
      org + elen*dfm2::CVec3d(ih+1,jh+0,kh+0),
      org + elen*dfm2::CVec3d(ih+0,jh+1,kh+0),
      org + elen*dfm2::CVec3d(ih+1,jh+1,kh+0),
      org + elen*dfm2::CVec3d(ih+0,jh+0,kh+1),
      org + elen*dfm2::CVec3d(ih+1,jh+0,kh+1),
      org + elen*dfm2::CVec3d(ih+0,jh+1,kh+1),
      org + elen*dfm2::CVec3d(ih+1,jh+1,kh+1) };
    for(int iface=0;iface<6;++iface){
      const dfm2::CVec3d& n = normalHexFace[iface];
      const dfm2::CVec3d& p0 = aP[noelElemFace_Vox[iface][0]];
      const dfm2::CVec3d& p1 = aP[noelElemFace_Vox[iface][1]];
      //      const CVector3& p2 = aP[noelHexFace[iface][2]];
      const dfm2::CVec3d& p3 = aP[noelElemFace_Vox[iface][3]];
      const dfm2::CVec3d pi = intersection_Plane_Line(p0,n, src_pic,dir_pic);
      const double r0 = (pi-p0)*(p1-p0)/(elen*elen);
      const double r1 = (pi-p0)*(p3-p0)/(elen*elen);
      if( r0>0 && r0<1 && r1>0 && r1< 1 ){
        double depth = -(pi-src_pic)*dir_pic/dir_pic.DLength();
        if( icube_pic == -1 || depth < depth_min ){
          depth_min = depth;
          icube_pic = ivox;
          iface_pic = iface;
        }
      }
    }
  }
}

void dfm2::Adj_CubeGrid
(int& ivx, int& ivy, int& ivz,
 int icube, int iface,
 std::vector<CCubeGrid>& aCube)
{
  ivx = aCube[icube].ivx;
  ivy = aCube[icube].ivy;
  ivz = aCube[icube].ivz;
  if( iface == 0 ){ ivx -= 1; }
  if( iface == 1 ){ ivx += 1; }
  if( iface == 2 ){ ivy -= 1; }
  if( iface == 3 ){ ivy += 1; }
  if( iface == 4 ){ ivz -= 1; }
  if( iface == 5 ){ ivz += 1; }
}

void dfm2::Add_CubeGrid
(std::vector<CCubeGrid>& aCube,
 int ivx1, int ivy1, int ivz1)
{
  for(auto & ic : aCube){
    if( ic.ivx == ivx1 && ic.ivy == ivy1 && ic.ivz == ivz1 ){
      if( ic.is_active ){
        return;
      }
      else{
        ic.is_active = true;
        return;
      }
    }
  }
  {
    CCubeGrid v(ivx1,ivy1,ivz1);
    aCube.push_back(v);
  }
}

void dfm2::Del_CubeGrid
(std::vector<CCubeGrid>& aCube,
 int i1, int j1, int k1)
{
  for(auto & ic : aCube){
    if( ic.ivx == i1 && ic.ivy == j1 && ic.ivz == k1 ){
      if( ic.is_active ){
        ic.is_active = false;
        return;
      }
      else{
        return;
      }
    }
  }
}


void dfm2::AABB_CubeGrid
(int aabb[6],
 const std::vector<CCubeGrid>& aCube)
{
  if( aCube.empty() ){
    aabb[0] = +1; aabb[1] = -1;
    aabb[2] = +1; aabb[3] = -1;
    aabb[4] = +1; aabb[5] = -1;
    return;
  }
  aabb[0] = aCube[0].ivx;  aabb[1] = aabb[0]+1;
  aabb[2] = aCube[0].ivy;  aabb[3] = aabb[0]+1;
  aabb[4] = aCube[0].ivz;  aabb[5] = aabb[0]+1;

  for(std::size_t ic=1;ic<aCube.size();++ic){
    if( aCube[ic].ivx+0 < aabb[0] ){ aabb[0] = aCube[ic].ivx+0; }
    if( aCube[ic].ivx+1 > aabb[1] ){ aabb[1] = aCube[ic].ivx+1; }
    if( aCube[ic].ivy+0 < aabb[2] ){ aabb[2] = aCube[ic].ivy+0; }
    if( aCube[ic].ivy+1 > aabb[3] ){ aabb[3] = aCube[ic].ivy+1; }
    if( aCube[ic].ivz+0 < aabb[4] ){ aabb[4] = aCube[ic].ivz+0; }
    if( aCube[ic].ivz+1 > aabb[5] ){ aabb[5] = aCube[ic].ivz+1; }
  }
}

// --------------------------------------------------------------------------

