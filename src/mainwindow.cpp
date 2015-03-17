#include <QMenuBar>
#include <QTabWidget>

#include "mainwindow.h"
#include "tabwidget.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  initMenuBar();

  qTabWidget = new QTabWidget(this);
  qTabWidget->addTab(new TabWidget(qTabWidget), "First Project");
  qTabWidget->addTab(new TabWidget(qTabWidget), "Second Project");
  qTabWidget->addTab(new TabWidget(qTabWidget), "Third Project");

  ui->gridLayout->addWidget(qTabWidget);
}

void MainWindow::initMenuBar() {
  QMenuBar *menuBar = this->menuBar();

  QMenu *menuFile = new QMenu("File", this);
  menuFile->addAction("Open...");
  menuFile->addAction("Add Curve", this, SLOT(addCurve()),
                      QKeySequence(Qt::CTRL + Qt::Key_A));
  menuFile->addAction("Save...");
  menuFile->addAction("Exit");

  QMenu *menuEdit = new QMenu("Edit", this);
  menuEdit->addAction("Redo", this, SLOT(undoCmd()),
                      QKeySequence(Qt::CTRL + Qt::Key_Z));
  menuEdit->addAction("Undo", this, SLOT(redoCmd()),
                      QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_Z));
  menuEdit->addAction("Copy Curve", this, SLOT(copyCurve()),
                      QKeySequence(Qt::CTRL + Qt::Key_C));
  menuEdit->addAction("Paste Curve", this, SLOT(pasteCurve()),
                      QKeySequence(Qt::CTRL + Qt::Key_V));
  menuEdit->addAction("Remove Curve", this, SLOT(removeCurve()),
                      QKeySequence(Qt::Key_Backspace));

  QMenu *menuAbout = new QMenu("About", this);

  menuBar->addMenu(menuFile);
  menuBar->addMenu(menuEdit);
  menuBar->addMenu(menuAbout);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::addCurve() {
  TabWidget *currentTab =
      reinterpret_cast<TabWidget *>(qTabWidget->currentWidget());
  currentTab->addCurve();
}

void MainWindow::copyCurve() {
  TabWidget *currentTab =
      reinterpret_cast<TabWidget *>(qTabWidget->currentWidget());
  currentTab->copyCurve();
}

void MainWindow::pasteCurve() {
  TabWidget *currentTab =
      reinterpret_cast<TabWidget *>(qTabWidget->currentWidget());
  currentTab->pasteCurve();
}

void MainWindow::removeCurve() {
  TabWidget *currentTab =
      reinterpret_cast<TabWidget *>(qTabWidget->currentWidget());
  currentTab->removeCurve();
}

void MainWindow::redoCmd() {
  TabWidget *currentTab =
      reinterpret_cast<TabWidget *>(qTabWidget->currentWidget());
  currentTab->redoCmd();
}

void MainWindow::undoCmd() {
  TabWidget *currentTab =
      reinterpret_cast<TabWidget *>(qTabWidget->currentWidget());
  currentTab->undoCmd();
}
