using System.Diagnostics;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace cs_snake
{
    public class Core
    {
        public const int SNAKE_CORE_VERSION = 2;
        public const int SNAKE_SUCCESS = 0;
        public const int SNAKE_FAILURE = -1;

        public int Version => _version;

        public int GridWidth => ABI.snake_grid_width(_game);
        public int GridHeight => ABI.snake_grid_height(_game);

        private int _version;
        private UIntPtr _game;

        public Core(int width, int height)
        {
            _version = ABI.snake_core_version();
            if (_version != SNAKE_CORE_VERSION)
            {
                throw new InvalidOperationException("Core version error");
            }
            _game = ABI.snake_create(new ABI.Config { width = width, height = height });
            if (_game == UIntPtr.Zero)
            {
                throw new InvalidOperationException("Failed to create new core game");
            }
        }

        public void Destroy()
        {
            int status = ABI.snake_destroy(_game);
            if (status == SNAKE_FAILURE)
            {
                throw new InvalidOperationException("Failed to destroy game");
            }
            _game = UIntPtr.Zero;
        }
    }

    public static partial class ABI
    {
        [StructLayout(LayoutKind.Sequential)]
        public struct Config
        {
            public Int32 width;
            public Int32 height;
        }

        [LibraryImport("snake_core.dll")]
        [UnmanagedCallConv(CallConvs = new[] { typeof(CallConvCdecl) })]
        public static partial Int32 snake_core_version();


        [LibraryImport("snake_core.dll")]
        [UnmanagedCallConv(CallConvs = new[] { typeof(CallConvCdecl) })]
        public static partial UIntPtr snake_create(Config config);

        [LibraryImport("snake_core.dll")]
        [UnmanagedCallConv(CallConvs = new[] { typeof(CallConvCdecl) })]
        public static partial Int32 snake_destroy(UIntPtr pGame);


        [LibraryImport("snake_core.dll")]
        [UnmanagedCallConv(CallConvs = new[] { typeof(CallConvCdecl) })]
        public static partial Int32 snake_grid_width(UIntPtr pGame);

        [LibraryImport("snake_core.dll")]
        [UnmanagedCallConv(CallConvs = new[] { typeof(CallConvCdecl) })]
        public static partial Int32 snake_grid_height(UIntPtr pGame);
    }
}