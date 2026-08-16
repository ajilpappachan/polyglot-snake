using System.Diagnostics;
using System.Net.NetworkInformation;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace cs_snake
{
    public enum SNAKE_STATUS : Int32
    {
        SNAKE_SUCCESS = 0,
        SNAKE_FAILURE = -1
    }
    public struct SegmentData
    {
        public int x;
        public int y;
        public Direction direction;
        public Color color;
    }
    public struct GameState
    {
        public bool isRunning;
        public List<SegmentData> segmentData;
    }

    public class Core
    {
        public const int SNAKE_CORE_VERSION = 4;

        private int _version;
        private nuint _gamePtr;
        private GameState _gameState;

        public int Version => _version;
        public GameState CurrentState => _gameState;

        public Core(int width, int height)
        {
            _version = ABI.GetCoreVersion();
            if (_version != SNAKE_CORE_VERSION)
            {
                throw new InvalidOperationException("Core version error");
            }
            _gamePtr = ABI.SnakeGameCreate(width, height);
            if (_gamePtr == UIntPtr.Zero)
            {
                throw new InvalidOperationException("Failed to create new core game");
            }

            // Get initial game state
            SNAKE_STATUS status = ABI.GetGameState(_gamePtr, out _gameState);
            if (status != SNAKE_STATUS.SNAKE_SUCCESS)
            {
                throw new InvalidOperationException("Failed to get game state from core");
            }
        }

        public void Destroy()
        {
            if (_gamePtr == 0) return;

            SNAKE_STATUS status = ABI.SnakeGameDestroy(_gamePtr);
            if (status != SNAKE_STATUS.SNAKE_SUCCESS)
            {
                throw new InvalidOperationException("Failed to destroy game");
            }
            _gamePtr = 0;
        }

        public (int width, int height) GetGridDimensions()
        {
            SNAKE_STATUS status = ABI.GetGridDimensions(_gamePtr, out int width, out int height);
            if (status != SNAKE_STATUS.SNAKE_SUCCESS)
            {
                throw new InvalidOperationException("Failed to get grid dimensions");
            }
            Debug.Assert(width > 0 && height > 0);
            return (width, height);
        }

        public void ChangeDirection(Direction direction)
        {
            SNAKE_STATUS status = ABI.ChangeDirection(_gamePtr, direction);
            if (status != SNAKE_STATUS.SNAKE_SUCCESS)
            {
                throw new InvalidOperationException("Failed to change direction in core");
            }
        }

        public void Update()
        {
            SNAKE_STATUS status;
            // Update Core
            status = ABI.Update(_gamePtr);
            if (status != SNAKE_STATUS.SNAKE_SUCCESS)
            {
                throw new InvalidOperationException("Failed to update core");
            }

            // Update Game State
            status = ABI.GetGameState(_gamePtr, out _gameState);
            if (status != SNAKE_STATUS.SNAKE_SUCCESS)
            {
                throw new InvalidOperationException("Failed to get game state from core");
            }
        }
    }

    public static partial class ABI
    {
        [StructLayout(LayoutKind.Sequential)]
        private struct C_Config
        {
            public Int32 width;
            public Int32 height;
        }
        [StructLayout(LayoutKind.Sequential)]
        private struct C_SegmentData
        {
            public Int32 x;
            public Int32 y;
            public Int32 direction;
            public Int32 color;
        }
        [StructLayout(LayoutKind.Sequential)]
        private struct C_GameState
        {
            public Byte isRunning;
            public Int32 segmentCount;
            public UIntPtr pSegmentData;
        }

        [LibraryImport("snake_core.dll")]
        [UnmanagedCallConv(CallConvs = new[] { typeof(CallConvCdecl) })]
        private static partial Int32 snake_core_version();
        [LibraryImport("snake_core.dll")]
        [UnmanagedCallConv(CallConvs = new[] { typeof(CallConvCdecl) })]
        private static partial UIntPtr snake_create(C_Config config);
        [LibraryImport("snake_core.dll")]
        [UnmanagedCallConv(CallConvs = new[] { typeof(CallConvCdecl) })]
        private static partial SNAKE_STATUS snake_destroy(UIntPtr pGame);
        [LibraryImport("snake_core.dll")]
        [UnmanagedCallConv(CallConvs = new[] { typeof(CallConvCdecl) })]
        private static partial SNAKE_STATUS snake_grid_dimensions(UIntPtr pGame, out Int32 width, out Int32 height);
        [LibraryImport("snake_core.dll")]
        [UnmanagedCallConv(CallConvs = new[] { typeof(CallConvCdecl) })]
        private static partial SNAKE_STATUS snake_game_state(UIntPtr pGame, out C_GameState pState);
        [LibraryImport("snake_core.dll")]
        [UnmanagedCallConv(CallConvs = new[] { typeof(CallConvCdecl) })]
        private static partial SNAKE_STATUS snake_change_direction(UIntPtr pGame, Int32 direction);
        [LibraryImport("snake_core.dll")]
        [UnmanagedCallConv(CallConvs = new[] { typeof(CallConvCdecl) })]
        private static partial SNAKE_STATUS snake_update(UIntPtr pGame);

        public static int GetCoreVersion()
        {
            return snake_core_version();
        }

        public static nuint SnakeGameCreate(int width, int height)
        {
            return snake_create(new C_Config{ width=width, height=height});
        }

        public static SNAKE_STATUS SnakeGameDestroy(nuint gamePtr)
        {
            return snake_destroy(gamePtr);
        }

        public static SNAKE_STATUS GetGridDimensions(nuint gamePtr, out int width, out int height)
        {
            return snake_grid_dimensions(gamePtr, out width, out height);
        }

        public static SNAKE_STATUS GetGameState(nuint gamePtr, out GameState gameState)
        {
            C_GameState newState = new C_GameState();
            SNAKE_STATUS status = snake_game_state(gamePtr, out newState);
            if (status == SNAKE_STATUS.SNAKE_SUCCESS)
            {
                gameState.isRunning = newState.isRunning == 0 ? false : true;
                gameState.segmentData = new List<SegmentData>(newState.segmentCount);
                ReadOnlySpan<C_SegmentData> segmentDataView = privGetSegmentDataView(newState);
                for (int i = 0; i < newState.segmentCount; i++)
                {
                    gameState.segmentData.Add(new SegmentData
                    {
                        x = segmentDataView[i].x,
                        y = segmentDataView[i].y,
                        direction = (Direction)segmentDataView[i].direction,
                        color = (Color)segmentDataView[i].color
                    });
                }
            }
            else
            {
                gameState = new GameState();
            }
            return status;
        }
        private static unsafe ReadOnlySpan<C_SegmentData> privGetSegmentDataView(C_GameState pState)
        {
            return new ReadOnlySpan<C_SegmentData>((void*)pState.pSegmentData, pState.segmentCount);
        }

        public static SNAKE_STATUS ChangeDirection(nuint gamePtr, Direction direction)
        {
            return snake_change_direction(gamePtr, (int)direction);
        }

        public static SNAKE_STATUS Update(nuint gamePtr)
        {
            return snake_update(gamePtr);
        }
    }
}