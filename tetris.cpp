#include "tetris.h"
#include <QPainter>
#include <QKeyEvent>
#include <cstdlib>
#include <ctime>

Tetris::Tetris(QWidget *parent) : QWidget(parent), blockX(0), blockY(0) {
    setFixedSize(gridWidth * blockSize, gridHeight * blockSize);

    // Initialize grid
    grid.resize(gridHeight, std::vector<int>(gridWidth, 0));

    // Define shapes
    shapes = {
        {{1, 1}, {1, 1}},          // Square shape
        {{1, 0}, {1, 0}, {1, 1}},  // L shape
        {{1,1,1}, {0,1,0}},        //T shape
        {{1,1,1}, {0,1,1}},        //Square with additional block
    };

    // Initialize timer
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Tetris::updateGame);
    timer->start(500);

    // Seed random generator
    srand(static_cast<unsigned>(time(0)));

    // Spawn the first block
    spawnBlock();
}

void Tetris::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    // Draw locked grid cells
    for (int y = 0; y < gridHeight; ++y) {
        for (int x = 0; x < gridWidth; ++x) {
            if (grid[y][x] == 1) {
                painter.fillRect(x * blockSize, y * blockSize, blockSize, blockSize, Qt::blue);
            }
        }
    }

    // Draw the current shape
    for (std::size_t y = 0; y < currentShape.size(); ++y) {
        for (std::size_t x = 0; x < currentShape[y].size(); ++x) {
            if (currentShape[y][x] == 1) {
                int drawX = (blockX + x) * blockSize;
                int drawY = (blockY + y) * blockSize;
                painter.fillRect(drawX, drawY, blockSize, blockSize, Qt::red);
            }
        }
    }
}

void Tetris::spawnBlock() {
    currentShape = shapes[rand() % shapes.size()];
    blockX = gridWidth / 2 - currentShape[0].size() / 2;
    blockY = 0;

    if (checkCollision(blockX, blockY)) {
        timer->stop();
        qDebug() << "Game Over!";
    }
}

void Tetris::rotateBlock() {
    // Save the original shape before rotation
    auto originalShape = currentShape;

    // Rotate the current shape 90 degrees clockwise
    int rows = currentShape.size();
    int cols = currentShape[0].size();
    std::vector<std::vector<int>> rotatedShape(cols, std::vector<int>(rows));

    // Transpose and reverse the rows
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            rotatedShape[x][rows - 1 - y] = currentShape[y][x];
        }
    }

    // Check if rotation causes a collision or goes out of bounds
    currentShape = rotatedShape;

    // Try to place the rotated block. If it collides, revert to the original shape.
    if (checkCollision(blockX, blockY)) {
        currentShape = originalShape;  // Revert rotation if there's a collision
    }
}



void Tetris::keyPressEvent(QKeyEvent *event) {
    int newX = blockX;
    int newY = blockY;

    switch (event->key()) {
    case Qt::Key_Left:
        newX--;
        break;
    case Qt::Key_Right:
        newX++;
        break;
    case Qt::Key_Down:
        newY++;
        break;
    case Qt::Key_Up:
        rotateBlock();
        break;
    }

    // Move shape if no collision
    if (!checkCollision(newX, newY)) {
        blockX = newX;
        blockY = newY;
        update();
    }
}

void Tetris::updateGame() {
    if (!checkCollision(blockX, blockY + 1)) {
        blockY++;
    } else {
        lockBlock();
        spawnBlock();
    }
    update();
}

bool Tetris::checkCollision(int newX, int newY) {
    for (std::size_t y = 0; y < currentShape.size(); ++y) {
        for (std::size_t x = 0; x < currentShape[y].size(); ++x) {
            if (currentShape[y][x] == 1) {
                int gridX = newX + x;
                int gridY = newY + y;

                // Check bounds
                if (gridX < 0 || gridX >= gridWidth || gridY >= gridHeight) {
                    return true;
                }

                // Check collision with locked cells
                if (gridY >= 0 && grid[gridY][gridX] == 1) {
                    return true;
                }
            }
        }
    }
    return false;
}

void Tetris::lockBlock() {
    for (std::size_t y = 0; y < currentShape.size(); ++y) {
        for (std::size_t x = 0; x < currentShape[y].size(); ++x) {
            if (currentShape[y][x] == 1) {
                int gridX = blockX + x;
                int gridY = blockY + y;

                // Lock only valid grid cells
                if (gridX >= 0 && gridX < gridWidth && gridY >= 0 && gridY < gridHeight) {
                    grid[gridY][gridX] = 1;
                }
            }
        }
    }
}
