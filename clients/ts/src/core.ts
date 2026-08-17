import MakeCoreLib from "../libs/snake_core.mjs";
const CoreLib = await MakeCoreLib();

const CORE_VERSION = 4;

const SNAKE_SUCCESS = 0;

class CoreABI {
  static coreVersion(): number {
    return CoreLib._snake_core_version();
  }

  static gameCreate(width: number, height: number): number {
    const sp = CoreLib.stackSave();
    const config = CoreLib.stackAlloc(8);
    CoreLib.setValue(config, width, "i32");
    CoreLib.setValue(config + 4, height, "i32");
    const gamePtr = CoreLib._snake_create(config);
    CoreLib.stackRestore(sp);
    return gamePtr;
  }

  static gameDestroy(gamePtr: number): number {
    return CoreLib._snake_destroy(gamePtr);
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
}

export class Core {
  version: number;
  gamePtr: number;

  constructor(width: number, height: number) {
    this.version = CoreABI.coreVersion();
    console.log(`Loaded core version ${this.version}`);
    if (this.version != CORE_VERSION) {
      throw new Error("Core Version mismatch");
    }

    this.gamePtr = CoreABI.gameCreate(width, height);
    if (this.gamePtr == 0) {
      throw new Error("Failed to create core game");
    }
  }

  destroy() {
    const status = CoreABI.gameDestroy(this.gamePtr);
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
}
