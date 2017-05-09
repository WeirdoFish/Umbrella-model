#include "myqopenglwidget.h"


#define pi 3.1415926535897

using std::cout;

MyQOpenGLWidget::MyQOpenGLWidget(QWidget *parent)  : QGLWidget(parent){
      setFocusPolicy(Qt::StrongFocus);
      matrixP.perspective(40.0f, 4.0f/3.0f, 0.1f, 100.0f);
      matrixT.translate(0.0, 0.0,0.0);
      matrixR.rotate(30.0,1.0,0.0,0.0);
      matrixS.scale(1.0);
      viewPoint = QVector3D(2.0f,-1.5f,1.6f);
      movingEnabled=false;
      axis='x';
      umbrella = new Umbrella(9);
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
}

void MyQOpenGLWidget::paintGL(){

    calculateMatrix();
    glEnable( GL_PROGRAM_POINT_SIZE );
   // glClearColor(0, 0.2, 0.2,1);
     glClearColor(1, 1, 1,1);
    glClear(GL_COLOR_BUFFER_BIT);
    render();
}

void MyQOpenGLWidget::render(){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);
    m_program->bind();

    m_program->setUniformValue("matrixP", matrixP);
    m_program->setUniformValue("matrixT", matrixT);
    m_program->setUniformValue("matrixR", matrixR);
    m_program->setUniformValue("matrixS", matrixS);
    m_program->setUniformValue("matrixV", matrixV);

    //axis

        float arr[]  = {0.0, 0.8, 0.0,  0.0,0.0,0.0,   0.0, 0.0, 0.8,  0.0,0.0,0.0,      0.8, 0.0, 0.0, 0.0,0.0,0.0, };

         glEnableVertexAttribArray(m_posAttr);
         m_program->setUniformValue("col", 1.0f,0.0f, 0.0f, 1.0f);
         glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, &arr[0]);
         glDrawArrays(GL_LINE_STRIP, 0, 2);


         m_program->setUniformValue("col", 1.0f,1.0f, 0.0f, 1.0f);
         glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, &arr[0]);
         glDrawArrays(GL_LINE_STRIP, 3, 2);


         m_program->setUniformValue("col", 0.0f,1.0f, 0.0f, 1.0f);
         glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, &arr[0]);
         glDrawArrays(GL_LINE_STRIP, 7, 2);
         glDisableVertexAttribArray(m_posAttr);


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
    double curX = (event->x()-350)/350.0;
    double curY = -(event->y()-350)/350.0;
    movingEnabled=!movingEnabled;
    std::cout<<curX << ' ' << curY << std::endl;

    this->updateGL();
}

void MyQOpenGLWidget::mouseMoveEvent(QMouseEvent *event){
    event->globalX();
    double curX = (event->x()-350)/350.0;
    double curY = -(event->y()-350)/350.0;
    if (event->buttons()==Qt::LeftButton){
        diffX = - prevX + event->x();
        diffY = prevY - event->y();
        prevX = event->x();
        prevY = event->y();

        update();
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

    right  = QVector3D(
        sin(horizontalAngle - 3.14f/2.0f),
        0,
        cos(horizontalAngle - 3.14f/2.0f)
    );

    QVector3D up = QVector3D::crossProduct(right,direction);
    QMatrix4x4 temp_matrixV;
    temp_matrixV.lookAt(
        position,           // Позиция камеры
        position+direction, // Направление камеры
        up                  // Вектор "Вверх" камеры
    );
    matrixV = temp_matrixV;
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
    update();
  }

void MyQOpenGLWidget::checkX(){
    axis='x';
}
void MyQOpenGLWidget::checkY(){
      axis='y';
}
void MyQOpenGLWidget::checkZ(){
        axis='z';
}


void MyQOpenGLWidget::rotatePos(){
     if (axis=='x'){
         matrixR.rotate(10.0,1.0,0.0,0.0);
     } else
     if (axis=='y'){
         matrixR.rotate(10.0,0.0,1.0,0.0);
     } else
     if (axis=='z'){
        matrixR.rotate(10.0,0.0,0.0,1.0);
     }
     this->updateGL();
}

void MyQOpenGLWidget::rotateNeg(){
    if (axis=='x'){
        matrixR.rotate(-10.0,1.0,0.0,0.0);
    } else
    if (axis=='y'){
        matrixR.rotate(-10.0,0.0,1.0,0.0);
    } else
    if (axis=='z'){
       matrixR.rotate(-10.0,0.0,0.0,1.0);
    }

    this->updateGL();
}

void MyQOpenGLWidget::decView(){
    if (axis=='x'){
       viewPoint.setX(viewPoint.x()+0.3);
    } else
    if (axis=='y'){
        viewPoint.setY(viewPoint.y()+0.3);
    } else
    if (axis=='z'){
        viewPoint.setZ(viewPoint.z()+0.3);
    }

    QMatrix4x4 temp_matrixV;
    temp_matrixV.lookAt(viewPoint,QVector3D(0.0f,0.0f,0.0f),QVector3D(0.0f,1.0f,0.0f));
    matrixV = temp_matrixV;
    this->updateGL();
}

void MyQOpenGLWidget::incView(){
    if (axis=='x'){
       viewPoint.setX(viewPoint.x()-0.3);
    } else
    if (axis=='y'){
        viewPoint.setY(viewPoint.y()-0.3);
    } else
    if (axis=='z'){
        viewPoint.setZ(viewPoint.z()-0.3);
    }
    QMatrix4x4 temp_matrixV;
    temp_matrixV.lookAt(viewPoint,QVector3D(0.0f,0.0f,0.0f),QVector3D(0.0f,1.0f,0.0f));
    matrixV = temp_matrixV;
    this->updateGL();
}






