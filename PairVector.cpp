#include <vector>
#include <utility>

/// A random-access collection of `(First, Second)` pairs, stored so
/// as to avoid internal fragmentation.
template <class First, class Second>
class pair_vector {
private:
  /// The first part of each element.
  std::vector<First> first = std::vector<First>();

  /// The second part of each element.
  std::vector<Second> second = std::vector<Second>();

public:
  /// Creates an empty instance.
  pair_vector() {}

  /// Returns the `i`th element of *this.
  auto operator [] (std::size_t i) const -> std::pair<First, Second> {
    return std::make_pair(first[i], second[i]);
  }

  /// Returns the length of *this.
  auto size() const -> std::size_t { return first.size(); }

  /// Adds x to the end of *this.
  void push_back(std::pair<First, Second> x) {
    first.push_back(x.first);
    second.push_back(x.second);
  }
};
