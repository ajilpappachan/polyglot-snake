using System.Diagnostics;

namespace cs_snake
{
    public class Grid
    {
        private int _width;
        private int _height;
        private int _cellSize;

        public int Width => _width;
        public int Height => _height;
        public int PixelWidth => _width * _cellSize;
        public int PixelHeight => _height * _cellSize;
        public int CellSize => _cellSize;

        public Grid(int width, int height, int cellSize)
        {
            Debug.Assert(width > 0);
            Debug.Assert(height > 0);
            Debug.Assert(cellSize > 0);

            _width = width;
            _height = height;
            _cellSize = cellSize;
        }

        public (int x, int y) GridToPixel(int gridX, int gridY)
        {
            return (gridX * _cellSize, gridY * _cellSize);
        }

        public (int x, int y) PixelToGrid(int pixelX, int pixelY)
        {
            return (pixelX / _cellSize, pixelY / _cellSize);
        }
    }
}