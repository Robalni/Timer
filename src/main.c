#include <SDL.h>
#include <SDL_ttf.h>
#include <stdbool.h>
#include <string.h>

struct delay_info {
  double delta_time;
  int current_tick;
  int next_frame_tick;
  int fps_wanted;
};

void delay(struct delay_info* di);

int main(int argc, char** argv)
{
  int updates_per_second = 100;
  int win_width = 200;
  int win_height = 50;

  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
  SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS, "1");
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
  TTF_Init();
  SDL_Window* win = SDL_CreateWindow("Timer", SDL_WINDOWPOS_UNDEFINED,
                                     SDL_WINDOWPOS_UNDEFINED,
                                     win_width, win_height,
                                     SDL_WINDOW_RESIZABLE);
  if (!win) {
    return 1;
  }
  SDL_Renderer* rend = SDL_CreateRenderer(win, -1, 0);
  if (!rend) {
    return 1;
  }
  SDL_RenderSetLogicalSize(rend, win_width, win_height);
  TTF_Font* font = TTF_OpenFont("font", 100);
  if (!font) {
    printf("TTF_OpenFont: %s\n", TTF_GetError());
    return 1;
  }
  SDL_Color text_color = {.r = 0x99, .g = 0x99, .b = 0x99, .a = 0xff};

  bool running = true;
  struct delay_info di = {.fps_wanted = updates_per_second};
  SDL_Joystick* joy = SDL_JoystickOpen(0);
  char time_str[100];
  int timer_started_ms = 0;
  int timer_at_ms = 0;
  bool timer_running = false;
  int seconds = 0;
  while (running) {
    int sec = timer_at_ms / 1000 % 60;
    int min = timer_at_ms / 1000 / 60;
    if (timer_running) {
      snprintf(time_str, sizeof time_str, "%02d:%02d.xx", seconds/60, seconds%60);
    } else {
      int subsec = timer_at_ms % 1000 / 10;
      snprintf(time_str, sizeof time_str, "%02d:%02d.%02d", min, sec, subsec);
    }

    SDL_RenderClear(rend);
    SDL_Surface* surf = TTF_RenderText_Blended(font, time_str, text_color);
    SDL_Texture* text_text = SDL_CreateTextureFromSurface(rend, surf);
    SDL_FreeSurface(surf);
    SDL_RenderCopy(rend, text_text, NULL, NULL);
    SDL_RenderPresent(rend);

    if (timer_running) {
      seconds++;
    }

    bool render_now = false;
    for (int i = 0; i < updates_per_second && running && !render_now; i++) {
      if (timer_running) {
        timer_at_ms = SDL_GetTicks() - timer_started_ms;
      }
      SDL_Event event;
      while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
          running = false;
          break;
        case SDL_JOYBUTTONDOWN:
          if (event.jbutton.button == 7) {
            timer_started_ms = SDL_GetTicks();
            if (timer_at_ms != 0 && !timer_running) {
              timer_at_ms = 0;
              seconds = 0;
            } else {
              timer_running = !timer_running;
            }
            render_now = true;
          }
          break;
        }
      }
      delay(&di);
    }
  }

  TTF_CloseFont(font);
  SDL_JoystickClose(joy);
  SDL_DestroyRenderer(rend);
  SDL_DestroyWindow(win);
  TTF_Quit();
  SDL_Quit();
  return 0;
}

void delay(struct delay_info* di)
{
  int new_tick = SDL_GetTicks();
  di->delta_time = (new_tick - di->current_tick) / 1000.0;
  di->current_tick = new_tick;
  di->next_frame_tick += 1000.0 / di->fps_wanted;
  if (di->next_frame_tick < di->current_tick) {
    di->next_frame_tick = di->current_tick;
  }
  SDL_Delay(di->next_frame_tick - di->current_tick);
}
