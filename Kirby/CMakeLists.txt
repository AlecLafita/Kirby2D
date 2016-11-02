cmake_minimum_required(VERSION 2.8)

cmake_policy(SET CMP0015 NEW)
if(UNIX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")
    execute_process(COMMAND ln -s ../shaders_linux)
else()
    execute_process(COMMAND ln -s ../shaders)
endif()

execute_process(COMMAND ln -s ../images)
execute_process(COMMAND ln -s ../levels)
execute_process(COMMAND ln -s ../sounds)

set(appName Kirby)

set(CMAKE_MODULE_PATH
        "${CMAKE_SOURCE_DIR}/base"
        "${CMAKE_SOURCE_DIR}/characters"
        "${CMAKE_SOURCE_DIR}/cmake_modules"
        "${CMAKE_SOURCE_DIR}/fonts"
        "${CMAKE_SOURCE_DIR}/helpers"
        "${CMAKE_SOURCE_DIR}/levels"
        "${CMAKE_SOURCE_DIR}/objects"
        "${CMAKE_SOURCE_DIR}/sounds"
        ${CMAKE_MODULE_PATH})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLM REQUIRED)
find_package(SOIL REQUIRED)
find_package(SFML COMPONENTS audio)
find_package(Freetype REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${GLUT_INCLUDE_DIRS})
include_directories(${GLEW_INCLUDE_DIRS})
include_directories(${GLM_INCLUDE_DIRS})
include_directories(${SOIL_INCLUDE_DIRS})
include_directories(${SFML_INCLUDE_DIRS})
include_directories(${FREETYPE_INCLUDE_DIRS})

link_directories(${OPENGL_LIBRARY_DIRS})
link_directories(${GLUT_LIBRARY_DIRS})
link_directories(${GLEW_LIBRARY_DIRS})
link_directories(${SOIL_LIBRARY_DIRS})
link_directories(${SFML_LIBRARY_DIRS})


link_directories(${FREETYPE_LIBRARY_DIRS})

add_executable(${appName} characters/Player.h characters/Player.cpp AnimKeyframes.h base/Sprite.h base/Sprite.cpp base/TileMap.h base/TileMap.cpp
        base/Texture.h base/Texture.cpp base/Scene.h base/Scene.cpp base/Shader.h base/Shader.cpp base/ShaderProgram.h
        base/ShaderProgram.cpp base/Game.h base/Game.cpp main.cpp characters/BaseEnemy.h characters/BaseEnemy.cpp characters/Character.h characters/Character.cpp
        objects/BaseObject.h objects/BaseObject.cpp objects/ProjectileObject.h objects/ProjectileObject.cpp base/Defines.h characters/PinxoEnemy.cpp
        characters/PinxoEnemy.h base/GUI.cpp base/GUI.h helpers/ColisionHelper.cpp helpers/ColisionHelper.h base/Text.cpp base/Text.h
        base/TexturedQuad.cpp base/TexturedQuad.h helpers/SoundHelper.h helpers/SoundHelper.cpp characters/BlackKirby.cpp characters/BlackKirby.h characters/Kirby.cpp characters/Kirby.h helpers/TransformationHelper.cpp helpers/TransformationHelper.h
        base/MainMenu.cpp base/MainMenu.h characters/FireKirby.cpp characters/FireKirby.h
        characters/PowerType.h characters/FlyingDummyEnemy.cpp characters/FlyingDummyEnemy.h
        objects/EnergyObject.h objects/EnergyObject.cpp objects/LifeObject.h objects/LifeObject.cpp characters/WalkingDummyEnemy.h characters/WalkingDummyEnemy.cpp
        objects/BigObject.cpp objects/BigObject.h characters/FireEnemy.cpp characters/FireEnemy.h characters/AquaKirby.cpp characters/AquaKirby.h characters/IcyEnemy.cpp characters/IcyEnemy.h characters/IceKirby.cpp characters/IceKirby.h characters/AttackEnemy.h characters/AttackEnemy.cpp objects/PortalObject.h objects/PortalObject.cpp characters/AquaEnemy.cpp characters/AquaEnemy.h objects/DoorObject.cpp objects/DoorObject.h objects/RotationObject.h
        objects/RotationObject.cpp)

target_link_libraries(${appName} ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${GLEW_LIBRARIES} ${SOIL_LIBRARIES} ${SFML_LIBRARIES} ${FREETYPE_LIBRARIES}) # ${GLM_LIBRARIES}



