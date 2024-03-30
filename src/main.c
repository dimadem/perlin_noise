#include "perlin_noise.h"

int main(void)
{
	SDL_Window *window = NULL;
	SDL_Surface *surface = NULL;
	SDL_Event event;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return 1;
	}

	window = SDL_CreateWindow("Perlin Noise", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return 1;
	}

	surface = SDL_GetWindowSurface(window);

	float time = 0;
	int quit = 0;

	while (!quit)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				quit = 1;
		}

		for (int y = 0; y < HEIGHT; y++)
		{
			for (int x = 0; x < WIDTH; x++)
			{
				float nx = (float)x / WIDTH;
				float ny = (float)y / HEIGHT;

				// Vary noise parameters over time
				float freq = 8.0f + 4.0f * sin(time * 0.5f);
				float amp = 0.5f + 0.25f * sin(time * 0.7f);
				int octaves = 4 + (int)(2.0f * sin(time * 0.3f));

				// Scroll noise field
				float scroll_x = time * 0.05f;
				float scroll_y = time * 0.01f;

				float noise = perlin2d(nx + scroll_x, ny + scroll_y, freq, octaves) * amp;

				Uint8 color = (Uint8)((noise + 1) / 2 * 255);

				Uint32 pixel = SDL_MapRGB(surface->format, color, color, color);

				Uint8 *target_pixel = (Uint8 *)surface->pixels + y * surface->pitch + x * 4;
				*(Uint32 *)target_pixel = pixel;
			}
		}

		SDL_UpdateWindowSurface(window);

		// Increment time
		time += 0.01f;
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}