# 🧩 C++ Console Tetris 🎮

A high-performance, object-oriented C++ implementation of the classic Tetris game, meticulously designed for the Windows console environment to provide an authentic, smooth, and challenging arcade experience. 🚀

---

## 🌟 1. Comprehensive Features & Capabilities
* **📈 Dynamic Difficulty Scaling:** The game engine intelligently monitors your total score, automatically decreasing the fall speed every time you reach a new level milestone, ensuring the game becomes progressively more intense!
* **⚡ Efficient, Flicker-Free Rendering:** By leveraging the Windows API (`SetConsoleCursorPosition`), the game avoids the standard performance-heavy screen refresh method. It updates only the specific grid coordinates, ensuring a butter-smooth visual experience.
* **🛡️ Proactive Collision Detection:** Before every frame update, move, or rotation, the `isCollision()` function performs a rigorous validation check against the board matrix to prevent illegal placements.
* **🕹️ Versatile Non-Blocking Input:** Utilizing `<conio.h>`, the game captures player keystrokes instantly without pausing the loop. This allows for fluid movement and rotations while the gravity timer continues to function seamlessly.
* **🎨 Advanced State Management:** The game maintains dual-layered tracking (occupancy and color), allowing each unique piece to retain its vibrant console color even after being locked into the grid.
* **💥 Hard Drop Mechanism:** Need to act fast? Instantly commit your piece to its lowest legal position using the `Spacebar` for those clutch plays!
* **🧹 Smart Line-Clearing Logic:** The `clearLines()` function scans for full rows, awards massive points for clearing multiple lines at once, and consolidates the board by shifting blocks downward.

---

## ⌨️ 2. Control Scheme
| Action | Key | Description |
| :--- | :--- | :--- |
| Move Left | `A` | Shifts the active tetromino one column left. |
| Move Right | `D` | Shifts the active tetromino one column right. |
| Rotate Piece | `W` | Rotates the tetromino 90 degrees clockwise. |
| Soft Drop | `S` | Increases descent speed for the current piece. |
| Hard Drop | `Space` | Instantly drops the piece to the lowest position. |
| Restart | `R` | Resets the game session instantly. |
| Quit Game | `Q` | Safely terminates the game loop. |

---

## ⚙️ 3. Technical Implementation
* **🖥️ Windows API Integration:** Interfaces directly with `STD_OUTPUT_HANDLE` to control console output attributes, enabling distinct color-coding for every `TetrominoType`.
* **⏱️ Precision Timing:** Uses the C++ `<chrono>` library to calculate exact millisecond intervals for piece descent, ensuring consistent speed regardless of CPU load.
* **🏗️ Object-Oriented Architecture:** The `Tetromino` class serves as the modular backbone, encapsulating geometric mapping, coordinates, and color-mapping properties for clean, maintainable code.
* **🧠 Memory & Performance:** Uses a lightweight `std::vector` structure for dynamic grid management, keeping the memory footprint minimal for rapid, real-time gameplay.

---

## 🚀 4. Installation & Deployment
1. **Requirements:** Windows OS is required due to `<windows.h>` and `<conio.h>` dependencies.
2. **Setup:** Clone the repository and load it into your preferred C++ IDE (VS Code, Visual Studio, or CLion).
3. **Compile:** Use your favorite compiler (e.g., G++): 
   `g++ main.cpp -o tetris.exe`
4. **Play:** Launch `tetris.exe` in your terminal to begin your journey! 🕹️

---

## 🔮 Future Roadmap
* **✨ Next Piece Preview:** Add a UI sidebar to display upcoming pieces.
* **🏆 High Score Tracker:** Implement local file I/O to save your personal bests.
* **🔊 Sound Effects:** Integrate Windows Multimedia API for retro sound cues.

---
