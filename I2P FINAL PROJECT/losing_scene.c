#include <allegro5/allegro.h>
#include <string.h>
#include "menu_scene.h"
#include "loading_scene.h"
#include "game_scene.h"
#include "setting_scene.h"
#include "utility.h"
#include "UI.h"
#include "game.h"
#include "losing_scene.h"
#include "player.h"

static int timer_countdown;
static ALLEGRO_BITMAP* player_bitmap;
static Button HomeButton;


static void init(void) {
    /*timer_countdown = 60*/; // -->AFTER 60 

    player_bitmap = al_load_bitmap("Assets/panda_lose.png");
    HomeButton = button_create(SCREEN_W / 2 - 200, 600, 400, 100, "Assets/UI_Button.png", "Assets/UI_Button_hovered.png");

    change_bgm("Assets/audio/GAMEOVER.mp3");
}

static void update(void) {
    /*timer_countdown--;
    if (timer_countdown == 0) {
        change_scene(create_game_scene());
    }*/
    update_button(&HomeButton);
    /*
        [TODO HACKATHON 4-3]

        Change scene to setting scene when the button is pressed
    */
    if (HomeButton.hovered && mouseState.buttons == 1)
    {
        change_scene(create_menu_scene());
        al_rest(0.2);
    }
}

static void draw(void){

    al_draw_text(
        TITLE_FONT,
        al_map_rgb(146, 161, 185),
        SCREEN_W / 2 + 10,
        SCREEN_H / 2,
        ALLEGRO_ALIGN_CENTER,
        "YOU DIED"
    );
    al_draw_scaled_bitmap(player_bitmap,
        0, 0, 64, 64, //ori size of picture
        SCREEN_W / 2 - 128, SCREEN_H / 3  - 128, //destination position buat y ama x
        256, 256, //lebar ama tinggi
        0);


    // button
    draw_button(HomeButton);
   
    al_draw_text(
        P2_FONT,
        al_map_rgb(66, 76, 110),
        SCREEN_W / 2,
        600 + 28 + HomeButton.hovered * 11,
        ALLEGRO_ALIGN_CENTER,
        "MENU"
    );
    al_draw_text(
        P2_FONT,
        al_map_rgb(225, 225, 225),
        SCREEN_W / 2,
        600 + 31 + HomeButton.hovered * 11,
        ALLEGRO_ALIGN_CENTER,
        "MENU"
    );
}

static void destroy(void) {
    al_destroy_bitmap(player_bitmap);
    destroy_button(&HomeButton);
}


Scene create_losing_scene(void) {
    Scene scene;
    memset(&scene, 0, sizeof(Scene));

    scene.name = "losing";
    scene.init = &init;
    scene.draw = &draw;
    scene.update = &update;
    scene.destroy = &destroy;

    return scene;
}
