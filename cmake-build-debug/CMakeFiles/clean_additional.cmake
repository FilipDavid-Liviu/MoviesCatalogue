# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\MoviesCatalogue_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\MoviesCatalogue_autogen.dir\\ParseCache.txt"
  "MoviesCatalogue_autogen"
  )
endif()
