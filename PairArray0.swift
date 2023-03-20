struct PairArray<First, Second> {
  private var first: [First] = []
  private var second: [Second] = []

  public init() {}

  public subscript(i: Int) -> (First, Second) {
    (first[i], second[i])
  }

  public var count: Int { first.count }

  public mutating func append(_ x: (First, Second)) {
    first.append(x.0)
    second.append(x.1)
  }
}
