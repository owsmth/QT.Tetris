#include "gameoverscreen.h"

GameOverScreen::GameOverScreen(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QLabel *title = new QLabel("Game Over", this);
    title->setAlignment(Qt::AlignCenter);
    QFont titleFont = title->font();
    titleFont.setPointSize(24);
    title->setFont(titleFont);

    restartButton = new QPushButton("Restart", this);
    restartButton->setFixedSize(200, 50);

    connect(restartButton, &QPushButton::clicked, this, &GameOverScreen::restartGame);

    mainLayout->addWidget(title);
    mainLayout->addWidget(restartButton, 0, Qt::AlignCenter);
    mainLayout->setAlignment(Qt::AlignCenter);

    setLayout(mainLayout);
    setWindowTitle("Tetris - Game Over");
    resize(400, 300);
}
