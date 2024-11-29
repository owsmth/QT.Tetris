#include "startscreen.h"

StartScreen::StartScreen(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *title = new QLabel("Welcome to Tetris!", this);
    title->setAlignment(Qt::AlignCenter);
    QFont titleFont = title->font();
    titleFont.setPointSize(24);
    title->setFont(titleFont);

    startButton = new QPushButton("Start Game", this);
    startButton->setFixedSize(200, 50);
    connect(startButton, &QPushButton::clicked, this, &StartScreen::startGame);

    layout->addWidget(title);
    layout->addWidget(startButton, 0, Qt::AlignCenter);
    layout->setAlignment(Qt::AlignCenter);

    setLayout(layout);
    setWindowTitle("Tetris - Start Screen");
    resize(400, 300);
}
