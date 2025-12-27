#include "Core.h"
#include "src/Bomb.h"
#include "src/Bullet.h"
#include "src/GameState.h"
#include "src/Map.h"
#include <chrono>
#include <iostream>
#include <set>
const double BOMB_SPEED = 250.0;
constexpr int MAP_DIMENSION = 64;
constexpr int TILE_SIZE = 64;

struct Explosion {
  int gridX, gridY;
  std::chrono::steady_clock::time_point startTime;
};

class Game : public Core::CoreApplication {

  bool canMoveTo(int newTileX, int newTileY) {
    if (newTileX < 0 || newTileY < 0 || newTileX >= MAP_DIMENSION ||
        newTileY >= MAP_DIMENSION) {
      return false;
    }

    if (grid.at(newTileX, newTileY).getType() == CellType::Destination)
      state.setWon();
    return grid.at(newTileX, newTileY).isWalkable();
  }

  bool GameShouldClose() override { return state.isDead() || state.Won(); }
  void Initialize() override {
    auto mKeyCallback = [this](const Core::KeyEvent &event) {
      if (event.GetKeyAction() == Core::KeyAction::Press ||
          event.GetKeyAction() == Core::KeyAction::Repeat) {
        int currentTileX = state.getTileX();
        int currentTileY = state.getTileY();

        if (event.GetKeyCode() == CORE_KEY_RIGHT ||
            event.GetKeyCode() == CORE_KEY_D) {
          if (canMoveTo(currentTileX + 1, currentTileY)) {
            state.moveTiles(1, 0);
          }
        } else if (event.GetKeyCode() == CORE_KEY_LEFT ||
                   event.GetKeyCode() == CORE_KEY_A) {
          if (canMoveTo(currentTileX - 1, currentTileY)) {
            state.moveTiles(-1, 0);
          }
        } else if (event.GetKeyCode() == CORE_KEY_UP ||
                   event.GetKeyCode() == CORE_KEY_W) {
          if (canMoveTo(currentTileX, currentTileY + 1)) {
            state.moveTiles(0, 1);
          }
        } else if (event.GetKeyCode() == CORE_KEY_DOWN ||
                   event.GetKeyCode() == CORE_KEY_S) {
          if (canMoveTo(currentTileX, currentTileY - 1)) {
            state.moveTiles(0, -1);
          }
        }
      }
    };
    SetKeyCallback(mKeyCallback);

    // Mouse callback - minimal, just like keyboard!
    auto mMouseCallback = [this](const Core::MouseEvent &event) {
      mouseX = event.GetX();
      mouseY = HEIGHT - event.GetY();

      if (event.GetAction() == Core::MouseAction::Press) {
        if (event.GetButton() == Core::MouseButton::Left &&
            state.canThrowBomb()) {
          int playerPixelX = state.getTileX() * TILE_SIZE + TILE_SIZE / 2;
          int playerPixelY = state.getTileY() * TILE_SIZE + TILE_SIZE / 2;

          int cameraPixelX = playerPixelX;
          int cameraPixelY = playerPixelY;

          double worldX = mouseX - (WIDTH / 2) + cameraPixelX;
          double worldY = mouseY - (HEIGHT / 2) + cameraPixelY;

          bombs.emplace_back(playerPixelX, playerPixelY, worldX, worldY,
                             BOMB_SPEED);
          state.throwBomb();
        }
      }
    };
    SetMouseCallback(mMouseCallback);

    Core::CoreWindow::GetWindow()->HideCursor(true);
    grid = Map(MAP_DIMENSION);
    for (int i = 0; i < grid.dimensions(); i++) {
      for (int j = 0; j < grid.dimensions(); j++) {
        std::cout << (int)grid.at(j, i).getType() << " ";
      }
      std::cout << std::endl;
    }
    WIDTH = Core::CoreWindow::GetWindow()->GetWidth();
    HEIGHT = Core::CoreWindow::GetWindow()->GetHeight();
    WIDTH_CELLS = (WIDTH / TILE_SIZE) + 1;
    HEIGHT_CELLS = (HEIGHT / TILE_SIZE) + 1;
    std::vector<int> startCoords = grid.getStartCoords();
    state = GameState(startCoords[0], startCoords[1]);

    std::cout << "Window size: " << WIDTH << "x" << HEIGHT << std::endl;
    std::cout << "Visible cells: " << WIDTH_CELLS << "x" << HEIGHT_CELLS
              << std::endl;
    std::cout << "Player starting at tile: (" << startCoords[0] << ", "
              << startCoords[1] << ")" << std::endl;
    std::cout << "Player pixel position: (" << state.getTileX() << ", "
              << state.getTileY() << ")" << std::endl;
    std::cout << "Tile type at spawn: "
              << (int)grid.at(startCoords[0], startCoords[1]).getType()
              << " (0=walkable, 1=wall, 2=turret)" << std::endl;
  }

