from pygame import Color, Surface

class GameObject:
    def __init__(self, x: int = 0, y: int = 0, width: int = 0, height: int = 0, color: Color = Color(0)) -> None:
        self.x = x
        self.y = y
        self.width = width
        self.height = height
        self.color = color

    def update(self, deltatime: float):
        pass

    def draw(self, screen: Surface):
        pass

class _GameObjectMan:
    def __init__(self) -> None:
        self._dict: dict[str, GameObject] = {}

    def add(self, name: str, go: GameObject) -> None:
        assert(self._dict.__contains__(name) == False)
        self._dict[name] = go

    def remove(self, name: str) -> None:
        assert(self._dict.__contains__(name) == True)
        self._dict.__delitem__(name)

    def get(self, name: str) -> GameObject:
        assert(self._dict[name] != None)
        return self._dict[name]

    def update(self, deltatime: float) -> None:
        for go in self._dict.values():
            go.update(deltatime)

    def draw(self, screen: Surface) -> None:
        for go in self._dict.values():
            go.draw(screen)

GameObjectMan = _GameObjectMan()