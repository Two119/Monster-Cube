#pragma once
#include <include/classes.hpp>
ObjectRenderer renderer_;
void initiliaze(){
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    SDL_ShowCursor(SDL_DISABLE);
    IMG_Init(IMG_INIT_JPG || IMG_INIT_PNG);
    int size[2] = {2, 1};
    int size2[2] = {4, 1};
    button_sprites.init(scale_surface(IMG_Load("assets/images/buttons.png")), size, black, 4);
    card_sprites.init(scale_surface(IMG_Load("assets/images/card.png"), 2), size2, black, 2);
    card_sprites2.init(scale_surface(IMG_Load("assets/images/card2.png"), 2), size2, black, 2);
    background_image.init(IMG_Load("assets/images/background.png"));
    speed_counter.init("assets/fonts/stacked_pixel.ttf", 16);
    death_f.init("assets/fonts/stacked_pixel.ttf", 40);
    death_f.fColor.g = 0;
    death_f.fColor.b = 0;
    int loc[2] = {0, 0};
    cursor_img.init(scale_surface(IMG_Load("assets/images/cursor.png"), 2));
    bouncesound.init("assets/sfx/bounce.wav");
    cardsound.init("assets/sfx/card.wav");
    bgsound.init("assets/sfx/background_music.wav");
    bgsound.play(1);
    //bgmusic.play(-1);
    renderer_.init();
    window_rect.x = 0;
    window_rect.y = 0;
    window_rect.w = 1280;
    window_rect.h = 720;
    int pos[2] = {100, 100};
    int pos2[2] = {100, 200};
}