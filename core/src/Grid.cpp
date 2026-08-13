#include "Grid.h"

Grid::Grid(int _width, int _height)
:
width(_width),
height(_height)
{
}

Grid::~Grid()
{
}

int Grid::GetWidth() const
{
    return this->width;
}
int Grid::GetHeight() const
{
    return this->height;
}