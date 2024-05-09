#pragma once
#include <unistd.h>
struct TriggerBot {
    ConfigLoader* cl;
    XDisplay* display;
    Level* level;
    LocalPlayer* localPlayer;
    std::vector<Player*>* players;
    bool zoomdelay = false;
    const float TB_MAX_RANGE_ZOOMED = util::metersToGameUnits(250);
    const float TB_MAX_RANGE_HIPFRE = util::metersToGameUnits(20);

    TriggerBot(ConfigLoader* cl, XDisplay* display, Level* level, LocalPlayer* localPlayer, std::vector<Player*>* players) {
        this->cl = cl;
        this->display = display;
        this->level = level;
        this->localPlayer = localPlayer;
        this->players = players;
    }

    void shootAtEnemy() {
        if (!cl->FEATURE_TRIGGERBOT_ON) return;
        if (!localPlayer->isCombatReady()) return;

        //only these weapons will work with trigger bot
        int weaponId = localPlayer->weaponIndex;
        // printf("Last weapon held: %s id: %d \n", WeaponName(weaponId).c_str(), weaponId);
        if (
            weaponId != WEAPON_KRABER &&
            weaponId != WEAPON_P2020 &&
            weaponId != WEAPON_MOZAMBIQUE &&
            weaponId != WEAPON_EVA8 &&
            weaponId != WEAPON_PEACEKEEPER &&
            weaponId != WEAPON_MASTIFF &&
            weaponId != WEAPON_WINGMAN &&
            weaponId != WEAPON_LONGBOW &&
            weaponId != WEAPON_SENTINEL &&
            weaponId != WEAPON_G7 &&
            weaponId != WEAPON_HEMLOCK &&
            weaponId != WEAPON_3030 &&
            weaponId != WEAPON_TRIPLE_TAKE &&
            weaponId != WEAPON_PROWLER &&
            weaponId != WEAPON_SNIPERS_MARK &&
            weaponId != WEAPON_THROWING_KNIFE
            )return;

        //max range changes based on if we are zoomed in or not
        const float RANGE_MAX = (localPlayer->inZoom) ? TB_MAX_RANGE_ZOOMED : TB_MAX_RANGE_HIPFRE;
	int delayseconds = 0;
	if (weaponId == WEAPON_KRABER)
	   delayseconds = 1000000;
        else if (weaponId == WEAPON_SENTINEL || weaponId == WEAPON_LONGBOW)
           delayseconds = 600000;
        else
           delayseconds = 100000;
           
	if (localPlayer->inZoom && zoomdelay == false)
	{
	 usleep(delayseconds);
	 zoomdelay = true;
	}
	if (!localPlayer->inZoom)
	zoomdelay = false;      
	     
        for (int i = 0; i < players->size(); i++) {
            Player* player = players->at(i);
            if (!player->isCombatReady()) continue;
            if (!player->enemy) continue;
            if (!player->aimedAt) continue;
            if (player->distanceToLocalPlayer < RANGE_MAX) {
                display->mouseClickLeft();
                break;
            }
        }
    }
};
