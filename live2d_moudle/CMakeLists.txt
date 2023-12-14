# Make 最低版本要求 
cmake_minimum_required(VERSION 3.16)

# 变量设置 
set(APP_NAME live2d_moudle)
set(ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set(OUT_PATH ${CMAKE_CURRENT_BINARY_DIR})
set(RES_PATH ${ROOT_PATH}/Resources)
set(CORE_PATH ${ROOT_PATH}/third/live2d_core)
set(FRAMEWORK_PATH ${ROOT_PATH}/Framework)
set(THIRD_PARTY_PATH ${ROOT_PATH}/third)
set(STB_PATH ${THIRD_PARTY_PATH}/stb)
set(GLEW_PATH ${THIRD_PARTY_PATH}/glew)
set(GLFW_PATH ${THIRD_PARTY_PATH}/glfw)

# 设置项目名
project(${APP_NAME})

# 设置VS启动项目
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT ${APP_NAME})

# 设置VS输出路径
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUT_PATH}/Output/${APP_NAME})

# 设置配置类型为 Debug 和 Release
set(CMAKE_CONFIGURATION_TYPES Debug Release
  CACHE STRING "Configurations" FORCE
)

# 禁止生成 ZERO_CHECK 项目，加快构建时间
set(CMAKE_SUPPRESS_REGENERATION ON)

# 禁止生成 GLEW 和 GLFW 的相关文档及测试，加快构建时间
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(BUILD_UTILS OFF CACHE BOOL "" FORCE)

# 设置编译相关
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 判断连接器标志，确定架构
if(CMAKE_EXE_LINKER_FLAGS STREQUAL "/machine:x64")
  set(ARCH x86_64)
elseif(CMAKE_EXE_LINKER_FLAGS STREQUAL "/machine:X86")
  set(ARCH x86)
else()
  message(FATAL_ERROR "[${APP_NAME}] Invalid linker flag ${CMAKE_EXE_LINKER_FLAGS}.")
endif()

# 判断 VS 版本，确定编译器
if(MSVC_VERSION MATCHES 1800)
  # Visual Studio 2013
  set(COMPILER 120)
elseif(MSVC_VERSION MATCHES 1900)
  # Visual Studio 2015
  set(COMPILER 140)
elseif(MSVC_VERSION GREATER_EQUAL 1910 AND MSVC_VERSION LESS 1920)
  # Visual Studio 2017
  set(COMPILER 141)
elseif(MSVC_VERSION GREATER_EQUAL 1920 AND MSVC_VERSION LESS 1930)
  # Visual Studio 2019
  set(COMPILER 142)
elseif(MSVC_VERSION GREATER_EQUAL 1930 AND MSVC_VERSION LESS 1940)
  # Visual Studio 2022
  set(COMPILER 143)
elseif(MSVC)
  message(FATAL_ERROR "[${APP_NAME}] Unsupported Visual C++ compiler used.")
else()
  message(FATAL_ERROR "[${APP_NAME}] Unsupported compiler used.")
endif()

# 确定 CRT
set(CRT MT)

# 外部添加 CubismCore 库
add_library(Live2DCubismCore STATIC IMPORTED)
set(CORE_LIB_SUFFIX ${CORE_PATH}/lib/windows/${ARCH}/${COMPILER})
set_target_properties(Live2DCubismCore
  PROPERTIES
    IMPORTED_LOCATION_DEBUG
      ${CORE_LIB_SUFFIX}/Live2DCubismCore_${CRT}d.lib
    IMPORTED_LOCATION_RELEASE
      ${CORE_LIB_SUFFIX}/Live2DCubismCore_${CRT}.lib
    INTERFACE_INCLUDE_DIRECTORIES ${CORE_PATH}/include
)

# 添加 GLEW, GLFW 库
add_subdirectory(${GLEW_PATH}/build/cmake ${OUT_PATH}/glew)
add_subdirectory(${GLFW_PATH} ${OUT_PATH}/glfw)

# 变量设置
set(FRAMEWORK_SOURCE OpenGL)
# 添加 Framework 目录
add_subdirectory(${FRAMEWORK_PATH} ${OUTPUT_PATH}/Framework)
# 设置 Framework 的编译选项
target_compile_definitions(Framework PUBLIC CSM_TARGET_WIN_GL)
# 设置 Framework 的引用目录
target_include_directories(Framework PUBLIC ${GLEW_PATH}/include)
# 设置 Framework 的链接库
target_link_libraries(Framework Live2DCubismCore glew_s)

# 查找 OpenGL 库
find_package(OpenGL REQUIRED)

# 添加可执行文件
add_executable(${APP_NAME})

# 添加 源文件 目录
add_subdirectory(src)

# 添加 头文件 目录
include_directories(inc)

# 添加 源文件 链接库
target_link_libraries(${APP_NAME}
  Framework
  glfw
  ${OPENGL_LIBRARIES}
  # Solve the MSVCRT confliction.
  debug -NODEFAULTLIB:libcmtd.lib
  optimized -NODEFAULTLIB:libcmt.lib
)

# 添加引用目录
target_include_directories(${APP_NAME} PRIVATE ${STB_PATH})

# 设置编译选项
target_compile_options(${APP_NAME} PRIVATE /MP)

# 将 源文件 复制到新添的目录
add_custom_command(
  TARGET ${APP_NAME}
  POST_BUILD
  COMMAND
    ${CMAKE_COMMAND} -E
      copy_directory ${RES_PATH} $<TARGET_FILE_DIR:${APP_NAME}>/Resources
)

# 设置项目环境
set_target_properties(${APP_NAME} PROPERTIES
  VS_DEBUGGER_WORKING_DIRECTORY
    ${OUT_PATH}/OUTPUT/${APP_NAME}/${CMAKE_CFG_INTDIR}
)