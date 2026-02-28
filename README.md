[[<video src="GameDemo.mp4" width="320" height="240" controls></video>](https://github.com/user-attachments/assets/795e7087-f802-4f)](https://github.com/user-attachments/assets/795e7087-f802-4f8f-9164-684e6921779b)
## Game Overview
Built on Game Engine built around GLFW
### Objective
Guide your soldier through a dangerous farm to reach the barn and find shelter from hostile alien UFOs. Navigate carefully, use cover wisely, and manage your health to survive the journey.

### Map Generation
- The farm map is **randomly generated** every time you play
- Despite being random, a path to the barn is **always guaranteed** to exist
- Each playthrough offers a unique layout and challenge

### The Threat: Alien UFOs
- UFOs patrol the farm shooting **plasma balls** at the soldier
- Each plasma ball hit deals **1 damage** to the soldier
- UFOs will relentlessly pursue and shoot at exposed targets
- However, UFOs **cannot see through haystacks** - use this to your advantage!

### Health System
- The soldier starts with **3 health points**
- Getting hit by a plasma ball reduces health by **1 point**
- When health reaches **0**, the game is over
- Health can be restored by eating steak (see below)

### Cows and Healing
- Cows roam the farm and can be caught in the crossfire
- When a cow is hit **3 times** by plasma balls, the heat cooks it into **steak**
- The soldier can **eat the steak to heal** and restore health
- Strategic positioning near cows can provide healing opportunities

### Haystacks: Your Shelter
- Haystacks are scattered throughout the farm
- **Hiding in a haystack** makes the soldier invisible to UFOs
- UFOs **stop shooting** when they can't see the soldier
- Haystacks are fragile with only **1 health point**
- When destroyed, haystacks turn into **grass** and no longer provide cover
- Use haystacks strategically to advance safely through dangerous areas

### Bombs
- **Left-click** to throw bombs at any location on the map
- **5 bombs** total per round - use them wisely!
- Bombs deal **1 damage** to the target cell **and all 8 surrounding cells** (3x3 area)
- **UFOs have 5 health** - requires 5 hits to destroy (bullets or bombs)
- Strategic uses:
  - Turn cows into steaks to heal yourself
  - Destroy UFOs blocking your path
  - Clear obstacles from a distance
- Bomb counter displayed in bottom-left corner (decreases as you throw)

## Building and Running the Game

### Prerequisites
- CMake 3.24 or higher
- C++20 compatible compiler
- Git

### Clone the Repository
First, clone the repository **recursively** to include all submodules (GLFW):

```bash
git clone --recursive <repository-url>
cd Fall_25_Marcin_Zarkowski
```

If you already cloned the repository without `--recursive`, initialize the submodules:

```bash
git submodule update --init --recursive
```

### Build with CMake

1. **Create a build directory:**
   ```bash
   mkdir build
   cd build
   ```

2. **Configure the project with CMake:**
   ```bash
   cmake ..
   ```

3. **Compile the game:**
   ```bash
   cmake --build .
   ```

   Or use `make` directly:
   ```bash
   make
   ```

### Run the Game

After building successfully, run the executable from the build directory:

```bash
./GameApp
```

The game will launch and you can start playing! Use the controls to navigate your soldier through the farm to the barn.
