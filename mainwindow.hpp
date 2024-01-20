#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

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

private slots:
    void aButtonClicked();
    void bButtonClicked();
    void cButtonClicked();
    void dButtonClicked();
    void eButtonClicked();

private:
    static QString const sm_logMessagePattern;
    static int constexpr sm_overlayTimeout = 3000; // ms

    Ui::MainWindow *ui;

    void blockingUiEvent(QString const &);
    void connectUiEvents();
    void disableUi();
    void enableUi();
};
#endif // MAINWINDOW_HPP
