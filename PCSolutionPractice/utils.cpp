#pragma once


#include "utils.h"


void drawPixel(void* buffer, int buffer_w, int x, int y, unsigned int color) {
	*(((unsigned int*)buffer) + ((y * buffer_w) + x)) = color;
}