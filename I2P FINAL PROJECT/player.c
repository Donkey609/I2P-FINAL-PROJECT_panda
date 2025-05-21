#include "player.h"
#include "game.h"
#include "utility.h"
#include "map.h"
#include "losing_scene.h"
#include "setting_scene.h"

int health_obtained;

#include <math.h>
// AKU TAMBAHIN TIMER COUNTDOWN
//static int timer_countdown;
static bool isCollision(Player* player, Map* map);
static ALLEGRO_SAMPLE* hit_sound;
static ALLEGRO_SAMPLE* stun_sound;
int lose;
NavigationMode current_navigation_mode = NAVIGATION_WASD;

Player create_player(char * path, int row, int col){
    Player player;
    memset(&player, 0, sizeof(player));
    
    player.coord = (Point){
        col * TILE_SIZE,
        row * TILE_SIZE
    };
    
    player.speed = 4;
    player.health = 50;
    
    player.image = al_load_bitmap(path);
    if(!player.image){
        game_abort("Error Load Bitmap with path : %s", path);
    }
    hit_sound = al_load_sample("Assets/audio/bonk.mp3"); // HIT SOUND BUAT PLAYER
    if (!hit_sound) {
        game_abort("Failed to load hit sound");
    }
    stun_sound = al_load_sample("Assets/audio/electro.mp3"); // HIT SOUND BUAT PLAYER
    if (!hit_sound) {
        game_abort("Failed to load hit sound");
    }
    return player;
}

