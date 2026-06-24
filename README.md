# Tetris_game
This C++ Tetris is a high-performance console game using Windows APIs for smooth, flicker-free rendering. It features a modular, object-oriented engine managing grid logic, collision detection, and dynamic difficulty scaling. The game utilizes non-blocking I/O and timers to accelerate gameplay as players advance.

# C++ Console Tetris

A high-performance, object-oriented C++ implementation of the classic Tetris game, meticulously designed for the Windows console environment to provide an authentic, smooth, and challenging arcade experience.

## 1. Comprehensive Features & Capabilities
* **Dynamic Difficulty Scaling:** The game engine intelligently monitors your total score, automatically decreasing the `currentSpeed` variable by the `SPEED_DECREMENT` value every time you reach a new `LEVEL_SCORE` milestone, ensuring the game becomes progressively more challenging.
* **Efficient, Flicker-Free Rendering Engine:** By leveraging the Windows API (`SetConsoleCursorPosition`), the game avoids the standard performance-heavy `system("cls")` method. It updates only the specific coordinates of the grid, ensuring a smooth, flicker-free visual experience.
* **Proactive Collision Detection:** Before every single frame update, movement command, or rotation, the `isCollision()` function performs a rigorous boundary and overlap validation check against the existing `board` matrix to prevent illegal placements.
* **Versatile Non-Blocking Input Handling:** Utilizing `<conio.h>`, the game captures player keystrokes instantly without pausing the game loop. This allows for fluid movement, rotations, and drops while the automatic gravity timer continues to function seamlessly in the background.
* **Advanced State Management:** The game maintains dual-layered tracking: a boolean `board` matrix for spatial occupancy and a `boardColors` matrix for aesthetic integrity, allowing each piece type to retain its unique, vibrant console color even after being locked into the grid.
* **Hard Drop Mechanism:** Players can instantly commit a piece to its lowest legal position using the `Spacebar`, utilizing a loop that updates the `y` coordinate until a collision is detected.
* **Smart Line-Clearing Logic:** The system features a dedicated `clearLines()` function that scans the board from bottom to top, identifying full rows, awarding points based on the number of cleared lines (up to 800 for a Tetris!), and shifting remaining blocks downward to consolidate the grid.

## 2. Control Scheme
| Action | Key | Description |
| :--- | :--- | :--- |
| Move Left | `A` | Shifts the active tetromino one column left. |
| Move Right | `D` | Shifts the active tetromino one column right. |
| Rotate Piece | `W` | Rotates the tetromino 90 degrees clockwise. |
| Soft Drop | `S` | Increases descent speed for the current piece. |
| Hard Drop | `Space` | Instantly drops the piece to the lowest possible position. |
| Restart | `R` | Resets the grid and score while keeping the process open. |
| Quit Game | `Q` | Safely terminates the game loop and exits to console. |

## 3. Technical Implementation Details
* **Windows API Integration:** The project interfaces directly with `STD_OUTPUT_HANDLE` to control console output attributes, enabling distinct color-coding for every `TetrominoType` through `SetConsoleTextAttribute`.
* **Precision Timing:** By utilizing the C++ `<chrono>` library, the game manages a high-resolution steady clock to calculate exact millisecond intervals for piece descent, ensuring the game runs at a consistent speed regardless of CPU load.
* **Object-Oriented Architecture:** The `Tetromino` class serves as the modular backbone of the application, encapsulating geometric bit-mapping, screen coordinate state, and color-mapping properties, which promotes clean and maintainable code.
* **Memory & Performance:** The game utilizes a lightweight `std::vector` structure for dynamic grid management, keeping the memory footprint minimal while ensuring rapid iteration and data retrieval during the rendering loop.

## 4. Installation & Deployment
1. **System Requirements:** Ensure your machine is running Windows, as the project relies on `<windows.h>` and `<conio.h>`.
2. **Environment:** Clone the repository and load the files into a modern C++ IDE like Visual Studio, CLion, or VS Code with the C++ extension.
3. **Compilation:** Use a standard C++ compiler (e.g., G++ or MSVC). For G++, run: `g++ main.cpp -o tetris.exe`.
4. **Execution:** Launch the resulting `tetris.exe` directly via the Command Prompt or PowerShell to ensure full support for the Windows API color codes.

---



