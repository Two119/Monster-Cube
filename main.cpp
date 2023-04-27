#include <include/game.hpp>
int music_delay = 0;
int main( int argc, char* args[] ) {
    initiliaze();
    while (playing){
        scoredelay += 1;
        music_delay += 1;
        framestart = SDL_GetTicks();
        SDL_RenderClear(renderer);
        background_image.blit(bgpos);
        button_state = SDL_GetMouseState(&mouse_pos[0], &mouse_pos[1]);
        keyboard_state = SDL_GetKeyboardState(NULL);
        mousepos = {mouse_pos[0], mouse_pos[1]};
        if (!Mix_Playing(1)) bgsound.play(1);
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                playing = false;
            }
        }
        renderer_.update();
        //button.update(test_func);
        //slider.update();
        speed = "Speed: "+to_string(sqrt((renderer_.player.velocity[0]*renderer_.player.velocity[0])+(renderer_.player.velocity[1]*renderer_.player.velocity[1])));
        population = "Total creatures (including dead): "+to_string(renderer_.player.population);
        killcount = "Dead: " + to_string(renderer_.player.killcount);
        score_s = "Score: " + to_string(score);
        if (scores.size() > 0)    max_score = "High Score: " + to_string(*max_element(scores.begin(), scores.end()));
        speed_counter.render(speed.c_str(), counter_pos);
        speed_counter.render(population.c_str(), counter_pos2);
        speed_counter.render(killcount.c_str(), counter_pos3);
        speed_counter.render(score_s.c_str(), counter_pos4);
        speed_counter.render("Background music by soundcloud.com/yyyn0889", counter_pos6);
        if (scores.size() > 0)speed_counter.render(max_score.c_str(), counter_pos5);
        //cursor_img.blit(mouse_pos);
        SDL_RenderPresent(renderer);
        frametime = SDL_GetTicks()-framestart;
        if (framedelay > frametime){
            SDL_Delay(framedelay - frametime);
        }
        if (scoredelay %60 == 0 && renderer_.player.killcount==0) score += 1;
    }
    return 0;
}