#include "game_element.h"

#include <vector>

#include "cpputils/graphics/image.h"

bool GameElement::IsOutOfBounds(const graphics::Image &screen) {
  return GetX() < 0 || GetY() < 0 || GetX() + GetWidth() > screen.GetWidth() ||
         GetY() + GetHeight() > screen.GetHeight();
}

bool GameElement::IntersectsWith(GameElement *other) {
  return !(GetX() > other->GetX() + other->GetWidth() ||
           other->GetX() > GetX() + GetWidth() ||
           GetY() > other->GetY() + other->GetHeight() ||
           other->GetY() > GetY() + GetHeight());
}

void GameElement::PadPoints(std::vector<int> &points, int pad_x, int pad_y) {
  for (int i = 0; i < points.size(); i++) {
    if (i % 2 == 0) {
      points[i] += pad_x;
    } else {
      points[i] += pad_y;
    }
  }
}