  void Update() override {
    Core::Renderer::GetRenderer()->Draw(grass, 0, 0, shaders);
    for (int y = 0; y < (HEIGHT / TILE_SIZE) + 1; y++) {
      for (int x = 0; x < (WIDTH / TILE_SIZE) + 1; x++) {
        Core::Renderer::GetRenderer()->Draw(grass, x * TILE_SIZE, y * TILE_SIZE,
                                            shaders);
      }
    }

    int cameraTileX = state.getTileX();
    int cameraTileY = state.getTileY();
    int cameraPixelX = cameraTileX * TILE_SIZE + TILE_SIZE / 2;
    int cameraPixelY = cameraTileY * TILE_SIZE + TILE_SIZE / 2;

    // Calculate which tiles are visible
    int leftTile = cameraTileX - WIDTH_CELLS / 2 - 1;
    int rightTile = cameraTileX + WIDTH_CELLS / 2 + 1;
    int topTile = cameraTileY - HEIGHT_CELLS / 2 - 1;
    int bottomTile = cameraTileY + HEIGHT_CELLS / 2 + 1;

    // Track which turrets have shot this frame to prevent duplicate bullets
    std::set<std::pair<int, int>> shotsThisFrame;

    for (int tileY = topTile; tileY <= bottomTile; tileY++) {
      for (int tileX = leftTile; tileX <= rightTile; tileX++) {
        // Calculate world position of this tile in pixels (top-left corner)
        int worldX = tileX * TILE_SIZE;
        int worldY = tileY * TILE_SIZE;

        // Convert to screen coordinates
        // Camera is at player center, so subtract camera position
        int screenX = worldX - cameraPixelX + (WIDTH / 2);
        int screenY = worldY - cameraPixelY + (HEIGHT / 2);

        // Check if out of bounds and draw wall, otherwise check tile type
        if (tileX < 0 || tileY < 0 || tileX >= MAP_DIMENSION ||
            tileY >= MAP_DIMENSION) {
          Core::Renderer::GetRenderer()->Draw(wall, screenX, screenY, shaders);
        } else if (grid.at(tileX, tileY).getType() == CellType::Wall) {
          Core::Renderer::GetRenderer()->Draw(wall, screenX, screenY, shaders);
        } else if (grid.at(tileX, tileY).getType() == CellType::Turret) {
          Core::Renderer::GetRenderer()->Draw(turret, screenX, screenY,
                                              shaders);
          // Only create bullet if this turret hasn't shot this frame yet
          std::pair<int, int> turretPos = {tileX, tileY};
          if (shotsThisFrame.find(turretPos) == shotsThisFrame.end() &&
              grid.at(tileX, tileY).canShoot() &&
              grid.at(state.getTileX(), state.getTileY()).getType() !=
                  CellType::HayStack) {
            int turretPixelX = tileX * TILE_SIZE + TILE_SIZE / 2;
            int turretPixelY = tileY * TILE_SIZE + TILE_SIZE / 2;
            int playerPixelX = state.getTileX() * TILE_SIZE + TILE_SIZE / 2;
            int playerPixelY = state.getTileY() * TILE_SIZE + TILE_SIZE / 2;
            bullets.emplace_back(turretPixelX, turretPixelY, playerPixelX,
                                 playerPixelY, 90.0f, tileX, tileY);
            shotsThisFrame.insert(turretPos);
          }
        } else if (grid.at(tileX, tileY).getType() == CellType::Destination) {
          Core::Renderer::GetRenderer()->Draw(barn, screenX, screenY, shaders);
        } else if (grid.at(tileX, tileY).getType() == CellType::Steak) {
          Core::Renderer::GetRenderer()->Draw(steak, screenX, screenY, shaders);
        } else if (grid.at(tileX, tileY).getType() == CellType::HayStack) {
          Core::Renderer::GetRenderer()->Draw(haystack, screenX, screenY,
                                              shaders);
        }
      }
    }

    // draw the player
    if (grid.at(state.getTileX(), state.getTileY()).getType() !=
        CellType::HayStack) {
      Core::Renderer::GetRenderer()->Draw(
          soldier, (WIDTH / 2) - (soldier.GetWidth() / 2),
          (HEIGHT / 2) - (soldier.GetHeight() / 2), shaders);
    }

    // Check if player is standing on steak - heal and remove it
    int playerTileX = state.getTileX();
    int playerTileY = state.getTileY();
    if (grid.at(playerTileX, playerTileY).getType() == CellType::Steak) {
      state.heal();
      grid.at(playerTileX, playerTileY).setType(CellType::Walkable);
    }

    // Draw health bar at top center
    int heartSize = TILE_SIZE / 2;
    int totalWidth = state.getHealth() * heartSize;
    int startX = (WIDTH / 2) - (totalWidth / 2);
    for (int i = 0; i < state.getHealth(); i++) {
      Core::Renderer::GetRenderer()->Draw(heart, 10 + i * (TILE_SIZE + 5), 10,
                                          shaders);
    }

    int bombDisplayX = 10 + 3 * (TILE_SIZE + 5) + 20;
    for (int i = 0; i < state.getBombsRemaining(); i++) {
      Core::Renderer::GetRenderer()->Draw(
          bomb, bombDisplayX + i * (TILE_SIZE + 5), 10, shaders);
    }

    // Update and render bullets
    const float deltaTime = 1.0f / 60.0f;
    std::vector<Bullet> newBullets;
    for (auto &bul : bullets) {
      bul.update(1.0f / 60.0f);
      int bulletGridX = bul.getGridX(TILE_SIZE);
      int bulletGridY = bul.getGridY(TILE_SIZE);

      // Cull bullets outside visible viewport (not just map)
      int bulletScreenX = (int)bul.getPixelX() - cameraPixelX + (WIDTH / 2);
      int bulletScreenY = (int)bul.getPixelY() - cameraPixelY + (HEIGHT / 2);
      if (bulletScreenX < -TILE_SIZE || bulletScreenX > WIDTH + TILE_SIZE ||
          bulletScreenY < -TILE_SIZE || bulletScreenY > HEIGHT + TILE_SIZE) {
        continue; // Outside viewport, don't keep
      }

      // Skip collision check if bullet is still in source turret tile
      if (bulletGridX == bul.getSourceTileX() &&
          bulletGridY == bul.getSourceTileY()) {
        // Still in source turret
      } else if (!grid.at(bulletGridX, bulletGridY).isWalkable()) {
        // Hit a non-walkable tile (wall/turret) - damage it
        grid.at(bulletGridX, bulletGridY).takeDamage();
        continue;
      } else if (grid.at(bulletGridX, bulletGridY).getType() ==
                 CellType::HayStack) {
        grid.at(bulletGridX, bulletGridY).takeDamage();
        continue;
      } else if (bulletGridX == state.getTileX() &&
                 bulletGridY == state.getTileY()) {
        state.takeDamage();
        continue;
      }

      newBullets.push_back(bul);

      int bulletScreenCenterX =
          (int)bul.getPixelX() - cameraPixelX + (WIDTH / 2);
      int bulletScreenCenterY =
          (int)bul.getPixelY() - cameraPixelY + (HEIGHT / 2);
      int bulletRenderX = bulletScreenCenterX - (TILE_SIZE / 2);
      int bulletRenderY = bulletScreenCenterY - (TILE_SIZE / 2);
      if (bulletScreenCenterX < WIDTH && bulletScreenCenterX >= 0 &&
          bulletScreenCenterY < HEIGHT && bulletScreenCenterY >= 0) {
        Core::Renderer::GetRenderer()->Draw(bullet, bulletRenderX,
                                            bulletRenderY, shaders);
      }
    }
    bullets = newBullets;

    // Update and render bombs
    std::vector<Bomb> newBombs;
    for (auto &b : bombs) {
      b.update();
      if (b.hasReachedTarget()) {
        int bombGridX = b.getGridX();
        int bombGridY = b.getGridY();
        auto explosionStart = std::chrono::steady_clock::now();

        for (int dx = -1; dx <= 1; dx++) {
          for (int dy = -1; dy <= 1; dy++) {
            int targetX = bombGridX + dx;
            int targetY = bombGridY + dy;
            if (targetX >= 0 && targetX < MAP_DIMENSION && targetY >= 0 &&
                targetY < MAP_DIMENSION) {
              grid.at(targetX, targetY).takeDamage();
              explosions.push_back({targetX, targetY, explosionStart});
            }
          }
        }
      } else {
        int bombScreenX =
            (int)b.getPixelX() - cameraPixelX + (WIDTH / 2) - (TILE_SIZE / 2);
        int bombScreenY =
            (int)b.getPixelY() - cameraPixelY + (HEIGHT / 2) - (TILE_SIZE / 2);
        if (bombScreenX < WIDTH && bombScreenX + TILE_SIZE > 0 &&
            bombScreenY < HEIGHT && bombScreenY + TILE_SIZE > 0) {
          Core::Renderer::GetRenderer()->Draw(bomb, bombScreenX, bombScreenY,
                                              shaders);
        }
        newBombs.push_back(b);
      }
    }
    bombs = newBombs;

    // Render and update explosions
    auto now = std::chrono::steady_clock::now();
    std::vector<Explosion> activeExplosions;
    for (const auto &exp : explosions) {
      auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
                         now - exp.startTime)
                         .count();
      if (elapsed < 350) { // Show for 1 second
        int explosionScreenX =
            exp.gridX * TILE_SIZE - cameraPixelX + (WIDTH / 2);
        int explosionScreenY =
            exp.gridY * TILE_SIZE - cameraPixelY + (HEIGHT / 2);
        Core::Renderer::GetRenderer()->Draw(explosion, explosionScreenX,
                                            explosionScreenY, shaders);
        activeExplosions.push_back(exp);
      }
    }
    explosions = activeExplosions;

