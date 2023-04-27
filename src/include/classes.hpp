#include <include/core_funcs.hpp>
class Enemy{
    public:
    double pos[2];
    int npos[2];
    Image surf;
    SDL_Rect rect;
    SDL_Rect rect2;
    SDL_Rect rect3;
    Uint32 color_1 = (255<<24) + (int(0)<<16) + (int(0)<<8) + int(150);
    Uint32 color_2 = (255<<24) + (int(0)<<16) + (int(0)<<8) + int(100);
    Uint32 color_3 = (255<<24) + (int(0)<<16) + (int(0)<<8) + int(50);
    double velocity[2] = {0, 0};
    int dir[2] = {0, 0};
    int spinspeed = 3;
    double acceleration = 0.05;
    double angle = 0.00;
    int delay = 0;
    bool alive = true;
    void init(double vel[2], int dir_[2], double pos_[2]){
        surf.init(SDL_CreateRGBSurface(0,64,64,32,0,0,0,SDL_ALPHA_OPAQUE));
        rect.x = 0;
        rect.y = 0;
        rect.w = 64;
        rect.h = 64;
        rect2.x = 8;
        rect2.y = 8;
        rect2.w = 48;
        rect2.h = 48;
        rect3.x = 18;
        rect3.y = 18;
        rect3.w = 28;
        rect3.h = 28;
        velocity[0] = vel[0];
        velocity[1] = vel[1];
        dir[0] = dir_[0];
        dir[1] = dir_[1];
        pos[0] = pos_[0]+(64*dir[0]);
        pos[1] = pos_[1]+(64*dir[1]);
        surf.dstrect.x = pos[0];
        surf.dstrect.y = pos[1];
        SDL_FillRect(surf.tex_surf, &rect, color_1);
        SDL_FillRect(surf.tex_surf, &rect2, color_2);
        SDL_FillRect(surf.tex_surf, &rect3, color_3);
        surf.init(surf.tex_surf);
    }
    void update(vector<SDL_Rect> border_rects){
        if (alive){
            if (delay < 300) delay += 1;
            
            if (SDL_HasIntersection(&surf.dstrect, &border_rects[0])==SDL_TRUE) {
                dir[0] = 1; 
                if (velocity[0] < 0){
                    velocity[0]*=-1;
                }
            }
            if (SDL_HasIntersection(&surf.dstrect, &border_rects[1])==SDL_TRUE) {
                dir[0] = -1; 
                if (velocity[0] > 0){
                    velocity[0]*=-1;
                }
            }
            if (SDL_HasIntersection(&surf.dstrect, &border_rects[2])==SDL_TRUE) {
                dir[1] = 1; 
                if (velocity[1] < 0){
                    velocity[1]*=-1;
                }
            }
            if (SDL_HasIntersection(&surf.dstrect, &border_rects[3])==SDL_TRUE) {
                dir[1] = -1; 
                if (velocity[1] > 0){
                    velocity[1]*=-1;
                }
            }
            velocity[0]+=(acceleration*dir[0]);
            velocity[1]+=(acceleration*dir[1]);
            pos[0]+=velocity[0];
            pos[1]+=velocity[1];
            surf.dstrect.x = pos[0];
            surf.dstrect.y = pos[1];
            npos[0] = pos[0];
            npos[1] = pos[1];
            surf.blit(npos);
        }
    }
};
vector<Enemy> enemies;
class Player{
    public:
    double pos[2] = {624-32, 336-32};
    int pos2[2] = {1060, 10};
    int npos[2];
    string delays;
    Image surf;
    SDL_Rect rect;
    SDL_Rect rect2;
    SDL_Rect rect3;
    Uint32 color_1 = (255<<24) + (int(255)<<16) + (int(0)<<8) + int(50);
    Uint32 color_2 = (255<<24) + (int(255)<<16) + (int(0)<<8) + int(100);
    Uint32 color_3 = (255<<24) + (int(255)<<16) + (int(0)<<8) + int(150);
    double velocity[2] = {0, 0};
    int dir[2] = {0, 0};
    int spinspeed = 3;
    double acceleration = 0.05;
    double angle = 0.00;
    int delay = 0;
    int choices[2] = {-1, 1};
    int killcount = 0;
    int population = 0;
    void init(){
        surf.init(SDL_CreateRGBSurface(0,64,64,32,0,0,0,SDL_ALPHA_OPAQUE));
        rect.x = 0;
        rect.y = 0;
        rect.w = 64;
        rect.h = 64;
        rect2.x = 8;
        rect2.y = 8;
        rect2.w = 48;
        rect2.h = 48;
        rect3.x = 18;
        rect3.y = 18;
        rect3.w = 28;
        rect3.h = 28;
        SDL_FillRect(surf.tex_surf, &rect, color_1);
        SDL_FillRect(surf.tex_surf, &rect2, color_2);
        SDL_FillRect(surf.tex_surf, &rect3, color_3);
        surf.init(surf.tex_surf);
        surf.dstrect.x = pos[0];
        surf.dstrect.y = pos[1];
    }
    void update(vector<SDL_Rect> border_rects){
        delays = "You can brake in: "+ to_string((900-delay)/60.0);
        speed_counter.render(delays.c_str(), pos2);
        if (killcount == 0){
            if (delay < 900) delay += 1;
            if(keyboard_state[SDL_SCANCODE_LEFT]){
                dir[0] = -1; 
                if (velocity[0] > 0){
                    velocity[0]*=-1;
                }
            }
            if(keyboard_state[SDL_SCANCODE_RIGHT]){
                dir[0] = 1; 
                if (velocity[0] < 0){
                    velocity[0]*=-1;
                }
            }
            if(keyboard_state[SDL_SCANCODE_UP]){
                dir[1] = -1; 
                if (velocity[1] > 0){
                    velocity[1]*=-1;
                }
            }
            if(keyboard_state[SDL_SCANCODE_DOWN]){
                dir[1] = 1; 
                if (velocity[1] < 0){
                    velocity[1]*=-1;
                }
            }
            if (keyboard_state[SDL_SCANCODE_SPACE] && 900-delay==0){
                dir[0] = 0; 
                dir[1] = 0;
                velocity[0] = 0;
                velocity[1] = 0;
                delay = 0;
            }
            if (dir[0]==0 && dir[1]==0 && 180-delay == 0){
                dir[Random::get(0, 1)] = choices[Random::get(0, 1)];
            }
            if (SDL_HasIntersection(&surf.dstrect, &border_rects[0])==SDL_TRUE) {
                dir[0] = 1; 
                if (velocity[0] < 0){
                    velocity[0]*=-1;
                }
                Enemy enem;
                enem.init(velocity, dir, pos);
                enemies.push_back(enem);
                enem.surf.dstrect.x = enem.pos[0];
                enem.surf.dstrect.y = enem.pos[1];
                population += 1;
                bouncesound.play();
                //audioPlayer.stop();
            }
            if (SDL_HasIntersection(&surf.dstrect, &border_rects[1])==SDL_TRUE) {
                dir[0] = -1; 
                if (velocity[0] > 0){
                    velocity[0]*=-1;
                }
                Enemy enem;
                enem.init(velocity, dir, pos);
                enemies.push_back(enem);
                enem.surf.dstrect.x = enem.pos[0];
                enem.surf.dstrect.y = enem.pos[1];
                population += 1;
                bouncesound.play();
               // audioPlayer.stop();
            }
            if (SDL_HasIntersection(&surf.dstrect, &border_rects[2])==SDL_TRUE) {
                dir[1] = 1; 
                if (velocity[1] < 0){
                    velocity[1]*=-1;
                }
                Enemy enem;
                enem.init(velocity, dir, pos);
                enemies.push_back(enem);
                enem.surf.dstrect.x = enem.pos[0];
                enem.surf.dstrect.y = enem.pos[1];
                population += 1;
                bouncesound.play();
                //audioPlayer.stop();
            }
            if (SDL_HasIntersection(&surf.dstrect, &border_rects[3])==SDL_TRUE) {
                dir[1] = -1; 
                if (velocity[1] > 0){
                    velocity[1]*=-1;
                }
                Enemy enem;
                enem.init(velocity, dir, pos);
                enemies.push_back(enem);
                enem.surf.dstrect.x = enem.pos[0];
                enem.surf.dstrect.y = enem.pos[1];
                population += 1;
                bouncesound.play();
                //audioPlayer.stop();
            }
            velocity[0]+=(acceleration*dir[0]);
            velocity[1]+=(acceleration*dir[1]);
            pos[0]+=velocity[0];
            pos[1]+=velocity[1];
        }
        surf.dstrect.x = pos[0];
        surf.dstrect.y = pos[1];
        npos[0] = pos[0];
        npos[1] = pos[1];
        surf.blit(npos);
    }
};

