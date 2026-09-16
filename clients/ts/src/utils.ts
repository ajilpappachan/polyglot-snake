export enum Direction {
  Up,
  Right,
  Down,
  Left,
}

export enum Color {
  Green,
  White,
  Red,
}

export class Utils {
  static getRenderColor(color: Color): string {
    let renderColor = "";
    switch (color) {
      case Color.Green:
        renderColor = "green";
        break;
      case Color.White:
        renderColor = "white";
        break;
      case Color.Red:
        renderColor = "red";
        break;
      default:
        throw new Error("Invalid render color");
        break;
    }
    return renderColor;
  }
}
