import { Core } from "./core";
import { Renderer } from "./renderer";

export class Game {
  core: Core;
  renderer: Renderer;
  constructor() {
    this.core = new Core(30, 30);
    this.renderer = new Renderer(this.core, 20);
  }

  run() {
    const runFrame = () => {
      this.renderer.update();
      this.renderer.draw();
      requestAnimationFrame(runFrame);
    };
    runFrame();
    // Cannot clean up because technically will never reach end of lifecycle unless the page is closed?
    // Maybe implement clean up if there is a restart button or move on to a different page
  }
}
