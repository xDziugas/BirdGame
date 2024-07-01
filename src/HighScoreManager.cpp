//
// Created by dziug on 7/1/2024.
//

#include "../include/HighScoreManager.h"
#include <fstream>
#include <iostream>
#include <algorithm>

HighScoreManager::HighScoreManager(const std::string &filePath) : highScoreFile(filePath) {
    loadHighScores();
}

void HighScoreManager::loadHighScores() {
    std::ifstream file(highScoreFile);
    if (file.is_open()) {
        int score;
        highScores.clear();
        while (file >> score) {
            highScores.push_back(score);
        }
        file.close();
    } else {
        // If the file doesn't exist, create it with default high scores
        std::ofstream createFile(highScoreFile);
        if (createFile.is_open()) {
            highScores = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
            for (int score : highScores) {
                createFile << score << std::endl;
            }
            createFile.close();
        } else {
            std::cerr << "Unable to create high score file" << std::endl;
        }
    }
}

void HighScoreManager::saveHighScores() {
    std::ofstream file(highScoreFile);
    if(file.is_open()) {
        for(int score : highScores) {
            file << score << std::endl;
        }
        file.close();
    } else {
        std::cerr << "Failed to save high scores" << std::endl;
    }
}

void HighScoreManager::updateHighScores(int score) {
    highScores.push_back(score);
    std::sort(highScores.rbegin(), highScores.rend());
    if (highScores.size() > 10) {
        highScores.resize(10);
    }
    saveHighScores();
}

const std::vector<int>& HighScoreManager::getHighScores() const {
    return highScores;
}
