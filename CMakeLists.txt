cmake_minimum_required(VERSION 3.6)
project(Project_HY454)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2 -DNDEBUG")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${${PROJECT_NAME}_SOURCE_DIR}/cmake_modules")


add_executable(${PROJECT_NAME}
        main.cpp
        sources/core/Event.h
        sources/core/Geometry.h
        sources/core/Timer.h                                sources/core/Timer.cpp
        sources/core/AbstractScreen.h sources/core/AbstractScreen.cpp
        sources/Screens/GameScreen/GameScreen.h sources/Screens/GameScreen/GameScreen.cpp
        sources/core/SDLBackend/SDLEngine.h sources/core/SDLBackend/SDLEngine.cpp
        sources/core/SDLBackend/SDLRenderer.h sources/core/SDLBackend/SDLRenderer.cpp
        sources/Screens/GameScreen/BirdSprite.h sources/Screens/GameScreen/BirdSprite.cpp
        sources/core/Animator/Animator.h                    sources/core/Animator/Animator.cpp
        sources/core/Animator/FrameRangeAnimator.h          sources/core/Animator/FrameRangeAnimator.cpp
        sources/core/Animator/MovingAnimator.h              sources/core/Animator/MovingAnimator.cpp
        sources/core/Animation/Animation.h
        sources/core/Animation/MovingAnimation.h
        sources/core/Animation/FrameRangeAnimation.h
        sources/core/AnimatorManager.h
        sources/core/Animation/GravityAnimation.h           sources/core/Animator/GravityAnimator.cpp
        sources/core/Animator/GravityAnimator.h
        sources/core/GameSettings.h                         sources/core/GameSettings.cpp
        sources/core/Animation/RotationAnimation.h
        sources/core/Animator/RotationAnimator.h                sources/core/Animator/RotationAnimator.cpp
        sources/core/Animator/GroupMovingAnimator.h             sources/core/Animator/GroupMovingAnimator.cpp
        sources/core/ScreenStack.cpp sources/core/ScreenStack.h  sources/Screens/StartScreen/StartScreen.cpp
        sources/Screens/StartScreen/StartScreen.h
        sources/Screens/ResultScreen/ResultScreen.cpp
        sources/Screens/ResultScreen/ResultScreen.h
        sources/core/SDLBackend/SDLSoundSystem.cpp
        sources/core/SDLBackend/SDLSoundSystem.h
        sources/core/GameEngineAbstract/SoundSystemInterface.h
        sources/core/SoundManager.h sources/core/SoundManager.cpp
        sources/Screens/GameScreen/Barriers/PipeBarrierSprite.cpp
        sources/Screens/GameScreen/Barriers/PipeBarrierSprite.h
        sources/core/UserGameData.cpp sources/core/UserGameData.h
        sources/Screens/PauseScreen/PauseScreen.cpp sources/Screens/PauseScreen/PauseScreen.h
        third-part/json/json.hpp
        sources/core/Sprites/Layer.cpp sources/core/Sprites/Layer.h
        sources/core/Sprites/Sprite.cpp sources/core/Sprites/Sprite.h
        sources/core/Sprites/ImageSprite.cpp sources/core/Sprites/ImageSprite.h
        sources/core/SDLBackend/SDLBitmap.cpp sources/core/SDLBackend/SDLBitmap.h
        sources/core/SDLBackend/SDLTextBitmap.cpp sources/core/SDLBackend/SDLTextBitmap.h
        sources/core/Sprites/TextSprite.cpp sources/core/Sprites/TextSprite.h
        sources/core/GameEngineAbstract/GameEngineInterface.h
        sources/core/GameEngineAbstract/GraphicsSystemInterface.h
        sources/GameDelegate.cpp sources/GameDelegate.h
        sources/core/Color.h
        sources/Screens/GameScreen/BarrierContainer.cpp sources/Screens/GameScreen/BarrierContainer.h sources/Screens/GameScreen/Barriers/BarrierInterface.h sources/core/Sprites/InfiniteBackgroundSprite.cpp sources/core/Sprites/InfiniteBackgroundSprite.h)

IF (WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++ -s")
    set(SDL2 "${${PROJECT_NAME}_SOURCE_DIR}/third-part/SDL2Components/Win32/SDL2")
    set(SDL2_TTF "${${PROJECT_NAME}_SOURCE_DIR}/third-part/SDL2Components/Win32/SDL2_ttf")
    set(SDL2_MIXER "${${PROJECT_NAME}_SOURCE_DIR}/third-part/SDL2Components/Win32/SDL2_mixer")
endif (WIN32)

find_package(SDL2 REQUIRED)
if (SDL2_FOUND)
    include_directories (${SDL2_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})
endif (SDL2_FOUND)

find_package(SDL2TTF REQUIRED)
if (SDL2TTF_LIBRARY)
    include_directories (${SDL2TTF_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SDL2TTF_LIBRARY})
endif (SDL2TTF_LIBRARY)

find_package(SDL2_Mixer REQUIRED)
if (SDL2_MIXER_FOUND)
    include_directories (${SDL2_MIXER_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SDL2_MIXER_LIBRARY})
endif (SDL2_MIXER_FOUND)