# SFMLGameEngine

A modular and lightweight 2D game engine built using C++ and SFML.  
This engine provides a solid foundation for developing 2D games, featuring an entity-component system, asset management, animation handling, and basic physics integration.

---

## ✨ Features

- **Entity-Component System (ECS):** Flexible architecture allowing dynamic composition of game entities.
- **Asset Management:** Efficient loading and management of textures, fonts, and other resources.
- **Animation System:** Support for sprite animations with customizable frame sequences.
- **Physics Integration:** Basic physics components for movement and collision detection.
- **Modular Design:** Clean separation of concerns, making it easy to extend and maintain.

---

## 🛠 Getting Started

### Prerequisites

- C++17 compatible compiler (e.g. g++, clang++)
- [SFML 2.5+](https://www.sfml-dev.org/download.php)

### Build Instructions (Manual Compilation)

Compile using `g++` (Linux/macOS) or any C++ compiler with SFML linked:

```bash
g++ -std=c++17 -o SFMLGameEngine \
Main.cpp Game.cpp GameEngine.cpp Entity.cpp EntityManager.cpp \
Components.cpp Assets.cpp Animation.cpp Physics.cpp \
-lsfml-graphics -lsfml-window -lsfml-system
