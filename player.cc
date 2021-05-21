#include "player.h"

#include <vector>

#include "cpputils/graphics/image.h"

void PlayerProjectile::Draw(graphics::Image &image) {
  graphics::Image pbullet;
  pbullet.Load("playerp.bmp");
  for (int i = 0; i < GetHeight(); i++) {
    for (int j = 0; j < GetWidth(); j++) {
      image.SetColor(GetX() + j, GetY() + i, pbullet.GetColor(j, i));
    }
  }
}

void Player::Draw(graphics::Image &image) {
  graphics::Image player;
  player.Load("player.bmp");
  for (int i = 0; i < GetHeight(); i++) {
    for (int j = 0; j < GetWidth(); j++) {
      image.SetColor(GetX() + j, GetY() + i, player.GetColor(j, i));
    }
  }
}

void PlayerProjectile::Move(const graphics::Image &screen) {
  SetY(GetY() - 6);
  if (IsOutOfBounds(screen)) {
    SetIsActive(false);
  }
}
