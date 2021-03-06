#ifndef MYQOPENGLWIDGET_H
#define MYQOPENGLWIDGET_H

#include <QGLWidget>

#include <QDebug>
#include <iostream>
#include <QMouseEvent>
#include <QTimer>
#include <vector>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include "umbrella.h"

using std::vector;

class MyQOpenGLWidget : public QGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
private:
    GLuint pointsBuffer;

    GLuint m_posAttr;
    GLuint m_colAttr;
    GLuint m_normAttr;
    GLuint m_matrixUniform;

    QOpenGLShaderProgram *m_program;
    int m_frame;

    QMatrix4x4 matrixT;
    QMatrix4x4 matrixP;
    QMatrix4x4 matrixR;
    QMatrix4x4 matrixS;
    QMatrix4x4 matrixV;
    QColor colors[14];
    GLuint element;

    QVector3D lightSourse;
    bool movingEnabled;
    char axis;
    Umbrella *umbrella;
    void calculateMatrix();
    double diffX;
    double diffY;
    int prevX, prevY;
    float horizontalAngle = 3.14f;
    // вертикальный угол
    float verticalAngle = 0.0f;
    QVector3D right,direction,position;
    float speed = 0.01f;


public:
     MyQOpenGLWidget(QWidget *parent=0);

public slots:


protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void mousePressEvent (QMouseEvent * event );
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void mouseReleaseEvent(QMouseEvent * event);
    void render();
    void drawUmbrella();


};

#endif // MYQOPENGLWIDGET_H
