#include "display.h"

display::display(const std::string &title, int width, int height) {
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height,
                              SDL_WINDOW_SHOWN | SDL_RENDERER_ACCELERATED);
    if (window == nullptr) {
        std::cerr << "Couldn't initialize the window. Reason: " << SDL_GetError() << std::endl;
    }
    std::cout << "Window created." << std::endl;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Couldn't initialize the renderer. Reason: " << SDL_GetError() << std::endl;
    }
    std::cout << "Renderer initialized." << std::endl;
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, constants::SCREEN_WIDTH,
                                constants::SCREEN_HEIGHT);
    if (texture == nullptr) {
        std::cerr << "Couldn't initialize the texture. Reason: " << SDL_GetError() << "\n";
    }
    std::cout << "Texture initialized." << std::endl;

    std::cout << "Display initialized." << std::endl;
}

display::~display() {
    SDL_DestroyTexture(texture);
    std::cout << "Texture destroyed." << std::endl;
    SDL_DestroyRenderer(renderer);
    std::cout << "Renderer destroyed." << std::endl;
    SDL_DestroyWindow(window);
    std::cout << "Window destroyed." << std::endl;
    std::cout << "Display destroyed." << std::endl;
}

void display::render(uint32_t *screen) {
    SDL_UpdateTexture(texture, nullptr, screen, constants::SCREEN_WIDTH * sizeof(uint32_t));
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
}

void display::change_name(const std::string &name) {
    if (window != nullptr) {
        SDL_SetWindowTitle(window, name.c_str());
    }
}

SDL_Window *display::getWindow() const {
    return window;
}

display::display() : display("CH80S", constants::SCREEN_WIDTH * constants::SCALE,
                             constants::SCREEN_HEIGHT * constants::SCALE) {}
