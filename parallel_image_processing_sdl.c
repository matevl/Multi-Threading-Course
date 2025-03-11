#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Structure to pass arguments to the thread function
typedef struct {
    unsigned char *image;
    int width;
    int height;
    int start_row;
    int end_row;
} ImageArgs;

/**
 * Function to convert a portion of the image to grayscale.
 *
 * @param arg Pointer to ImageArgs containing image data and row range.
 * @return NULL
 */
void* convert_to_grayscale(void* arg) {
    ImageArgs* args = (ImageArgs*)arg;
    for (int i = args->start_row; i < args->end_row; ++i) {
        for (int j = 0; j < args->width; ++j) {
            int index = (i * args->width + j) * 3;
            unsigned char gray = 0.3 * args->image[index] + 0.59 * args->image[index + 1] + 0.11 * args->image[index + 2];
            args->image[index] = args->image[index + 1] = args->image[index + 2] = gray;
        }
    }
    pthread_exit(NULL);
}

void parallel_image_processing(unsigned char *image, int width, int height, int num_threads) {
    pthread_t threads[num_threads];
    ImageArgs args[num_threads];
    int rows_per_thread = height / num_threads;

    for (int i = 0; i < num_threads; ++i) {
        args[i].image = image;
        args[i].width = width;
        args[i].height = height;
        args[i].start_row = i * rows_per_thread;
        args[i].end_row = (i == num_threads - 1) ? height : args[i].start_row + rows_per_thread;
        pthread_create(&threads[i], NULL, convert_to_grayscale, &args[i]);
    }

    for (int i = 0; i < num_threads; ++i) {
        pthread_join(threads[i], NULL);
    }
}

int main() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    // Load the PNG image using SDL_image
    SDL_Surface *image_surface = IMG_Load("resources/image1.jpg");
    if (!image_surface) {
        fprintf(stderr, "IMG_Load Error: %s\n", IMG_GetError());
        SDL_Quit();
        return 1;
    }

    // Convert the surface to a format we can manipulate
    SDL_Surface *formatted_surface = SDL_ConvertSurfaceFormat(image_surface, SDL_PIXELFORMAT_RGB24, 0);
    SDL_FreeSurface(image_surface);
    if (!formatted_surface) {
        fprintf(stderr, "SDL_ConvertSurfaceFormat Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Get image dimensions and pixel data
    int width = formatted_surface->w;
    int height = formatted_surface->h;
    unsigned char *image_data = (unsigned char *)formatted_surface->pixels;

    // Apply grayscale filter using multithreading
    int num_threads = 8;
    parallel_image_processing(image_data, width, height, num_threads);

    // Save the grayscale image
    SDL_SaveBMP(formatted_surface, "resources/grayscale_image.bmp");

    // Clean up
    SDL_FreeSurface(formatted_surface);
    SDL_Quit();

    return 0;
}
