/*
 *   Copyright DATAN(c) 2023
 *   3DViewer_v1.0 made by bernardi, joaquind, stonehom, hazzeasu, killeral
 *   All rights reserved.
 */

#include "mainwindow.h"

#include "glwidget.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setWindowTitle("3DViewer_v1.0");

  timer = new QTimer;
  gifImage = new QImage[50]{};
  connect(timer, SIGNAL(timeout()), this, SLOT(slotTimer()));
  this->settingFile = QApplication::applicationDirPath() + "/settings.conf";

  sliderSetup();
  connectSetup();
  defaultSettings();
}

MainWindow::~MainWindow() {
  saveSettings();
  delete timer;
  delete[] gifImage;
  delete ui;
}

void MainWindow::sliderSetup() {
  // Rotate
  ui->slider_rotate_x->setRange(0, 360 * 16);
  ui->slider_rotate_x->setSingleStep(16);
  ui->slider_rotate_x->setPageStep(15 * 16);

  ui->slider_rotate_y->setRange(0, 360 * 16);
  ui->slider_rotate_y->setSingleStep(16);
  ui->slider_rotate_y->setPageStep(15 * 16);

  ui->slider_rotate_z->setRange(0, 360 * 16);
  ui->slider_rotate_z->setSingleStep(16);
  ui->slider_rotate_z->setPageStep(15 * 16);

  // Translate
  ui->slider_translate_x->setRange(0, 100);
  ui->slider_translate_x->setSingleStep(1);

  ui->slider_translate_y->setRange(0, 100);
  ui->slider_translate_y->setSingleStep(1);

  ui->slider_translate_z->setRange(0, 100);
  ui->slider_translate_z->setSingleStep(1);

  // Scale
  ui->scale_slider->setRange(1, 100);
  ui->scale_slider->setSingleStep(1);

  // Vertices
  ui->slider_vertices->setRange(1, 10);
  ui->slider_vertices->setSingleStep(1);

  // Edges
  ui->slider_edges->setRange(1, 10);
  ui->slider_edges->setSingleStep(1);
}

