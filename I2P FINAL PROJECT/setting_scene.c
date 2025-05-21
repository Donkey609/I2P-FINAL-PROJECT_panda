#include <allegro5/allegro.h>
#include "setting_scene.h"
#include "menu_scene.h"
#include "utility.h"
#include "UI.h"
#include "game.h"
#include "player.h"

static Button backButton;
static Button WASDButton;
static Button ARROWButton;

static void init(void) {

    backButton = button_create(SCREEN_W / 2 - 200, 650, 400, 100, "Assets/UI_Button.png", "Assets/UI_Button_hovered.png");
    WASDButton = button_create(SCREEN_W / 2 - 200, 450, 400, 100, "Assets/UI_Button.png", "Assets/UI_Button_hovered.png");
    ARROWButton = button_create(SCREEN_W / 2 - 200, 250, 400, 100, "Assets/UI_Button.png", "Assets/UI_Button_hovered.png");

}

static void update(void) {

    update_button(&backButton);
    update_button(&WASDButton);
    update_button(&ARROWButton);

    if (mouseState.buttons && backButton.hovered == true) {
        change_scene(create_menu_scene());
    }
    if (mouseState.buttons && WASDButton.hovered == true) {
        current_navigation_mode = NAVIGATION_WASD;
    }
    if (mouseState.buttons && ARROWButton.hovered == true) {
        current_navigation_mode = NAVIGATION_ARROW;
    }

}

static void draw(void) {
    // button
    draw_button(backButton);
    draw_button(WASDButton);
    draw_button(ARROWButton);
    //button text
    al_draw_text(
        P2_FONT,
        al_map_rgb(66, 76, 110),
        SCREEN_W / 2,
        650 + 28 + backButton.hovered * 11,
        ALLEGRO_ALIGN_CENTER,
        "BACK"
    );
    al_draw_text(
        P2_FONT,
        al_map_rgb(225, 225, 225),
        SCREEN_W / 2,
        650 + 31 + backButton.hovered * 11,
        ALLEGRO_ALIGN_CENTER,
        "BACK"
    );
    //WASD
    al_draw_text(
        P2_FONT,
        al_map_rgb(255, 255, 0),
        SCREEN_W / 2,
        450 + 28 + WASDButton.hovered * 11,
        ALLEGRO_ALIGN_CENTER,
        "WASD"
    );
    al_draw_text(
        P2_FONT,
        al_map_rgb(255, 255, 0),
        SCREEN_W / 2,
        450 + 31 + WASDButton.hovered * 11,
        ALLEGRO_ALIGN_CENTER,
        "WASD"
    );
    //ARROW
    al_draw_text(
        P2_FONT,
        al_map_rgb(255, 255, 0),
        SCREEN_W / 2,
        250 + 28 + ARROWButton.hovered * 11,
        ALLEGRO_ALIGN_CENTER,
        "ARROW"
    );
    al_draw_text(
        P2_FONT,
        al_map_rgb(255, 255, 0),
        SCREEN_W / 2,
        250 + 31 + ARROWButton.hovered * 11,
        ALLEGRO_ALIGN_CENTER,
        "ARROW"
    );
    
    al_draw_text(
        P2_FONT,
        al_map_rgb(225, 225, 225),
        SCREEN_W / 2,
        100 + 31,
        ALLEGRO_ALIGN_CENTER,
        "CHOOSE YOUR NAVIGATION KEY"
    );
}

static void destroy(void) {
    destroy_button(&backButton);
    destroy_button(&WASDButton);
    destroy_button(&ARROWButton);
}

Scene create_setting_scene(void) {
    Scene scene;
    memset(&scene, 0, sizeof(Scene));

    scene.name = "setting";
    scene.init = &init;
    scene.draw = &draw;
    scene.update = &update;
    scene.destroy = &destroy;

    return scene;
}
