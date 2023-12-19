cmake_minimum_required(VERSION 3.16)

# 变量设置
set(APP_NAME Schedule)
set(ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set(OUT_PATH ${CMAKE_CURRENT_BINARY_DIR})

# 项目名
project(${APP_NAME})

# 设置 VS 启动项目
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT ${APP_NAME})

# 设置VS输出路径
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUT_PATH}/Output/${APP_NAME})

# 设置配置类型为 Debug 和 Release
set(CMAKE_CONFIGURATION_TYPES Debug Release
  CACHE STRING "Configurations" FORCE
)

# 禁止生成 ZERO_CHECK 项目，加快构建时间
set(CMAKE_SUPPRESS_REGENERATION ON)

# 设置编译相关
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 添加可执行文件
add_executable(${APP_NAME})

# 添加 源文件 目录
add_subdirectory(src)

# 添加 头文件 目录
target_include_directories(${APP_NAME} PUBLIC inc)

# 设置项目环境
set_target_properties(${APP_NAME} PROPERTIES
  VS_DEBUGGER_WORKING_DIRECTORY
    ${OUT_PATH}/OUTPUT/${APP_NAME}/${CMAKE_CFG_INTDIR}
)
