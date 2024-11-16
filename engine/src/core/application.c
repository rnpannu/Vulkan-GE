
#include "application.h"
#include "game_types.h"
#include "logger.h"
#include "platform/platform.h"
// Singleton "object"

typedef struct application_state{
    game* game_inst;
    b8 is_running;
    b8 is_suspended;
    platform_state platform; //pointer to platform state
    i16 width;
    i16 height;
    f64 last_time;
} application_state;

static b8 initialized = FALSE; // One time state check
static application_state app_state;

b8 application_create(game* game_inst){
    if(initialized){
        KERROR("application_create called more than once.");
        return FALSE;
    }

    app_state.game_inst = game_inst;

    // Initialize subsystems
    initialize_logging();
    // TODO: Get rid of
    KFATAL("A test message: %f", 3.14f);
    KERROR("A test message: %f", 3.14f);
    KWARN("A test message: %f", 3.14f);
    KDEBUG("A test message: %f", 3.14f);
    KTRACE("A test message: %f", 3.14f);

    app_state.is_running = TRUE;
    app_state.is_suspended = FALSE; // Minimize/pause application

    if(!platform_startup(
        &app_state.platform, 
        game_inst->app_config.name, 
        game_inst->app_config.start_pos_x, 
        game_inst->app_config.start_pos_y, 
        game_inst->app_config.start_width, 
        game_inst->app_config.start_height)){
        return FALSE;
    }
    if (!app_state.game_inst->initialize(app_state.game_inst)){
        KFATAL("Game failed to initialze");
    }

    app_state.game_inst->on_resize(app_state.game_inst, app_state.width, app_state.height);

    initialized = TRUE;

    return TRUE;

}

b8 application_run(){
    while (app_state.is_running){
        if(!platform_pump_messages(&app_state.platform)){
            app_state.is_running = FALSE;
        }

        if(!app_state.is_suspended){
            // Update routine
            if(!app_state.game_inst->update(app_state.game_inst, (f32)0)){ // delta time placeholder
                KFATAL("Game update failed");
                app_state.is_running = FALSE;
                break;
            }

            // Renderer routine
            if(!app_state.game_inst->render(app_state.game_inst, (f32)0)){ // delta time placeholder
                KFATAL("Game render failed");
                app_state.is_running = FALSE;
                break;
            }
        }

    }

    app_state.is_running = FALSE;

    platform_shutdown(&app_state.platform);
    return TRUE;
}