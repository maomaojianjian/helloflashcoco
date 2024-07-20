cmake_minimum_required(VERSION 3.10)
project(MyNCCLDemo VERSION 1.0)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 包含头文件目录
include_directories(include /usr/local/openmpi/include)

# 查找MPI包
find_package(MPI REQUIRED)

# 定义源文件搜索路径
set(SOURCE_DIR "src")

# 查找所有 .cc 文件
file(GLOB_RECURSE SOURCE_FILES "${SOURCE_DIR}/*.cc")

# 添加特定的文件
set(SOURCE_FILES ${SOURCE_FILES} "demo.cc")

# 创建可执行文件
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# 链接MPI库
target_link_libraries(${PROJECT_NAME} ${MPI_CXX_LIBRARIES})

# 设置编译选项
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)

# 如果需要安装可执行文件到特定目录，可以取消下面两行的注释
# set(CMAKE_INSTALL_PREFIX /usr/local)
# install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)