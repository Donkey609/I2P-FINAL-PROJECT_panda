#include <allegro5/allegro.h>
#include "menu_scene.h"
#include "utility.h"
#include "UI.h"
#include "game.h"
#include "player.h"
#include "shop_scene.h"

static Button backButton;
static Button buyButton;
static ALLEGRO_BITMAP* player_bitmap;
static ALLEGRO_SAMPLE* buy_sound;
int coins_obtained;
int health_obtained;

static ALLEGRO_BITMAP* heart_image;
static ALLEGRO_BITMAP* coin_image;

bool sniperBuy;
bool thanks = false;
static void init(void) {

    player_bitmap = al_load_bitmap("Assets/sniperblack.png");
    backButton = button_create(SCREEN_W / 2 - 200, 650, 400, 100, "Assets/UI_Button.png", "Assets/UI_Button_hovered.png");
    buyButton = button_create(SCREEN_W / 2 - 100, 500, 200, 100, "Assets/UI_Button.png", "Assets/UI_Button_hovered.png");

    heart_image = al_load_bitmap("Assets/heart.png");
    if (!heart_image) {
        game_abort("Failed to load heart image");
    }

    coin_image = al_load_bitmap("Assets/coin_icon.png");
    if (!coin_image) {
        game_abort("Failed to load coin image");
    }
    buy_sound = al_load_sample("Assets/audio/buy.mp3"); 
    if (!buy_sound) {
        game_abort("Failed to load buy sound");
    }
    change_bgm("Assets/audio/MASK.mp3");

}

static void update(void) {

    update_button(&backButton);
    update_button(&buyButton); 


    if (mouseState.buttons && backButton.hovered == true) {
        change_scene(create_menu_scene());
    }
    if (mouseState.buttons && buyButton.hovered == true && coins_obtained == 10) {
        sniperBuy = true;
        thanks = true;
        coins_obtained -= 10;
        al_play_sample(buy_sound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
    }
    /*if (mouseState.buttons && BuyButton.hovered == true) {
        
    }*/
    

}

static void draw(void) {
    float desired_height = 24.0f; // Font size is 24

    float heart_scale = 4 * (desired_height / al_get_bitmap_height(heart_image));
    float coin_scale = 4 * (desired_height / al_get_bitmap_height(coin_image));
    al_draw_scaled_bitmap(heart_image,
        0, 0, al_get_bitmap_width(heart_image), al_get_bitmap_height(heart_image),
        10, 10,
        al_get_bitmap_width(heart_image) * heart_scale,
        al_get_bitmap_height(heart_image) * heart_scale,
        0);

    al_draw_textf(
        P1_FONT,
        al_map_rgb(255, 255, 255),
        100, 35,
        ALLEGRO_ALIGN_LEFT,
        "%0.2d", health_obtained
    );


    al_draw_scaled_bitmap(coin_image,
        0, 0, al_get_bitmap_width(coin_image), al_get_bitmap_height(coin_image),
        10, 70,
        al_get_bitmap_width(coin_image) * coin_scale,
        al_get_bitmap_height(coin_image) * coin_scale,
        0);

    al_draw_textf(
        P1_FONT,
        al_map_rgb(255, 255, 255),
        100, 100,
        ALLEGRO_ALIGN_LEFT,
        "%0.2d", coins_obtained
    );
    // button
    draw_button(backButton);
    draw_button(buyButton);

    al_draw_scaled_bitmap(player_bitmap,
        0, 0, 800, 490, //ori size of picture
        SCREEN_W / 2 - 200, SCREEN_H / 3 - 50, //destination position buat y ama x
        400, 245, //lebar ama tinggi
        0);

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
    
    //BUY
    al_draw_text(
        P2_FONT,
        al_map_rgb(66, 76, 110),
        SCREEN_W / 2,
        500 + 28 + buyButton.hovered * 11,
        ALLEGRO_ALIGN_CENTER,
        "BUY 10c"
    );
    al_draw_text(
        P2_FONT,
        al_map_rgb(255, 0, 0),
        SCREEN_W / 2,
        500 + 31 + buyButton.hovered * 11,
        ALLEGRO_ALIGN_CENTER,
        "BUY 10c"
    );

    al_draw_text(
        P2_FONT,
        al_map_rgb(225, 225, 225),
        SCREEN_W / 2,
        100 + 31,
        ALLEGRO_ALIGN_CENTER,
        "SHOP"
    );
    if (thanks) {
        al_draw_text(
            P2_FONT,
            al_map_rgb(0, 255, 0), // Green color for the message
            SCREEN_W / 2,
            SCREEN_H / 2, // Center the message vertically
            ALLEGRO_ALIGN_CENTER,
            "OBTAINED!"
        );
    }
}

static void destroy(void) {
    destroy_button(&backButton);
    destroy_button(&buyButton);
    al_destroy_bitmap(player_bitmap); 
    al_destroy_sample(buy_sound);
  
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
