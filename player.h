#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

#include "cpputils/graphics/image.h"
#include "game_element.h"
#include "opponent.h"

class PlayerProjectile : public GameElement {
 public:
  PlayerProjectile() : PlayerProjectile(0, 0) {}

  PlayerProjectile(int x, int y) : GameElement(x, y, 5, 5) {}

  void Draw(graphics::Image& screen) override;

  void Move(const graphics::Image& screen) override;

 private:
  const graphics::Color kBlue{0, 0, 255};
};

class Player : public GameElement {
 public:
  Player() : Player(0, 0) {}

  Player(int x, int y) : GameElement(x, y, 50, 50) {}

  void Draw(graphics::Image& screen) override;

  void Move(const graphics::Image& screen) override {}

 private:
  const graphics::Color kBlack{0, 0, 0};
  const graphics::Color kGreen{0, 255, 0};
  const graphics::Color kRed{255, 0, 0};
  const graphics::Color kBlue{0, 0, 255};
};

#endif
