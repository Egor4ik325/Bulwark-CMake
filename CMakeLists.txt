#
# Created by Егор Зорин on 01/04/2020.
#
cmake_minimum_required(VERSION 3.15)
project(Bulwark)
set(CMAKE_CXX_STANDARD 17)

#set(CMAKE_BUILD_TYPE Debug)

message("START UP " ${PROJECT_NAME})

# Replace binary directory
#set(CMAKE_BINARY_DIR  ${CMAKE_BINARY_DIR}/bin)
#set(PROJECT_BINARY_DIR ${PROJECT_BINARY_DIR}/bin)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# Set CMAKE debug mode
#set(CMAKE_C_FLAGS_DEBUG "-D_DEBUG")
#set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
# Print DIR
message("Project Source DIR " ${PROJECT_SOURCE_DIR})
message("CMake BINARY DIR   " ${CMAKE_BINARY_DIR})
message("Project BINARY DIR " ${PROJECT_BINARY_DIR})
message("Run time directory " ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
message("Framework path     " ${CMAKE_FRAMEWORK_PATH})

# Add Preprocessor definition FOO (flag or macro)
# If build type is Debug
if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
add_definitions(-DBW_DEBUG)
endif()


#link_directories(${PROJECT_SOURCE_DIR}/dependencies)

# Search SFML .cmake scripts
#find_package(SFML COMPONENTS graphics REQUIRED)

#file(GLOB CPP  "src/*.cpp" "src/Item/*.cpp" "src/Map/*.cpp" "src/UI/*.cpp")
#file(GLOB HEAD "src/*.h" "src/Item/*.h" "src/Map/*.h" "src/UI/*.h")
#message("CPP = ${CPP}")

add_executable(
        Bulwark src/Animation.h src/Application.cpp src/Application.h src/Content.cpp
        src/Content.h src/DebugGraphics.cpp src/DebugGraphics.h src/Effect.cpp src/Effect.h src/Global.cpp
        src/Global.h src/Inventory.cpp src/Inventory.h src/InventoryCell.cpp src/InventoryCell.h
        src/Item/Item.cpp src/Item/Item.h src/Item/ItemLayer.cpp src/Item/ItemLayer.h src/main.cpp
        src/Player.cpp src/Player.h src/Map/MapLayer.cpp src/Map/MapLayer.h src/Map/TinyXML/tinystr.cpp src/Map/TinyXML/tinystr.h
        src/Map/TinyXML/tinyxml.cpp src/Map/TinyXML/tinyxml.h src/Map/TinyXML/tinyxmlerror.cpp src/Map/TinyXML/tinyxmlparser.cpp src/UI/UIBase.cpp
        src/UI/UIBase.h src/UI/UIButton.cpp src/UI/UIButton.h src/UI/UIDragable.cpp src/UI/UIDragable.h src/LayerStack.cpp
        src/LayerStack.h src/UI/UILayer.cpp src/UI/UILayer.h src/UI/UIWindow.cpp src/UI/UIWindow.h src/UIs.h
        src/UI/UIItem.cpp src/UI/UIItem.h src/Animation.h
        src/Layer.cpp src/Layer.h src/Event.cpp src/Event.h)

# add all .dylib to file LIBRATIES
file(GLOB LIBRARIES "dependencies/lib/*.2.5.1.dylib")
message("LIBRATIES = ${LIBRARIES}")

target_include_directories(Bulwark PUBLIC ${CMAKE_SOURCE_DIR}/Dependencies/include)
target_link_libraries     (Bulwark ${LIBRARIES})
# Include Project's source direction to all source files
include_directories(${PROJECT_SOURCE_DIR}/src)

# link libraries to the project
#target_link_libraries(Application sfml-graphics)