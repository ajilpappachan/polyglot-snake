import type { Core } from "./core";

export class Renderer {
  core: Core;
  cellSize: number;
  width: number;
  height: number;
  canvas: CanvasRenderingContext2D;
  lastFrameTime: number;
  deltaTime: number;
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
  }

  destroy() {}

  update() {
    this.deltaTime = Date.now() - this.lastFrameTime;
    if (this.deltaTime > 16) this.deltaTime = 16;
    this.lastFrameTime = Date.now();
  }

  draw() {
    // Clear
    this.canvas.fillStyle = "white";
    this.canvas.fillRect(0, 0, this.width, this.height);
  }
}
