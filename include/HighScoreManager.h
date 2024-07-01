//
// Created by dziug on 7/1/2024.
//

#ifndef HIGHSCOREMANAGER_H
#define HIGHSCOREMANAGER_H

#include <vector>
#include <string>

class HighScoreManager {
public:
    HighScoreManager(const std::string &filePath);
    void loadHighScores();
    void saveHighScores();
    void updateHighScores(int score);
    const std::vector<int>& getHighScores() const;

private:
    std::string highScoreFile;
    std::vector<int> highScores;
};

#endif //HIGHSCOREMANAGER_H
