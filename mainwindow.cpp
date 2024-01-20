#include "mainwindow.hpp"
#include "./ui_mainwindow.h"

#include <QTimer>

QString const MainWindow::sm_logMessagePattern{
    R"([%{time yyyy-MMM-dd h:mm:ss.zzztt}] - %{message})"};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    /***************
     * Boilerplate *
     ***************/
    qSetMessagePattern(sm_logMessagePattern);
    ui->setupUi(this);
    connectUiEvents();
    /*******************
     * End Boilerplate *
     *******************/

    // Guarantee the overlay widget isn't visible.
    ui->overlayGraphicsView->hide();

    // ui->overlayGraphicsView takes over ownership of the new QGraphicsScene on the heap, so no
    //     need to keep a reference to it in the MainWindow class.
    ui->overlayGraphicsView->setScene(new QGraphicsScene{});
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectUiEvents()
{
    // Using connect(...) calls to avoid the clang warning about auto-UIC;
    //     AKA /Slots named on_.* are error prone/ (clazy-connect-by-name).
    connect(ui->aPushButton, &QAbstractButton::clicked, this, &MainWindow::aButtonClicked);
    connect(ui->bPushButton, &QAbstractButton::clicked, this, &MainWindow::bButtonClicked);
    connect(ui->cPushButton, &QAbstractButton::clicked, this, &MainWindow::cButtonClicked);
    connect(ui->dPushButton, &QAbstractButton::clicked, this, &MainWindow::dButtonClicked);
    connect(ui->ePushButton, &QAbstractButton::clicked, this, &MainWindow::eButtonClicked);
}

// Probably redundant, but C.Y.A.
void MainWindow::disableUi()
{
    // All children inherit disabled state. Could be done at a per-widget level.
    ui->centralwidget->setDisabled(true);
}

// Probably redundant, but C.Y.A.
void MainWindow::enableUi()
{
    // All children inherit disabled state. Could be done at a per-widget level.
    ui->centralwidget->setDisabled(false);
}

void MainWindow::blockingUiEvent(QString const &overlayMessage)
{
    qDebug() << QString{"In blockingUiEvent(\"%1\"): showing overlay"}.arg(overlayMessage);

    // Permits overlayGraphicsView widget to be behind the functional UI in Qt Creator's "Design" mode.
    ui->overlayGraphicsView->raise();

    ui->overlayGraphicsView->scene()->clear();
    ui->overlayGraphicsView->scene()->addText(overlayMessage);
    ui->overlayGraphicsView->show();

    disableUi();

    QTimer::singleShot(sm_overlayTimeout, ui->centralwidget, [this, overlayMessage]() {
        // TODO: Other delayed synchronization, state persistence, and/or maintenance activities.

        qDebug() << QString{"In blockingUiEvent(\"%1\"): hiding overlay"}.arg(overlayMessage);
        enableUi();
        ui->overlayGraphicsView->hide();
    });
}

void MainWindow::aButtonClicked()
{
    blockingUiEvent("\"A\" button clicked");
    // TODO: Other immediate synchronization, state persistence, and/or maintenance activities.
}

void MainWindow::bButtonClicked()
{
    blockingUiEvent("\"B\" button clicked");
    // TODO: Other immediate synchronization, state persistence, and/or maintenance activities.
}

void MainWindow::cButtonClicked()
{
    blockingUiEvent("\"C\" button clicked");
    // TODO: Other immediate synchronization, state persistence, and/or maintenance activities.
}

void MainWindow::dButtonClicked()
{
    blockingUiEvent("\"D\" button clicked");
    // TODO: Other immediate synchronization, state persistence, and/or maintenance activities.
}

void MainWindow::eButtonClicked()
{
    blockingUiEvent("\"E\" button clicked");
    // TODO: Other immediate synchronization, state persistence, and/or maintenance activities.
}
