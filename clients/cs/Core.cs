using System.Diagnostics;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace cs_snake
{
    public class Core
    {
        public struct SegmentData
        {
            public int x;
            public int y;
            public Direction direction;
            public Color color;
        }
        public struct GameState
        {
            public List<SegmentData> segmentData;
        }

        public const int SNAKE_CORE_VERSION = 3;

        private int _version;
        private UIntPtr _game;
        private GameState _gameState;

        public int Version => _version;
        public GameState CurrentState => _gameState;

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

            _gameState = new GameState { segmentData = new List<SegmentData>() };
        }

        public void Destroy()
        {
            if (_game == UIntPtr.Zero) return;

            ABI.SNAKE_STATUS status = ABI.snake_destroy(_game);
            if (status == ABI.SNAKE_STATUS.SNAKE_FAILURE)
            {
                throw new InvalidOperationException("Failed to destroy game");
            }
            _game = UIntPtr.Zero;
        }

        public (int width, int height) GetGridDimensions()
        {
            ABI.SNAKE_STATUS status = ABI.snake_grid_dimensions(_game, out int width, out int height);
            if (status == ABI.SNAKE_STATUS.SNAKE_FAILURE)
            {
                throw new InvalidOperationException("Failed to get grid dimensions");
            }
            Debug.Assert(width > 0 && height > 0);
            return (width, height);
        }

        public void Update()
        {
            // TODO Update Core

            // Update Game State
            privUpdateGameState();
        }

        private void privUpdateGameState()
        {
            ABI.SNAKE_STATUS status = ABI.snake_game_state(_game, out ABI.GameState newState);
            if (status == ABI.SNAKE_STATUS.SNAKE_FAILURE)
            {
                throw new InvalidOperationException("Failed to get game state");
            }

            if (newState.segmentCount != _gameState.segmentData.Count)
            {
                _gameState.segmentData = [.. new SegmentData[newState.segmentCount]];
            }

            var inSegmentData = ABI.GetSegmentDataView(newState);

            for (int i = 0; i < _gameState.segmentData.Count; i++)
            {
                _gameState.segmentData[i] = new SegmentData
                {
                    x = inSegmentData[i].x,
                    y = inSegmentData[i].y,
                    direction = (Direction)inSegmentData[i].direction,
                    color = (Color)inSegmentData[i].color
                };
            }
        }
    }

    public static partial class ABI
    {
        public enum SNAKE_STATUS : Int32
        {
            SNAKE_SUCCESS = 0,
            SNAKE_FAILURE = -1
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct Config
        {
            public Int32 width;
            public Int32 height;
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct SegmentData
        {
            public Int32 x;
            public Int32 y;
            public Int32 direction;
            public Int32 color;
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct GameState
        {
            public Int32 segmentCount;
            public UIntPtr pSegmentData;
        }

        [LibraryImport("snake_core.dll")]
        [UnmanagedCallConv(CallConvs = new[] { typeof(CallConvCdecl) })]
        public static partial Int32 snake_core_version();

        [LibraryImport("snake_core.dll")]
        [UnmanagedCallConv(CallConvs = new[] { typeof(CallConvCdecl) })]
        public static partial UIntPtr snake_create(Config config);

        [LibraryImport("snake_core.dll")]
        [UnmanagedCallConv(CallConvs = new[] { typeof(CallConvCdecl) })]
        public static partial SNAKE_STATUS snake_destroy(UIntPtr pGame);

        [LibraryImport("snake_core.dll")]
        [UnmanagedCallConv(CallConvs = new[] { typeof(CallConvCdecl) })]
        public static partial SNAKE_STATUS snake_grid_dimensions(UIntPtr pGame, out Int32 width, out Int32 height);

        [LibraryImport("snake_core.dll")]
        [UnmanagedCallConv(CallConvs = new[] { typeof(CallConvCdecl) })]
        public static partial SNAKE_STATUS snake_game_state(UIntPtr pGame, out GameState pState);

        public static unsafe ReadOnlySpan<SegmentData> GetSegmentDataView(GameState pState)
        {
            return new ReadOnlySpan<SegmentData>((void*)pState.pSegmentData, pState.segmentCount);
        }

    }
}