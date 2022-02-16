#
# This file is part of the µOS++ distribution.
#   (https://github.com/micro-os-plus)
# Copyright (c) 2021 Liviu Ionescu
#
# Permission to use, copy, modify, and/or distribute this software
# for any purpose is hereby granted, under the terms of the MIT license.
#
# If a copy of the license was not distributed with this file, it can
# be obtained from https://opensource.org/licenses/MIT/.
#
# -----------------------------------------------------------------------------

# https://cmake.org/cmake/help/v3.20/
# https://cmake.org/cmake/help/v3.20/manual/cmake-packages.7.html#package-configuration-file
cmake_minimum_required(VERSION 3.20)

message(STATUS "Processing xPack ${PACKAGE_JSON_NAME}@${PACKAGE_JSON_VERSION} rtos-port...")

# -----------------------------------------------------------------------------
# Dependencies.

# find_package(micro-os-plus-rtos REQUIRED)
# find_package(micro-os-plus-diag-trace REQUIRED)

# -----------------------------------------------------------------------------
## The project library definitions ##

# https://cmake.org/cmake/help/v3.20/command/add_library.html?highlight=interface#normal-libraries
# PRIVATE: build definitions, used internally
# INTERFACE: usage definitions, passed up to targets linking to it
# PUBLIC: both

add_library(micro-os-plus-rtos-synthetic-posix-interface INTERFACE EXCLUDE_FROM_ALL)

# -----------------------------------------------------------------------------
# Target settings.


target_sources(micro-os-plus-rtos-synthetic-posix-interface INTERFACE
  "src/port.cpp"
)

target_include_directories(micro-os-plus-rtos-synthetic-posix-interface INTERFACE
  "include"
)

target_compile_definitions(micro-os-plus-rtos-synthetic-posix-interface INTERFACE
  "_XOPEN_SOURCE=700L"
)

target_link_libraries(micro-os-plus-rtos-synthetic-posix-interface INTERFACE
  # ???
  micro-os-plus::diag-trace
)

# -----------------------------------------------------------------------------
# Aliases.

add_library(micro-os-plus::rtos-synthetic-posix ALIAS micro-os-plus-rtos-synthetic-posix-interface)
# message(STATUS "=> micro-os-plus::rtos-synthetic-posix")
add_library(micro-os-plus::rtos-port ALIAS micro-os-plus-rtos-synthetic-posix-interface)
message(STATUS "=> micro-os-plus::rtos-port")

# -----------------------------------------------------------------------------
