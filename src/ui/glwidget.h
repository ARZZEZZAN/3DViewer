/*
 *   Copyright DATAN(c) 2023
 *   3DViewer_v1.0 made by bernardi, joaquind, stonehom, hazzeasu, killeral
 *   All rights reserved.
 */

#ifndef GLWIDGET_H
#define GLWIDGET_H

#define GL_SILENCE_DEPRECATION

#include <QColor>
#include <QColorDialog>
#include <QOpenGLWidget>
#include <QPushButton>
#include <algorithm>
#include <cstring>

using namespace std;
extern "C" {
#include "../backend/s21_3DViewer_v1.h"
}

class GLWidget : public QOpenGLWidget {
  Q_OBJECT
 public:
  GLWidget(QWidget *parent = nullptr);
  ~GLWidget();
  QColor backgroundColor;
  QColor lineColor;
  QColor dotColor;

  int projectionMode;
  int pointMode;
  int pointSize;
  int lineSize;
  int lineMode;

  data_t data = {0, 0, NULL, 0.0, {0, 0, 0}, NULL, NULL, 0, NULL};

  char model_file_name[S_SIZE] = {0};

  void initSettings();

 public slots:
  void setXTranslate(int step);
  void setYTranslate(int step);
  void setZTranslate(int step);

  void setXRotation(int angle);
  void setYRotation(int angle);
  void setZRotation(int angle);

  void setScale(int scale);

 private:
  int m_xRot = 360 * 8;
  int m_yRot = 360 * 8;
  int m_zRot = 360 * 8;
  int m_xMove = 0;
  int m_yMove = 0;
  int m_zMove = 0;
  int scaleVal = 1;

  int a_prev_x = 0;
  int a_prev_y = 0;
  int a_prev_z = 0;

  int angle_prev_x = 360 * 8;
  int angle_prev_y = 360 * 8;
  int angle_prev_z = 360 * 8;

  int prev_scale = 1;

  void setupPerspective();

  void pointDrawing();
  void lineDrawing();

 protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
};

#endif  // GLWIDGET_H
