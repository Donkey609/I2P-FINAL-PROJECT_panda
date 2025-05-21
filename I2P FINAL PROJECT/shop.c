#include <allegro5/allegro.h>
#include "menu_scene.h"
#include "utility.h"
#include "UI.h"
#include "game.h"
#include "player.h"
#include "shop_scene.h"

static Button backButton;
static Button buyButton;


static void init(void) {

    backButton = button_create(SCREEN_W / 2 - 200, 650, 400, 100, "Assets/UI_Button.png", "Assets/UI_Button_hovered.png");
    buyButton = button_create(SCREEN_W / 2 - 200, 450, 400, 100, "Assets/UI_Button.png", "Assets/UI_Button_hovered.png");
  

}

static void update(void) {

    update_button(&backButton);
    update_button(&buyButton); 


    if (mouseState.buttons && backButton.hovered == true) {
        change_scene(create_menu_scene());
    }
    /*if (mouseState.buttons && BuyButton.hovered == true) {
        
    }*/
    

}

static void draw(void) {
    // button
    draw_button(backButton);
    draw_button(buyButton);

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
    

    al_draw_text(
        P2_FONT,
        al_map_rgb(225, 225, 225),
        SCREEN_W / 2,
        100 + 31,
        ALLEGRO_ALIGN_CENTER,
        "SHOP"
    );
    al_draw_text(
        P2_FONT,
        al_map_rgb(225, 225, 225),
        SCREEN_W / 2,
        100 + 31,
        ALLEGRO_ALIGN_CENTER,
        "SHOP"
    );
}

static void destroy(void) {
    destroy_button(&backButton);
    destroy_button(&buyButton);
  
}

Scene create_shop_scene(void) {
    Scene scene;
    memset(&scene, 0, sizeof(Scene));

    scene.name = "shop";
    scene.init = &init;
    scene.draw = &draw;
    scene.update = &update;
    scene.destroy = &destroy;

    return scene;
}
