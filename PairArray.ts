// A random-access collection of pairs.
class PairArray<First, Second> {
  // The first part of each element.
  private first: First[] = [];

  // The second part of each element.
  private second: Second[] = [];

  // Creates an empty instance.
  public constructor() {}

  // The `i`th element.
  public get(i: number): [First, Second] {
    return [this.first[i], this.second[i]];
  }

  // The length.
  public get length(): number { return this.first.length; }

  // Adds x to the end.
  public push(x: [First, Second]) {
    this.first.push(x[0]);
    this.second.push(x[1]);
  }
}
const x = new PairArray<number, number>();
x.push([1, 2]);
console.log(x.get(0));
