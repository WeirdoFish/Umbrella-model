#include "myqopenglwidget.h"


#define pi 3.1415926535897

using std::cout;

MyQOpenGLWidget::MyQOpenGLWidget(QWidget *parent)  : QGLWidget(parent){
      setFocusPolicy(Qt::StrongFocus);
      matrixP.setToIdentity();
      matrixP.perspective(30.0f, 16.0f/9.0f, 0.1f, 100.0f);
      //matrixP.ortho(-1,1,-1,1,0.1f,1000.0f);
      matrixT.translate(0.0, 0.0,0.0);
      matrixS.scale(1.0);
      position = QVector3D(1.68f,0.47f,-0.49f);
      movingEnabled=false;
      axis='x';
      umbrella = new Umbrella(9);
      horizontalAngle = 5.02;
      verticalAngle = -0.31;
      colors[0] = QColor(255,56,0);
      colors[1] = QColor(255,112,0);
      colors[2] = QColor(255,160,0);
      colors[3] = QColor(255,191,0);
      colors[4] = QColor(255,216,0);
      colors[5] = QColor(255,244,0);
      colors[6] = QColor(209,250,0);
      colors[7] = QColor(158,230,0);
      colors[8] = QColor(84,221,0);
      colors[9] = QColor(0,193,33);
      colors[10] = QColor(0,170,114);
      colors[11] = QColor(15,79,168);
      colors[12] = QColor(112,10,170);
      colors[13] = QColor(204,0,114);

      lightSourse = QVector3D(10.0,0.0,0.5);
}

void MyQOpenGLWidget::paintGL(){
    //std::cout << position.x() << " " << position.y() << " " << position.z() <<"\n";
    calculateMatrix();
    glEnable( GL_PROGRAM_POINT_SIZE );
   // glClearColor(0, 0.2, 0.2,1);
     glClearColor(0.89, 1, 1,1);
    glClear(GL_COLOR_BUFFER_BIT);
    render();
}

void MyQOpenGLWidget::render(){
    //qDebug() << direction.x() <<  " " << direction.y() << " " << direction.z();
   // qDebug() << horizontalAngle <<  " " << verticalAngle;
    // qDebug() << position.x() <<  " " << position.y() << " " << position.z();
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);
    m_program->bind();
    matrixR.setToIdentity();
    m_program->setUniformValue("matrixP", matrixP);
    m_program->setUniformValue("matrixT", matrixT);
    m_program->setUniformValue("matrixR", matrixR);
    m_program->setUniformValue("matrixS", matrixS);
    m_program->setUniformValue("matrixV", matrixV);

    //grass surface

        float arr[]  = {-0.5, -0.03, -0.5,  -0.5,-0.03,0.5,   0.5, -0.03, -0.5,  0.5,-0.03,0.5};
         matrixS.scale(500.0);

         m_program->setUniformValue("matrixS", matrixS);
         glEnableVertexAttribArray(m_posAttr);
         m_program->setUniformValue("col", 0.69f,0.87f, 0.54f, 1.0f);
         glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, &arr[0]);
         glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
         glDisableVertexAttribArray(m_posAttr);
         matrixS.setToIdentity();

         m_program->setUniformValue("matrixS", matrixS);
         drawUmbrella();
         m_program->release();
}

void MyQOpenGLWidget::drawUmbrella(){
    vector<GLfloat> sec= umbrella->getSector();
    vector<GLfloat> secNormals= umbrella->getSecNormals();

    vector<GLfloat> stick = umbrella->getStick();
    vector <int> stickIdx = umbrella->getStickIdx();
    vector<GLfloat> stickNormals= umbrella->getStickNormals();

    vector <GLfloat> slat = umbrella->getSlat();
    vector <int> slatIdx = umbrella->getSlatIdx();
    vector<GLfloat> slatNormals= umbrella->getSlatNormals();

    vector <GLfloat> riv = umbrella->getRivet();
    vector <int> rivIdx = umbrella->getRivetIdx();
    vector<GLfloat> rivNormals= umbrella->getRivetNormals();


    matrixR.rotate(41.0,-1.0,0.0,0.0);
    matrixR.rotate(-30.0,0.0,0.0,1.0);


    m_program->setUniformValue("col", 0.51f,0.78f, 0.6f, 1.0f);

   for (int i = 0; i<14; i++){
        m_program->setUniformValue("col", colors[i]);
        matrixR.rotate(25.7, 0.0, 0.0, 1.0);
        m_program->setUniformValue("matrixR", matrixR);
//sectors
        glEnableVertexAttribArray(m_posAttr);
        glEnableVertexAttribArray(m_normAttr);
        glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, &sec[0]);
        glVertexAttribPointer(m_normAttr, 3, GL_FLOAT, GL_FALSE, 0, &secNormals[0]);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, sec.size()/3);
        //glDisableVertexAttribArray(m_normAttr);

