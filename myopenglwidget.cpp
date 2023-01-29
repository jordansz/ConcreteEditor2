#include "myopenglwidget.h"
#include <QDebug>
#include <QSurfaceFormat>
#include <QMatrix4x4>
#include <QImage>
#include <QtMath>

GLfloat square[] = {
//Square1 pos                  textid   text Coord       color
    -2.79f, -2.79f, -2.0f, 1.0f,  1,       0.0f, 1.0f,      1.0f, 1.0f, 0.5f, 0.0f,
     2.79f, -2.79f, -2.0f, 1.0f,  1,       1.0f, 1.0f,      1.0f, 1.0f, 0.5f, 0.0f,
     2.79f,  2.79f, -2.0f, 1.0f,  1,       1.0f, 0.0f,      1.0f, 1.0f, 0.5f, 0.0f,
    -2.79f,  2.79f, -2.0f, 1.0f,  1,       0.0f, 0.0f,      1.0f, 1.0f, 0.5f, 0.0f,

    -2.0f, -2.0f, 0.0f, 1.0f,  0,       0.0f, 1.0f,      1.0f, 0.0f, 0.5f, 0.0f,       //bottom left
     2.0f, -2.0f, 0.0f, 1.0f,  0,       1.0f, 1.0f,      1.0f, 0.0f, 0.5f, 0.0f,       //bottom right
     2.0f,  2.0f, 0.0f, 1.0f,  0,       1.0f, 0.0f,      1.0f, 0.0f, 0.5f, 0.0f,       //top right
    -2.0f,  2.0f, 0.0f, 1.0f,  0,       0.0f, 0.0f,      1.0f, 0.0f, 0.5f, 0.0f,       //top left
    };

GLfloat squareBackup[] = {
//Square1 pos                  textid   text Coord       color
    -2.79f, -2.79f, -2.0f, 1.0f,  1,       0.0f, 1.0f,      1.0f, 1.0f, 0.5f, 0.0f,
     2.79f, -2.79f, -2.0f, 1.0f,  1,       1.0f, 1.0f,      1.0f, 1.0f, 0.5f, 0.0f,
     2.79f,  2.79f, -2.0f, 1.0f,  1,       1.0f, 0.0f,      1.0f, 1.0f, 0.5f, 0.0f,
    -2.79f,  2.79f, -2.0f, 1.0f,  1,       0.0f, 0.0f,      1.0f, 1.0f, 0.5f, 0.0f,

    -2.0f, -2.0f, 0.0f, 1.0f,  0,       0.0f, 1.0f,      1.0f, 0.0f, 0.5f, 0.0f,       //bottom left
     2.0f, -2.0f, 0.0f, 1.0f,  0,       1.0f, 1.0f,      1.0f, 0.0f, 0.5f, 0.0f,       //bottom right
     2.0f,  2.0f, 0.0f, 1.0f,  0,       1.0f, 0.0f,      1.0f, 0.0f, 0.5f, 0.0f,       //top right
    -2.0f,  2.0f, 0.0f, 1.0f,  0,       0.0f, 0.0f,      1.0f, 0.0f, 0.5f, 0.0f,       //top left
    };

int stride = 11 * sizeof(GLfloat);

GLuint squareIndeces[] = {
    0, 1, 2, 0, 3, 2,
    4, 5, 6, 4, 7, 6,
//        0, 1, 1, 2, 2, 3, 3, 0    //square wire frame
};

//GLfloat squareBackup[sizeof(square) / sizeof(square[0])];

