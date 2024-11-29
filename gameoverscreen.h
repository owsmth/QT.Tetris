#ifndef GAMEOVERSCREEN_H
#define GAMEOVERSCREEN_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

class GameOverScreen : public QWidget {
    Q_OBJECT

public:
    explicit GameOverScreen(QWidget *parent = nullptr);

signals:
    void restartGame();

private:
    QPushButton *restartButton;
};

#endif // GAMEOVERSCREEN_H