void MainWindow::connectSetup() {
  // Translate
  // TranslateX
  connect(ui->slider_translate_x, &QScrollBar::valueChanged, ui->OGLWidget,
          &GLWidget::setXTranslate);
  connect(ui->translate_x_lcd, SIGNAL(editingFinished()), (this),
          SLOT(xTranslateTextEdit()));
  // Translate Y
  connect(ui->slider_translate_y, &QScrollBar::valueChanged, ui->OGLWidget,
          &GLWidget::setYTranslate);
  connect(ui->translate_y_lcd, SIGNAL(editingFinished()), (this),
          SLOT(yTranslateTextEdit()));
  // Translate Z
  connect(ui->slider_translate_z, &QScrollBar::valueChanged, ui->OGLWidget,
          &GLWidget::setZTranslate);
  connect(ui->translate_z_lcd, SIGNAL(editingFinished()), (this),
          SLOT(zTranslateTextEdit()));

  // Connecting slider translate to text
  connect(ui->slider_translate_x, &QScrollBar::valueChanged, (this),
          &MainWindow::xTranslateSliderValueChanged);
  connect(ui->slider_translate_y, &QScrollBar::valueChanged, (this),
          &MainWindow::yTranslateSliderValueChanged);
  connect(ui->slider_translate_z, &QScrollBar::valueChanged, (this),
          &MainWindow::zTranslateSliderValueChanged);

  // Rotate
  // Rotate X
  connect(ui->slider_rotate_x, &QScrollBar::valueChanged, ui->OGLWidget,
          &GLWidget::setXRotation);
  connect(ui->rotate_x_lcd, SIGNAL(editingFinished()), (this),
          SLOT(xRotateTextEdit()));
  // Rotate Y
  connect(ui->slider_rotate_y, &QScrollBar::valueChanged, ui->OGLWidget,
          &GLWidget::setYRotation);
  connect(ui->rotate_y_lcd, SIGNAL(editingFinished()), (this),
          SLOT(yRotateTextEdit()));
  // Rotate Z
  connect(ui->slider_rotate_z, &QScrollBar::valueChanged, ui->OGLWidget,
          &GLWidget::setZRotation);
  connect(ui->rotate_z_lcd, SIGNAL(editingFinished()), (this),
          SLOT(zRotateTextEdit()));

  // Connecting slider rotate to text
  connect(ui->slider_rotate_x, &QScrollBar::valueChanged, (this),
          &MainWindow::xRotateValueChanged);
  connect(ui->slider_rotate_y, &QScrollBar::valueChanged, (this),
          &MainWindow::yRotateValueChanged);
  connect(ui->slider_rotate_z, &QScrollBar::valueChanged, (this),
          &MainWindow::zRotateValueChanged);

  // Scale
  connect(ui->scale_slider, &QScrollBar::valueChanged, ui->OGLWidget,
          &GLWidget::setScale);
  connect(ui->scale_text, SIGNAL(editingFinished()), (this),
          SLOT(scaleTextEdit()));
  // Connecting slider scale to text
  connect(ui->scale_slider, &QScrollBar::valueChanged, (this),
          &MainWindow::scaleSliderValueChanged);

  // Type of projection
  connect(ui->type_of_projection_parallel_button, &QRadioButton::pressed,
          (this), &MainWindow::projectionParallel);
  connect(ui->type_of_projection_central_button, &QRadioButton::pressed, (this),
          &MainWindow::projectionCentral);

  // Edge parameters
  connect(ui->edges_solid_button, &QRadioButton::pressed, (this),
          &MainWindow::linesTypeSolid);
  connect(ui->dashed_solid_button, &QRadioButton::pressed, (this),
          &MainWindow::linesTypeDashed);
  connect(ui->slider_edges, &QScrollBar::valueChanged, (this),
          &MainWindow::linesSizeSliderChanged);
  connect(ui->color_edges_button, SIGNAL(released()), (this),
          SLOT(onChangeLineColor()));

  // Vertice parameters
  connect(ui->verticies_disable_button, &QRadioButton::pressed, (this),
          &MainWindow::DisableView);
  connect(ui->verticies_circle_button, &QRadioButton::pressed, (this),
          &MainWindow::CircleView);
  connect(ui->verticies_square_button, &QRadioButton::pressed, (this),
          &MainWindow::SquareView);
  connect(ui->slider_vertices, &QScrollBar::valueChanged, (this),
          &MainWindow::vertexSize);

  connect(ui->color_verticies_button, SIGNAL(released()), (this),
          SLOT(onChangeDotColor()));

  connect(ui->background_color_button, SIGNAL(released()), (this),
          SLOT(onChangeBackgroundColor()));
  // Open file
  connect(ui->open_button, &QRadioButton::pressed, (this),
          &MainWindow::on_action_triggered);
  // Reset
  connect(ui->reset_values_button, SIGNAL(released()), (this),
          SLOT(resetValue()));
}

void MainWindow::defaultSliders() {
  ui->slider_translate_x->setValue(50);
  ui->slider_translate_y->setValue(50);
  ui->slider_translate_z->setValue(50);
  ui->translate_x_lcd->setText(QString::number(0));
  ui->translate_y_lcd->setText(QString::number(0));
  ui->translate_z_lcd->setText(QString::number(0));

  ui->slider_rotate_x->setValue(360 * 8);
  ui->slider_rotate_y->setValue(360 * 8);
  ui->slider_rotate_z->setValue(360 * 8);
  ui->rotate_x_lcd->setText(QString::number(0));
  ui->rotate_y_lcd->setText(QString::number(0));
  ui->rotate_z_lcd->setText(QString::number(0));

  ui->scale_slider->setValue(1);
  ui->scale_text->setText(QString::number(1));
}

