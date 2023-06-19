# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\CyclingSystem_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\CyclingSystem_autogen.dir\\ParseCache.txt"
  "CyclingSystem_autogen"
  )
endif()
