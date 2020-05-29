#ifndef MODERNOPENGL__RECT_H_
#define MODERNOPENGL__RECT_H_
template<typename T>
struct Rect {
  explicit Rect(const T &x = 0, const T &y = 0, const T &w = 0, const T &h = 0)
      : x(x), y(y), w(w), h(h) {}

  T x;
  T y;
  T w;
  T h;
};

typedef Rect<float> Rectf;
typedef Rect<int> Recti;
typedef Rect<double> Rectd;
#endif //MODERNOPENGL__RECT_H_