//void makeSquareBackupCopy(){
//    for(int i = 0; i < sizeof(square) / sizeof(square[0]); i++){
//        squareBackup[i] = square[i];
//    }
//}

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
    , m_program(new QOpenGLShaderProgram(nullptr))
{
//    makeSquareBackupCopy();
//    set opengl version to #330
    QSurfaceFormat format;
    format.setVersion(3, 3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    setFormat(format);
    hasTexture = false;
    connect(this, SIGNAL(enableSliders()), parent, SLOT(enableSliders()));
}


MyOpenGLWidget::~MyOpenGLWidget()
{
    makeCurrent();
    delete m_program;
    delete m_texture1;

    m_vbo.destroy();
    m_vao.destroy();

    doneCurrent();
}

void MyOpenGLWidget::updateTexture(QImage img)
{
    qDebug() << "Updating Texture and Square: ";
    transformSquare(img);
    initTextures(img, img);

}

void MyOpenGLWidget::initializeGL()
{
    emit enableSliders();
    initializeOpenGLFunctions();
    glClearColor(0.9f, 0.8f, 0.8f, 0.0f);
//    glClearColor(1.0f, 1.0f, 1.0f, 0.5f);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    m_vao.create();
    if (m_vao.isCreated())
        m_vao.bind();

    m_vbo.create();
    m_vbo.bind();
    m_vbo.setUsagePattern(QOpenGLBuffer::DynamicDraw);
    m_vbo.allocate((void*)square, sizeof(square));

    initShader(":/Shaders/default.vert", ":/Shaders/default.frag");

    attributePos = m_program->attributeLocation("position");
    m_program->enableAttributeArray(attributePos);
    m_program->setAttributeBuffer(attributePos, GL_FLOAT, 0, 4, stride);

    attributeTextIndex = m_program->attributeLocation("tIndex");
    m_program->enableAttributeArray(attributeTextIndex);
    m_program->setAttributeBuffer(attributeTextIndex, GL_FLOAT, 4 * sizeof(GLfloat), 1, stride);

    attributeTextCoord = m_program->attributeLocation("textCoord");
    m_program->enableAttributeArray(attributeTextCoord);
    m_program->setAttributeBuffer(attributeTextCoord, GL_FLOAT, 5 * sizeof(GLfloat), 2, stride);

    attributeColor = m_program->attributeLocation("color");
    m_program->enableAttributeArray(attributeColor);
    m_program->setAttributeBuffer(attributeColor, GL_FLOAT, 7 * sizeof(GLfloat), 4, stride);

//    m_program->setUniformValue("u_Texture", 0);
//    GLfloat backSquareMaxW = qAbs(qTan(22.5f) * (5 + qAbs(square[0])));
//    GLfloat backSquareMaxH = qAbs(qTan(22.5f) * (5 + qAbs(square[1])));
    qDebug() << "xmax: " << square[0] << "xval here: " << square[0] << "  ymax" << square[1];

    m_program->setUniformValue("maxSquareWidth", qAbs(square[0]));
    m_program->setUniformValue("maxSquareHeight", qAbs(square[1]));

    m_texture1->release();
    m_vbo.release();
    m_program->release();
    m_vao.release();
}


void MyOpenGLWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_program->bind();
    m_vao.bind();
    m_texture1->bind();

    QMatrix4x4 model;
    QMatrix4x4 view;
    view.lookAt(QVector3D(0.0f, 0.0f, 5.0f), QVector3D(0.0f, 0.0f, 0.0f), QVector3D(0.0f, 1.0f, 0.0f));
    view.rotate(30, QVector3D(0.0f, 0.0f, 1.0f));
    QMatrix4x4 projection;
    projection.perspective(45.0f, width() / float(height()), 0.01f, 200.0f);
    QMatrix4x4 mvp = projection * view * model;

    m_program->setUniformValue("u_MVP", mvp);
    m_program->setUniformValue("u_Texture", 0);

    int halfSize = (sizeof(squareIndeces) / sizeof(squareIndeces[0])) / 2;
    glDrawElements(GL_TRIANGLES, halfSize, GL_UNSIGNED_INT, &squareIndeces[0]);
    glDrawElements(GL_TRIANGLES, halfSize, GL_UNSIGNED_INT, &squareIndeces[halfSize]);

    m_vao.release();
    m_program->release();
}


void MyOpenGLWidget::resizeGL(int w, int h){
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}


//void MyOpenGLWidget::mousePressEvent(QMouseEvent *event){
//    qDebug() << "Point clicked: " << event->pos();
//}

//void MyOpenGLWidget::keyPressEvent(QKeyEvent *event)
//{
////    transformsquare();
//}

//void MyOpenGLWidget::showEvent(QShowEvent *event)
//{
//    QOpenGLWidget::showEvent(event);
//}

void MyOpenGLWidget::initTextures(QImage img1, QImage img2){
        m_texture1 = new QOpenGLTexture(img1);
        m_texture1->setMinificationFilter(QOpenGLTexture::Nearest);
        m_texture1->setMagnificationFilter(QOpenGLTexture::Linear);
        m_texture1->setWrapMode(QOpenGLTexture::Repeat);
}

void MyOpenGLWidget::initShader(const QString &fp1, const QString &fp2){
    if(!m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, fp1)){
        qDebug() << "Problem compiling vertex shader\n" << __FILE__;
        close();
    }

    // Compile fragment shader
    if (!m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, fp2)){
        qDebug() << "Problem compiling Frag shader\n" << __FILE__;
        close();
    }

    // Link shader pipeline
    if (!m_program->link()){
        qDebug() << "Problem linking shader\n" << __FILE__;
        close();
    }

    // Bind shader pipeline for use
    if (!m_program->bind()){
        qDebug() << "Problem binding shader\n" << __FILE__;
        close();
    }
}

void MyOpenGLWidget::hasTexturePicked()
{
    hasTexture = true;
}

void MyOpenGLWidget::updateTilt(double num)
{

}

void MyOpenGLWidget::updateWobble(double num)
{

}

void MyOpenGLWidget::restart()
{
    qDebug() << "Reseting Opengl Widget";
    for(int i = 0; i < sizeof(square) / sizeof(square[0]); i++){
        square[i] = squareBackup[i];
    }
}

void MyOpenGLWidget::transformSquare(QImage img){
    double imgWRatio = img.width() / (double)img.height();
    double imgHRatio = img.height() / (double)img.width();
    double ratio = qMin(imgHRatio, imgWRatio);
    int size = (sizeof(square) / sizeof(square[0]));
    int index = ((imgWRatio >= 1) ? 1 : 0) + (size / 2);
    int increment = stride / sizeof(square[0]);
    for(; index < size; index += increment){
        if(square[index] < 0){
            square[index] = -(abs(square[index]) * ratio);
            square[index - 44] = -(abs(square[index - 44]) * ratio);
        }
        else{
            square[index] *= ratio;
            square[index - 44] *= ratio;
        }
    }
}

// previous transform for testing
//    square[0] -= 0.1f;

//    m_vbo.bind();
//    m_vbo.write(0, (void*)square, sizeof(square));

//    m_program->enableAttributeArray(attributePos);
//    m_program->setAttributeBuffer(attributePos, GL_FLOAT, 0, 4, 10*sizeof(GLfloat) );
//    m_vbo.release();
//    update();
