#include "myopenglwidget.h"
#include <QDebug>
#include <QSurfaceFormat>
#include <QImage>
#include <QtMath>


// These values are for front square w/ length of 4, back square i
GLfloat square[] = {
//Square1 pos                  textid   text Coord       color
    -100.0f, -100.0f, -5.0f, 1.0f,  1,  0.0f, 100.0f,      1.0f, 1.0f, 0.5f, 0.0f,
     100.0f, -100.0f, -5.0f, 1.0f,  1,  100.0f, 100.0f,      1.0f, 1.0f, 0.5f, 0.0f,
     100.0f,  100.0f, -5.0f, 1.0f,  1,  100.0f, 0.0f,      1.0f, 1.0f, 0.5f, 0.0f,
    -100.0f,  100.0f, -5.0f, 1.0f,  1,  0.0f, 0.0f,      1.0f, 1.0f, 0.5f, 0.0f,

    -2.0f, -2.0f, 0.0f, 1.0f,  0,       0.0f, 1.0f,      1.0f, 0.0f, 0.5f, 0.5f,       //bottom left
     2.0f, -2.0f, 0.0f, 1.0f,  0,       1.0f, 1.0f,      1.0f, 0.0f, 0.5f, 0.5f,       //bottom right
     2.0f,  2.0f, 0.0f, 1.0f,  0,       1.0f, 0.0f,      1.0f, 0.0f, 0.5f, 0.5f,       //top right
    -2.0f,  2.0f, 0.0f, 1.0f,  0,       0.0f, 0.0f,      1.0f, 0.0f, 0.5f, 0.5f,       //top left
};

