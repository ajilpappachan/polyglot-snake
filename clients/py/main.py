from core import Core

core = Core("core.dll")
assert(core.abi_version() == 1)
print(core.add(12, 4))