class Card{
    public:
    int pos[2];
    bool collected = false;
    SDL_Rect rect;
    bool gift = false;
    int frame = 0;
    int delay = 0;
    int loc[2] = {0, 0};
    Image cardimg;
    void init(int pos_[2], int gift_){
        if (gift_<3) gift = true;
        pos[0] = pos_[0];
        pos[1] = pos_[1];
        rect.x = pos_[0];
        rect.y = pos_[1];
        rect.w = card_sprites.size[0];
        rect.h = card_sprites.size[1];
    }
    void update(){
        loc[0] = frame;
        if (!gift) cardimg.init_tex(card_sprites.get(loc));
        else cardimg.init_tex(card_sprites2.get(loc));
        delay += 1;
        if (delay%15 == 0) frame += 1;
        if (frame > 3) frame = 0;
        cardimg.blit(pos);
    }
};

class ObjectRenderer{
    public:
    int init_render_pos[2] = {32, 32};
    int final_render_pos[2] = {1248, 672};
    int tile_size[2] = {64, 64};
    int map_size[2] = {19, 10};
    vector<SDL_Rect> border_rects;
    vector<vector<int>> map;
    Player player;
    vector<Card> cards = {};
    int delay = 0;
    void init(){
        for (int i = 0; i < map_size[1]; i=i+1){
            vector<int> l = {};
            for (int j = 0; j < map_size[0]; j=j+1){
                int num;
                num = (int)Random::get(0, 10);
                l.push_back(num);
                if (num == 1){
                    Card test;
                    int position[2] = {j*64+32, i*64+32};
                    test.init(position, (int)Random::get(0, 6));
                    cards.push_back(test);
                }
            }
            map.push_back(l);
        }
        SDL_Rect left;
        left.x = 0;
        left.y = 0;
        left.w = 32;
        left.h = 720;
        SDL_Rect right;
        right.x = 1248;
        right.y = 0;
        right.w = 32;
        right.h = 720;
        SDL_Rect top;
        top.x = 0;
        top.y = 0;
        top.w = 1280;
        top.h = 32;
        SDL_Rect bottom;
        bottom.x = 0;
        bottom.y = 688;
        bottom.w = 1280;
        bottom.h = 32;
        border_rects = {left, right, top, bottom};
        int pos[2] = {624-32, 336-32};
        player.init();
    }
    void update(){
        if (player.killcount != 0){
            if (delay < 300){
                delay += 1;
                death_f.render("You Lost!", death_pos);
            }
            else {
                delay = 0;
                player.killcount = 0;
                player.dir[0] = 0;
                player.dir[1] = 0;
                player.velocity[0] = 0;
                player.velocity[1] = 0;
                player.population = 0;
                //double pos[2] = {624-32, 336-32};
                player.pos[0] = 624-32;
                player.pos[1] = 336-32;
                player.delay = 0;
                enemies = {};
                cards = {};
                map = {};
                scores.push_back(score);
                score = 0;
                scoredelay = 0;
                for (int i = 0; i < map_size[1]; i=i+1){
                    vector<int> l = {};
                    for (int j = 0; j < map_size[0]; j=j+1){
                        int num;
                        num = (int)Random::get(0, 10);
                        l.push_back(num);
                        if (num == 1){
                            Card test;
                            int position[2] = {j*64+32, i*64+32};
                            test.init(position, (int)Random::get(0, 6));
                            cards.push_back(test);
                        }
                    }
                    map.push_back(l);
                }
            }
        }
        
        player.update(border_rects);
        for (int j = 0; j < enemies.size(); j+=1){
            if (player.killcount == 0){
                if (enemies[j].alive) enemies[j].update(border_rects);
                if (SDL_HasIntersection(&enemies[j].surf.dstrect, &player.surf.dstrect)==SDL_TRUE){
                    enemies[j].alive = false;
                    
                    player.killcount += 1;
                }
            }
            else {
                enemies[j].surf.dstrect.x = enemies[j].pos[0];
                enemies[j].surf.dstrect.y = enemies[j].pos[1];
                int position_[2] = {enemies[j].pos[0], enemies[j].pos[1]};
                enemies[j].surf.blit(position_);
            }
        }
        int u = -1;
        for (Enemy enem :enemies){
            u+=1;
            if (u > 0) {if (!enem.alive) enemies.erase(enemies.begin()+(u-1));}
            else if (!enem.alive) enemies.erase(enemies.begin());
            
        }
        for (int i = 0; i < cards.size(); i+=1){
            if (!cards[i].collected)  {
                cards[i].update();
                if (SDL_HasIntersection(&cards[i].rect, &player.surf.dstrect)==SDL_TRUE){
                    cards[i].collected = true;
                    cardsound.play();
                    if (cards[i].gift){player.velocity[0]/=10; player.velocity[1]/=10;}
                    else {player.velocity[0]*=2; player.velocity[1]*=2;}
                    //cout << "collected" << endl;
                }
            }
        }
        
    }
};