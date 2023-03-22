/// A random-access collection of `(First, Second)` pairs.
struct PairArray<First, Second> {
  /// The first part of each element.
  private var first: [First] = []

  /// The second part of each element.
  private var second: [Second] = []

  /// An empty instance.
  public init() {}

  /// The `i`th element.
  public subscript(i: Int) -> (First, Second) {
    (first[i], second[i])
  }

  /// The length.
  public var count: Int { first.count }

  /// Adds x to the end.
  public mutating func append(_ x: (First, Second)) {
    first.append(x.0)
    second.append(x.1)
  }
}