    // Draw crosshair at mouse position
    int crosshairX = static_cast<int>(mouseX) - (TILE_SIZE / 2);
    int crosshairY = static_cast<int>(mouseY) - (TILE_SIZE / 2);
    Core::Renderer::GetRenderer()->Draw(crosshair, crosshairX, crosshairY,
                                        shaders);
  }

private:
  std::vector<Bullet> bullets;
  std::vector<Bomb> bombs;
  std::vector<Explosion> explosions;
  Map grid;
  GameState state;
  Core::Shader shaders{"../Core/Assets/Shaders/defaultVertexShader.glsl",
                       "../Core/Assets/Shaders/defaultFragmentShader.glsl"};
  int WIDTH;
  int HEIGHT;
  int WIDTH_CELLS;
  int HEIGHT_CELLS;
  // Core::Image pic{ "../Core/Assets/Textures/board.png"};
  Core::Image grass{"../Assets/grass.png", TILE_SIZE};
  Core::Image wall{"../Assets/cow.png", TILE_SIZE};
  Core::Image soldier{"../Assets/soldier.png", TILE_SIZE};
  //../Assets/soldiers/Soldier_1/Run_frames/frame_01.png
  Core::Image turret{"../Assets/UFO.png", TILE_SIZE};
  Core::Image barn{"../Assets/barn.png", TILE_SIZE};
  Core::Image bullet{"../Assets/projectile.png", TILE_SIZE};
  Core::Image steak{"../Assets/steak.png", TILE_SIZE};
  Core::Image heart{"../Assets/heart.png", TILE_SIZE};
  Core::Image haystack{"../Assets/haystack.png", TILE_SIZE};
  Core::Image bomb{"../Assets/bomb.png", TILE_SIZE};
  Core::Image crosshair{"../Assets/crosshair.png", TILE_SIZE};
  Core::Image explosion{"../Assets/explosion.png", TILE_SIZE};
  // Mouse tracking
  double mouseX = 0.0;
  double mouseY = 0.0;
};
START_CORE_GAME(Game);
