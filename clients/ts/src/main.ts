import { Core } from "./core";

const core = new Core(30, 30);

console.log(core);
console.log(core.getGridDimensions());

core.destroy();

document.querySelector<HTMLDivElement>("#app")!.innerHTML = `
  <p>TODO Renderer<p>
`;
