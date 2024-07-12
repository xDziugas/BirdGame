cmake_minimum_required(VERSION 3.28)
project(BirdGame)

set(CMAKE_CXX_STANDARD 17)

set(SFML_DIR "C:/SFML/SFML-2.6.1/lib/cmake/SFML")

include_directories("C:/SFML/SFML-2.6.1/include/SFML")
include_directories(include)

find_package(SFML 2.6.1 COMPONENTS system window graphics network audio REQUIRED)

add_executable(BirdGame main.cpp
        src/Bird.cpp
        include/Bird.h
        src/Background.cpp
        include/Background.h
        src/Ground.cpp
        include/Ground.h
        src/Pipe.cpp
        include/Pipe.h
        src/Game.cpp
        include/Game.h
        src/State.cpp
        include/State.h
        src/InputHandler.cpp
        include/InputHandler.h
        src/HighScoreManager.cpp
        include/HighScoreManager.h
        src/GameConfig.cpp
        include/GameConfig.h
        include/json.hpp)
target_link_libraries(BirdGame sfml-audio sfml-graphics sfml-system sfml-window)

# Install target and necessary files
install(TARGETS BirdGame DESTINATION bin)
install(FILES config.json highscores.txt DESTINATION bin)
install(DIRECTORY assets DESTINATION bin)

# CPack configuration
include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_NAME "BirdGame")
set(CPACK_PACKAGE_VERSION "1.0")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Flappy Bird Clone Game")

# Find the MinGW libraries
if(WIN32)
    find_file(LIBGCC_S_SEH_1_DLL libgcc_s_seh-1.dll PATHS "C:/MinGW/bin")
    find_file(LIBSTDCXX_6_DLL libstdc++-6.dll PATHS "C:/MinGW/bin")
    find_file(LIBWINPTHREAD_1_DLL libwinpthread-1.dll PATHS "C:/MinGW/bin")

    # Find the SFML libraries
    find_file(SFML_SYSTEM_DLL sfml-system-2.dll PATHS "C:/SFML/SFML-2.6.1/bin")
    find_file(SFML_WINDOW_DLL sfml-window-2.dll PATHS "C:/SFML/SFML-2.6.1/bin")
    find_file(SFML_GRAPHICS_DLL sfml-graphics-2.dll PATHS "C:/SFML/SFML-2.6.1/bin")
    find_file(SFML_AUDIO_DLL sfml-audio-2.dll PATHS "C:/SFML/SFML-2.6.1/bin")
    find_file(SFML_NETWORK_DLL sfml-network-2.dll PATHS "C:/SFML/SFML-2.6.1/bin")

    # Install MinGW runtime libraries
    if(LIBGCC_S_SEH_1_DLL)
        install(FILES ${LIBGCC_S_SEH_1_DLL} DESTINATION bin)
    endif()
    if(LIBSTDCXX_6_DLL)
        install(FILES ${LIBSTDCXX_6_DLL} DESTINATION bin)
    endif()
    if(LIBWINPTHREAD_1_DLL)
        install(FILES ${LIBWINPTHREAD_1_DLL} DESTINATION bin)
    endif()

    # Install SFML libraries
    if(SFML_SYSTEM_DLL)
        install(FILES ${SFML_SYSTEM_DLL} DESTINATION bin)
    endif()
    if(SFML_WINDOW_DLL)
        install(FILES ${SFML_WINDOW_DLL} DESTINATION bin)
    endif()
    if(SFML_GRAPHICS_DLL)
        install(FILES ${SFML_GRAPHICS_DLL} DESTINATION bin)
    endif()
    if(SFML_AUDIO_DLL)
        install(FILES ${SFML_AUDIO_DLL} DESTINATION bin)
    endif()
    if(SFML_NETWORK_DLL)
        install(FILES ${SFML_NETWORK_DLL} DESTINATION bin)
    endif()
endif()

# Set CPack generator to ZIP
set(CPACK_GENERATOR "ZIP")

include(CPack)