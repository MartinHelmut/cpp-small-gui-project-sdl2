# https://github.com/lefticus/cppbestpractices/blob/master/02-Use_the_Tools_Available.md

option(WARNINGS_AS_ERRORS "Treat compiler warnings as errors" TRUE)
message(STATUS "Treat compiler warnings as errors")

set(MSVC_WARNINGS
  /W4 # Baseline reasonable warnings
  /w14242 # 'identifier': conversion from 'type1' to 'type1', possible loss
  # of data
  /w14254 # 'operator': conversion from 'type1:field_bits' to
  # 'type2:field_bits', possible loss of data
  /w14263 # 'function': member function does not override any base class
  # virtual member function
  /w14265 # 'classname': class has virtual functions, but destructor is not
  # virtual instances of this class may not be destructed correctly
  /w14287 # 'operator': unsigned/negative constant mismatch
  /we4289 # nonstandard extension used: 'variable': loop control variable
  # declared in the for-loop is used outside the for-loop scope
  /w14296 # 'operator': expression is always 'boolean_value'
  /w14311 # 'variable': pointer truncation from 'type1' to 'type2'
  /w14545 # expression before comma evaluates to a function which is missing
  # an argument list
  /w14546 # function call before comma missing argument list
  /w14547 # 'operator': operator before comma has no effect; expected
  # operator with side-effect
  /w14549 # 'operator': operator before comma has no effect; did you intend
  # 'operator'?
  /w14555 # expression has no effect; expected expression with side- effect
  /w14619 # pragma warning: there is no warning number 'number'
  /w14640 # Enable warning on thread un-safe static member initialization
  /w14826 # Conversion from 'type1' to 'type_2' is sign-extended. This may
  # cause unexpected runtime behavior.
  /w14905 # wide string literal cast to 'LPSTR'
  /w14906 # string literal cast to 'LPWSTR'
  /w14928 # illegal copy-initialization; more than one user-defined
  # conversion has been implicitly applied
  /permissive- # standards conformance mode for MSVC compiler.
  )

set(CLANG_WARNINGS
  -Wall
  -Wextra # reasonable and standard
  -Wshadow # warn the user if a variable declaration shadows one from a
  # parent context
  -Wnon-virtual-dtor # warn the user if a class with virtual functions has a
  # non-virtual destructor. This helps catch hard to
  # track down memory errors
  -Wcast-align # warn for potential performance problem casts
  -Wunused # warn on anything being unused
  -Woverloaded-virtual # warn if you overload (not override) a virtual
  # function
  -Wpedantic # warn if non-standard C++ is used
  -Wconversion # warn on type conversions that may lose data
  -Wsign-conversion # warn on sign conversions
  -Wnull-dereference # warn if a null dereference is detected
  -Wformat=2 # warn on security issues around functions that format output
  # (ie printf)
  )

if (WARNINGS_AS_ERRORS)
  set(CLANG_WARNINGS ${CLANG_WARNINGS} -Werror)
  set(MSVC_WARNINGS ${MSVC_WARNINGS} /WX)
endif ()

set(GCC_WARNINGS
  ${CLANG_WARNINGS}
  -Wmisleading-indentation # warn if indentation implies blocks where blocks
  )

if (MSVC)
  set(PROJECT_WARNINGS ${MSVC_WARNINGS})
elseif (CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
  set(PROJECT_WARNINGS ${CLANG_WARNINGS})
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(PROJECT_WARNINGS ${GCC_WARNINGS})
else ()
  message(AUTHOR_WARNING "No compiler warnings set for '${CMAKE_CXX_COMPILER_ID}' compiler.")
endif ()

# Link this "library" to use the warnings specified in CompilerWarnings.cmake.
add_library(project_warnings INTERFACE)
target_compile_options(project_warnings INTERFACE ${PROJECT_WARNINGS})
