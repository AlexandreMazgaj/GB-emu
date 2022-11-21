#include <stdio.h>
#include "headers/gb_cpu.h"
#include "headers/gb_mmu.h"
#include "headers/opcodes.h"
#include "headers/gb_ppu.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


void drawScreen(SDL_Surface *surface)
{
    SDL_LockSurface(surface);
    uint32_t *pixels = (uint32_t *)surface->pixels;
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        for (int j = 0; j < SCREEN_WIDTH; j++) {
            pixels[i*SCREEN_WIDTH + j] = ppu.screen[i*SCREEN_WIDTH + j] == 0 ? 0 : 0xFFFFFFFF;
            // pixels[i*SCREEN_WIDTH + j] = 0xFFFFFFFF;
        }
    }
    SDL_UnlockSurface(surface);
}




int main() {

    CPU_init();
    MMU_init();

    uint8_t error = loadCartridge("/home/IBEO.AS/ama/pers_workspace/GB/GB-emu/roms/05-op_rp.gb");

    if (error)
        return 9;


    SDL_Surface *gameboyGraphics = NULL;
    SDL_Surface *scaledGraphics = NULL;



    //The window we'll be rendering to
    SDL_Window* window = NULL;
    
    //The surface contained by the window
    SDL_Surface* screenSurface = NULL;


    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_EVENTS) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }
    window = SDL_CreateWindow("GAME BOY", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH*2, SCREEN_HEIGHT*2,
                              SDL_WINDOW_SHOWN);
    SDL_SetWindowResizable(window, SDL_TRUE);
    if( window == NULL ){
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        return 1;
    } 

    TTF_Init();


    TTF_Font *font = TTF_OpenFont("fonts/arial/arial.ttf", 11);

    SDL_Color color = { 255, 255, 255 };

    SDL_Surface * text_surface = TTF_RenderText_Solid(font, "Welcome to Gigi Labs", color);

    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);


    // used to display text
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, text_surface);


    // SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);


    //Get window surface
    screenSurface = SDL_GetWindowSurface( window );

    gameboyGraphics = SDL_CreateRGBSurface(0, DISPLAY_WIDTH, DISPLAY_HEIGHT, 32, 0, 0, 0, 0);
    scaledGraphics = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0, 0, 0, 0);


    SDL_RenderPresent(renderer);


    // //Update the surface
    // SDL_UpdateWindowSurface( window );

    SDL_Delay( 100 );
    unsigned int t1;
    unsigned int t2;
    unsigned int elapsed;
    int          remaining;
    unsigned int interval = 1000 / TICKS;

    Uint8* keys = SDL_GetKeyboardState(NULL);

    uint8_t emuRun = 0;
    uint8_t oneByOne = 0;

    SDL_Event e;



    printf("Everything is ready, lauching emulator\n");

    // printf("rom[213] = %X\n", mmu.rom[0x213]);

    // FILE *file = fopen("output_rom.txt", "w");


    // for (int i = 0; i < 1000; i++) {
    //     fprintf(file, "rom[%X] = %X\n", i, mmu.rom[i]);
    // }

    // fclose(file);


    while (1) {

        t1 = SDL_GetTicks();

        if (emuRun) {
            if (CPU_clock() == 220) {
                // emuRun = 0;
            }

            PPU_clock();
        }
        else {
            if (oneByOne) {
                while (!CPU_clock());
                PPU_clock();
                oneByOne = 0;
            }
        }

        if ((SDL_PollEvent(&e)) != 0) {
            if (e.type == SDL_QUIT) {
                break;
            }
            // Start or pause the emulation
            if (e.type == SDL_KEYDOWN && keys[SDL_SCANCODE_SPACE]) {
                emuRun ^= 1;
            }

            if (e.type == SDL_KEYDOWN && keys[SDL_SCANCODE_B]) {
                break;
            }

            if (e.type == SDL_KEYDOWN && keys[SDL_SCANCODE_Y]) {
              oneByOne = 1;
            }

            if (e.type == SDL_KEYDOWN && keys[SDL_SCANCODE_P]) {
                printRegisters();
            }
        }
        

        if (0) {
            drawScreen(gameboyGraphics);
            SDL_BlitScaled(gameboyGraphics, NULL, scaledGraphics, NULL);
            // Update the intermediate texture with the contents of the RGBA buffer.
            SDL_UpdateTexture(texture, NULL, scaledGraphics->pixels, scaledGraphics->pitch);
            SDL_RenderClear(renderer);
            // SDL_RenderCopy(renderer, texture, NULL, NULL);
            SDL_RenderPresent(renderer);
            //Update the surface
            SDL_UpdateWindowSurface( window );

            // mip.draw_flag = 0;
        }

        t2 = SDL_GetTicks();
        elapsed = t2 - t1;
        remaining = interval - elapsed;
        if (remaining > 0) {
            // SDL_Delay(remaining/2);
            elapsed = interval;
        }
    }

    SDL_DestroyWindow( window );
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(text_surface);
    TTF_CloseFont(font);

    //Quit SDL subsystems
    SDL_Quit();


    return 0;
}