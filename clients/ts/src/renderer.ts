import type { Core } from "./core";
import { Direction, Utils } from "./utils";

export class Renderer {
  core: Core;
  cellSize: number;
  width: number;
  height: number;
  canvas: CanvasRenderingContext2D;
  lastFrameTime: number;
  deltaTime: number;
  timeSinceCoreUpdate: number;
  coreUpdateFrequency: number;
  pendingDirection: Direction | null;
  constructor(core: Core, cellSize: number) {
    this.core = core;
    this.cellSize = cellSize;
    const { width: gridWidth, height: gridHeight } = core.getGridDimensions();
    this.width = gridWidth * cellSize;
    this.height = gridHeight * cellSize;

    // Initialize canvas
    const canvasEl: HTMLCanvasElement =
      document.querySelector("#windowcanvas")!;
    const loadingEl: HTMLElement = document.querySelector(".windowloading")!;
    canvasEl.width = this.width;
    canvasEl.height = this.height;
    loadingEl.classList.remove("show");
    canvasEl.classList.add("show");
    this.canvas = canvasEl.getContext("2d")!;

    this.lastFrameTime = 0;
    this.deltaTime = 0;
    this.timeSinceCoreUpdate = 0;
    this.coreUpdateFrequency = 1000;
    this.pendingDirection = null;

    window.addEventListener("keydown", (event) => {
      if (event.key == "ArrowUp" || event.key == "w") {
        event.preventDefault();
        this.pendingDirection = Direction.Up;
      }
      if (event.key == "ArrowRight" || event.key == "d") {
        event.preventDefault();
        this.pendingDirection = Direction.Right;
      }
      if (event.key == "ArrowDown" || event.key == "s") {
        event.preventDefault();
        this.pendingDirection = Direction.Down;
      }
      if (event.key == "ArrowLeft" || event.key == "a") {
        event.preventDefault();
        this.pendingDirection = Direction.Left;
      }
    });
  }

  destroy() {}

  update() {
    this.deltaTime = Date.now() - this.lastFrameTime;
    if (this.deltaTime > 16) this.deltaTime = 16;
    this.lastFrameTime = Date.now();

    if (this.core.currentState.isRunning == false) return;

    this.timeSinceCoreUpdate += this.deltaTime;
    if (this.timeSinceCoreUpdate > this.coreUpdateFrequency) {
      if (this.pendingDirection != null) {
        this.core.changeDirection(this.pendingDirection);
        this.pendingDirection = null;
      }
      this.core.update();
      this.timeSinceCoreUpdate = 0;
    }
  }

  draw() {
    // Clear
    this.canvas.fillStyle = "purple";
    this.canvas.fillRect(0, 0, this.width, this.height);

    const gameState = this.core.currentState;

    gameState.segmentData.forEach((segment) => {
      this.canvas.fillStyle = Utils.getRenderColor(segment.color);
      this.canvas.fillRect(
        segment.x * this.cellSize,
        segment.y * this.cellSize,
        this.cellSize,
        this.cellSize,
      );
    });

    if (gameState.isRunning == false) {
      this.canvas.fillStyle = "white";
      const gameOverText = "Game Over!";
      this.canvas.font = "32px Arial";
      const { width: textWidth } = this.canvas.measureText(gameOverText);
      this.canvas.fillText(gameOverText, this.width / 2 - textWidth / 2, 50);
    }
  }
}
