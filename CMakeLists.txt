cmake_minimum_required(VERSION 3.22)

include(cmake/UniversalAppleBuild.cmake)

project(
  SmallSDL2App
  DESCRIPTION "Small GUI app with SDL2."
  VERSION 1.0.0
  LANGUAGES CXX)

set(PROJECT_COMPANY_NAME "My Company")
set(PROJECT_COMPANY_NAMESPACE "com.mycompany")  # Reverse domain name notation

include(GNUInstallDirs)

include(cmake/StandardProjectSettings.cmake)
include(cmake/CompilerWarnings.cmake)
include(cmake/Dependencies.cmake)

add_subdirectory(packaging)
add_subdirectory(src)
