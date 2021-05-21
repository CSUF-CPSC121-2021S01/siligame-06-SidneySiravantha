#include "game.h"

#include <iostream>

#include "cpputils/graphics/image_event.h"

void Game::Init() {
  my_player_.SetX(375);
  my_player_.SetY(500);
  game_screen_.AddMouseEventListener(*this);
  game_screen_.AddAnimationEventListener(*this);
}

void Game::CreateOpponents() {
  for (int i = 0; i < 5; i++) {
    opponents_.push_back(std::make_unique<Opponent>(100 * i, 20));
  }
}

void Game::LaunchProjectiles() {
  std::unique_ptr<OpponentProjectile> projectile;
  for (int i = 0; i < opponents_.size(); i++) {
    projectile = opponents_[i]->LaunchProjectile();
    if (projectile != nullptr) {
      opponent_projectiles_.push_back(std::move(projectile));
    }
  }
}

void Game::MoveGameElements() {
  for (int i = 0; i < opponents_.size(); i++) {
    if (opponents_[i]->GetIsActive()) {
      opponents_[i]->Move(game_screen_);
    }
  }
  for (int i = 0; i < opponent_projectiles_.size(); i++) {
    if (opponent_projectiles_[i]->GetIsActive()) {
      opponent_projectiles_[i]->Move(game_screen_);
    }
  }
  for (int i = 0; i < player_projectiles_.size(); i++) {
    if (player_projectiles_[i]->GetIsActive()) {
      player_projectiles_[i]->Move(game_screen_);
    }
  }
}

void Game::FilterIntersections() {
  for (int i = 0; i < opponents_.size(); i++) {
    if (my_player_.IntersectsWith(opponents_[i].get())) {
      my_player_.SetIsActive(false);
      opponents_[i]->SetIsActive(false);
      lost_ = true;
    }
  }
  for (int i = 0; i < opponent_projectiles_.size(); i++) {
    if (opponent_projectiles_[i]->IntersectsWith(&my_player_)) {
      my_player_.SetIsActive(false);
      opponent_projectiles_[i]->SetIsActive(false);
      lost_ = true;
    }
  }
  for (int i = 0; i < player_projectiles_.size(); i++) {
    for (int j = 0; j < opponents_.size(); j++) {
      if (player_projectiles_[i]->IntersectsWith(opponents_[j].get())) {
        player_projectiles_[i]->SetIsActive(false);
        opponents_[j]->ReduceHealthPoints();
        if (opponents_[j]->GetHealthPoints() == 0) {
          opponents_[j]->SetIsActive(false);
          if (my_player_.GetIsActive()) {
            score_++;
          }
          if (score_ % 10 == 0) {
            ult_count++;
          }
        }
      }
    }
  }
}

void Game::UpdateScreen() {
  game_screen_.DrawRectangle(0, 0, game_screen_.GetWidth(),
                             game_screen_.GetHeight(),
                             graphics::Color(255, 255, 255));
  if (my_player_.GetIsActive()) {
    my_player_.Draw(game_screen_);
  }
  for (int i = 0; i < opponent_projectiles_.size(); i++) {
    if (opponent_projectiles_[i]->GetIsActive()) {
      opponent_projectiles_[i]->Draw(game_screen_);
    }
  }
  for (int i = 0; i < player_projectiles_.size(); i++) {
    if (player_projectiles_[i]->GetIsActive()) {
      player_projectiles_[i]->Draw(game_screen_);
    }
  }
  for (int i = 0; i < opponents_.size(); i++) {
    if (opponents_[i]->GetIsActive()) {
      opponents_[i]->Draw(game_screen_);
    }
  }
  if (!HasLost()) {
    game_screen_.DrawText(0, 0, std::to_string(score_), 50,
                          graphics::Color(0, 0, 0));
    game_screen_.DrawText(0, 51, "Ground Zero: " + std::to_string(ult_count), 25,
                          graphics::Color(0, 0, 0));
  } else {
    game_screen_.DrawText(game_screen_.GetWidth() / 2 - 50,
                          game_screen_.GetHeight() / 2, "Game Over", 40,
                          graphics::Color(255, 0, 0));
  }
}

void Game::RemoveInactive() {
  for (int i = opponents_.size() - 1; i >= 0; i--) {
    if (!opponents_[i]->GetIsActive()) {
      opponents_.erase(opponents_.begin() + i);
    }
  }
  for (int i = opponent_projectiles_.size() - 1; i >= 0; i--) {
    if (!opponent_projectiles_[i]->GetIsActive()) {
      opponent_projectiles_.erase(opponent_projectiles_.begin() + i);
    }
  }
  for (int i = player_projectiles_.size() - 1; i >= 0; i--) {
    if (!player_projectiles_[i]->GetIsActive()) {
      player_projectiles_.erase(player_projectiles_.begin() + i);
    }
  }
}

void Game::Start() { game_screen_.ShowUntilClosed(); }

void Game::OnMouseEvent(const graphics::MouseEvent &event) {
  if (event.GetMouseAction() == graphics::MouseAction::kMoved ||
      event.GetMouseAction() == graphics::MouseAction::kDragged) {
    int new_x = event.GetX() - my_player_.GetWidth() / 2;
    int new_y = event.GetY() - my_player_.GetHeight() / 2;
    int old_x = my_player_.GetX();
    int old_y = my_player_.GetY();

    my_player_.SetX(new_x);
    my_player_.SetY(new_y);

    player_projectiles_.push_back(std::make_unique<PlayerProjectile>(
        my_player_.GetX() + 25, my_player_.GetY()));

    if (my_player_.IsOutOfBounds(game_screen_)) {
      my_player_.SetX(old_x);
      my_player_.SetY(old_y);
    }
  }

  if (ult_count > 0 &&
      event.GetMouseAction() == graphics::MouseAction::kPressed) {
    opponents_.clear();
    opponent_projectiles_.clear();
    ult_count--;
  }
}

void Game::OnAnimationStep() {
  if (opponents_.size() == 0) {
    CreateOpponents();
  }
  MoveGameElements();
  LaunchProjectiles();
  FilterIntersections();
  RemoveInactive();
  UpdateScreen();
  game_screen_.Flush();
}
