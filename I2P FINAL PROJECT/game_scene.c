#include <string.h>
#include "game_scene.h"
#include "menu_scene.h"
#include "loading_scene.h"
#include "game.h"
#include "player.h"
#include "map.h"
#include "enemy.h"
#include "weapon.h"
#include "UI.h"
#include "losing_scene.h"
#include "winning_scene.h"
#include "map.h"
#include <math.h>
#include "shop_scene.h"

Player player; // Player
Map map; // Map
static ALLEGRO_BITMAP* heart_image;
static ALLEGRO_BITMAP* coin_image;
enemyNode * enemyList; // Enemy List
BulletNode * bulletList; // Bullet List


// Weapon
Weapon weapon; 
int coins_obtained; 
int trophies_obtained;
int health_obtained;

int win = 0;
int lose = 0;

static void init(void){
    coins_obtained = 0;
    health_obtained = 50;
    initEnemy();
    map = create_map("Assets/map0.txt", 0);
    player = create_player("Assets/panda.png", map.Spawn.x, map.Spawn.y);

    heart_image = al_load_bitmap("Assets/heart.png");
    if (!heart_image) {
        game_abort("Failed to load heart image");
    }

    coin_image = al_load_bitmap("Assets/coin_icon.png");
    if (!coin_image) {
        game_abort("Failed to load coin image");
    }

    enemyList = createEnemyList();
    bulletList = createBulletList();

    weapon = create_weapon("Assets/guns.png", "Assets/yellow_bullet.png", 16, 8, 10); // Default weapon

    
    for(int i=0; i<map.EnemySpawnSize; i++){
        Enemy enemy = createEnemy(map.EnemySpawn[i].x, map.EnemySpawn[i].y, map.EnemyCode[i]);
        insertEnemyList(enemyList, enemy);
    }

    game_log("coord x:%d \n coords y:%d \n", map.Spawn.x, map.Spawn.y);
    change_bgm("Assets/audio/persona.mp3");
}

static void update(void){
    /*
        [TODO Homework]
        
        Change the scene if winning/losing to win/lose scene
    */
    if (keyState[ALLEGRO_KEY_1] && sniperBuy == true) {
        delete_weapon(&weapon);
        weapon = create_weapon("Assets/guns.png", "Assets/yellow_bullet.png", 16, 8, 10); // Default weapon    }
    }
    else if (keyState[ALLEGRO_KEY_2] && sniperBuy == true) {
        delete_weapon(&weapon);
        weapon = create_weapon("Assets/sniper.png", "Assets/yellow_bullet.png", 24, 15, 20);
    }
    //INI AKU TAMBAHIN MASIH ERROR
    if (win) {
        win = 0;
        al_rest(1.0);
        change_scene(create_winning_scene());
        return;
    }

    if (lose) {
        lose = 0;
        coins_obtained = 0;
        al_rest(1.0);
        change_scene(create_losing_scene());
        return; //JGN LUPA RETURN AHAHA
    }
    //sampe sini
    update_player(&player, &map);

    Point Camera;
    /*
        [TODO HACKATHON 1-3]
        
        Calcualte the formula for the Camera
        Camera.x = ...
        Camera.y = ...

        Hint: Adjust it based on player position variable, then subtract it with half of the gameplay screen
    */
    

    Camera = (Point){ 0, 0 };
    Camera.x = player.coord.x - (SCREEN_W / 2) + (TILE_SIZE / 2);
    Camera.y = player.coord.y - (SCREEN_H / 2) + (TILE_SIZE / 2);

    

    updateEnemyList(enemyList, &map, &player);
    update_weapon(&weapon, bulletList, player.coord, Camera);
    updateBulletList(bulletList, enemyList, &map);
    update_map(&map, player.coord, /*&player,*/ &coins_obtained, &trophies_obtained, &health_obtained);
    
}
void health_coins(Player* player, int coins_obtained) {
    float desired_height = 24.0f; //-->font
    if (player->health < health_obtained) player->health = health_obtained;
    
    float heart_scale = 4* (desired_height / al_get_bitmap_height(heart_image));
    float coin_scale = 4* (desired_height / al_get_bitmap_height(coin_image));

    // Health
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
        "%0.2d", player->health
    );

    //coin
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
}
static void draw(void){
    Point Camera;
    /*
        [TODO HACKATHON 1-4]
        
        Calcualte the formula for the Camera
        Camera.x = ...
        Camera.y = ...

        Hint: Just copy from the [TODO HACKATHON 1-3]
    */
    Camera = (Point){ 0, 0 };
    Camera.x = player.coord.x - (SCREEN_W / 2) + (TILE_SIZE/2);
    Camera.y = player.coord.y - (SCREEN_H / 2) + (TILE_SIZE / 2);
    // Draw
    draw_map(&map, Camera);
    drawEnemyList(enemyList, Camera);
    drawBulletList(bulletList, Camera);
    draw_player(&player, Camera);
    draw_weapon(&weapon, player.coord, Camera); // sniper
    health_coins(&player, coins_obtained); 
    /*
        [TODO Homework]
        
        Draw the UI of Health and Total Coins
    */
    //BLM BISA MASUK KE GEM SCREEN
    printf("Health: %d%%\n", player.health); // buat cek animasi doang
    printf("Coins: %d\n", coins_obtained);
}

static void destroy(void){
    delete_player(&player);
    delete_weapon(&weapon);
    destroy_map(&map);
    al_destroy_bitmap(heart_image);
    al_destroy_bitmap(coin_image);
    destroyBulletList(bulletList);
    destroyEnemyList(enemyList);
    terminateEnemy();
}


Scene create_game_scene(void){
    Scene scene;
    memset(&scene, 0, sizeof(Scene));
    
    scene.name = "game";
    scene.init = &init;
    scene.draw = &draw;
    scene.update = &update;
    scene.destroy = &destroy;
    
    return scene;
}
