/*
 *   Copyright DATAN(c) 2023
 *   3DViewer_v1.0 made by bernardi, joaquind, stonehom, hazzeasu, killeral
 *   All rights reserved.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <stdlib.h>

#include <QColor>
#include <QColorDialog>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QMainWindow>
#include <QSettings>
#include <QTimer>
#include <cstring>

#include "glwidget.h"
#include "qgifimage.h"

extern "C" {
#include "../backend/s21_3DViewer_v1.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void xTranslateTextEdit();
  void yTranslateTextEdit();
  void zTranslateTextEdit();

  void xTranslateSliderValueChanged(int value);
  void yTranslateSliderValueChanged(int value);
  void zTranslateSliderValueChanged(int value);

  void xRotateTextEdit();
  void yRotateTextEdit();
  void zRotateTextEdit();

  void xRotateValueChanged(int value);
  void yRotateValueChanged(int value);
  void zRotateValueChanged(int value);

  void scaleTextEdit();
  void scaleSliderValueChanged(int value);

  void projectionParallel();
  void projectionCentral();

  void DisableView();
  void CircleView();
  void SquareView();
  void resetValue();

  void vertexSize(int value);

  void linesTypeSolid();
  void linesTypeDashed();
  void linesSizeSliderChanged(int value);

  void on_action_triggered();

  void onChangeLineColor();
  void onChangeBackgroundColor();
  void onChangeDotColor();

  void on_bmp_button_clicked();

  void on_gif_button_clicked();

  void slotTimer();

 private:
  Ui::MainWindow *ui;
  QString settingFile;
  QTimer *timer;
  QGifImage *gif;
  QImage *gifImage;
  int gifTime = 0;
  void color_by_customer();
  void connectSetup();
  void sliderSetup();
  void defaultSettings();
  void saveSettings();
  void defaultSliders();
  void updateUiColors();
};
#endif  // MAINWINDOW_H