void MainWindow::defaultSettings() {
  defaultSliders();

  for (int i = 0; ui->OGLWidget->data.massiv &&
                  i < (ui->OGLWidget->data.count_of_vertexes + 1) * 3;
       ++i)
    ui->OGLWidget->data.massiv[i] = ui->OGLWidget->data.massiv_const[i];

  ui->type_of_projection_central_button->setChecked(true);

  ui->verticies_circle_button->setChecked(true);
  ui->slider_vertices->setEnabled(true);
  ui->slider_vertices->setValue(5);

  ui->edges_solid_button->setChecked(true);
  ui->slider_edges->setValue(1);

  ui->OGLWidget->initSettings();

  if (QFile::exists(settingFile)) {
    QSettings settings(settingFile, QSettings::IniFormat);

    settings.beginGroup("LineSet");
    if (settings.value("solid").toBool()) {
      ui->edges_solid_button->setChecked(true);
      ui->OGLWidget->lineMode = 1;
    } else if (settings.value("dashed").toBool()) {
      ui->dashed_solid_button->setChecked(true);
      ui->OGLWidget->lineMode = 0;
    }
    if (settings.value("LineColor").toString().length() > 0) {
      ui->OGLWidget->lineColor = settings.value("LineColor").toString();
    }
    ui->slider_edges->setValue(settings.value("value").toInt());
    settings.endGroup();

    settings.beginGroup("Verticies");
    if (settings.value("disable").toBool()) {
      ui->verticies_disable_button->setChecked(true);
      ui->OGLWidget->pointMode = 0;

    } else if (settings.value("circle").toBool()) {
      ui->verticies_circle_button->setChecked(true);
      ui->OGLWidget->pointMode = 1;

    } else if (settings.value("square").toBool()) {
      ui->verticies_square_button->setChecked(true);
      ui->OGLWidget->pointMode = 2;
    }
    ui->OGLWidget->dotColor = settings.value("color").toString();
    ui->slider_vertices->setValue(settings.value("size").toInt());
    settings.endGroup();

    settings.beginGroup("background");
    if (settings.value("color").toString().length() > 0) {
      ui->OGLWidget->backgroundColor = settings.value("color").toString();
    }
    settings.endGroup();
  }
  updateUiColors();
}

void MainWindow::saveSettings() {
  QSettings settings(settingFile, QSettings::IniFormat);

  settings.beginGroup("LineSet");
  settings.setValue("solid", ui->edges_solid_button->isChecked());
  settings.setValue("dashed", ui->dashed_solid_button->isChecked());
  settings.setValue("LineColor", ui->OGLWidget->lineColor);
  settings.setValue("value", ui->slider_edges->value());
  settings.endGroup();

  settings.beginGroup("Verticies");
  settings.setValue("disable", ui->verticies_disable_button->isChecked());
  settings.setValue("circle", ui->verticies_circle_button->isChecked());
  settings.setValue("square", ui->verticies_square_button->isChecked());
  settings.setValue("color", ui->OGLWidget->dotColor);
  settings.setValue("size", ui->slider_vertices->value());
  settings.endGroup();

  settings.beginGroup("background");
  settings.setValue("color", ui->OGLWidget->backgroundColor);
  settings.endGroup();
}

// Translate
void MainWindow::xTranslateSliderValueChanged(int value) {
  ui->translate_x_lcd->setText(QString::number(value - 50));
}
void MainWindow::yTranslateSliderValueChanged(int value) {
  ui->translate_y_lcd->setText(QString::number(value - 50));
}
void MainWindow::zTranslateSliderValueChanged(int value) {
  ui->translate_z_lcd->setText(QString::number(value - 50));
}
void MainWindow::xTranslateTextEdit() {
  int val = ui->translate_x_lcd->text().toInt();
  val += 50;
  ui->slider_translate_x->setValue(val);
}
void MainWindow::yTranslateTextEdit() {
  int val = ui->translate_y_lcd->text().toInt();
  val += 50;
  ui->slider_translate_y->setValue(val);
}
void MainWindow::zTranslateTextEdit() {
  int val = ui->translate_z_lcd->text().toInt();
  val += 50;
  ui->slider_translate_z->setValue(val);
}

// Rotate
void MainWindow::xRotateValueChanged(int value) {
  ui->rotate_x_lcd->setText(QString::number(-180 + value / 16));
}
void MainWindow::yRotateValueChanged(int value) {
  ui->rotate_y_lcd->setText(QString::number(-180 + value / 16));
}
void MainWindow::zRotateValueChanged(int value) {
  ui->rotate_z_lcd->setText(QString::number(-180 + value / 16));
}

