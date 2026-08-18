import { Game } from "./game";

document.querySelector<HTMLDivElement>("#app")!.innerHTML = `
  <div class="window">
    <div class="titlebar">
      TS_Snake
    </div>
    <div class="windowloading show">Loading...</div>
    <canvas id="windowcanvas" class="windowcanvas" width=0 height=0><canvas>
  </div>
`;

const game = new Game();
game.run();
