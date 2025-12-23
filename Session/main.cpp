#include "Core.h"
#include "src/Bullet.h"
#include "src/GameState.h"
#include "src/Map.h"
#include <iostream>
constexpr int MAP_DIMENSION = 64;
constexpr int TILE_SIZE = 64;

class Game : public Core::CoreApplication {

  // Helper function to check if player can move to a tile
  bool canMoveTo(int newTileX, int newTileY) {
    // Check if out of bounds
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
    grid = Map(MAP_DIMENSION);
    for (int i = 0; i < grid.dimensions(); i++) {
      for (int j = 0; j < grid.dimensions(); j++) {
        std::cout << (int)grid.at(j, i).getType() << " ";
      }
      std::cout << std::endl;
    }
    WIDTH = Core::CoreWindow::GetWindow()->GetWidth();
    HEIGHT = Core::CoreWindow::GetWindow()->GetHeight();
    WIDTH_CELLS =
        (WIDTH / TILE_SIZE) + 1; // Number of tiles visible horizontally
    HEIGHT_CELLS =
        (HEIGHT / TILE_SIZE) + 1; // Number of tiles visible vertically
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
    // Draw grass on whole camera
    Core::Renderer::GetRenderer()->Draw(grass, 0, 0, shaders);
    for (int y = 0; y < (HEIGHT / TILE_SIZE) + 1; y++) {
      for (int x = 0; x < (WIDTH / TILE_SIZE) + 1; x++) {
        Core::Renderer::GetRenderer()->Draw(grass, x * TILE_SIZE, y * TILE_SIZE,
                                            shaders);
      }
    }

    // Draw walls and turrets
    // Camera is centered on player (convert tile to pixel for camera)
    int cameraTileX = state.getTileX();
    int cameraTileY = state.getTileY();
    int cameraPixelX = cameraTileX * TILE_SIZE + TILE_SIZE / 2;
    int cameraPixelY = cameraTileY * TILE_SIZE + TILE_SIZE / 2;

    // Calculate which tiles are visible
    int leftTile = cameraTileX - WIDTH_CELLS / 2 - 1;
    int rightTile = cameraTileX + WIDTH_CELLS / 2 + 1;
    int topTile = cameraTileY - HEIGHT_CELLS / 2 - 1;
    int bottomTile = cameraTileY + HEIGHT_CELLS / 2 + 1;

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
          if (grid.at(tileX, tileY).canShoot() &&
              grid.at(state.getTileX(), state.getTileY()).getType() !=
                  CellType::HayStack) {
            int turretPixelX = tileX * TILE_SIZE + TILE_SIZE / 2;
            int turretPixelY = tileY * TILE_SIZE + TILE_SIZE / 2;
            int playerPixelX = state.getTileX() * TILE_SIZE + TILE_SIZE / 2;
            int playerPixelY = state.getTileY() * TILE_SIZE + TILE_SIZE / 2;
            bullets.emplace_back(turretPixelX, turretPixelY, playerPixelX,
                                 playerPixelY, 90.0f, tileX, tileY);
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
    int heartSize = 32;
    int totalWidth = state.getHealth() * heartSize;
    int startX = (WIDTH / 2) - (totalWidth / 2);
    int heartY = 10;
    for (int i = 0; i < state.getHealth(); i++) {
      Core::Renderer::GetRenderer()->Draw(heart, startX + i * heartSize, heartY,
                                          shaders);
    }

    // Update and render bullets
    const float deltaTime = 1.0f / 60.0f;
    std::vector<Bullet> newBullets;
    for (auto &bul : bullets) {
      bul.update(deltaTime);
      int bulletGridX = bul.getGridX(TILE_SIZE);
      int bulletGridY = bul.getGridY(TILE_SIZE);

      // Remove bullets outside viewport (user doesn't want to track off-screen
      // bullets)
      if (bulletGridX < leftTile || bulletGridY < topTile ||
          bulletGridX > rightTile || bulletGridY > bottomTile)
        continue;

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
      int bulletScreenX = bulletScreenCenterX - (TILE_SIZE / 2);
      int bulletScreenY = bulletScreenCenterY - (TILE_SIZE / 2);

      if (bulletScreenX < WIDTH && bulletScreenX + TILE_SIZE > 0 &&
          bulletScreenY < HEIGHT && bulletScreenY + TILE_SIZE > 0) {
        Core::Renderer::GetRenderer()->Draw(bullet, bulletScreenX,
                                            bulletScreenY, shaders);
      }
    }
    bullets = newBullets;
  }

private:
  // Hash function for pair (for unordered_map key)

  std::vector<Bullet> bullets;
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
};
START_CORE_GAME(Game);
