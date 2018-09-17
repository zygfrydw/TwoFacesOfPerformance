#include "stdafx.h"
#include "Image.h"


Image::Image(): ptr(nullptr), width(0), height(0), step(0)
{
}

Image::Image(uint8_t* ptr, int width, int height, int step) : ptr(ptr), width(width), height(height), step(step)
{
}

Image::~Image()
{
}
