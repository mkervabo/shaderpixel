# Install script for directory: /Users/gper/workspace/ShaderPixelNew/libs/assimp/code

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/Library/Developer/CommandLineTools/usr/bin/objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/bin/libassimp.5.0.1.dylib"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/bin/libassimp.5.dylib"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.5.0.1.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.5.dylib"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/Library/Developer/CommandLineTools/usr/bin/strip" -x "${file}")
      endif()
    endif()
  endforeach()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/Users/gper/workspace/ShaderPixelNew/libs/assimp/bin/libassimp.dylib")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.dylib" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.dylib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Library/Developer/CommandLineTools/usr/bin/strip" -x "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libassimp.dylib")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xassimp-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp" TYPE FILE FILES
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/anim.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/aabb.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/ai_assert.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/camera.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/color4.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/color4.inl"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/config.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/ColladaMetaData.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/commonMetaData.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/defs.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/Defines.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/cfileio.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/light.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/material.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/material.inl"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/matrix3x3.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/matrix3x3.inl"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/matrix4x4.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/matrix4x4.inl"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/mesh.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/pbrmaterial.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/postprocess.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/quaternion.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/quaternion.inl"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/scene.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/metadata.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/texture.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/types.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/vector2.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/vector2.inl"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/vector3.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/vector3.inl"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/version.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/cimport.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/importerdesc.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/Importer.hpp"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/DefaultLogger.hpp"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/ProgressHandler.hpp"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/IOStream.hpp"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/IOSystem.hpp"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/Logger.hpp"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/LogStream.hpp"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/NullLogger.hpp"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/cexport.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/Exporter.hpp"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/DefaultIOStream.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/DefaultIOSystem.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/ZipArchiveIOSystem.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/SceneCombiner.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/fast_atof.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/qnan.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/BaseImporter.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/Hash.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/MemoryIOWrapper.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/ParsingUtils.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/StreamReader.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/StreamWriter.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/StringComparison.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/StringUtils.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/SGSpatialSort.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/GenericProperty.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/SpatialSort.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/SkeletonMeshBuilder.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/SmallVector.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/SmoothingGroups.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/SmoothingGroups.inl"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/StandardShapes.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/RemoveComments.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/Subdivision.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/Vertex.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/LineSplitter.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/TinyFormatter.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/Profiler.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/LogAux.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/Bitmap.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/XMLTools.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/IOStreamBuffer.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/CreateAnimMesh.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/XmlParser.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/BlobIOSystem.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/MathFunctions.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/Exceptional.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/ByteSwapper.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xassimp-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp/Compiler" TYPE FILE FILES
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/Compiler/pushpack1.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/Compiler/poppack1.h"
    "/Users/gper/workspace/ShaderPixelNew/libs/assimp/code/../include/assimp/Compiler/pstdint.h"
    )
endif()

