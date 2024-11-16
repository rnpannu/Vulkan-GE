#pragma once

#include "core/application.h"
#include "core/logger.h"
#include "game_types.h"

extern b8 create_game(game* out_game);

// Main entry of application
int main(void){
    game game_inst;
    if(!create_game(&game_inst)){
        KFATAL("Could not create game!");
        return -1;
    }

    if (!game_inst.initialize || !game_inst.render || !game_inst.update || !game_inst.on_resize){
        KFATAL("The game's function pointers must be assigned!");
        return -2;
    }

    // Initialize/create application
    if (!application_create(&game_inst)){
        KINFO("Application failed to create. ");
    }

    // Begin game loop
    if (!application_run()){
        KINFO("Application did not shut down gracefully. ");
        return 2;
    }


    return 0;
}