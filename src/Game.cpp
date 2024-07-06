//
// Created by dziug on 6/30/2024.
//

#include "../include/Game.h"
#include <sstream>
#include <iostream>
#include <filesystem>
#include <ctime>
#include <iomanip>
#include "State.h"

Game::Game(const GameConfig &config)
    : window(),
      config(config),
      gameState(State(StartScreen)),
      bird(config.bird, config.keyBinds),
      background(config.background.texture, config.background.scroll_speed, config.window),
      ground(config.ground.texture, config.ground.scroll_speed, static_cast<float>(config.window.width), config.ground.height, static_cast<float>(config.window.height) - config.ground.height),
      pipeSpawnInterval(config.pipe.spawn_interval),
      score(0),
      isPaused(false),
      highScoreManager("highscores.txt") {

    initializeWindow();
    initializeAssets();

    initializeText(fpsText, "", config.frameRate.position, config.frameRate.color, config.frameRate.size);
    initializeText(scoreText, "", config.gameSettings.scoreMessage.position, config.gameSettings.scoreMessage.color, config.gameSettings.scoreMessage.size);
    initializeText(startMessageText, config.gameSettings.startMessage.text, { static_cast<float>(window.getSize().x) / 2.0f, static_cast<float>(window.getSize().y) / 2.0f - 50.0f }, config.gameSettings.startMessage.color, config.gameSettings.startMessage.size);
    initializeText(pauseMessageText, config.gameSettings.pauseMessage.text, { static_cast<float>(window.getSize().x) / 2.0f, static_cast<float>(window.getSize().y) / 2.0f - 50.0f }, config.gameSettings.pauseMessage.color, config.gameSettings.pauseMessage.size);
    initializeText(settingsMessageText, config.gameSettings.settingsMessage.text, { static_cast<float>(window.getSize().x) / 2.0f, static_cast<float>(window.getSize().y) / 2.0f - 150.0f }, config.gameSettings.settingsMessage.color, config.gameSettings.settingsMessage.size);

    highScoreManager.loadHighScores();
}

void Game::run() {
    sf::Clock fpsClock;
    int frameCount = 0;

    while (window.isOpen()) {
        processEvents();

        if (gameState.get() == Playing && !isPaused) {
            update(clock.restart());
        }

        updateFPS(fpsClock, frameCount);

        render();
    }
}

void Game::processEvents() {
    sf::Event event{};
    while (window.pollEvent(event)) {
        handleEvent(event);
    }
}

void Game::handleEvent(sf::Event& event) {
    if (event.type == sf::Event::Closed) {
        window.close();
    }
    inputHandler.handleInput(event, gameState, clock, pipeSpawnClock, isPaused, pauseTime, totalPauseTime, pipes, score, [this]() { resetGame(); }, config.keyBinds);
}

void Game::update(const sf::Time dt) {
    bird.update(dt.asSeconds());
    background.update(dt.asSeconds());
    ground.update(dt.asSeconds());

    handlePipeSpawning();
    updatePipes(dt.asSeconds());
    incrementScore();
    removeOffScreenPipes();

    checkCollisions();
}

void Game::handlePipeSpawning() {
    if ((pipeSpawnClock.getElapsedTime() - totalPauseTime).asSeconds() >= pipeSpawnInterval) {
        spawnPipe();
        totalPauseTime = sf::Time::Zero;  // Reset total pause time after spawning a pipe
    }
}

void Game::updatePipes(const float dt) {
    for (auto &pipe : pipes) {
        pipe.update(dt);
    }
}

void Game::incrementScore() {
    for (auto &pipe : pipes) {
        if (!pipe.isPassed() && pipe.getPosition().x < bird.getPosition().x) {
            pipe.markAsPassed();
            score++;
        }
    }
}

void Game::removeOffScreenPipes() {
    pipes.erase(std::remove_if(pipes.begin(), pipes.end(), [](const Pipe &pipe) {
        return pipe.isOffScreen();
    }), pipes.end());
}

void Game::render() {
    window.clear();

    renderCommonElements();

    switch (gameState.get()) {
        case StartScreen:
            renderStartScreen();
            break;
        case Pause:
            renderPauseScreen();
            break;
        case Settings:
            renderSettingsScreen();
            break;
        case GameOver:
            renderGameOverScreen();
            break;
        case Playing:
            renderPlayingScreen();
            break;
    }

    if (config.frameRate.showFps) {
        window.draw(fpsText);
    }

    window.display();
}

