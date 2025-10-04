#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Water Alarm");
    connect(&timer1, SIGNAL(timeout()), this, SLOT(CheckTime()));
    timer1.setSingleShot(false);
    timer1.start(1000);
    trayIcon = new QSystemTrayIcon(this);
    QIcon icon = QApplication::style()->standardIcon(QStyle::SP_ComputerIcon);
    trayIcon = new QSystemTrayIcon(icon, this);
    trayIcon->setToolTip("Water Alarm");
    trayIcon->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::CheckTime()
{
    secondsPassed++;
    ui->lcdTimer->display(secondsPassed);

    if(secondsPassed % 10 == 0)
    {
        trayIcon->showMessage("Reminder", "Drink Water", QSystemTrayIcon::Critical, 5000);
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (trayIcon->isVisible())
    {
        this->hide();
        event->ignore();
    } else {
        event->accept();
    }
}

// void MainWindow::onTrayIconActivated(QSystemTrayIcon::ActivationReason reason)
// {
//     if (reason == QSystemTrayIcon::Trigger || reason == QSystemTrayIcon::DoubleClick) {
//         if (isVisible()) {
//             this->hide();
//         } else {
//             this->show();
//             this->activateWindow(); // Bring the window to the front
//         }
//     }
// }
