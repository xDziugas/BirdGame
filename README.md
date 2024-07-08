# Flappy Bird Clone

Welcome to the Flappy Bird Clone game! This project is a personal implementation of the popular Flappy Bird game with added functionality. The game is written in C++ using the SFML library and is highly configurable through a JSON configuration file.

## Table of Contents
- [Features](#features)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Configuration](#configuration)
- [Controls](#controls)
- [Packaging](#packaging)


## Features

- Flappy Bird gameplay
- High score tracking (top 10 scores)
- Configurable assets (background, bird, pipes, etc.)
- Configurable game settings (e.g., window size, frame rate)
- Pause and resume functionality
- Settings screen
- FPS display

## Requirements

- C++17
- SFML 2.6.1
- [nlohmann/json](https://github.com/nlohmann/json) library for JSON parsing
- CMake 3.28 or later

## Installation

### From Source

1. Clone the repository:
    ```sh
    git clone https://github.com/xDziugas/BirdGame.git
    cd BirdGame
    ```

2. Install dependencies:
    - Make sure you have SFML and nlohmann/json library installed.
    - Include SFML and nlohmann/json in your project.

3. Open the project in your preferred IDE (e.g., CLion).

4. Build the project using your IDE or command line:
    ```sh
    mkdir build
    cd build
    cmake -DCMAKE_BUILD_TYPE=Release ..
    cmake --build .
    ```

### From Pre-built Package

1. Download the latest release from the [Releases page](https://github.com/xDziugas/BirdGame/releases).
2. Extract the contents of the ZIP file to your desired location.
3. Run the executable (`BirdGame.exe`) found in the extracted folder.

## Usage

### From Source

1. Build the project using your IDE or command line (as described above).
2. Run the executable:
    ```sh
    ./BirdGame
    ```

### From Pre-built Package

1. Run the executable (`BirdGame.exe`) found in the extracted folder from the release.

## Configuration

The game settings can be configured via the `config.json` file. The following are some example configuration options available:

- Window settings
- Background texture and scroll speed
- Ground texture, scroll speed, and height
- Bird texture, size, gravity, jump strength, and default position
- Pipe texture, speed, gap, spawn interval, and height multipliers
- Frame rate settings
- Game settings including fonts and messages
- Key bindings

## Controls

- **Space**: Jump / Start Game / Resume Game
- **P**: Pause / Unpause
- **S**: Open Settings

## Packaging

To create an installer or ZIP package with all the necessary files, use CPack:

1. Build the project:
    ```sh
    cd build
    cmake --build .
    ```

2. Run CPack:
    ```sh
    cpack
    ```

The generated installer or ZIP package will include the executable, configuration files, assets, and all necessary DLLs.