void update_player(Player * player, Map* map){

    Point original = player->coord;

    if (player->status == PLAYER_DYING) {
        player->animation_tick %= 40;
        lose = 1;
        return;
    }
    // stun
    if (player->isStunned) {
        if (player->stunTimer > 0) {
            player->stunTimer--;
        }
        else {
            player->isStunned = false; 
        }
        return; // skip kalo player di stun
    }
    //knockback
    if(player->knockback_CD > 0){

        player->knockback_CD--;
        int next_x = player->coord.x + player->speed * cos(player->knockback_angle);
        int next_y = player->coord.y + player->speed * sin(player->knockback_angle);
        Point next;
        next = (Point){next_x, player->coord.y};
        
        if(!isCollision(player, map)){
            player->coord = next;
        }
        
        next = (Point){player->coord.x, next_y};
        if(!isCollision(player, map)){
            player->coord = next;
        }
    }
    
    player->status = PLAYER_IDLE;
    /*
        [TODO HACKATHON 1-1] 
        
        Player Movement
        Adjust the movement by player->speed

        if (keyState[ALLEGRO_KEY_W]) {
            player->coord.y = ...
            player->direction = ...
        }
        if (keyState[ALLEGRO_KEY_S]) {
            player->coord.y = ...
            player->direction = ...
        }
    */
    if (current_navigation_mode == NAVIGATION_WASD) {
        if (keyState[ALLEGRO_KEY_W]) {
            player->coord.y = player->coord.y - player->speed;
            player->direction = UP;
            player->status = PLAYER_WALKING;
        }
        if (keyState[ALLEGRO_KEY_S]) {
            player->coord.y = player->coord.y + player->speed;
            player->direction = DOWN;
            player->status = PLAYER_WALKING;
        }

        // if Collide, snap to the grid to make it pixel perfect
        if (isCollision(player, map)) {
            player->coord.y = round((float)original.y / (float)TILE_SIZE) * TILE_SIZE;
        }

        /*
            [TODO HACKATHON 1-2]

            Player Movement
            Add/Subtract the movement by player->speed

            if (keyState[ALLEGRO_KEY_A]) {
                player->coord.y = ...
                player->direction = ...
            }
            if (keyState[ALLEGRO_KEY_D]) {
                player->coord.y = ...
                player->direction = ...

        }
        */
        if (keyState[ALLEGRO_KEY_A]) {
            player->coord.x = player->coord.x - player->speed;
            player->direction = LEFT;
            player->status = PLAYER_WALKING;
        }
        if (keyState[ALLEGRO_KEY_D]) {
            player->coord.x = player->coord.x + player->speed;
            player->direction = RIGHT;
            player->status = PLAYER_WALKING;
        }

        if (isCollision(player, map)) {
            player->coord.x = round((float)original.x / (float)TILE_SIZE) * TILE_SIZE;
        }
    }
    else if (current_navigation_mode == NAVIGATION_ARROW) {
        if (keyState[ALLEGRO_KEY_UP]) {
            player->coord.y = player->coord.y - player->speed;
            player->direction = UP;
            player->status = PLAYER_WALKING;
        }
        if (keyState[ALLEGRO_KEY_DOWN]) {
            player->coord.y = player->coord.y + player->speed;
            player->direction = DOWN;
            player->status = PLAYER_WALKING;
        }

        // if Collide, snap to the grid to make it pixel perfect
        if (isCollision(player, map)) {
            player->coord.y = round((float)original.y / (float)TILE_SIZE) * TILE_SIZE;
        }

        /*
            [TODO HACKATHON 1-2]

            Player Movement
            Add/Subtract the movement by player->speed

            if (keyState[ALLEGRO_KEY_A]) {
                player->coord.y = ...
                player->direction = ...
            }
            if (keyState[ALLEGRO_KEY_D]) {
                player->coord.y = ...
                player->direction = ...

        }
        */
        if (keyState[ALLEGRO_KEY_LEFT]) {
            player->coord.x = player->coord.x - player->speed;
            player->direction = LEFT;
            player->status = PLAYER_WALKING;
        }
        if (keyState[ALLEGRO_KEY_RIGHT]) {
            player->coord.x = player->coord.x + player->speed;
            player->direction = RIGHT;
            player->status = PLAYER_WALKING;
        }

        if (isCollision(player, map)) {
            player->coord.x = round((float)original.x / (float)TILE_SIZE) * TILE_SIZE;
        }
    }
    
    
    /*
        [TODO Homework] 
        
        Calculate the animation tick to draw animation later
    */
    
    
    //INI YG AKU TAMBAHIN -> ERROR
    
   //if (player->health <= 0 && player->status == PLAYER_DYING) {
   //     // Optionally, you can add a delay before transitioning to the game over screen
   //     if (timer_countdown <= 0) {
   //         // Change to the losing scene
   //         printf("Transitioning to losing scene...\n");
   //         change_scene(create_losing_scene());  // Assuming `create_losing_scene` is a function that creates the game over scene
   //     }
   // }
   // timer_countdown--;
}

void draw_player(Player * player, Point cam){
    int dy = player->coord.y - cam.y; // destiny y axis
    int dx = player->coord.x - cam.x; // destiny x axis
    
    
    /*
        [TODO Homework] 
        
        Draw Animation of Dying, Walking, and Idle
    */
    //INI AKU TAMBAHIN
    
    player->animation_tick++;
    if (player->status == PLAYER_IDLE) {
        player->animation_tick %= 20;
    }
    else if (player->status == PLAYER_WALKING) {
        player->animation_tick %= 40;
    }

    ALLEGRO_COLOR tintColor = al_map_rgb(255, 255, 255); // sebelum dipukul
    if (player->isHit) {
        tintColor = al_map_rgb(255, 0, 0); // red if udh dipukul
        player->hitTimer--;
        if (player->hitTimer <= 0) {
            player->isHit = false; 
        }
    }
    if (player->isStunned) {
        tintColor = al_map_rgb(128, 0, 128); // purple if udh distun
        player->stunTimer--;
        if (player->stunTimer <= 0) {
            player->isStunned = false;
        }
    }

    int frame = (player->animation_tick / 10) % 4; 
    int src_x = frame * 32; 
    int src_y = player->status * 32; 

    int flag = 0;
    if (player->direction == LEFT)
        flag = ALLEGRO_FLIP_HORIZONTAL;

    
    al_draw_tinted_scaled_bitmap(
        player->image, tintColor,
        src_x, src_y, 32, 32, 
        dx, dy, TILE_SIZE, TILE_SIZE, 
        flag 
    );
    
#ifdef DRAW_HITBOX
    al_draw_rectangle(
        dx, dy, dx + TILE_SIZE, dy + TILE_SIZE,
        al_map_rgb(255, 0, 0), 1
    );
#endif
    
}


