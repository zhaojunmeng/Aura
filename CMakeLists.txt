# Aura's CMakeLists.txt
cmake_minimum_required(VERSION 2.6)

project(AURA)
set(AURA 1.0)

# Dependencies
subdirs(Dependencies)

# Aura :)
subdirs(Aura)
