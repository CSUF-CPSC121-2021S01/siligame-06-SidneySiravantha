#include "opponent.h"

#include <vector>

#include "cpputils/graphics/image.h"

void Opponent::Draw(graphics::Image &image) {
  graphics::Image oppo;
  oppo.Load("opponent.bmp");
  for (int i = 0; i < GetHeight(); i++) {
    for (int j = 0; j < GetWidth(); j++) {
      image.SetColor(GetX() + j, GetY() + i, oppo.GetColor(j, i));
    }
  }
}

void OpponentProjectile::Draw(graphics::Image &image) {
  graphics::Image obullet;
  obullet.Load("opponentp.bmp");
  for (int i = 0; i < GetHeight(); i++) {
    for (int j = 0; j < GetWidth(); j++) {
      image.SetColor(GetX() + j, GetY() + i, obullet.GetColor(j, i));
    }
  }
}

void Opponent::Move(const graphics::Image &screen) {
  if (going_right_ && GetX() + GetWidth() >= screen.GetWidth()) {
    going_right_ = false;
  } else if (!going_right_ && GetX() <= 0) {
    going_right_ = true;
  }
  int offset = going_right_ ? 1 : -1;

  SetX(GetX() + offset * 5);
  SetY(GetY() + 2);

  if (IsOutOfBounds(screen)) {
    SetIsActive(false);
  }
}

void OpponentProjectile::Move(const graphics::Image &screen) {
  SetY(GetY() + 3);
  if (IsOutOfBounds(screen)) {
    SetIsActive(false);
  }
}

std::unique_ptr<class OpponentProjectile> Opponent::LaunchProjectile() {
  if (counter % 30 == 0) {
    counter++;
    return std::make_unique<OpponentProjectile>(GetX() + 25, GetY() + 50);
  }
  counter++;
  return nullptr;
}