void delete_player(Player * player){
    al_destroy_bitmap(player->image);
    al_destroy_sample(hit_sound);
    al_destroy_sample(stun_sound);
}

static bool isCollision(Player* player, Map* map){

    if (player->coord.x < 0 ||
        player->coord.y < 0 ||
        (player->coord.x + TILE_SIZE - 1) / TILE_SIZE >= map->col ||
        (player->coord.y + TILE_SIZE - 1) / TILE_SIZE >= map->row)
        return true;
    int left = player->coord.x / TILE_SIZE;
    int right = (player->coord.x + TILE_SIZE - 1) / TILE_SIZE;
    int top = player->coord.y / TILE_SIZE;
    int bottom = (player->coord.y + TILE_SIZE - 1) / TILE_SIZE;
    /*

        [TODO HACKATHON 2-1] 
    
        Check every corner of enemy if it's collide or not

        We check every corner if it's collide with the wall/hole or not
        You can activate DRAW_HITBOX in utility.h to see how the collision work

        if(!isWalkable(map->map[...][...])) return true;
        if(!isWalkable(map->map[...][...])) return true;
        if(!isWalkable(map->map[...][...])) return true;
        if(!isWalkable(map->map[...][...])) return true;

    */
    if (!isWalkable(map->map[top][left])) return true;
    if (!isWalkable(map->map[top][right])) return true;
    if (!isWalkable(map->map[bottom][left])) return true;
    if (!isWalkable(map->map[bottom][right])) return true;
    
    return false;
}

void hitPlayer(Player * player, Point enemy_coord, int damage){
    if(player->knockback_CD == 0){
        float dY = player->coord.y - enemy_coord.y;
        float dX = player->coord.x - enemy_coord.x;
        float angle = atan2(dY, dX);

        /*
            [TODO Homework]
            
            Game Logic when the player get hit or die

            player->knockback_angle = angle;
            player->knockback_CD = 32;

            player->health = ...
            if(player->health <= 0){

                player->health = 0;
                player->status = ...

                ...
            }
        */

        player->knockback_angle = angle;
        player->knockback_CD = 32;
        player->isHit = true;
        player->hitTimer = 10;

        player->health -= damage;
        health_obtained = player->health;
        if (player->health <= 0) {

            player->health = 0;
            player->status = PLAYER_DYING;
            //timer_countdown = 60;
            
        }
        else
        {
            player->status = PLAYER_IDLE;
            float volume = 1.0; // Set volume to 50%
            al_play_sample(hit_sound, volume, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            
        }
       
        
    }
}
void stunPlayer(Player* player, Point enemy_coord, int damage) {
    if (player->knockback_CD == 0) {
        float dY = player->coord.y - enemy_coord.y;
        float dX = player->coord.x - enemy_coord.x;
        float angle = atan2(dY, dX);

        player->knockback_angle = angle;
        player->knockback_CD = 10;
        player->isStunned = true;
        player->stunTimer = 40;

        player->health -= damage;
        health_obtained = player->health;
        if (player->health <= 0) {

            player->health = 0;
            player->status = PLAYER_DYING;

        }
        else
        {
            player->status = PLAYER_IDLE;
            float volume = 1.0; // Set volume to 50%
            al_play_sample(stun_sound, volume, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

        }


    }
}
