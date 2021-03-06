#ifndef BUILDING_H
#define BUILDING_H

#include <atomic>
#include <chrono>
#include <thread>
#include <QString>
#include <math.h>
#include "clickable_label.h"
#include "gold_purse.h"


class Building {
public:
    Building(QString name,
             ClickableLabel *ui_unbuilt,
             ClickableLabel *ui_built,
             GoldPurse *purse,
             int gold_per_tick, int tick_interval, int cost);
    ~Building();

    QString getName();
    int getTier();
    int getCost();
    int getSellCost();
    int getGPT();
    int getTickInterval();
    QPixmap getBuiltImg();

    void upgrade(int x = 1);
    void reset();

private:
    QString name;
    std::atomic_bool active;
    std::thread *worker = nullptr;

    const double GOLD_UPG_PC = 1.25;
    const double TICK_UPG_PC = 0.99;
    const double COST_UPG_PC = 2;
    const double SELL_COST_PC = 0.5;

    int cost;
    int tier = 0;
    GoldPurse *purse;

    ClickableLabel *ui_unbuilt;
    ClickableLabel *ui_built;

    const int BASE_COST;
    const int BASE_GPT;
    const int BASE_TICK_INT;

    std::atomic_int gold_per_tick;
    std::atomic_int tick_interval;  // in ms

    void produce();
};

#endif // BUILDING_H
