#include "game_window.h"
#include "ui_game_window.h"


/**
 * Constructor.
 */
GameWindow::GameWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    setFixedSize(size());

    // centering window
    QRect desktopRect = QApplication::desktop()->availableGeometry(this);
    QPoint center = desktopRect.center();
    move(center.x() - width() * 0.5, center.y() - height() * 0.5);

    // initializing gold purse
    this->purse = new GoldPurse(ui->gold_label);
    purse->addGold(100);  // initial gold

    // initializing buildings
    this->buildings["castle"] = new Building("Castle",
                                             ui->castle_unbuilt, ui->castle,
                                             this->purse,
                                             500, 1000, 100000);
    this->buildings["tavern"] = new Building("Tavern",
                                             nullptr, ui->castle,
                                             this->purse,
                                             30, 1000, 500);
    this->buildings["apple"] = new Building("Apple Orchard",
                                            ui->apple_unbuilt, ui->apple,
                                            this->purse,
                                            5, 250, 100);
    this->buildings["inn"] = new Building("Inn",
                                          ui->inn_unbuilt, ui->inn,
                                          this->purse,
                                          60, 3000, 250);
    this->buildings["farm"] = new Building("Farm",
                                          ui->farm_unbuilt, ui->farm,
                                          this->purse,
                                          15, 500, 150);
}


/**
 * Destructor.
 */
GameWindow::~GameWindow() {
    delete ui;
}


/**
 * Handles what happens when the user clicks on a building.
 * @param key
 */
void GameWindow::built_clicked(QString key) {
    BuildingDialog *dialog = new BuildingDialog(nullptr, this->buildings[key]->getName());
    dialog->exec();
}


/**
 * Handles what happens when the user clicks on an unbuilt building.
 * @param key
 */
void GameWindow::unbuilt_clicked(QString key) {
    Building *b = this->buildings[key];
    BuyDialog *dialog = new BuyDialog(nullptr, b->getName(), b->getCost());
    dialog->exec();

    if(dialog->accepted_buying) {
        if(purse->getBalance() >= b->getCost()) {
            this->purse->addGold(-b->getCost());
            b->upgrade();
        }
        else {
            QMessageBox *dialog = new QMessageBox();
            dialog->setWindowTitle("Not enough gold!");
            dialog->setText(
                QString("You don't have enough gold (%1 gold missing).")
                    .arg(b->getCost() - this->purse->getBalance()));
            dialog->show();
        }
    }
}


// Tavern
void GameWindow::on_tavern_clicked() {this->built_clicked("tavern");}

// Castle
void GameWindow::on_castle_unbuilt_clicked() {this->unbuilt_clicked("castle");}
void GameWindow::on_castle_clicked() {this->built_clicked("castle");}

// Apple Orchard
void GameWindow::on_apple_unbuilt_clicked() {this->unbuilt_clicked("apple");}
void GameWindow::on_apple_built_clicked() {this->built_clicked("apple");}
void GameWindow::on_apple_clicked() {this->built_clicked("apple");}

// Inn
void GameWindow::on_inn_unbuilt_clicked() {this->unbuilt_clicked("inn");}
void GameWindow::on_inn_clicked() {this->built_clicked("inn");}

// Farm
void GameWindow::on_farm_unbuilt_clicked() {this->unbuilt_clicked("farm");}
void GameWindow::on_farm_clicked() {this->built_clicked("farm");}