//
// Created by dziug on 7/3/2024.
//

#include "../include/GameConfig.h"
#include <fstream>

using json = nlohmann::json;

bool GameConfig::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    json j;
    file >> j;

    window.width = j["window"]["width"];
    window.height = j["window"]["height"];
    window.title = j["window"]["title"];

    frameRate.fps = j["frameRate"]["fps"];
    frameRate.position = sf::Vector2f(
        j["frameRate"]["position"]["x"],
        j["frameRate"]["position"]["y"]
    );
    frameRate.size = j["frameRate"]["size"];
    frameRate.color = sf::Color(
        j["frameRate"]["color"]["r"],
        j["frameRate"]["color"]["g"],
        j["frameRate"]["color"]["b"]
    );
    frameRate.showFps = j["frameRate"]["showFps"];

    bird.texture = j["bird"]["texture"];
    bird.gravity = j["bird"]["gravity"];
    bird.jump_strength = j["bird"]["jump_strength"];
    bird.jump_cooldown = j["bird"]["jump_cooldown"];
    bird.default_position = sf::Vector2f(
        j["bird"]["default_position"]["x"],
        j["bird"]["default_position"]["y"]
    );
    bird.width = j["bird"]["width"];
    bird.height = j["bird"]["height"];
    bird.enableRotation = j["bird"]["enableRotation"];

    background.texture = j["background"]["texture"];
    background.scroll_speed = j["background"]["scroll_speed"];

    ground.texture = j["ground"]["texture"];
    ground.scroll_speed = j["ground"]["scroll_speed"];
    ground.height = j["ground"]["height"];

    pipe.texture = j["pipe"]["texture"];
    pipe.speed = j["pipe"]["speed"];
    pipe.spawn_interval = j["pipe"]["spawn_interval"];
    pipe.gap = j["pipe"]["gap"];
    pipe.minPipeHeightMultiplier = j["pipe"]["minPipeHeightMultiplier"];
    pipe.maxPipeHeightMultiplier = j["pipe"]["maxPipeHeightMultiplier"];

    gameSettings.font.file = j["font"]["file"];
    gameSettings.font.size = j["font"]["size"];
    gameSettings.font.color = sf::Color(
        j["font"]["color"]["r"],
        j["font"]["color"]["g"],
        j["font"]["color"]["b"]
    );

    gameSettings.startMessage.text = j["startMessage"]["text"];
    gameSettings.startMessage.size = j["startMessage"]["size"];
    gameSettings.startMessage.color = sf::Color(
        j["startMessage"]["color"]["r"],
        j["startMessage"]["color"]["g"],
        j["startMessage"]["color"]["b"]
    );
    gameSettings.startMessage.position = sf::Vector2f(
        j["startMessage"]["position"]["x"],
        j["startMessage"]["position"]["y"]
    );

    gameSettings.pauseMessage.text = j["pauseMessage"]["text"];
    gameSettings.pauseMessage.size = j["pauseMessage"]["size"];
    gameSettings.pauseMessage.color = sf::Color(
        j["pauseMessage"]["color"]["r"],
        j["pauseMessage"]["color"]["g"],
        j["pauseMessage"]["color"]["b"]
    );
    gameSettings.pauseMessage.position = sf::Vector2f(
        j["pauseMessage"]["position"]["x"],
        j["pauseMessage"]["position"]["y"]
    );

    gameSettings.scoreMessage.text = j["scoreMessage"]["text"];
    gameSettings.scoreMessage.size = j["scoreMessage"]["size"];
    gameSettings.scoreMessage.color = sf::Color(
        j["scoreMessage"]["color"]["r"],
        j["scoreMessage"]["color"]["g"],
        j["scoreMessage"]["color"]["b"]
    );
    gameSettings.scoreMessage.position = sf::Vector2f(
        j["scoreMessage"]["position"]["x"],
        j["scoreMessage"]["position"]["y"]
    );

    gameSettings.settingsMessage.text = j["settingsMessage"]["text"];
    gameSettings.settingsMessage.size = j["settingsMessage"]["size"];
    gameSettings.settingsMessage.color = sf::Color(
        j["settingsMessage"]["color"]["r"],
        j["settingsMessage"]["color"]["g"],
        j["settingsMessage"]["color"]["b"]
    );
    gameSettings.settingsMessage.position = sf::Vector2f(
        j["settingsMessage"]["position"]["x"],
        j["settingsMessage"]["position"]["y"]
    );

    keyBinds.jump = j["keyBinds"]["jump"];
    keyBinds.pause = j["keyBinds"]["pause"];
    keyBinds.settings = j["keyBinds"]["settings"];

    gameSettings.gameOverTexture = j["gameOverTexture"];

    return true;
}