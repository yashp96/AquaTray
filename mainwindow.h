#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QSystemTrayIcon>
#include <QStyle>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QCloseEvent>
#include <QApplication>
#include <QMessageBox>
#include <QIcon>
#include <QEvent>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTimer timer1;
    int secondsPassed = 0;
    QSystemTrayIcon* SysTrayHandle;
    QAction *HideApp;
    QAction* QuitApp;
    QMenu menu;

    const int DfltReminderInterval = 1800; // in seconds

    void InitSystemTray(QObject *parent);
    void InitTicker(QTimer* timer);

protected:
    void closeEvent(QCloseEvent *event) override;\
    void OnTrayAppActivated(QSystemTrayIcon::ActivationReason reason);
    // void changeEvent(QEvent *event) override;

private slots:
    void CheckTime();
    void RestoreWindow();
    void SureQuit();

};
#endif // MAINWINDOW_H