void Game::renderCommonElements() {
    background.render(window);
    for (auto &pipe : pipes) {
        pipe.render(window);
    }
    ground.render(window);
    bird.render(window);
}

void Game::renderStartScreen() {
    renderCommonElements();
    window.draw(startMessageText);
}

void Game::renderPauseScreen() {
    renderCommonElements();
    window.draw(pauseMessageText);
}

void Game::renderSettingsScreen() {
    window.draw(settingsMessageText);
}

void Game::renderGameOverScreen() {
    window.draw(gameOverSprite);

    std::stringstream ss;
    ss << "Score! " << score;
    scoreText.setString(ss.str());
    scoreText.setPosition(
        config.gameSettings.scoreMessage.position.x - scoreText.getLocalBounds().width / 2.0f,
        config.gameSettings.scoreMessage.position.y
    );

    window.draw(scoreText);

    renderHighScores();
}

void Game::renderPlayingScreen() {
    renderCommonElements();

    std::stringstream ss;
    ss << score;
    scoreText.setString(ss.str());
    scoreText.setPosition(config.gameSettings.scoreMessage.position.x,
                          config.gameSettings.scoreMessage.position.y);
    window.draw(scoreText);
}

void Game::renderHighScores() {
    float yOffset = 100;
    for (int i = 0; i < highScoreManager.getHighScores().size(); ++i) {
        sf::Text highScoreText;
        highScoreText.setFont(font);
        highScoreText.setCharacterSize(config.highScore.size);
        highScoreText.setFillColor(config.highScore.color);
        highScoreText.setPosition(static_cast<float>(window.getSize().x) / 2 - 100, yOffset + static_cast<float>(i * 40));

        std::stringstream hs_ss;
        hs_ss << std::setw(5) << std::setfill('0') << highScoreManager.getHighScores()[i];
        highScoreText.setString(std::to_string(i + 1) + "! " + hs_ss.str());

        window.draw(highScoreText);
    }
}

void Game::resetGame() {
    bird.reset();
    updateHighScores();
    gameState.set(StartScreen);
}

void Game::updateHighScores() {
    highScoreManager.updateHighScores(score);
}

void Game::spawnPipe() {
    Pipe newPipe(config.pipe);
    newPipe.spawnPipe(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y), ground.getGroundHeight(), config.pipe.minPipeHeightMultiplier, config.pipe.maxPipeHeightMultiplier);
    pipes.emplace_back(std::move(newPipe));
    pipeSpawnClock.restart();
}

void Game::checkCollisions() {
    if (checkBirdPipeCollisions() || checkBirdGroundCollision()) {
        gameState.set(GameOver);
    }
}

bool Game::checkBirdPipeCollisions() const {
    sf::FloatRect birdBounds = bird.getBounds();
    for (const auto &pipe : pipes) {
        for (const auto &bounds : pipe.getBounds()) {
            if (birdBounds.intersects(bounds)) {
                return true;
            }
        }
    }
    return false;
}

bool Game::checkBirdGroundCollision() const {
    sf::FloatRect birdBounds = bird.getBounds();
    return birdBounds.top + birdBounds.height >= static_cast<float>(window.getSize().y) - ground.getGroundHeight();
}

void Game::initializeWindow() {
    window.create(sf::VideoMode(config.window.width, config.window.height), config.window.title);
    window.setFramerateLimit(config.frameRate.fps);
    srand(static_cast<unsigned int>(time(nullptr)));
}

void Game::initializeAssets() {
    if (!Pipe::loadTexture(config.pipe.texture)) {
        throw std::runtime_error("Failed to load pipe texture");
    }

    if (!gameOverTexture.loadFromFile(config.gameSettings.gameOverTexture)) {
        throw std::runtime_error("Failed to load game over texture");
    }
    gameOverSprite.setTexture(gameOverTexture);

    if (!font.loadFromFile(config.gameSettings.font.file)) {
        throw std::runtime_error("Failed to load font");
    }
}

void Game::initializeText(sf::Text& text, const std::string& message, const sf::Vector2f& position, const sf::Color& color, int size) const {
    text.setFont(font);
    text.setCharacterSize(size);
    text.setFillColor(color);
    text.setString(message);

    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(position);
}

void Game::updateFPS(sf::Clock& fpsClock, int& frameCount) {
    frameCount++;
    if (fpsClock.getElapsedTime().asSeconds() >= 1.0f) {
        fpsText.setString("FPS " + std::to_string(frameCount));
        frameCount = 0;
        fpsClock.restart();
    }
}