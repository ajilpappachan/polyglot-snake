from ctypes import CDLL, c_int
from pathlib import Path

class Core:
    def __init__(self, dll_name) -> None:
        dll_path = Path(__file__).with_name(dll_name)
        self.lib = CDLL(dll_path)
        self.lib.core_abi_version.restype = c_int
        self.lib.core_abi_version.argtypes = []
        self.lib.core_add.restype = c_int
        self.lib.core_add.argtypes = [c_int, c_int]

    def abi_version(self) -> int:
        return self.lib.core_abi_version()

    def add(self, a: int, b: int) -> int:
        return self.lib.core_add(a, b)