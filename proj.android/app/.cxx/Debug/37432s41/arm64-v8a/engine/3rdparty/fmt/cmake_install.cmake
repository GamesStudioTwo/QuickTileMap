# Install script for directory: C:/Users/Admin/Documents/Cocos/axmol-dev/3rdparty/fmt

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/QuickTileMap")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
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

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "C:/Users/Admin/AppData/Local/Android/Sdk/ndk/23.2.8568313/toolchains/llvm/prebuilt/windows-x86_64/bin/llvm-objdump.exe")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Admin/Documents/QuickTileMap/proj.android/app/.cxx/Debug/37432s41/arm64-v8a/lib/libfmtd.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/fmt" TYPE FILE FILES
    "C:/Users/Admin/Documents/Cocos/axmol-dev/3rdparty/fmt/include/fmt/args.h"
    "C:/Users/Admin/Documents/Cocos/axmol-dev/3rdparty/fmt/include/fmt/chrono.h"
    "C:/Users/Admin/Documents/Cocos/axmol-dev/3rdparty/fmt/include/fmt/color.h"
    "C:/Users/Admin/Documents/Cocos/axmol-dev/3rdparty/fmt/include/fmt/compile.h"
    "C:/Users/Admin/Documents/Cocos/axmol-dev/3rdparty/fmt/include/fmt/core.h"
    "C:/Users/Admin/Documents/Cocos/axmol-dev/3rdparty/fmt/include/fmt/format.h"
    "C:/Users/Admin/Documents/Cocos/axmol-dev/3rdparty/fmt/include/fmt/format-inl.h"
    "C:/Users/Admin/Documents/Cocos/axmol-dev/3rdparty/fmt/include/fmt/os.h"
    "C:/Users/Admin/Documents/Cocos/axmol-dev/3rdparty/fmt/include/fmt/ostream.h"
    "C:/Users/Admin/Documents/Cocos/axmol-dev/3rdparty/fmt/include/fmt/printf.h"
    "C:/Users/Admin/Documents/Cocos/axmol-dev/3rdparty/fmt/include/fmt/ranges.h"
    "C:/Users/Admin/Documents/Cocos/axmol-dev/3rdparty/fmt/include/fmt/std.h"
    "C:/Users/Admin/Documents/Cocos/axmol-dev/3rdparty/fmt/include/fmt/xchar.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/fmt" TYPE FILE FILES
    "C:/Users/Admin/Documents/QuickTileMap/proj.android/app/.cxx/Debug/37432s41/arm64-v8a/engine/3rdparty/fmt/fmt-config.cmake"
    "C:/Users/Admin/Documents/QuickTileMap/proj.android/app/.cxx/Debug/37432s41/arm64-v8a/engine/3rdparty/fmt/fmt-config-version.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/fmt/fmt-targets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/fmt/fmt-targets.cmake"
         "C:/Users/Admin/Documents/QuickTileMap/proj.android/app/.cxx/Debug/37432s41/arm64-v8a/engine/3rdparty/fmt/CMakeFiles/Export/lib/cmake/fmt/fmt-targets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/fmt/fmt-targets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/fmt/fmt-targets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/fmt" TYPE FILE FILES "C:/Users/Admin/Documents/QuickTileMap/proj.android/app/.cxx/Debug/37432s41/arm64-v8a/engine/3rdparty/fmt/CMakeFiles/Export/lib/cmake/fmt/fmt-targets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/fmt" TYPE FILE FILES "C:/Users/Admin/Documents/QuickTileMap/proj.android/app/.cxx/Debug/37432s41/arm64-v8a/engine/3rdparty/fmt/CMakeFiles/Export/lib/cmake/fmt/fmt-targets-debug.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Admin/Documents/QuickTileMap/proj.android/app/.cxx/Debug/37432s41/arm64-v8a/engine/3rdparty/fmt/fmt.pc")
endif()

