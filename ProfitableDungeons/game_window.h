#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "building_dialog.h"
#include "buy_dialog.h"
#include "building.h"
#include "gold_purse.h"

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

private slots:
    void on_tavern_clicked();
    void on_castle_clicked();
    void on_castle_unbuilt_clicked();
    void on_apple_unbuilt_clicked();
    void on_apple_built_clicked();
    void on_apple_clicked();
    void on_inn_unbuilt_clicked();
    void on_inn_clicked();
    void on_farm_unbuilt_clicked();
    void on_farm_clicked();

private:
    Ui::GameWindow *ui;
    GoldPurse *purse;
    QMap <QString, Building*> buildings;

    void unbuilt_clicked(QString key);
    void built_clicked(QString key);
};

#endif // GAME_WINDOW_H