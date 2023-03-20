// A displacement in a cartesian coordinate system.
struct Vec2 {
  // The first component of *this.
  float x;

  // The second component of *this.
  float y;

  // Offsets *this by d.
  //
  // - Precondition: x, y, d.x, nor d.y are neither NaN or infinite.
  void add(Vec2 d) {
    x += d.x;
    y += d.y;
  }

  // Returns *this offset by d.
  //
  // - Precondition: x, y, d.x, nor d.y are neither NaN or infinite.
  Vec2 plus(Vec2 d) const {
    Vec2 r = *this;
    r.add(d);
    return r;
  }

  // Offsets *this by the negation of d.
  //
  // - Precondition: x, y, d.x, nor d.y are neither NaN or infinite.
  void subtract(Vec2 translation) {
    add(d.negated())
  }

  // Returns *this offset by the negation of d.
  //
  // - Precondition: x, y, d.x, nor d.y are neither NaN or infinite.
  Vec2 minus(Vec2 d) const {
    x += d.x;
    y += d.y;
  }

  // Returns the negation of *this.
  Vec2 negated() const {
    Vec2 r = *this;
    r.negate();
    return r;
  }

  // Replaces *this by its negation.
  void negate() {
    x = -x;
    y = -y;
  }

  // Returns true if neither x nor y are NaN or infinite.
  bool isValid() {
    return x - x + y - y == 0;
  }
};

// A position in a 2D coordinate system.
struct Point2D {
  // The displacement of *this from the origin of the coordinate system.
  Vec2 offsetFromOrigin;

  // The displacement of *this along the x axis
  int x() { return offsetFromOrigin.x; }

  // The displacement of *this along the y axis
  int y() { return offsetFromOrigin.y; }
};

// A rectangle in a cartesian coordinate system with sides parallel to
// the axes.
struct Rect {
  // The top left corner of *this.
  Point2D top_left;

  // The bottom right corner of *this.
  Point2D bottom_right;
};
