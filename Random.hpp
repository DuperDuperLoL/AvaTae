#pragma once
class Random
{
private:
    ConfigLoader* cl;
    XDisplay* display;
    Level* level;
    LocalPlayer* localPlayer;
    std::vector<Player*>* players;
public:
    Random(ConfigLoader* cl,
          XDisplay* display,
          Level* level,
          LocalPlayer* localPlayer,
          std::vector<Player*>* players
          )
    {
        cl = cl;
        display = display;
        level = level;
        localPlayer = localPlayer;
        players = players;
    }
    //==========---------[SUPERGLIDE]-------------==================
   /* void superGlide(){
        while (display->keyDown(XK_space))
        {
            static float startjumpTime = 0;
            static bool startSg = false;
            static float traversalProgressTmp = 0.0;
 
            float worldtime = mem::Read<float>(m_localPlayer->base + OFFSET_TIME_BASE); // Current time
            float traversalStartTime = mem::Read<float>(m_localPlayer->base + OFFSET_TRAVERSAL_START_TIME); // Time to start wall climbing
            float traversalProgress = mem::Read<float>(m_localPlayer->base + OFFSET_TRAVERSAL_PROGRESS); // Wall climbing, if > 0.87 it is almost over.
            auto HangOnWall = -(traversalStartTime - worldtime);
 
            if (HangOnWall > 0.1 && HangOnWall < 0.12)
            {
                mem::Write<int>(OFF_REGION + OFF_IN_JUMP + 0x8, 4);
            }
            if (traversalProgress > 0.87f && !startSg && HangOnWall > 0.1f && HangOnWall < 1.5f)
            {
                //start SG
                startjumpTime = worldtime;
                startSg = true;
            }
            if (startSg)
            {
                //printf ("sg Press jump\n");
                mem::Write<int>(OFF_REGION + OFF_IN_JUMP + 0x8, 5);
                while (mem::Read<float>(m_localPlayer->base + OFFSET_TIME_BASE) - startjumpTime < 0.011);
                {
                    mem::Write<int>(OFF_REGION + OFF_IN_DUCK + 0x8, 6);
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                    mem::Write<int>(OFF_REGION + OFF_IN_JUMP + 0x8, 4);
                    std::this_thread::sleep_for(std::chrono::milliseconds(600));
                }
                startSg = false;
                break;
            }
        }
 
        // Automatic wall jump
        int wallJumpNow = 0;
 
        static float onWallTmp = 0;
        float onWall = mem::Read<float>(localPlayer->base + OFFSET_WALL_RUN_START_TIME);
        if (onWall > onWallTmp + 0.1) // 0.1
        {
            if (mem::Read<int>(OFF_REGION + OFFSET_IN_FORWARD) == 0)
            {
                wallJumpNow = 1;
                //printf("wall jump Press jump\n");
                mem::Write<int>(OFF_REGION + OFF_IN_JUMP + 0x8, 5);
                std::this_thread::sleep_for(std::chrono::milliseconds(300));
                mem::Write<int>(OFF_REGION + OFF_IN_JUMP + 0x8, 4);
            }
        }
        onWallTmp = onWall;
 
        static float onEdgeTmp = 0;
        float onEdge = mem::Read<float>(localPlayer->base + OFFSET_TRAVERSAL_PROGRESS);
        if (onEdge > onEdgeTmp + 0.1) // 0.1
        {
            if (mem::Read<int>(OFF_REGION + OFFSET_IN_FORWARD) == 0)
            {
                wallJumpNow = 2;
                //printf("wall jump onEdge Press jump\n");
                mem::Write<int>(OFF_REGION + OFF_IN_JUMP + 0x8, 5);
                std::this_thread::sleep_for(std::chrono::milliseconds(300));
                mem::Write<int>(OFF_REGION + OFF_IN_JUMP + 0x8, 4);
            }
        }
        onEdgeTmp = onEdge;    
    }*/


    //==================---------------[SPECTATORVIEW]-------------------==================
    void spectatorView()
    {
        //if(!level->playable) return;
        int spectatorcount = 0;   
        std::vector<std::string> spectatorlist;
        if(cl->FEATURE_SPECTATOR_ON){
            for (int i = 0; i < players->size(); i++)
            { 
                Player *p = players->at(i);          
                      
                float targetyaw = p->view_yaw; // get Yaw player
                float localyaw= localPlayer->local_yaw; // get Yaw LocalPlayer
                //printf("LocalViewYaw: %f == PlayerViewYaw: %f \n", localyaw, targetyaw);
                if (targetyaw == localyaw && p->currentHealth == 0){
                    spectatorcount++;
                    
                }            
            }
            const auto spectatorlist_size = static_cast<int>(spectatorlist.size());
           
            if (spectatorcount > 0){
                {   
                    printf("\n-[%d]-- SPECTATORS -- \n", spectatorcount);
                    for (int i = 0; i < spectatorlist_size; i++)   //show list of spectators by name
                    {   
                        printf("---[%s]---\n", spectatorlist.at(i).c_str());
                    }
                }
            }              
        }      
    }


};
