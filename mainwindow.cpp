#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("AquaTray");
    InitSystemTray(this);
    InitTicker(&timer1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitSystemTray(QObject *parent)
{
    QIcon icon = QApplication::style()->standardIcon(QStyle::SP_ComputerIcon);
    SysTrayHandle = new QSystemTrayIcon(icon, parent);

    HideApp = new QAction(tr("&Show"), parent);
    connect(HideApp, &QAction::triggered, this, &MainWindow::RestoreWindow);
    menu.addAction(HideApp);
    menu.addSeparator();

    QuitApp = new QAction(tr("&Quit"), parent);
    connect(QuitApp, &QAction::triggered, this, &MainWindow::SureQuit);
    menu.addAction(QuitApp);
    SysTrayHandle->setContextMenu(&menu);

    SysTrayHandle->setToolTip("AquaTray");
    connect(SysTrayHandle, &QSystemTrayIcon::activated, this, &MainWindow::OnTrayAppActivated);
    SysTrayHandle->show();
}

void MainWindow::InitTicker(QTimer *timer)
{
    connect(timer, SIGNAL(timeout()), this, SLOT(CheckTime()));
    timer->setSingleShot(false);
    timer->start(1000);
}

void MainWindow::CheckTime()
{
    secondsPassed++;
    ui->lcdTimer->display(secondsPassed);

    if(secondsPassed % DfltReminderInterval == 0)
    {
        SysTrayHandle->showMessage("Reminder", "Drink Water", QSystemTrayIcon::Critical, 5000);
        ui->ToastMessage->setText("Drink Water!");
    }
    else if (secondsPassed % 10 == 0) // action at every 10s
    {
        if(!ui->ToastMessage->text().isEmpty())
        {
            ui->ToastMessage->clear();
        }
    }
    else
    {

    }
}

void MainWindow::RestoreWindow()
{
    this->show();
}

void MainWindow::SureQuit()
{
    this->close();
    qApp->quit();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (SysTrayHandle->isVisible())
    {
        this->hide();
        event->ignore();
    } else {
        event->accept();
    }
}

void MainWindow::OnTrayAppActivated(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::Trigger || reason == QSystemTrayIcon::DoubleClick) {
        if (isVisible()) {
            this->hide();
        } else {
            this->show();
            this->activateWindow();
        }
    }
}
