#include <iostream>  // Standard input/output stream
#include <vector>    // Dynamic array container
#include <cstdlib>   // General utilities including rand()
#include <ctime>     // Time-related functions
#include <chrono>    // Time utilities for game loop
#include <thread>    // Sleep functionality
#include <conio.h>   // Console input (kbhit, getch)
#include <windows.h> // Windows API for console control
#include <algorithm> // min/max functions

using namespace std; // Standard namespace

const int BOARD_WIDTH = 10;  // Width of game board in blocks
const int BOARD_HEIGHT = 20; // Height of game board in blocks
const int BASE_SPEED = 1000; // Initial fall speed (ms)
const int MIN_SPEED = 100;   // Minimum fall speed (ms)
const int LEVEL_SCORE = 100; // Points needed per level
const int SPEED_DECREMENT = 100; // Speed decrease per level

enum class TetrominoType { I, J, L, O, S, T, Z }; // All tetromino types

enum ConsoleColor { // Windows console color codes
    BLACK = 0,
    BLUE = 1,
    GREEN = 2,
    CYAN = 3,
    RED = 4,
    MAGENTA = 5,
    YELLOW = 6,
    WHITE = 7,
    GRAY = 8,
    LIGHT_BLUE = 9,
    LIGHT_GREEN = 10,
    LIGHT_CYAN = 11,
    LIGHT_RED = 12,
    LIGHT_MAGENTA = 13,
    LIGHT_YELLOW = 14,
    BRIGHT_WHITE = 15
};

class Tetromino {
private:
    TetrominoType type; // Type of tetromino
    int x, y;           // Position on board
    vector<vector<bool>> shape; // Shape matrix

public:
    Tetromino() : x(0), y(0) {} // Default constructor
    
    TetrominoType getType() const { return type; } // Getter for type
    void setType(TetrominoType newType) { type = newType; } // Setter for type
    
    int getX() const { return x; } // Get X position
    void setX(int newX) { x = newX; } // Set X position
    
    int getY() const { return y; } // Get Y position
    void setY(int newY) { y = newY; } // Set Y position
    
    const vector<vector<bool>>& getShape() const { return shape; } // Get shape
    void setShape(const vector<vector<bool>>& newShape) { shape = newShape; } // Set shape

    ConsoleColor getColor() const { // Get color based on type
        switch (type) {
            case TetrominoType::O: return YELLOW;
            case TetrominoType::I: return LIGHT_BLUE;
            case TetrominoType::S: return LIGHT_RED;
            case TetrominoType::Z: return LIGHT_GREEN;
            case TetrominoType::L: return YELLOW; 
            case TetrominoType::J: return LIGHT_MAGENTA; 
            case TetrominoType::T: return MAGENTA; 
            default: return WHITE;
        }
    }
};

vector<vector<bool>> board(BOARD_HEIGHT, vector<bool>(BOARD_WIDTH, false)); // Game board (filled cells)
vector<vector<ConsoleColor>> boardColors(BOARD_HEIGHT, vector<ConsoleColor>(BOARD_WIDTH, BLACK)); // Cell colors
Tetromino currentPiece;  // Current falling piece
int score = 0;           // Current score
int level = 1;           // Current level
bool gameOver = false;   // Game state flag