//sticks

      //  m_program->setUniformValue("col", 0.2f, 0.1f, 0.0f, 1.0f);
        m_program->setUniformValue("col", 0.89f, 0.8f, 0.8f, 1.0f);
        glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, &stick[0]);
        glVertexAttribPointer(m_normAttr, 3, GL_FLOAT, GL_FALSE, 0, &stickNormals[0]);
        glDrawElements(GL_TRIANGLE_STRIP,stickIdx.size(),GL_UNSIGNED_INT, &stickIdx[0]);


//slats
        glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, &slat[0]);
        glVertexAttribPointer(m_normAttr, 3, GL_FLOAT, GL_FALSE, 0, &slatNormals[0]);
        glDrawElements(GL_TRIANGLE_STRIP,slatIdx.size(),GL_UNSIGNED_INT, &slatIdx[0]);

//rivets
        m_program->setUniformValue("col", 0.99f, 0.86f, 0.45f, 1.0f);
        glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, &riv[0]);
        glVertexAttribPointer(m_normAttr, 3, GL_FLOAT, GL_FALSE, 0, &rivNormals[0]);
        glDrawElements(GL_TRIANGLE_STRIP,rivIdx.size(),GL_UNSIGNED_INT, &rivIdx[0]);

        glDisableVertexAttribArray(m_posAttr);
        glDisableVertexAttribArray(m_normAttr);

  }

   vector <GLfloat> wand = umbrella->getWand();
   vector <int> wandIdx = umbrella->getWandIdx();
   vector<GLfloat> wandNormals= umbrella->getWandNormals();

   glEnableVertexAttribArray(m_normAttr);
   glEnableVertexAttribArray(m_posAttr);
   m_program->setUniformValue("col", 0.7f, 0.7f, 0.8f, 1.0f);
   glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, &wand[0]);
   glVertexAttribPointer(m_normAttr, 3, GL_FLOAT, GL_FALSE, 0, &wandNormals[0]);
   glDrawElements(GL_TRIANGLE_STRIP,wandIdx.size(),GL_UNSIGNED_INT, &wandIdx[0]);
   //glDrawArrays(GL_POINTS,0, wand.size()/3);
   glDisableVertexAttribArray(m_posAttr);
   glDisableVertexAttribArray(m_normAttr);

}

void MyQOpenGLWidget::resizeGL(int w, int h){
    glViewport(0,0,w,h);
}
void MyQOpenGLWidget::initializeGL(){
     initializeOpenGLFunctions();
     m_program = new QOpenGLShaderProgram(this);

     QOpenGLShader vShader( QOpenGLShader::Vertex );
     vShader.compileSourceFile( "C:/Users/pc-home/Code/CG/CG_Umbrella/Shaders/vertexShader.glsl" );

     QOpenGLShader fShader( QOpenGLShader::Fragment );
     fShader.compileSourceFile( "C:/Users/pc-home/Code/CG/CG_Umbrella/Shaders/fragmentShader.glsl" );

     m_program->addShader( &vShader );
     m_program->addShader( &fShader );

     m_program->link();
     m_posAttr = m_program->attributeLocation("posAttr");
     m_normAttr = m_program->attributeLocation("normAttr");
     m_colAttr = m_program->attributeLocation("colAttr");
     glEnable(GL_PROGRAM_POINT_SIZE);

     glGenBuffers(1,&element);
}

void MyQOpenGLWidget::mousePressEvent ( QMouseEvent * event ){
    prevX = event->x();
    prevY = event->y();
   // this->updateGL();
}

void MyQOpenGLWidget::mouseMoveEvent(QMouseEvent *event){
    if (event->buttons()==Qt::LeftButton){
        diffX = prevX - event->x();
        diffY = prevY - event->y();
        prevX = event->x();
        prevY = event->y();

        this->updateGL();
    }

  }

void MyQOpenGLWidget::calculateMatrix(){

    horizontalAngle += 0.01*float( diffX );
    verticalAngle   += 0.01*float( diffY );

    direction = QVector3D(
                cos(verticalAngle) * sin(horizontalAngle),
                sin(verticalAngle),
                cos(verticalAngle) * cos(horizontalAngle)
            );

    right = QVector3D(
        sin(horizontalAngle - 3.14f/2.0f),
        0,
        cos(horizontalAngle - 3.14f/2.0f)
    );

    QVector3D up = QVector3D::crossProduct(right,direction);

    direction.normalize();
    right.normalize();
    up.normalize();

    matrixV.setToIdentity();
    matrixV.lookAt(
        position,           // Позиция камеры
        position+direction, // Направление камеры
        up                  // Вектор "Вверх" камеры
    );
}
void MyQOpenGLWidget::mouseReleaseEvent(QMouseEvent * event){
    diffX = 0.0f;
    diffY = 0.0f;
}

void MyQOpenGLWidget::keyPressEvent(QKeyEvent *event){

    if (event->key() == Qt::Key_W){
        position += direction * speed;
    }
    // Движение назад
    if (event->key() == Qt::Key_S){
        position -= direction  * speed;
    }
    // Стрэйф вправо
    if (event->key() == Qt::Key_D){
        position += right  * speed;
    }
    // Стрэйф влево
    if (event->key() == Qt::Key_A){
        position -= right  * speed;
    }
    this->updateGL();
  }