GLfloat squareBackup[] = {
//Square1 pos                  textid   text Coord       color
    -100.0f, -100.0f, -5.0f, 1.0f,  1,  0.0f, 100.0f,      1.0f, 1.0f, 0.5f, 0.0f,
     100.0f, -100.0f, -5.0f, 1.0f,  1,  100.0f, 100.0f,      1.0f, 1.0f, 0.5f, 0.0f,
     100.0f,  100.0f, -5.0f, 1.0f,  1,  100.0f, 0.0f,      1.0f, 1.0f, 0.5f, 0.0f,
    -100.0f,  100.0f, -5.0f, 1.0f,  1,  0.0f, 0.0f,      1.0f, 1.0f, 0.5f, 0.0f,

    -2.0f, -2.0f, 0.0f, 1.0f,  0,       0.0f, 1.0f,      1.0f, 0.0f, 0.5f, 0.5f,       //bottom left
     2.0f, -2.0f, 0.0f, 1.0f,  0,       1.0f, 1.0f,      1.0f, 0.0f, 0.5f, 0.5f,       //bottom right
     2.0f,  2.0f, 0.0f, 1.0f,  0,       1.0f, 0.0f,      1.0f, 0.0f, 0.5f, 0.5f,       //top right
    -2.0f,  2.0f, 0.0f, 1.0f,  0,       0.0f, 0.0f,      1.0f, 0.0f, 0.5f, 0.5f,       //top left
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

MyOpenGLWidget::MyOpenGLWidget(QImage img, QWidget *parent)
    : QOpenGLWidget(parent)
    , m_program(new QOpenGLShaderProgram(nullptr))
    , m_texture1(nullptr)
    , m_texture2(nullptr)
    , scaleSize(100.0f)
    , frontImg(img)
{
    qDebug() << "Constructing new openglWidget";
    makeCurrent();
    initialized = false;
    rotationVec = QVector3D(0.0f, 0.0f, 0.0f);

//    set opengl version to #330
    QSurfaceFormat format;
    format.setVersion(3, 3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    setFormat(format);

    connect(this, SIGNAL(enableSliders()), parent, SLOT(enableSliders()));
    connect(this, SIGNAL(readyForBackTexture()), parent, SLOT(displaySelectedBackImg()));
}


MyOpenGLWidget::~MyOpenGLWidget()
{
    qDebug() << "openglWidget Deconstructor called";
    makeCurrent();
    delete m_program;
    if(m_texture1 != nullptr)
        delete m_texture1;
    if(m_texture2 != nullptr)
        delete m_texture2;

    m_vbo.destroy();
    m_vao.destroy();
    doneCurrent();
}

void MyOpenGLWidget::initializeGL()
{
    qDebug() << "Initializing opengl for myOpenglWidget";
    emit enableSliders();
    initializeOpenGLFunctions();
    glClearColor(0.9f, 0.8f, 0.8f, 0.0f);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    m_vao.create();
    if (m_vao.isCreated())
        m_vao.bind();

    m_vbo.create();
    m_vbo.bind();
    m_vbo.setUsagePattern(QOpenGLBuffer::DynamicDraw);

    updateTexture(frontImg, m_texture1);            // must before allocating vbo data because of the function changing the global square variable
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

//    double maxSquareHeight = qAbs(qTan(22.5) * square[45]);
    GLfloat maxSquareHeight = qAbs(square[45]) * (5.0f + qAbs(square[2])) / 5.0f;
//    qDebug() << maxSquareHeight;
    GLfloat maxSquareWidth = qAbs(square[44]) * (5.0 + qAbs(square[2])) / 5.0f;

    qDebug() << "y: " << square[45] << " ymax: " << maxSquareHeight << " xmax: " << maxSquareWidth;

    m_program->setUniformValue("maxSquareWidth", maxSquareWidth);
    m_program->setUniformValue("maxSquareHeight", maxSquareHeight);

    m_texture1->release();
    m_vbo.release();
    m_program->release();
    m_vao.release();
    initialized = true;

    emit readyForBackTexture();
}

void MyOpenGLWidget::updateTexture(QImage img, QOpenGLTexture *&texture)
{
    qDebug() << "Updating Texture and Square";
    if(texture == nullptr && initialized == false){
        transformSquare(img);
    }
    initTexture(img, texture);

}

void MyOpenGLWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_program->bind();
    m_vao.bind();
    m_texture1->bind();

    QMatrix4x4 model;
//    model.scale(scaleSize);
    model.rotate(rotationVec.x(), QVector3D(1, 0, 0));
    model.rotate(rotationVec.y(), QVector3D(0, 1, 0));

    QMatrix4x4 view;
    view.lookAt(QVector3D(0.0f, 0.0f, 5.0f), QVector3D(0.0f, 0.0f, 0.0f), QVector3D(0.0f, 1.0f, 0.0f));
    QMatrix4x4 projection;
    projection.perspective(45.0f, width() / float(height()), 0.01f, 200.0f);
    QMatrix4x4 mvp = projection * view * model;

    m_program->setUniformValue("u_MVP", mvp);

    qDebug() << "Val: " << mvp * QVector4D(square[0], square[1], square[2], square[3]);

    int halfSize = (sizeof(squareIndeces) / sizeof(squareIndeces[0])) / 2;

    if(m_texture2 != nullptr){
        m_texture2->bind();
        m_program->setUniformValue("u_Texture", 0);
        m_program->setUniformValue("u_hasTexture", 1);
    }
    else
        m_program->setUniformValue("u_hasTexture", 0);
    glDrawElements(GL_TRIANGLES, halfSize, GL_UNSIGNED_INT, &squareIndeces[0]);

    m_program->setUniformValue("u_Texture", 0);
    m_program->setUniformValue("u_hasTexture", 1);
    mvp = projection * view * QMatrix4x4();
    qDebug() << "Val2: " << mvp * QVector4D(square[44], square[45], square[46], square[47]);
    qDebug() << "Square val[0]" << square[0];
    m_program->setUniformValue("u_MVP", mvp);
    m_texture1->bind();
    glDrawElements(GL_TRIANGLES, halfSize, GL_UNSIGNED_INT, &squareIndeces[halfSize]);


    m_texture1->release();
    if(m_texture2 != nullptr)
        m_texture2->release();
    m_vao.release();
    m_program->release();
}


void MyOpenGLWidget::resizeGL(int w, int h){
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}


void MyOpenGLWidget::initTexture(QImage img1, QOpenGLTexture *&texture){
    if(texture != nullptr){
        delete texture;
    }
    texture = new QOpenGLTexture(img1);
    texture->setMinificationFilter(QOpenGLTexture::Nearest);
    texture->setMagnificationFilter(QOpenGLTexture::Linear);
    texture->setWrapMode(QOpenGLTexture::Repeat);
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

void MyOpenGLWidget::updateSize(double val)
{
    if(val < 0.02)
        val = 0.04;
    qDebug() << val;
    square[6]  = val;
    square[16] = val;
    square[17] = val;
    square[27] = val;

    m_vbo.bind();
    m_vbo.write(0, (void*)square, sizeof(square) / 2);
    m_program->enableAttributeArray(attributeTextCoord);
    m_program->setAttributeBuffer(attributeTextCoord, GL_FLOAT, 5, 2, stride);
}

void MyOpenGLWidget::updateSliderVals(QVector4D vec)
{
    rotationVec = QVector3D(vec.x(), vec.y(), vec.z());
    scaleSize = vec.w();
    updateSize(scaleSize);
    update();
}

void MyOpenGLWidget::updateBackTexture(QImage img)
{
    initTexture(img, m_texture2);
}

//void MyOpenGLWidget::hasTexturePicked()
//{
//    hasTexture = true;
//}


void MyOpenGLWidget::restart()
{
    qDebug() << "Reseting Opengl Widget";
    for(int i = 0; i < sizeof(square) / sizeof(square[0]); i++){
        square[i] = squareBackup[i];
    }
    m_vbo.bind();
    m_vbo.write(0, (void*)square, sizeof(square) / 2);
    m_program->enableAttributeArray(attributeTextCoord);
    m_program->setAttributeBuffer(attributeTextCoord, GL_FLOAT, 5, 2, stride);
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
//            square[index - 44] = -(abs(square[index - 44]) * ratio);
        }
        else{
            square[index] *= ratio;
//            square[index - 44] *= ratio;
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
