# Aura's CMakeLists.txt
cmake_minimum_required(VERSION 2.6)

# Tools
if(BUILD_TOOLS)
subdirs(Tools)
endif()

# Engine
if(BUILD_ENGINE)
subdirs(source)
endif()
