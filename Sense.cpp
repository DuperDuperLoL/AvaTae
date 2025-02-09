#pragma once
struct Sense {
    ConfigLoader* cl;
    XDisplay* display;
    Level* level;
    LocalPlayer* localPlayer;
    std::vector<Player*>* players;

    Sense(ConfigLoader* cl, XDisplay* display, Level* level, LocalPlayer* localPlayer, std::vector<Player*>* players) {
        this->cl = cl;
        this->display = display;
        this->level = level;
        this->localPlayer = localPlayer;
        this->players = players;
    }

    void modifyHighlights() {
        if (!this->cl->FEATURE_SENSE_ON)return;
        const long highlightSettingsPtr = mem::Read<long>(OFF_REGION + OFF_GLOW_HIGHLIGHTS, "Sense highlights settings ptr");
        const long highlightSize = 0x34;
        { //player highlight - visible 
            int highlightId = 0;
            const GlowMode newGlowMode = {
                cl->SENSE_ENEMY_VISIBLE_BODY_STYLE,
                cl->SENSE_ENEMY_VISIBLE_BORDER_STYLE,
                cl->SENSE_ENEMY_VISIBLE_BORDER_WIDTH,
                127
            };
            const GlowMode oldGlowMode = mem::Read<GlowMode>(highlightSettingsPtr + (highlightSize * highlightId) + 0, "Sense old oldGlowMode");
            if (newGlowMode != oldGlowMode)
                mem::Write<GlowMode>(highlightSettingsPtr + (highlightSize * highlightId) + 0, newGlowMode);
            Color newColor = {
                cl->SENSE_ENEMY_VISIBLE_COLOR_RED,
                cl->SENSE_ENEMY_VISIBLE_COLOR_GREEN,
                cl->SENSE_ENEMY_VISIBLE_COLOR_BLUE
            };
            const Color oldColor = mem::Read<Color>(highlightSettingsPtr + (highlightSize * highlightId) + 4, "Sense old oldColor");
            if (oldColor != newColor)
                mem::Write<Color>(highlightSettingsPtr + (highlightSize * highlightId) + 4, newColor);
        }
        { //player highlight - invisible
            int highlightId = 1;
            const GlowMode newGlowMode = {
                cl->SENSE_ENEMY_INVISIBLE_BODY_STYLE,
                cl->SENSE_ENEMY_INVISIBLE_BORDER_STYLE,
                cl->SENSE_ENEMY_INVISIBLE_BORDER_WIDTH,
                127
            };
            const GlowMode oldGlowMode = mem::Read<GlowMode>(highlightSettingsPtr + (highlightSize * highlightId) + 0, "Sense old oldGlowMode");
            if (newGlowMode != oldGlowMode)
                mem::Write<GlowMode>(highlightSettingsPtr + (highlightSize * highlightId) + 0, newGlowMode);
            Color newColor = {
                cl->SENSE_ENEMY_INVISIBLE_COLOR_RED,
                cl->SENSE_ENEMY_INVISIBLE_COLOR_GREEN,
                cl->SENSE_ENEMY_INVISIBLE_COLOR_BLUE
            };
            const Color oldColor = mem::Read<Color>(highlightSettingsPtr + (highlightSize * highlightId) + 4, "Sense old oldColor");
            if (oldColor != newColor)
                mem::Write<Color>(highlightSettingsPtr + (highlightSize * highlightId) + 4, newColor);
        }
        { //player highlight - aimbot locked
            int highlightId = 2;
            const GlowMode newGlowMode = {
                cl->SENSE_ENEMY_LOCKEDON_BODY_STYLE,
                cl->SENSE_ENEMY_LOCKEDON_BORDER_STYLE,
                cl->SENSE_ENEMY_LOCKEDON_BORDER_WIDTH,
                127
            };
            const GlowMode oldGlowMode = mem::Read<GlowMode>(highlightSettingsPtr + (highlightSize * highlightId) + 0, "Sense old oldGlowMode");
            if (newGlowMode != oldGlowMode)
                mem::Write<GlowMode>(highlightSettingsPtr + (highlightSize * highlightId) + 0, newGlowMode);
            Color newColor = { cl->SENSE_ENEMY_LOCKEDON_COLOR_RED,cl->SENSE_ENEMY_LOCKEDON_COLOR_GREEN,cl->SENSE_ENEMY_LOCKEDON_COLOR_BLUE };
            const Color oldColor = mem::Read<Color>(highlightSettingsPtr + (highlightSize * highlightId) + 4, "Sense old oldColor");
            if (oldColor != newColor)
                mem::Write<Color>(highlightSettingsPtr + (highlightSize * highlightId) + 4, newColor);
        }

        const GlowMode newGlowModeShieldBased = { 2,113,80,127 };
        { //player highlight | shields = 0 
            int highlightId = 3;
            const GlowMode oldGlowMode = mem::Read<GlowMode>(highlightSettingsPtr + (highlightSize * highlightId) + 0, "Sense old oldGlowMode");
            if (newGlowModeShieldBased != oldGlowMode)
                mem::Write<GlowMode>(highlightSettingsPtr + (highlightSize * highlightId) + 0, newGlowModeShieldBased);
            Color newColor = { 0,10,0 };
            const Color oldColor = mem::Read<Color>(highlightSettingsPtr + (highlightSize * highlightId) + 4, "Sense old oldColor");
            if (oldColor != newColor)
                mem::Write<Color>(highlightSettingsPtr + (highlightSize * highlightId) + 4, newColor);
        }
        { //player highlight | shields <= 50  
            int highlightId = 4;
            const GlowMode oldGlowMode = mem::Read<GlowMode>(highlightSettingsPtr + (highlightSize * highlightId) + 0, "Sense old oldGlowMode");
            if (newGlowModeShieldBased != oldGlowMode)
                mem::Write<GlowMode>(highlightSettingsPtr + (highlightSize * highlightId) + 0, newGlowModeShieldBased);
            Color newColor = { 10,10,10 };
            const Color oldColor = mem::Read<Color>(highlightSettingsPtr + (highlightSize * highlightId) + 4, "Sense old oldColor");
            if (oldColor != newColor)
                mem::Write<Color>(highlightSettingsPtr + (highlightSize * highlightId) + 4, newColor);
        }
        { //player highlight | shields <= 75  
            int highlightId = 5;
            const GlowMode oldGlowMode = mem::Read<GlowMode>(highlightSettingsPtr + (highlightSize * highlightId) + 0, "Sense old oldGlowMode");
            if (newGlowModeShieldBased != oldGlowMode)
                mem::Write<GlowMode>(highlightSettingsPtr + (highlightSize * highlightId) + 0, newGlowModeShieldBased);
            Color newColor = { 0,5,10 };
            const Color oldColor = mem::Read<Color>(highlightSettingsPtr + (highlightSize * highlightId) + 4, "Sense old oldColor");
            if (oldColor != newColor)
                mem::Write<Color>(highlightSettingsPtr + (highlightSize * highlightId) + 4, newColor);
        }
        { //player highlight | shields <= 100  
            int highlightId = 6;
            const GlowMode oldGlowMode = mem::Read<GlowMode>(highlightSettingsPtr + (highlightSize * highlightId) + 0, "Sense old oldGlowMode");
            if (newGlowModeShieldBased != oldGlowMode)
                mem::Write<GlowMode>(highlightSettingsPtr + (highlightSize * highlightId) + 0, newGlowModeShieldBased);
            Color newColor = { 5,0,10 };
            const Color oldColor = mem::Read<Color>(highlightSettingsPtr + (highlightSize * highlightId) + 4, "Sense old oldColor");
            if (oldColor != newColor)
                mem::Write<Color>(highlightSettingsPtr + (highlightSize * highlightId) + 4, newColor);
        }
        { //player highlight | shields <= 125 
            int highlightId = 7;
            const GlowMode oldGlowMode = mem::Read<GlowMode>(highlightSettingsPtr + (highlightSize * highlightId) + 0, "Sense old oldGlowMode");
            if (newGlowModeShieldBased != oldGlowMode)
                mem::Write<GlowMode>(highlightSettingsPtr + (highlightSize * highlightId) + 0, newGlowModeShieldBased);
            Color newColor = { 10,0,0 };
            const Color oldColor = mem::Read<Color>(highlightSettingsPtr + (highlightSize * highlightId) + 4, "Sense old oldColor");
            if (oldColor != newColor)
                mem::Write<Color>(highlightSettingsPtr + (highlightSize * highlightId) + 4, newColor);
        }
        { //player highlight - friendlies
            int highlightId = 8;
            const GlowMode oldGlowMode = mem::Read<GlowMode>(highlightSettingsPtr + (highlightSize * highlightId) + 0, "Sense old oldGlowMode");
            GlowMode myGm = { 112, 6, 32, 127 };
            if (myGm != oldGlowMode)
                mem::Write<GlowMode>(highlightSettingsPtr + (highlightSize * highlightId) + 0, myGm);
            Color newColor = { 1,1,0 };
            const Color oldColor = mem::Read<Color>(highlightSettingsPtr + (highlightSize * highlightId) + 4, "Sense old oldColor");
            if (oldColor != newColor)
                mem::Write<Color>(highlightSettingsPtr + (highlightSize * highlightId) + 4, newColor);
        }

        //item highlights
        for (int highlightId = 9; highlightId <= 70; highlightId++) {
            if(highlightId !=55)
            {
            	const GlowMode newGlowMode = { 137,0,0,127 };
            	const GlowMode oldGlowMode = mem::Read<GlowMode>(highlightSettingsPtr + (highlightSize * highlightId) + 0, "Sense old oldGlowMode");
            	if (newGlowMode != oldGlowMode)
            	mem::Write<GlowMode>(highlightSettingsPtr + (highlightSize * highlightId) + 0, newGlowMode);
            }
        }
    }

    void glowPlayers() {
        if (!this->cl->FEATURE_SENSE_ON)return;
        for (int i = 0; i < players->size(); i++) {
            Player* p = players->at(i);
            if (!p->isValid()) continue;
            if (p->enemy) {
                if (cl->SENSE_ENEMY_COLOR_SHIELD_BASED) p->glowShieldBased();
                else p->glow();
            }
            else
                p->glowFriendly();
        }
    }

};
