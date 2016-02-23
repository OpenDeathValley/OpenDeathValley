#include "odv_sdl_test.h"

SDL_Texture *odv_sdl_map(const char *filename, SDL_Renderer *renderer)
{
    struct ODVMap *mfile = NULL;
    SDL_Surface *surface = NULL;
    SDL_Texture *tex = NULL;

    fprintf(stderr, "[+] odv_map_open = %s\n", filename);
    mfile = odv_map_open(filename);
    if (mfile == NULL)
        return NULL;
    surface = SDL_CreateRGBSurface(0, mfile->img->width, mfile->img->height, 16, 0, 0, 0, 0);
    if (surface == NULL) {
        fprintf(stderr, "[-] SDL_CreateRGBSurface error: %s\n", SDL_GetError());
        return NULL;
    }
    SDL_LockSurface(surface);
    memcpy(surface->pixels, mfile->img->buf, mfile->img->width * mfile->img->height * 2);
    SDL_UnlockSurface(surface);
    tex = SDL_CreateTextureFromSurface(renderer, surface);
    if (tex == NULL) {
        fprintf(stderr, "[-] SDL_CreateTextureFromSurface error: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        return NULL;
    }
    SDL_FreeSurface(surface);
    odv_map_close(mfile);
    return tex;
}

SDL_Texture *odv_sdl_dvm(const char *filename, SDL_Renderer *renderer)
{
    struct ODVDvm *dvm = NULL;
    SDL_Surface *surface = NULL;
    SDL_Texture *tex = NULL;

    fprintf(stderr, "[+] odv_dvm_open = %s\n", filename);
    dvm = odv_dvm_open(filename);
    if (dvm == NULL)
        return NULL;
    surface = SDL_CreateRGBSurface(0, dvm->img->width, dvm->img->height, 16, 0, 0, 0, 0);
    if (surface == NULL) {
        fprintf(stderr, "[-] SDL_CreateRGBSurface error: %s\n", SDL_GetError());
        return NULL;
    }
    SDL_LockSurface(surface);
    memcpy(surface->pixels, dvm->img->buf, dvm->img->width * dvm->img->height * 2);
    SDL_UnlockSurface(surface);
    tex = SDL_CreateTextureFromSurface(renderer, surface);
    if (tex == NULL) {
        fprintf(stderr, "[-] SDL_CreateTextureFromSurface error: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        return NULL;
    }
    SDL_FreeSurface(surface);
    odv_dvm_close(dvm);
    return tex;
}

SDL_Texture *odv_sdl_sxt(const char *filename, SDL_Renderer *renderer)
{
    struct ODVSxt *sxt = NULL;
    SDL_Surface *surface = NULL;
    SDL_Texture *tex = NULL;

    fprintf(stderr, "[+] odv_sxt_open = %s\n", filename);
    sxt = odv_sxt_open(filename);
    if (sxt == NULL)
        return NULL;
    surface = SDL_CreateRGBSurface(0, sxt->img->width, sxt->img->height, 16, 0, 0, 0, 0);
    if (surface == NULL) {
        fprintf(stderr, "[-] SDL_CreateRGBSurface error: %s\n", SDL_GetError());
        return NULL;
    }
    SDL_LockSurface(surface);
    memcpy(surface->pixels, sxt->img->buf, sxt->img->width * sxt->img->height * 2);
    SDL_UnlockSurface(surface);
    tex = SDL_CreateTextureFromSurface(renderer, surface);
    if (tex == NULL) {
        fprintf(stderr, "[-] SDL_CreateTextureFromSurface error: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        return NULL;
    }
    SDL_FreeSurface(surface);
    odv_sxt_close(sxt);
    return tex;
}

void odv_rend_texture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y)
{
    int w, h;
    SDL_Rect dst;
    
    SDL_QueryTexture(tex, NULL, NULL, &w, &h);
    dst.x = x;
    dst.y = y;
    dst.w = w;
    dst.h = h;
    SDL_RenderCopy(ren, tex, NULL, &dst);
}

void help(void)
{
    printf("OPTION:\n");
    printf("\t-m: map interface (*.map)\n");
    printf("\t-v: map (*.dvm)\n");
    printf("\t-x: screen win/loose (*.sxt)\n");
}

void sdl_loop(SDL_Window *win, SDL_Renderer *renderer, SDL_Texture *tex)
{
    SDL_Event event;
    int quit = 0x00;
    int mouse_move = 0x00;
    int mouse_x = 0x00;
    int mouse_y = 0x00;
    int diff_x = 0x00;
    int diff_y = 0x00;
    int pos_x = 0x00;
    int pos_y = 0x00;
    
    SDL_ShowWindow(win);
    while (quit == 0x00) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 0x01;
            }
            switch (event.type) {
                case SDL_MOUSEBUTTONDOWN:
                    mouse_move = 1;
                    mouse_x = event.button.x;
                    mouse_y = event.button.y;
                    break;
                case SDL_MOUSEBUTTONUP:
                    mouse_move = 0;
                    diff_x = 0;
                    diff_y = 0;
                    break;
                case SDL_MOUSEMOTION:
                    if (mouse_move) {
                        pos_x -= diff_x;
                        pos_y -= diff_y;
                        diff_x = event.motion.x - mouse_x;
                        diff_y = event.motion.y - mouse_y;
                        pos_x += diff_x;
                        pos_y += diff_y;
                    }
                    break;
            }
        }
        SDL_RenderClear(renderer);
        odv_rend_texture(tex, renderer, pos_x, pos_y);
        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }
}

int main(int argc, char *argv[])
{
    SDL_Window *win = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *tex = NULL;
    

    if (argc < 3) {
        fprintf(stderr, "[-] Usage: %s OPTION FILE\n", argv[0]);
        help();
    }
    if (argv[1][0] != '-') {
        help();
    }
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        fprintf(stderr, "[-] SDL_Init error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    win = SDL_CreateWindow("ODV SDL TEST", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_HIDDEN);
    if (win == NULL) {
        fprintf(stderr, "[-] SDL_CreateWindow error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        fprintf(stderr, "[-] SDL_CreateRenderer error: %s\n", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    switch (argv[1][1]) {
        case 'm':
            tex = odv_sdl_map(argv[2], renderer);
            break;
        case 'v':
            tex = odv_sdl_dvm(argv[2], renderer);
            break;
        case 'x':
            tex = odv_sdl_sxt(argv[2], renderer);
            break;
        default:
            help();
            break;
    }
    if (tex == NULL) {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(win);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    sdl_loop(win, renderer, tex);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}