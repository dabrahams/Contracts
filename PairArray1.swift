struct PairArray<First, Second> {
  private var first: [First] = []
  private var second: [Second] = []

  /// Init a new object as a PairArray. After construction, both
  /// sub-arrays are empty.
  public init() {}

  /// Gets access to the pair at the specified offset from the
  /// start of the PairArray.
  public subscript(i: Int) -> (First, Second) {
    (first[i], second[i])
  }

  /// The total number of elements in the PairArray.
  public var count: Int { first.count }

  /// Appends the given pair to the PairArray.
  public mutating func append(_ x: (First, Second)) {
    first.append(x.0)
    second.append(x.1)
  }
}
