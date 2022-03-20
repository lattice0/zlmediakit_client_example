set (CMAKE_CXX_STANDARD 17)

add_subdirectory(ZLMediaKit)

add_executable(player player.cpp)
include_directories("ZLMediaKit/src/" "ZLMediaKit/3rdpart/ZLToolKit/src/")
#target_include_directories(player PUBLIC "ZLMediaKit/src/" "ZLMediaKit/3rdpart/ZLToolKit/src/")
target_link_libraries(player PRIVATE zlmediakit zltoolkit mov mpeg flv pthread)