int valueNormalize(int val) {
  while (val > 180) {
    val -= 360;
  }
  while (val < -180) {
    val += 360;
  }
  return val;
}
void MainWindow::xRotateTextEdit() {
  int val = ui->rotate_x_lcd->text().toInt();
  val += 180;
  ui->slider_rotate_x->setValue(val * 16);
  val = valueNormalize(val);
  ui->OGLWidget->setXRotation(val * 16);
}
void MainWindow::yRotateTextEdit() {
  int val = ui->rotate_y_lcd->text().toInt();
  val += 180;
  ui->slider_rotate_y->setValue(val * 16);
  val = valueNormalize(val);
  ui->OGLWidget->setYRotation(val * 16);
}
void MainWindow::zRotateTextEdit() {
  int val = ui->rotate_z_lcd->text().toInt();
  val += 180;
  ui->slider_rotate_z->setValue(val * 16);
  val = valueNormalize(val);
  ui->OGLWidget->setZRotation(val * 16);
}
// Scale
void MainWindow::scaleSliderValueChanged(int value) {
  ui->scale_text->setText(QString::number(value));
}
void MainWindow::scaleTextEdit() {
  int val = ui->scale_text->text().toInt();
  ui->scale_slider->setValue(val);
}

// Type of projection
void MainWindow::projectionCentral() {
  ui->OGLWidget->projectionMode = 0;
  ui->OGLWidget->update();
}
void MainWindow::projectionParallel() {
  ui->OGLWidget->projectionMode = 1;
  ui->OGLWidget->update();
}

// Edge parameters
void MainWindow::linesTypeSolid() {
  ui->OGLWidget->lineMode = 0;
  ui->OGLWidget->update();
}
void MainWindow::linesTypeDashed() {
  ui->OGLWidget->lineMode = 1;
  ui->OGLWidget->update();
}
void MainWindow::linesSizeSliderChanged(int value) {
  ui->OGLWidget->lineSize = value;
  ui->OGLWidget->update();
}

// Vertice parameters
void MainWindow::DisableView() {
  ui->OGLWidget->pointMode = 0;
  ui->slider_vertices->setValue(0);
  ui->slider_vertices->setEnabled(false);
  ui->OGLWidget->update();
}
void MainWindow::CircleView() {
  ui->OGLWidget->pointMode = 1;
  ui->slider_vertices->setEnabled(true);
  ui->OGLWidget->update();
}
void MainWindow::SquareView() {
  ui->OGLWidget->pointMode = 2;
  ui->slider_vertices->setEnabled(true);
  ui->OGLWidget->update();
}
void MainWindow::vertexSize(int value) {
  ui->OGLWidget->pointSize = value;
  ui->OGLWidget->update();
}

void MainWindow::onChangeBackgroundColor() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Select Color",
                                        QColorDialog::DontUseNativeDialog);
  if (color.isValid()) {
    ui->OGLWidget->backgroundColor = color;
    updateUiColors();  // this will trigger the paintGL() method to be called
  }
}
void MainWindow::onChangeLineColor() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Select Color",
                                        QColorDialog::DontUseNativeDialog);
  if (color.isValid()) {
    ui->OGLWidget->lineColor = color;
    updateUiColors();  // this will trigger the paintGL() method to be called
  }
}
void MainWindow::onChangeDotColor() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Select Color",
                                        QColorDialog::DontUseNativeDialog);
  if (color.isValid()) {
    ui->OGLWidget->dotColor = color;
    updateUiColors();  // this will trigger the paintGL() method to be called
  }
}

