#include <vector>
#include <utility>

/// A random-access collection of `(First, Second)` pairs.
template <class First, class Second>
class pair_vector {
private:
  /// The first part of each element.
  std::vector<First> first = std::vector<First>();

  /// The second part of each element.
  std::vector<Second> second = std::vector<Second>();

public:
  /// An empty instance.
  pair_vector() {}

  /// The `i`th element.
  auto operator [] (std::size_t i) const -> std::pair<First, Second> {
    return std::make_pair(first[i], second[i]);
  }

  /// Returns the length.
  auto size() const -> std::size_t { return first.size(); }

  /// Adds x to the end.
  void push_back(std::pair<First, Second> x) {
    first.push_back(x.first);
    second.push_back(x.second);
  }
};
