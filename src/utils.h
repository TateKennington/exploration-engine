#ifndef UTILS_H

#define UTILS_H

bool init();
SDL_Texture* loadTexture(std::string fname);
SDL_Rect castShadow(SDL_Rect src, int srcz, int lightx, int lighty, int lightz, int destz);
void close();

#endif

