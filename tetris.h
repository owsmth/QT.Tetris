#ifndef TETRIS_H
#define TETRIS_H

#include <QWidget>
#include <QTimer>
#include <vector>

class Tetris : public QWidget {
    Q_OBJECT

public:
    Tetris(QWidget *parent = nullptr);
    void resetGame();

signals:
    void gameOver();

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void updateGame();

private:
    static const int gridWidth = 10;
    static const int gridHeight = 20;
    static const int blockSize = 30;

    std::vector<std::vector<std::vector<int>>> shapes;  // Store multiple shapes
    std::vector<std::vector<int>> currentShape;         // Current falling shape


    std::vector<std::vector<int>> grid; // 2D grid for the game
    int blockX, blockY;                 // Block's current position
    QTimer *timer;

    bool checkCollision(int newX, int newY);
    void lockBlock();
    void spawnBlock();
    void rotateBlock();
};

#endif // TETRIS_H
