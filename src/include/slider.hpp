#include <include/core_funcs.hpp>
class Slider {
    public:
    int pos[2];
    SDL_Surface *bar_surf;
    SDL_Surface *slider_surf;
    SDL_Rect bar_rect;
    SDL_Rect slider_rect;
    SDL_Rect dstbar;
    SDL_Rect dstslider;
    int value;
    int offset;
    void init(int pos_[2]){
        offset = 0;
        value = 0;
        pos[0] = pos_[0];
        pos[1] = pos_[1];
        bar_surf = SDL_CreateRGBSurface(0,100,20,32,0,0,0,SDL_ALPHA_OPAQUE);
        slider_surf = SDL_CreateRGBSurface(0,10,40,32,0,0,0,SDL_ALPHA_OPAQUE);
        bar_rect.x = 0;
        bar_rect.y = 0;
        bar_rect.w = 100;
        bar_rect.h = 20;
        slider_rect.x = 0;
        slider_rect.y = 0;
        slider_rect.w = 10;
        slider_rect.h = 40;
        dstslider.x = pos[0];
        dstslider.y = pos[1];
        dstslider.w = 10;
        dstslider.h = 40;
        dstbar.x = pos[0];
        dstbar.y = pos[1]+10;
        dstbar.w = 100;
        dstbar.h = 20;
        SDL_FillRect(bar_surf, &bar_rect, blue);
        SDL_FillRect(slider_surf, &slider_rect, white);
    }
    void update(){
        SDL_BlitSurface(bar_surf, &bar_rect, window_surface, &dstbar);
        SDL_BlitSurface(slider_surf, &slider_rect, window_surface, &dstslider);
        if (SDL_PointInRect(&mousepos, &dstbar) == SDL_TRUE){
            if (button_state&SDL_BUTTON(1)){
                dstslider.x = mouse_pos[0];
                offset = mouse_pos[0]-pos[0];
                value = offset/10;
            }
        }
        //cout << value << endl;
    }
};