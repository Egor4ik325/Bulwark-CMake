#
# Created by Егор Зорин on 01/04/2020.
#
cmake_minimum_required(VERSION 3.15)
project(Bulwark)
set(CMAKE_CXX_STANDARD 17)

message("All right!")

find_package(SFML COMPONENTS graphics REQUIRED)

add_executable(Bulwark src/Animation.cpp src/Animation.h src/Bulwark.cpp src/Bulwark.h src/Content.cpp
        src/Content.h src/DebugRect.cpp src/DebugRect.h src/Effect.cpp src/Effect.h src/Global.cpp
        src/Global.h src/Inventory.cpp src/Inventory.h src/InventoryCell.cpp src/InventoryCell.h
        src/Item.cpp src/Item.h src/ItemManager.cpp src/ItemManager.h src/main.cpp
        src/Player.cpp src/Player.h src/TileMap.cpp src/TileMap.h src/tinystr.cpp src/tinystr.h
        src/tinyxml.cpp src/tinyxml.h src/tinyxmlerror.cpp src/tinyxmlparser.cpp src/UIBase.cpp
        src/UIBase.h src/UIButton.cpp src/UIButton.h src/UIDragable.cpp src/UIDragable.h src/UIManager.cpp
        src/UIManager.h src/UIScreen.cpp src/UIScreen.h src/UIWindow.cpp src/UIWindow.h src/UserInterfaces.h
        src/UIItem.cpp src/UIItem.h
        )

target_link_libraries(Bulwark sfml-graphics)