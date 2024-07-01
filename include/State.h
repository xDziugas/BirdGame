//
// Created by dziug on 7/1/2024.
//

#ifndef STATE_H
#define STATE_H

enum GameState {
    StartScreen,
    Playing,
    GameOver,
    Pause,
    Settings
};

class State {
public:
    State(GameState initialState);
    GameState get() const;
    void set(GameState state);

private:
    GameState currentState;
};

#endif //STATE_H
