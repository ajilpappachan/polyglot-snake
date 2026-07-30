import CreateCore from "../libs/core_lib.mjs";
const Core = await CreateCore();

export const abiVersion = () => Core._core_abi_version();
export const add = (a: number, b: number) => Core._core_add(a, b);
