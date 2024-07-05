//
// Created by dziug on 7/3/2024.
//

#ifndef GAMECONFIG_H
#define GAMECONFIG_H

#include <string>
#include <json.hpp>
#include <Graphics/Color.hpp>
#include <System/Vector2.hpp>

class GameConfig {
public:
    struct WindowConfig {
        int width;
        int height;
        std::string title;
    } window;

    struct FrameRateConfig {
        int fps;
        sf::Vector2f position;
        int size;
        sf::Color color;
        bool showFps;
    } frameRate;

    struct BirdConfig {
        std::string texture;
        float gravity;
        float jump_strength;
        float jump_cooldown;
        float width;
        float height;
        sf::Vector2f default_position;
        bool enableRotation;
    } bird;

    struct BackgroundConfig {
        std::string texture;
        float scroll_speed;
    } background;

    struct GroundConfig {
        std::string texture;
        float scroll_speed;
        float height;
    } ground;

    struct PipeConfig {
        std::string texture;
        float speed;
        float spawn_interval;
        float gap;
        float minPipeHeightMultiplier;
        float maxPipeHeightMultiplier;
    } pipe;

    struct FontConfig {
        std::string file;
        int size;
        sf::Color color;
    };

    struct MessageConfig {
        std::string text;
        int size;
        sf::Color color;
        sf::Vector2f position;
    };

    struct GameSettingsConfig {
        FontConfig font;
        MessageConfig startMessage;
        MessageConfig pauseMessage;
        MessageConfig settingsMessage;
        MessageConfig scoreMessage;
        std::string gameOverTexture;
    } gameSettings;

    struct KeyBinds {
        int jump;
        int pause;
        int settings;
    } keyBinds;

    bool loadFromFile(const std::string& filename);
};

#endif //GAMECONFIG_H
