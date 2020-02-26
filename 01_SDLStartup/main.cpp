#include <thread>
#include <chrono>
#include <SDL.h>

int SDL_main(int argc, char** arg) {
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer);

	SDL_RenderClear(renderer);
	SDL_Rect* rect = new SDL_Rect;
	rect->x = 0;
	rect->y = 0;
	rect->w = 200;
	rect->h = 200;
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer, rect);
	SDL_RenderPresent(renderer);

	std::this_thread::sleep_for(std::chrono::seconds(5));

	delete rect;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}