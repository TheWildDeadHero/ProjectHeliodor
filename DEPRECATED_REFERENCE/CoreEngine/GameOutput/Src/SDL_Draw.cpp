#include <SDL2/SDL.h>
#include <stdio.h>

class SDLWindow
{
public:

    SDLWindow()
    {
        set_window_size(240, 160);
    }

    SDLWindow(int width, int height)
    {
        set_window_size(width, height);
    }

    ~SDLWindow()
    {
        close();
    }

    void set_window_size(int width, int height)
    {
        width_ = width;
        height_ = height;
    }

    bool init()
    {
        bool success = true;

        // Catch when the video stream has not been initialized, then display the
        // relavent error.
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            printf("SDL Could not be initialized! SDL_ERROR: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            // Actually create the window
            window_ = SDL_CreateWindow("TEST", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width_, height_, SDL_WINDOW_SHOWN);

            // Catch if the window couldn't be created and display the error.
            if (window_ == nullptr)
            {
                printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                // Get the wndow surface
                surface_ = SDL_GetWindowSurface(window_);
            }
        }

        return success;
    }

    void close()
    {
        // Deallocate the surface
        SDL_FreeSurface(image_);
    }

    bool load_media(char *filename = "hello_world.bmp")
    {
        bool success = false;

        // Load the bitmap image onto the surface.
        image_ = SDL_LoadBMP(filename);

        // If the bitmap couldn't be loaded, return false.
        if (image_ == nullptr)
        {
            printf("Could not load image file! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }

        return success;
    }

private:

    SDL_Window  *window_    = nullptr;
    SDL_Surface *surface_   = nullptr;
    SDL_Surface *image_     = nullptr;

    int width_;
    int height_;
};

const int WIDTH = 320;
const int HEIGHT = 240;

int main()
{
    SDL_Window  *window         = nullptr;
    SDL_Surface *screen_surface = nullptr;



    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}