void MainWindow::updateUiColors() {
  ui->graphics_background_color->setAutoFillBackground(true);
  ui->graphics_background_color->setStyleSheet(
      QString("border-style: solid; border-width: 1px; border-color: black; "
              "padding-top: 3px; background-color: rgb(%1, %2, %3);")
          .arg(ui->OGLWidget->backgroundColor.red())
          .arg(ui->OGLWidget->backgroundColor.green())
          .arg(ui->OGLWidget->backgroundColor.blue()));
  ui->graphics_color_edges->setAutoFillBackground(true);
  ui->graphics_color_edges->setStyleSheet(
      QString("border-style: solid; border-width: 1px; border-color: black; "
              "padding-top: 3px; background-color: rgb(%1, %2, %3);")
          .arg(ui->OGLWidget->lineColor.red())
          .arg(ui->OGLWidget->lineColor.green())
          .arg(ui->OGLWidget->lineColor.blue()));
  ui->graphics_verticies_color->setAutoFillBackground(true);
  ui->graphics_verticies_color->setStyleSheet(
      QString("border-style: solid; border-width: 1px; border-color: black; "
              "padding-top: 3px; background-color: rgb(%1, %2, %3);")
          .arg(ui->OGLWidget->dotColor.red())
          .arg(ui->OGLWidget->dotColor.green())
          .arg(ui->OGLWidget->dotColor.blue()));
  ui->OGLWidget->update();
}

// Reset
void MainWindow::resetValue() {
  if (QFile::exists(settingFile)) {
    QFile::remove(settingFile);
  }
  defaultSettings();
  ui->OGLWidget->update();
}

void MainWindow::on_action_triggered() {
  QFileDialog *fileDialog = new QFileDialog(this);
  if (fileDialog) {
    fileDialog->setWindowTitle(tr("Choose .obj-file"));
    fileDialog->setNameFilter(tr("(*.obj)"));
    fileDialog->setViewMode(QFileDialog::Detail);
    fileDialog->setFileMode(QFileDialog::ExistingFile);
    QStringList fileNames;
    if (fileDialog->exec()) {
      fileNames = fileDialog->selectedFiles();
      if (fileNames.size() > 0) {
        QString fileName = fileNames.at(0);
        QByteArray ba = fileName.toLocal8Bit();
        char *input = ba.data();
        s21_remove_data(&ui->OGLWidget->data);
        if (s21_parsing(&ui->OGLWidget->data, input)) {
          printf("ok\n");
          setWindowTitle(fileName);
          ui->statusBar->showMessage("Path: " + fileName);
          ui->number_of_facets->setText(
              QString::number(ui->OGLWidget->data.count_of_facets));
          ui->number_of_vertices->setText(
              QString::number(ui->OGLWidget->data.count_of_vertexes));
          defaultSliders();
        } else {
          printf("error\n");
          s21_remove_data(&ui->OGLWidget->data);
        }
      }
    }
    delete fileDialog;
  } else {
    printf("error!\n");
  }
}

void MainWindow::on_bmp_button_clicked() {
  saveSettings();
  QFileDialog dialogPhoto(this);
  QDateTime dateTime = dateTime.currentDateTime();
  QString currentDateTime = dateTime.toString("dd.MM.yy_HH.mm.ss_zzz");
  QString name_photo = dialogPhoto.getSaveFileName(
      this, "Save as...", "Screenshot_" + currentDateTime,
      "BMP (*.bmp);; JPEG (*.jpeg)");
  ui->OGLWidget->grabFramebuffer().save(name_photo);
}

void MainWindow::on_gif_button_clicked() {
  ui->gif_button->setEnabled(false);
  saveSettings();
  timer->start(100);
}

void MainWindow::slotTimer() {
  if (gifTime < 50) {
    gifImage[gifTime] = ui->OGLWidget->grab().toImage();
    ++gifTime;
  } else {
    gif = new QGifImage;

    for (int i = 0; i < gifTime; ++i) {
      gif->addFrame(gifImage[i], 0);
    }
    QDateTime dateTime = dateTime.currentDateTime();
    QString currentDateTime = dateTime.toString("dd.MM.yy_HH.mm.ss_zzz");
    QString fileName = QFileDialog::getSaveFileName(
        this, "Save GIF", "GIF_" + currentDateTime, "GIF (*.gif)");
    gif->save(fileName);
    ui->gif_button->setEnabled(true);
    timer->stop();
    delete gif;
    gifTime = 0;
  }
}
