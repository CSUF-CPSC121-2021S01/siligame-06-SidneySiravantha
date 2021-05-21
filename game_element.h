#ifndef GAME_ELEMENT_H
#define GAME_ELEMENT_H

#include "cpputils/graphics/image.h"

class GameElement {
 public:
  GameElement() : GameElement(0, 0, 50, 50) {}
  GameElement(int x, int y, int width, int height)
      : x_(x), y_(y), height_(height), width_(width) {}

 public:
  void SetX(int x) { x_ = x; }
  void SetY(int y) { y_ = y; }
  void SetIsActive(bool is_active) { is_active_ = is_active; }

  int GetX() const { return x_; }
  int GetY() const { return y_; }

  int GetWidth() const { return width_; }
  int GetHeight() const { return height_; }

  bool GetIsActive() const { return is_active_; }

  bool IntersectsWith(GameElement* other);

  bool IsOutOfBounds(const graphics::Image& screen);

  virtual void Draw(graphics::Image& game_screen) = 0;
  virtual void Move(const graphics::Image& game_screen) = 0;

 protected:
  void PadPoints(std::vector<int>& points, int pad_x, int pad_y);

 private:
  int x_ = 0;
  int y_ = 0;
  int width_ = 50;
  int height_ = 50;
  bool is_active_ = true;
};

#endif
