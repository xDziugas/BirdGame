//
// Created by dziug on 7/1/2024.
//

#include "../include/State.h"

State::State(GameState initialState) : currentState(initialState) {}

GameState State::get() const {
    return currentState;
}

void State::set(GameState state) {
    currentState = state;
}
