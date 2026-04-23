//
// Created by rahul on 4/23/2026.
//

#ifndef CUBECHESS_SAVE_FILE_H
#define CUBECHESS_SAVE_FILE_H
#include "game_state.h"

void save_file(GameState* game_state, const char* filepath);

GameState* load_file(const char* filepath);

#endif //CUBECHESS_SAVE_FILE_H
