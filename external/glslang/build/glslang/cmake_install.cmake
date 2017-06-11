# Install script for directory: /home/luizorv/Downloads/VulkanSamples/external/glslang/glslang

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/luizorv/Downloads/VulkanSamples/external/glslang/build/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
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

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/luizorv/Downloads/VulkanSamples/external/glslang/build/glslang/libglslang.a")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/glslang/Public" TYPE FILE FILES "/home/luizorv/Downloads/VulkanSamples/external/glslang/glslang/Public/ShaderLang.h")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/glslang/Include" TYPE FILE FILES "/home/luizorv/Downloads/VulkanSamples/external/glslang/glslang/Include/arrays.h")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/glslang/Include" TYPE FILE FILES "/home/luizorv/Downloads/VulkanSamples/external/glslang/glslang/Include/BaseTypes.h")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/glslang/Include" TYPE FILE FILES "/home/luizorv/Downloads/VulkanSamples/external/glslang/glslang/Include/Common.h")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/glslang/Include" TYPE FILE FILES "/home/luizorv/Downloads/VulkanSamples/external/glslang/glslang/Include/ConstantUnion.h")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/glslang/Include" TYPE FILE FILES "/home/luizorv/Downloads/VulkanSamples/external/glslang/glslang/Include/InfoSink.h")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/glslang/Include" TYPE FILE FILES "/home/luizorv/Downloads/VulkanSamples/external/glslang/glslang/Include/InitializeGlobals.h")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/glslang/Include" TYPE FILE FILES "/home/luizorv/Downloads/VulkanSamples/external/glslang/glslang/Include/intermediate.h")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/glslang/Include" TYPE FILE FILES "/home/luizorv/Downloads/VulkanSamples/external/glslang/glslang/Include/PoolAlloc.h")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/glslang/Include" TYPE FILE FILES "/home/luizorv/Downloads/VulkanSamples/external/glslang/glslang/Include/ResourceLimits.h")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/glslang/Include" TYPE FILE FILES "/home/luizorv/Downloads/VulkanSamples/external/glslang/glslang/Include/revision.h")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/glslang/Include" TYPE FILE FILES "/home/luizorv/Downloads/VulkanSamples/external/glslang/glslang/Include/ShHandle.h")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/glslang/Include" TYPE FILE FILES "/home/luizorv/Downloads/VulkanSamples/external/glslang/glslang/Include/Types.h")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/glslang/MachineIndependent" TYPE FILE FILES "/home/luizorv/Downloads/VulkanSamples/external/glslang/glslang/MachineIndependent/glslang_tab.cpp.h")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/glslang/MachineIndependent" TYPE FILE FILES "/home/luizorv/Downloads/VulkanSamples/external/glslang/glslang/MachineIndependent/gl_types.h")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/glslang/MachineIndependent" TYPE FILE FILES "/home/luizorv/Downloads/VulkanSamples/external/glslang/glslang/MachineIndependent/Initialize.h")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/glslang/MachineIndependent" TYPE FILE FILES "/home/luizorv/Downloads/VulkanSamples/external/glslang/glslang/MachineIndependent/iomapper.h")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/glslang/MachineIndependent" TYPE FILE FILES "/home/luizorv/Downloads/VulkanSamples/external/glslang/glslang/MachineIndependent/LiveTraverser.h")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/glslang/MachineIndependent" TYPE FILE FILES "/home/luizorv/Downloads/VulkanSamples/external/glslang/glslang/MachineIndependent/localintermediate.h")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/glslang/MachineIndependent" TYPE FILE FILES "/home/luizorv/Downloads/VulkanSamples/external/glslang/glslang/MachineIndependent/ParseHelper.h")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/glslang/MachineIndependent" TYPE FILE FILES "/home/luizorv/Downloads/VulkanSamples/external/glslang/glslang/MachineIndependent/reflection.h")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/glslang/MachineIndependent" TYPE FILE FILES "/home/luizorv/Downloads/VulkanSamples/external/glslang/glslang/MachineIndependent/RemoveTree.h")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/glslang/MachineIndependent" TYPE FILE FILES "/home/luizorv/Downloads/VulkanSamples/external/glslang/glslang/MachineIndependent/Scan.h")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/glslang/MachineIndependent" TYPE FILE FILES "/home/luizorv/Downloads/VulkanSamples/external/glslang/glslang/MachineIndependent/ScanContext.h")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/glslang/MachineIndependent" TYPE FILE FILES "/home/luizorv/Downloads/VulkanSamples/external/glslang/glslang/MachineIndependent/SymbolTable.h")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/glslang/MachineIndependent" TYPE FILE FILES "/home/luizorv/Downloads/VulkanSamples/external/glslang/glslang/MachineIndependent/Versions.h")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/glslang/MachineIndependent" TYPE FILE FILES "/home/luizorv/Downloads/VulkanSamples/external/glslang/glslang/MachineIndependent/parseVersions.h")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/glslang/MachineIndependent" TYPE FILE FILES "/home/luizorv/Downloads/VulkanSamples/external/glslang/glslang/MachineIndependent/propagateNoContraction.h")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/glslang/MachineIndependent/preprocessor" TYPE FILE FILES "/home/luizorv/Downloads/VulkanSamples/external/glslang/glslang/MachineIndependent/preprocessor/PpContext.h")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/glslang/MachineIndependent/preprocessor" TYPE FILE FILES "/home/luizorv/Downloads/VulkanSamples/external/glslang/glslang/MachineIndependent/preprocessor/PpTokens.h")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/luizorv/Downloads/VulkanSamples/external/glslang/build/glslang/OSDependent/Unix/cmake_install.cmake")

endif()
