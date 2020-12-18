#include "building.h"


/**
 * Base constructor.
 */
Building::Building(QString name,
                   ClickableLabel *ui_unbuilt,
                   ClickableLabel *ui_built,
                   GoldPurse *purse,
                   int gold_per_tick, int tick_interval, int cost)
{
    this->name = name;
    this->active = false;
    this->ui_unbuilt = ui_unbuilt;
    this->ui_built = ui_built;
    this->purse = purse;
    this->gold_per_tick = gold_per_tick;
    this->tick_interval = tick_interval;
    this->cost = cost;

    if(ui_unbuilt != nullptr) {
        ui_built->setVisible(false);
        ui_unbuilt->setVisible(true);
    }
}


/**
 * Destructor. Necessary to stop the production thread.
 */
Building::~Building() {
    this->active = false;
    this->worker->join();
}


QString Building::getName() {
    return this->name;
}


int Building::getCost() {
    return this->cost;
}


/**
 * Handle the production of the building.
 */
void Building::produce() {
    while(this->active) {
        this->purse->addGold(this->gold_per_tick);
        std::this_thread::sleep_for(std::chrono::milliseconds(this->tick_interval));
    }
}


/**
 * Upgrades the building's tier.
 */
void Building::upgrade() {
    this->tier++;

    // shows building
    if(this->tier == 1 && ui_unbuilt != nullptr) {
        this->ui_unbuilt->setVisible(false);
        this->ui_built->setVisible(true);
    }

    // starts production
    if(!this->active) {
        this->active = true;
        this->worker = new std::thread(&Building::produce, this);
    }

    // updates gold per tick, tick interval and cost
    // to_do
}