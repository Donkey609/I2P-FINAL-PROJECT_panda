#include <allegro5/allegro.h>
#include <string.h>
#include "menu_scene.h"
#include "game_scene.h"
#include "setting_scene.h"
#include "loading_scene.h"
#include "utility.h"
#include "UI.h"
#include "game.h"
#include "shop_scene.h"

static Button settingButton;
static Button shopButton;
static Button leaderboardButton;
static ALLEGRO_BITMAP* player_bitmap;

int coins_obtained;
int health_obtained;

static void init(void) {
    coins_obtained = 10;
    health_obtained = 50;
    player_bitmap = al_load_bitmap("Assets/sigmapanda.png");
    settingButton = button_create(SCREEN_W / 2 - 200, 600, 400, 100, "Assets/UI_Button.png", "Assets/UI_Button_hovered.png");
    shopButton = button_create(SCREEN_W / 2 - 200, 500, 400, 100, "Assets/UI_Button.png", "Assets/UI_Button_hovered.png");
    leaderboardButton = button_create(SCREEN_W / 2 - 200, 400, 400, 100, "Assets/UI_Button.png", "Assets/UI_Button_hovered.png");

    change_bgm("Assets/audio/SIGMABOY.mp3");
}

static void update(void) {
    update_button(&settingButton);
    update_button(&shopButton);
    update_button(&leaderboardButton);


    if (keyState[ALLEGRO_KEY_ENTER]) {
        change_scene(create_loading_scene());
    }

    /*
        [TODO HACKATHON 4-3] 
        
        Change scene to setting scene when the button is pressed
    */
    if (settingButton.hovered && mouseState.buttons == 1)
    {
        change_scene(create_setting_scene());
        al_rest(0.2);
    }
    //yg shop ama leaderboard blm diganti
    if (shopButton.hovered && mouseState.buttons == 1)
    {
        change_scene(create_shop_scene());
        al_rest(0.2);
    }
    if (leaderboardButton.hovered && mouseState.buttons == 1)
    {
        change_scene(create_setting_scene());
        al_rest(0.2);
    }
}

static void draw(void) {

    al_draw_scaled_bitmap(player_bitmap,
        0, 0, 600, 600, //ori size of picture
        SCREEN_W / 2 - 128, SCREEN_H / 3 - 150, //destination position buat y ama x
        256, 256, //lebar ama tinggi
        0);

    // Title Text
    al_draw_text(
        TITLE_FONT,
        al_map_rgb(146, 161, 185),
        SCREEN_W / 2,
        50,
        ALLEGRO_ALIGN_CENTER,
        "SIGMA PANDA"
    );
    al_draw_text(
        TITLE_FONT,
        al_map_rgb(199, 207, 221),
        SCREEN_W / 2,
        50,
        ALLEGRO_ALIGN_CENTER,
        "SIGMA PANDA"
    );

    al_draw_text(
        P2_FONT,
        al_map_rgb(255, 255, 255),
        SCREEN_W / 2,
        725,
        ALLEGRO_ALIGN_CENTER,
        "PRESS [ENTER] TO PLAY"
    );

    // button
    draw_button(settingButton);
    draw_button(shopButton);
    draw_button(leaderboardButton);

    // setting
    al_draw_text(
        P2_FONT,
        al_map_rgb(66, 76, 110),
        SCREEN_W / 2,
        600 + 28 + settingButton.hovered * 11,
        ALLEGRO_ALIGN_CENTER,
        "SETTING"
    );
    al_draw_text(
        P2_FONT,
        al_map_rgb(225, 225, 225),
        SCREEN_W / 2,
        600 + 31 + settingButton.hovered * 11,
        ALLEGRO_ALIGN_CENTER,
        "SETTING"
    );
    //shop
    al_draw_text(
        P2_FONT,
        al_map_rgb(66, 76, 110),
        SCREEN_W / 2,
        500 + 28 + shopButton.hovered * 11,
        ALLEGRO_ALIGN_CENTER,
        "SHOP"
    );
    al_draw_text(
        P2_FONT,
        al_map_rgb(225, 225, 225),
        SCREEN_W / 2,
        500 + 31 + shopButton.hovered * 11,
        ALLEGRO_ALIGN_CENTER,
        "SHOP"
    );
    //leaderboard
    al_draw_text(
        P2_FONT,
        al_map_rgb(66, 76, 110),
        SCREEN_W / 2,
        400 + 28 + leaderboardButton.hovered * 11,
        ALLEGRO_ALIGN_CENTER,
        "LEADERBOARD"
    );
    al_draw_text(
        P2_FONT,
        al_map_rgb(225, 225, 225),
        SCREEN_W / 2,
        400 + 31 + leaderboardButton.hovered * 11,
        ALLEGRO_ALIGN_CENTER,
        "LEADERBOARD"
    );
}

static void destroy(void) {
    destroy_button(&settingButton);
    destroy_button(&shopButton);
    destroy_button(&leaderboardButton);
    al_destroy_bitmap(player_bitmap); 
}


Scene create_menu_scene(void) {
    Scene scene;
    memset(&scene, 0, sizeof(Scene));

    scene.name = "menu";
    scene.init = &init;
    scene.draw = &draw;
    scene.update = &update;
    scene.destroy = &destroy;

    return scene;
}
