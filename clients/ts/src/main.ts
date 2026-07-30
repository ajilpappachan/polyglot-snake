import { abiVersion, add } from "./core";

document.querySelector<HTMLDivElement>("#app")!.innerHTML = `
  <p>ABI VERSION: ${abiVersion()}<p>
  <p>5 + 2 = ${add(5, 2)}<p>
`;
