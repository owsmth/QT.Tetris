#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

class StartScreen : public QWidget {
    Q_OBJECT

public:
    explicit StartScreen(QWidget *parent = nullptr);

signals:
    void startGame();

private:
    QPushButton *startButton;
};

#endif // STARTSCREEN_H
