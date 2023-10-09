#include <stdio.h>
#include <SDL.h>
#include <math.h>

#define pi 3.142857

int s_width;
int s_height;
int x_eyes_1 = 0, x_eyes_2 = 0, y_eyes_1 = 0, y_eyes_2 = 0;
int mousex, mousey;
int key_pressed;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

void mouse_pointer(int x, int y) {
    mousex = x;
    mousey = y;
    x_eyes_1 = 20 * cos(atan2(x - (s_width / 2 - 100), y - (s_height / 2 - 75)));
    x_eyes_2 = 20 * cos(atan2(x - (s_width / 2 + 100), y - (s_height / 2 - 75)));
    y_eyes_1 = 20 * sin(atan2(x - (s_width / 2 - 100), y - (s_height / 2 - 75)));
    y_eyes_2 = 20 * sin(atan2(x - (s_width / 2 + 100), y - (s_height / 2 - 75)));
}

void keyboard(SDL_Event event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_b:
                key_pressed = 98;  // 'b'
                break;
            case SDLK_c:
                key_pressed = 99;  // 'c'
                break;
            case SDLK_h:
                key_pressed = 104; // 'h'
                break;
            case SDLK_s:
                key_pressed = 115; // 's'
                break;
            case SDLK_o:
                key_pressed = 111; // 'o'
                break;
            default:
                break;
        }
    }
    else if (event.type == SDL_KEYUP) {
        key_pressed = 0;
    }
}

void myInit(void) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL initialization failed: %s\n", SDL_GetError());
        exit(1);
    }

    s_width = 800;
    s_height = 600;

    window = SDL_CreateWindow("Emo-Interactive Emoji", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, s_width, s_height, 0);
    if (!window) {
        printf("SDL window creation failed: %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("SDL renderer creation failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }
}

void drawCircle(int x, int y, int radius) {
    int numSegments = 100;
    double angle = 2 * pi / numSegments;

    for (int i = 0; i < numSegments; i++) {
        double x1 = x + radius * cos(i * angle);
        double y1 = y + radius * sin(i * angle);
        double x2 = x + radius * cos((i + 1) * angle);
        double y2 = y + radius * sin((i + 1) * angle);
        SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
    }
}

void display(void) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);

    if (key_pressed == 98 || key_pressed == 99) {
        x_eyes_1 = x_eyes_2 = y_eyes_1 = y_eyes_2 = 0;
    }

    // Draw the base emoji outline
    for (double i = 0; i < (2 * pi); i += 0.01) {
        int x = s_width / 2 + 220 * cos(i);
        int y = s_height / 2 + 220 * sin(i);
        drawCircle(x, y, 1);
    }

    // Draw the eyes which follow the mouse pointer
    for (double i = 0; i < (2 * pi); i += 0.01) {
        int x = -x_eyes_1 + s_width / 2 - 100 + (10 * cos(i));
        int y = y_eyes_1 + s_height / 2 - 75 + (10 * sin(i));
        int z = -x_eyes_2 + (s_width / 2) + 100 + ((10 * cos(i)));
        int w = y_eyes_2 + (s_height / 2) - 75 + (10 * sin(i));

        drawCircle(x, y, 1);
        drawCircle(z, w, 1);
    }

    // Draw the center of the eye
    SDL_RenderDrawPoint(renderer, -x_eyes_1 + s_width / 2 - 100, y_eyes_1 + s_height / 2 - 75);
    SDL_RenderDrawPoint(renderer, -x_eyes_2 + s_width / 2 + 100, y_eyes_2 + s_height / 2 - 75);

    SDL_RenderPresent(renderer);
}

int main(int argc, char** argv) {
    myInit();

    SDL_Event event;
    while (1) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                SDL_Quit();
                return 0;
            }
            else if (event.type == SDL_MOUSEMOTION) {
                mouse_pointer(event.motion.x, event.motion.y);
            }
            else if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
                keyboard(event);
            }
        }

        display();
    }

    return 0;
}