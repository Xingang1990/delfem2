cmake_minimum_required(VERSION 2.8)

project(examples_glut)

# opengl
add_subdirectory(00_viewer3d)
add_subdirectory(glbuffer)
add_subdirectory(shader)

# geometry
add_subdirectory(edit_cubes)
add_subdirectory(transform_handler)

# fem
add_subdirectory(rigidbody3d_rotation)
add_subdirectory(fem3d)
add_subdirectory(femcloth_selfcollision)

# pbd
add_subdirectory(pbdcloth_cad)
add_subdirectory(pbdcloth_cad_gltf)
