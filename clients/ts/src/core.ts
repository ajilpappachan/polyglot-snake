import MakeCoreLib from "../libs/snake_core.mjs";
import { Direction, Color } from "./utils";
const CoreLib = await MakeCoreLib();

const CORE_VERSION = 4;

const SNAKE_SUCCESS = 0;

class CoreABI {
  static coreVersion(): number {
    return CoreLib._snake_core_version();
  }

  static gameCreate(width: number, height: number): { gamePtr: number } {
    const sp = CoreLib.stackSave();
    const config = CoreLib.stackAlloc(8);
    CoreLib.setValue(config, width, "i32");
    CoreLib.setValue(config + 4, height, "i32");
    const gamePtr = CoreLib._snake_create(config);
    CoreLib.stackRestore(sp);
    return { gamePtr };
  }

  static gameDestroy(gamePtr: number): { status: number } {
    return { status: CoreLib._snake_destroy(gamePtr) };
  }

  static getGridDimensions(gamePtr: number): {
    status: number;
    width: number;
    height: number;
  } {
    const sp = CoreLib.stackSave();
    const dim = CoreLib.stackAlloc(8);
    const status = CoreLib._snake_grid_dimensions(gamePtr, dim, dim + 4);
    const width = CoreLib.getValue(dim, "i32");
    const height = CoreLib.getValue(dim + 4, "i32");
    CoreLib.stackRestore(sp);
    return { status, width, height };
  }

  static getGameState(gamePtr: number): {
    status: number;
    data: SnakeGameData;
  } {
    const sp = CoreLib.stackSave();
    const coreGameData = CoreLib.stackAlloc(4 * 3); // Refer struct SnakeGameState in core
    const status = CoreLib._snake_game_state(gamePtr, coreGameData);
    const isRunning = CoreLib.getValue(coreGameData, "i8");
    const segmentCount = CoreLib.getValue(coreGameData + 4, "i32");
    const segmentDataPtr = CoreLib.getValue(coreGameData + 8, "i32");
    const segmentDataView = new Uint32Array(
      CoreLib.HEAP32.buffer,
      segmentDataPtr,
      segmentCount * 4,
    );
    const data: SnakeGameData = {
      isRunning: isRunning == 0 ? false : true,
      segmentData: [],
    };
    for (let i = 0; i < segmentCount; i++) {
      const segmentData: SnakeSegmentData = {
        x: segmentDataView[i * 4 + 0],
        y: segmentDataView[i * 4 + 1],
        direction: segmentDataView[i * 4 + 2],
        color: segmentDataView[i * 4 + 3],
      };
      data.segmentData.push(segmentData);
    }
    CoreLib.stackRestore(sp);
    return { status, data };
  }

  static changeDirection(
    gamePtr: number,
    direction: Direction,
  ): { status: number } {
    return { status: CoreLib._snake_change_direction(gamePtr, direction) };
  }

  static update(gamePtr: number) {
    return { status: CoreLib._snake_update(gamePtr) };
  }
}

export type SnakeSegmentData = {
  x: number;
  y: number;
  direction: Direction;
  color: Color;
};

export type SnakeGameData = {
  isRunning: boolean;
  segmentData: SnakeSegmentData[];
};

export class Core {
  version: number;
  gamePtr: number;
  currentState: SnakeGameData;

  constructor(width: number, height: number) {
    this.version = CoreABI.coreVersion();
    console.log(`Loaded core version ${this.version}`);
    if (this.version != CORE_VERSION) {
      throw new Error("Core Version mismatch");
    }

    const { gamePtr } = CoreABI.gameCreate(width, height);
    if (gamePtr == 0) {
      throw new Error("Failed to create core game");
    }
    this.gamePtr = gamePtr;

    const { status, data } = CoreABI.getGameState(this.gamePtr);
    if (status != SNAKE_SUCCESS) {
      throw new Error("Failed to get state from core");
    }
    this.currentState = data;
  }

  destroy() {
    const { status } = CoreABI.gameDestroy(this.gamePtr);
    this.gamePtr = 0;
    if (status != SNAKE_SUCCESS) {
      throw new Error("Failed to destroy core game");
    }
  }

  getGridDimensions(): { width: number; height: number } {
    const { status, width, height } = CoreABI.getGridDimensions(this.gamePtr);
    if (status != SNAKE_SUCCESS) {
      throw new Error("Failed to get dimensions from core");
    }
    return { width, height };
  }

  changeDirection(direction: Direction) {
    const { status } = CoreABI.changeDirection(this.gamePtr, direction);
    if (status != SNAKE_SUCCESS) {
      throw new Error("Failed to change direction in core");
    }
  }

  update() {
    const { status: updateStatus } = CoreABI.update(this.gamePtr);
    if (updateStatus != SNAKE_SUCCESS) {
      throw new Error("Failed to update core.");
    }
    const { status: stateStatus, data } = CoreABI.getGameState(this.gamePtr);
    if (stateStatus != SNAKE_SUCCESS) {
      throw new Error("Failed to update state from core.");
    }
    this.currentState = data;
  }
}