void setColor(ConsoleColor color) { // Set console text color
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void hideCursor() { // Hide console cursor
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void showCursor() { // Show console cursor
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = TRUE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void initializeTetromino(Tetromino& tetromino) { // Initialize piece shape/position
    tetromino.setX(BOARD_WIDTH / 2 - 2); // Center horizontally
    tetromino.setY(0); // Start at top
    switch (tetromino.getType()) { // Set shape based on type
        case TetrominoType::I: tetromino.setShape({{true, true, true, true}}); break;
        case TetrominoType::J: tetromino.setShape({{true, false, false}, {true, true, true}}); break;
        case TetrominoType::L: tetromino.setShape({{false, false, true}, {true, true, true}}); break;
        case TetrominoType::O: tetromino.setShape({{true, true}, {true, true}}); break;
        case TetrominoType::S: tetromino.setShape({{false, true, true}, {true, true, false}}); break;
        case TetrominoType::T: tetromino.setShape({{false, true, false}, {true, true, true}}); break;
        case TetrominoType::Z: tetromino.setShape({{true, true, false}, {false, true, true}}); break;
    }
}

TetrominoType getRandomTetrominoType() { // Get random piece type
    return static_cast<TetrominoType>(rand() % 7);
}

void spawnNewPiece() { // Create new random piece
    currentPiece.setType(getRandomTetrominoType());
    initializeTetromino(currentPiece);
}

bool isCollision() { // Check for collisions
    const auto& shape = currentPiece.getShape();
    for (size_t y = 0; y < shape.size(); ++y) {
        for (size_t x = 0; x < shape[y].size(); ++x) {
            if (shape[y][x]) {
                int boardX = currentPiece.getX() + x;
                int boardY = currentPiece.getY() + y;
                if (boardX < 0 || boardX >= BOARD_WIDTH || boardY >= BOARD_HEIGHT ||
                    (boardY >= 0 && board[boardY][boardX])) {
                    return true;
                }
            }
        }
    }
    return false;
}

void mergePieceToBoard() { // Lock piece into board
    const auto& shape = currentPiece.getShape();
    ConsoleColor color = currentPiece.getColor();
    for (size_t y = 0; y < shape.size(); ++y) {
        for (size_t x = 0; x < shape[y].size(); ++x) {
            if (shape[y][x]) {
                board[currentPiece.getY() + y][currentPiece.getX() + x] = true;
                boardColors[currentPiece.getY() + y][currentPiece.getX() + x] = color;
            }
        }
    }
}

void clearLines() { // Check and clear completed lines
    int linesCleared = 0;
    for (int y = BOARD_HEIGHT - 1; y >= 0; --y) {
        bool lineFull = true;
        for (int x = 0; x < BOARD_WIDTH; ++x) {
            if (!board[y][x]) {
                lineFull = false;
                break;
            }
        }
        if (lineFull) {
            linesCleared++;
            for (int yy = y; yy > 0; --yy) {
                board[yy] = board[yy - 1];
                boardColors[yy] = boardColors[yy - 1];
            }
            board[0] = vector<bool>(BOARD_WIDTH, false);
            boardColors[0] = vector<ConsoleColor>(BOARD_WIDTH, BLACK);
            ++y;
        }
    }
    
    if (linesCleared > 0) { // Update score
        int points = 0;
        switch (linesCleared) {
            case 1: points = 100; break;
            case 2: points = 300; break;
            case 3: points = 500; break;
            case 4: points = 800; break;
        }
        score += points;
        
        int newLevel = score / LEVEL_SCORE + 1; // Check level up
        if (newLevel > level) {
            level = newLevel;
            system("cls");
            setColor(LIGHT_YELLOW);
            cout << "\n\n      LEVEL UP!\n";
            cout << "    Now at level " << level << "!\n";
            cout << "    Speed increased!\n";
            Sleep(800);
            setColor(WHITE);
        }
    }
}

void rotatePiece() { // Rotate current piece
    const auto& originalShape = currentPiece.getShape();
    vector<vector<bool>> rotated(originalShape[0].size(), 
                                    vector<bool>(originalShape.size()));
    for (size_t y = 0; y < originalShape.size(); ++y) {
        for (size_t x = 0; x < originalShape[y].size(); ++x) {
            rotated[x][originalShape.size() - 1 - y] = originalShape[y][x];
        }
    }
    currentPiece.setShape(rotated);
    if (isCollision()) { // Revert if collision
        currentPiece.setShape(originalShape);
    }
}

void drawBoard() { // Render game state
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {0, 0};
    SetConsoleCursorPosition(hConsole, coord);
    
    setColor(WHITE);
    cout << "Score: " << score << "   Level: " << level << "   Speed: " 
              << max(MIN_SPEED, BASE_SPEED - (level-1)*SPEED_DECREMENT) << "ms\n";
    cout << "Next Level in: " << LEVEL_SCORE - (score % LEVEL_SCORE) << " points\n";
    
    const auto& currentShape = currentPiece.getShape();
    ConsoleColor currentColor = currentPiece.getColor();
    for (int y = 0; y < BOARD_HEIGHT; ++y) {
        for (int x = 0; x < BOARD_WIDTH; ++x) {
            bool isCurrent = false;
            for (size_t pieceY = 0; pieceY < currentShape.size(); ++pieceY) {
                for (size_t pieceX = 0; pieceX < currentShape[pieceY].size(); ++pieceX) {
                    if (currentShape[pieceY][pieceX] && 
                        x == currentPiece.getX() + pieceX && 
                        y == currentPiece.getY() + pieceY) {
                        isCurrent = true;
                    }
                }
            }
            
            if (isCurrent) {
                setColor(currentColor);
                cout << "[]";
            } else if (board[y][x]) {
                setColor(boardColors[y][x]);
                cout << "##";
            } else {
                setColor(BLACK);
                cout << "  ";
            }
        }
        setColor(WHITE);
        cout << "\n";
    }
    setColor(WHITE);
    cout << string(BOARD_WIDTH * 2, '-') << "\n";
    cout << "Controls: [A]Left [D]Right [W]Rotate [S]Drop [Space]Hard Drop\n";
    cout << "          [R]Restart [Q]Quit\n";
}

void resetGame() { // Reset game state
    system("cls");
    board = vector<vector<bool>>(BOARD_HEIGHT, vector<bool>(BOARD_WIDTH, false));
    boardColors = vector<vector<ConsoleColor>>(BOARD_HEIGHT, vector<ConsoleColor>(BOARD_WIDTH, BLACK));
    score = 0;
    level = 1;
    gameOver = false;
    spawnNewPiece();
}

void gameLoop() { // Main game loop
    hideCursor();
    resetGame();
    
    auto lastFallTime = chrono::steady_clock::now();
    while (!gameOver) {
        int currentSpeed = max(MIN_SPEED, BASE_SPEED - (level-1)*SPEED_DECREMENT);
        
        drawBoard();
        
        if (_kbhit()) { // Handle input
            char key = _getch();
            switch (tolower(key)) {
                case 'a': 
                    currentPiece.setX(currentPiece.getX() - 1);
                    if (isCollision()) currentPiece.setX(currentPiece.getX() + 1);
                    break;
                case 'd': 
                    currentPiece.setX(currentPiece.getX() + 1);
                    if (isCollision()) currentPiece.setX(currentPiece.getX() - 1);
                    break;
                case 's': 
                    currentPiece.setY(currentPiece.getY() + 1);
                    if (isCollision()) {
                        currentPiece.setY(currentPiece.getY() - 1);
                        mergePieceToBoard();
                        clearLines();
                        spawnNewPiece();
                        if (isCollision()) gameOver = true;
                    }
                    break;
                case 'w': rotatePiece(); break;
                case ' ': 
                    while (!isCollision()) currentPiece.setY(currentPiece.getY() + 1);
                    currentPiece.setY(currentPiece.getY() - 1);
                    mergePieceToBoard();
                    clearLines();
                    spawnNewPiece();
                    if (isCollision()) gameOver = true;
                    break;
                case 'r': resetGame(); break;
                case 'q': gameOver = true; break;
            }
        }
        
        auto currentTime = chrono::steady_clock::now(); // Automatic falling
        if (chrono::duration_cast<chrono::milliseconds>(currentTime - lastFallTime).count() > currentSpeed) {
            currentPiece.setY(currentPiece.getY() + 1);
            if (isCollision()) {
                currentPiece.setY(currentPiece.getY() - 1);
                mergePieceToBoard();
                clearLines();
                spawnNewPiece();
                if (isCollision()) gameOver = true;
            }
            lastFallTime = currentTime;
        }
        Sleep(30); // Small delay to reduce CPU usage
    }
    
    showCursor();
    system("cls");
    setColor(LIGHT_RED);
    cout << "\n\n  GAME OVER!\n";
    setColor(WHITE);
    cout << "  Final Score: " << score << "\n";
    cout << "  Final Level: " << level << "\n";
    cout << "  Speed Reached: " << max(MIN_SPEED, BASE_SPEED - (level-1)*SPEED_DECREMENT) << "ms\n\n";
    cout << "  Press R to restart or any other key to quit\n";
    
    if (_getch() == 'r' || _getch() == 'R') { // Restart check
        gameLoop();
    }
}

int main() { // Entry point
    srand(static_cast<unsigned>(time(nullptr))); // Seed random generator
    gameLoop(); // Start game
    showCursor(); // Ensure cursor is visible on exit
    return 0;
}