#ifndef map_h
#define map_h

#include <stdint.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "utility.h"


// IF YOU WANT TO INCREASE YOUR MAP SIZE OR ENEMY SIZE MAKE SURE TO INCREASE DEFINE VARIABLE BELOW IF IT EXCEED THE MAXIMUM
#define MAX_MAP_ROW 100
#define MAX_MAP_COL 100
#define MAX_ENEMY_SPAWN 100

/*
    Map Tiles type
    Hint : Some type might need a background, to configure it try to modify "get_map_offset(Map * map)"
*/
typedef enum _BLOCK_TYPE{
    FLOOR,
    WALL,
    DOOR_CLOSE,
    HOLE,
    COIN,
    TROPHY,
    APPLE,
    NOTHING
} BLOCK_TYPE;

typedef enum _COIN_STATUS {
    APPEAR,
    DISAPPEARING,
    DISAPPEAR
} COIN_STATUS;

typedef enum _TROPHY_STATUS {
    T_APPEAR,
    T_DISAPPEAR
} TROPHY_STATUS;

typedef enum _APPLE_STATUS {
    A_APPEAR,
    A_DISAPPEAR 
} APPLE_STATUS;

// Map Struct
typedef struct Map_{
    uint8_t ** map; // Map array
    Point ** offset_assets; // Assets
    COIN_STATUS coin_status[MAX_MAP_ROW][MAX_MAP_COL];
    TROPHY_STATUS trophy_status[MAX_MAP_ROW][MAX_MAP_COL];
    APPLE_STATUS apple_status[MAX_MAP_ROW][MAX_MAP_COL];
    int row, col;
    
    // Map assets
    ALLEGRO_BITMAP* assets;
    ALLEGRO_BITMAP* coin_assets;
    ALLEGRO_BITMAP* trophy_assets;
    ALLEGRO_BITMAP* apple_assets;


    // Coin Properties
    ALLEGRO_SAMPLE* coin_audio;
    uint8_t coin_ani_tick;
    uint8_t coin_ani_tick_disappear[MAX_MAP_ROW][MAX_MAP_COL];
    
    //trophy properties
    ALLEGRO_SAMPLE* trophy_audio;
    uint8_t trophy_ani_tick;
    uint8_t trophy_ani_tick_disappear[MAX_MAP_ROW][MAX_MAP_COL];

    ////APPLE-> HEALTH
    ALLEGRO_SAMPLE* apple_audio;
    uint8_t apple_ani_tick;
    uint8_t apple_ani_tick_disappear[MAX_MAP_ROW][MAX_MAP_COL];

    // Spawn Coordinate
    Point Spawn;
    Point EnemySpawn[MAX_ENEMY_SPAWN];
    char EnemyCode[MAX_ENEMY_SPAWN];
    uint8_t EnemySpawnSize;

} Map;

/*
    MAP FUNCTION
    Feel free to add more if you have some idea or interaction with the map
 */
Map create_map(char * path, uint8_t type); // Create a map based on given file path
void draw_map(Map * map, Point cam); // Draw the map
void update_map(Map * map, Point player_coord, /*Player * player,*/ int * total_coins, int * total_trophies, int * total_health); //aku 
void destroy_map(Map * map); // Destroy map

bool isWalkable(BLOCK_TYPE block);

#endif /* map_h */
