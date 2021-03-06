cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_STANDARD 11)
if(MSVC)
  # GTest is static compiled by default
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")  
  set(CMAKE_CXX_FLAGS "/wd4267")
endif()

project(testsDelFEM2)
set(MY_BINARY_NAME runUnitTests)

add_definitions(-DPATH_INPUT_DIR="${PROJECT_SOURCE_DIR}/../test_inputs")

set(DELFEM2_INCLUDE_DIR "../include")
set(DELFEM2_INC         "../include/delfem2")
set(3RD_PARTY           "../3rd_party")

get_filename_component(GTEST_DIR ${3RD_PARTY}/googletest ABSOLUTE)

enable_testing()

include_directories(
  ${GTEST_DIR}/googletest/include
  ${DELFEM2_INCLUDE_DIR}
  ${3RD_PARTY}
)

# Add test cpp file
add_executable(${MY_BINARY_NAME}
  ${DELFEM2_INC}/vec3.h                 ${DELFEM2_INC}/vec3.cpp
  ${DELFEM2_INC}/vec2.h                 ${DELFEM2_INC}/vec2.cpp
  ${DELFEM2_INC}/mat3.h                 ${DELFEM2_INC}/mat3.cpp
  ${DELFEM2_INC}/quat.h                 ${DELFEM2_INC}/quat.cpp
  ${DELFEM2_INC}/funcs.h                ${DELFEM2_INC}/funcs.cpp
  ${DELFEM2_INC}/specialfuncs.h         ${DELFEM2_INC}/specialfuncs.cpp
  ${DELFEM2_INC}/mshmisc.h              ${DELFEM2_INC}/mshmisc.cpp
  ${DELFEM2_INC}/mshtopo.h              ${DELFEM2_INC}/mshtopo.cpp
  ${DELFEM2_INC}/mshio.h                ${DELFEM2_INC}/mshio.cpp
  ${DELFEM2_INC}/voxel.h                ${DELFEM2_INC}/voxel.cpp
  ${DELFEM2_INC}/evalmathexp.h          ${DELFEM2_INC}/evalmathexp.cpp
  ${DELFEM2_INC}/lp.h                   ${DELFEM2_INC}/lp.cpp
  ${DELFEM2_INC}/bvh.h                  ${DELFEM2_INC}/bvh.cpp
  ${DELFEM2_INC}/primitive.h            ${DELFEM2_INC}/primitive.cpp
  ${DELFEM2_INC}/slice.h                ${DELFEM2_INC}/slice.cpp
  ${DELFEM2_INC}/emat.h                 ${DELFEM2_INC}/emat.cpp
  ${DELFEM2_INC}/dtri.h                 ${DELFEM2_INC}/dtri.cpp
  ${DELFEM2_INC}/mats.h                 ${DELFEM2_INC}/mats.cpp
  ${DELFEM2_INC}/vecxitrsol.h           ${DELFEM2_INC}/vecxitrsol.cpp
  ${DELFEM2_INC}/bv.h
  
  ${DELFEM2_INC}/v23m3q.h            ${DELFEM2_INC}/v23m3q.cpp
  ${DELFEM2_INC}/fem_emats.h            ${DELFEM2_INC}/fem_emats.cpp
  ${DELFEM2_INC}/ilu_mats.h             ${DELFEM2_INC}/ilu_mats.cpp
  ${DELFEM2_INC}/dtri_v2.h              ${DELFEM2_INC}/dtri_v2.cpp
  ${DELFEM2_INC}/objfunc_v23.h          ${DELFEM2_INC}/objfunc_v23.cpp
  ${DELFEM2_INC}/srchuni_v3.h           ${DELFEM2_INC}/srchuni_v3.cpp
  ${DELFEM2_INC}/srchbi_v3bvh.h
  ${DELFEM2_INC}/srch_v3bvhmshtopo.h

  test_bvh.cpp
  test_lp.cpp
  test_gltf.cpp
  test_fem.cpp
  main.cpp  
)

if(MSVC)
  if(CMAKE_CL_64)
    set(GTEST_MAIN_LIBRARY ${GTEST_DIR}/buildVS64/lib/Release/gtest_main.lib)
    set(GTEST_LIBRARY      ${GTEST_DIR}/buildVS64/lib/Release/gtest.lib)
  else()
    set(GTEST_MAIN_LIBRARY ${GTEST_DIR}/buildVS32/lib/Release/gtest_main.lib)
    set(GTEST_MAIN_LIBRARY ${GTEST_DIR}/buildVS32/lib/Release/gtest.lib)
  endif()
  target_link_libraries(${MY_BINARY_NAME}
    ${GTEST_LIBRARY}
    ${GTEST_MAIN_LIBRARY})  
else()
  target_link_libraries(${MY_BINARY_NAME}
      ${GTEST_DIR}/lib/libgtest.a
      ${GTEST_DIR}/lib/libgtest_main.a
      -pthread)
endif()    

add_test(
  NAME ${MY_BINARY_NAME}
  COMMAND ${MY_BINARY_NAME}
)
