#ifndef GRID_H
#define GRID_H

class Grid
{
    public:
    Grid() = delete;
    Grid(int width, int height);
    Grid(const Grid&) = delete;
    Grid& operator= (const Grid&) = delete;
    ~Grid();

    int GetWidth() const;
    int GetHeight() const;

    private:
    int width;
    int height;
};

#endif // GRID_H