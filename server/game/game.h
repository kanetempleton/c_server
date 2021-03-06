#ifndef H_GAME
#define H_GAME
#define MAX_PLAYERS 30
#define MAX_NPCS 1000
#define START_X 245
#define START_Y 246
#define MAP_WIDTH 14
#define MAP_HEIGHT 12
#include "entity/player/player.h"
#include "../util/HashMap.h"
#include "entity/npc/NPC.h"
typedef struct {
    int * numPlayers;
    int * nextPlayerId;
    Player * players[MAX_PLAYERS];

    int * numNPCs;
    int * nextNPCId;
    Npc * npcs[MAX_NPCS];
    HashMap* playersByMapSection;
} Game;
Game* newGame();
void initGame(Game* g);
void deleteGame(Game* g);
void addPlayer(Game* g,char* name, int fd); //plan to be obsolete
void addPlayerToGame(Game* g, Player* p);
void removePlayer(Game* g,int id);
void addPlayerToMapTable(Game* g, Player* p);
void removePlayerFromMapTable(Game* g, Player* p);
void broadcastExistenceInMapSection(Game* g, Player* p, int fromX, int fromY);
void fetchPlayersInMapSection(Game* g, Player*  p);
void removePlayerFromMapSection(Game* g, Player* p, int oldSec, int sendCurPos);
void * runGame(void * arg);
Player * getPlayer_fd(Game* g,int fd); //probably should never use this
Player * getPlayer_id(Game* g, int id);
Player * getPlayer_name(Game*g, char* n);
Player * getPlayer(Game* g, int plid); //probably just gonna use this one
int fetchID(Game* g);
void logoutPlayer(Game* g, Player* p);
int computeMapDataSection(int x, int y);
void saveMapdata(int section, char* data);
void actionToPlayersInMapSection(Game* g, int sec, void (*v)(), Player* plrArg, void* arg);


//NPC methods
void spawnNPC(Game* g, int id, int x, int y, int z);

/* autospawnNPCs():
    spawns all NPCs that should be present when the server is started
    autospawn data is stored in data/npc/spawn.txt
*/
void autospawnNPCs(Game* g);
#endif
