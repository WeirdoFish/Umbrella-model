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

    QVector3D viewPoint;
    bool movingEnabled;
    char axis;
    Umbrella *umbrella;

public:
     MyQOpenGLWidget(QWidget *parent=0);

public slots:

     void checkX();
     void checkY();
     void checkZ();
     void rotatePos();
     void rotateNeg();
     void incView();
     void decView();


protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void mousePressEvent (QMouseEvent * event );
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void render();
    void drawUmbrella();


};

#endif // MYQOPENGLWIDGET_H
