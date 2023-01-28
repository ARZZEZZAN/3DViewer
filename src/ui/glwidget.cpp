/*
 *   Copyright DATAN(c) 2023
 *   3DViewer_v1.0 made by bernardi, joaquind, stonehom, hazzeasu, killeral
 *   All rights reserved.
 */

#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent) { initSettings(); }

GLWidget::~GLWidget() { s21_remove_data(&data); }

void GLWidget::initSettings() {
  projectionMode = 0;
  pointSize = 5;
  pointMode = 1;
  lineSize = 1;
  lineMode = 0;
  backgroundColor.setRgb(0, 0, 0);
  lineColor.setRgb(255, 255, 255);
  dotColor.setRgb(255, 255, 255);
}

void GLWidget::initializeGL() {
  glClearColor(0.0, 0.0, 0.0, 1.0);  // Заливка черным цветом
  glClearDepth(1.0);  // Разрешить очистку буфера глубины
  glEnable(GL_DEPTH_TEST);  // Разрешить тест глубины
  setupPerspective();
}

void GLWidget::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);  // Установка точки опоры
}

void GLWidget::paintGL() {
  if (data.massiv) {
    glClearColor(backgroundColor.redF(), backgroundColor.greenF(),
                 backgroundColor.blueF(), backgroundColor.alphaF());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);  // Инициализация матрицы проекции
    glLoadIdentity();  // Сброс матрицы проекции

    setupPerspective();

    glMatrixMode(GL_MODELVIEW);  // Инициализация матрицы модели
    glLoadIdentity();  // Сброс матрицы вида модели

    glVertexPointer(3, GL_DOUBLE, 0, data.massiv);
    glEnableClientState(GL_VERTEX_ARRAY);
    pointDrawing();
    lineDrawing();
    glDisableClientState(GL_VERTEX_ARRAY);
  } else {
    s21_remove_data(&data);
  }
}

void GLWidget::pointDrawing() {
  if (pointMode != 0) {
    glColor3d(dotColor.redF(), dotColor.greenF(), dotColor.blueF());
    glPointSize(pointSize);
    if (pointMode == 1) {
      glEnable(GL_POINT_SMOOTH);
    }
    glDrawArrays(GL_POINTS, 1, data.count_of_vertexes);
    if (pointMode == 1) {
      glDisable(GL_POINT_SMOOTH);
    }
  }
}

void GLWidget::lineDrawing() {
  glColor3d(lineColor.redF(), lineColor.greenF(), lineColor.blueF());
  glLineWidth(lineSize);
  if (lineMode == 1) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(2, 0x00F0);
  }
  glDrawElements(GL_LINES, data.sizePolygons, GL_UNSIGNED_INT,
                 data.massivPolygons);
  if (lineMode == 1) {
    glDisable(GL_LINE_STIPPLE);
  }
}

void GLWidget::setupPerspective() {
  if (data.max_coord < 1) {
    data.max_coord = 2;
  }
  GLdouble zNear = 0.001;  // Ближнее расстояние отсечения
  GLdouble zFar = data.max_coord * 5;  // Дальнее расстояние отсечения

  if (projectionMode == 0) {  // Central/Perspective projection

    GLdouble fovY = 90;  // Поле зрения в градусах по оси y
    GLdouble fH = tan(fovY / 360 * M_PI) * zNear;
    GLdouble fW = fH;

    glFrustum(-fW, fW, -fH, fH, zNear,
              zFar);  // Устанавливает усеченный конус в режим перспективы
    glTranslatef(0, 0, -data.max_coord);
  } else {  // Parallel/Orthographic projection
    glOrtho(-data.max_coord, data.max_coord, -data.max_coord, data.max_coord,
            -data.max_coord, zFar);
  }
}

void GLWidget::setScale(int scale) {
  if (scale != scaleVal) {
    scaleVal = scale;
    s21_scale(&data, fabs(scaleVal / 1000.0f), fabs(prev_scale / 1000.0f));
    prev_scale = scaleVal;
    update();
  }
}

void GLWidget::setXTranslate(int step) {
  if (step != m_xMove) {
    m_xMove = step;
    s21_move_x(&data, 0.05 * (50 - m_xMove), 0.05 * (50 - (a_prev_x)));
    a_prev_x = m_xMove;
    update();
  }
}
void GLWidget::setYTranslate(int step) {
  if (step != m_yMove) {
    m_yMove = step;
    s21_move_y(&data, 0.05 * (50 - m_yMove), 0.05 * (50 - (a_prev_y)));
    a_prev_y = m_yMove;
    update();
  }
}
void GLWidget::setZTranslate(int step) {
  if (step != m_zMove) {
    m_zMove = step;
    s21_move_z(&data, 0.05 * (50 - m_zMove), 0.05 * (50 - (a_prev_z)));
    a_prev_z = m_zMove;
    update();
  }
}

static void qNormalizeAngle(int &angle) {
  while (angle < 0) angle += 360 * 16;
  while (angle > 360 * 16) angle -= 360 * 16;
}
void GLWidget::setXRotation(int angle) {
  qNormalizeAngle(angle);
  if (angle != m_xRot) {
    m_xRot = angle;
    s21_rotate_x(&data, -(180.0 - m_xRot / 16.0),
                 -(180.0 - angle_prev_x / 16.0));
    angle_prev_x = m_xRot;
    update();
  }
}
void GLWidget::setYRotation(int angle) {
  qNormalizeAngle(angle);
  if (angle != m_yRot) {
    m_yRot = angle;
    s21_rotate_y(&data, -(180.0 - m_yRot / 16.0),
                 -(180.0 - angle_prev_y / 16.0));
    angle_prev_y = m_yRot;
    update();
  }
}
void GLWidget::setZRotation(int angle) {
  qNormalizeAngle(angle);
  if (angle != m_zRot) {
    m_zRot = angle;
    s21_rotate_z(&data, -(180.0 - m_zRot / 16.0),
                 -(180.0 - angle_prev_z / 16.0));
    angle_prev_z = m_zRot;
    update();
  }
}
