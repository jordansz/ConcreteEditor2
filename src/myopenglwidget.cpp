#include "myopenglwidget.h"
#include <QDebug>
#include <QSurfaceFormat>
#include <QImage>
#include <QtMath>


// These values are for front square w/ length of 4, back square i
GLfloat square[] = {
//Square1 pos                  textid   text Coord       color
    -100.0f, -100.0f, -5.0f, 1.0f,  1,  0.0f,   100.0f,    1.0f, 1.0f, 0.5f, 0.0f,
     100.0f, -100.0f, -5.0f, 1.0f,  1,  100.0f, 100.0f,    1.0f, 1.0f, 0.5f, 0.0f,
     100.0f,  100.0f, -5.0f, 1.0f,  1,  100.0f, 0.0f,      1.0f, 1.0f, 0.5f, 0.0f,
    -100.0f,  100.0f, -5.0f, 1.0f,  1,  0.0f,   0.0f,      1.0f, 1.0f, 0.5f, 0.0f,

    -2.0f, -2.0f, 0.0f, 1.0f,  0,       0.0f, 1.0f,      1.0f, 0.0f, 0.5f, 0.5f,       //bottom left
     2.0f, -2.0f, 0.0f, 1.0f,  0,       1.0f, 1.0f,      1.0f, 0.0f, 0.5f, 0.5f,       //bottom right
     2.0f,  2.0f, 0.0f, 1.0f,  0,       1.0f, 0.0f,      1.0f, 0.0f, 0.5f, 0.5f,       //top right
    -2.0f,  2.0f, 0.0f, 1.0f,  0,       0.0f, 0.0f,      1.0f, 0.0f, 0.5f, 0.5f,       //top left
};

GLfloat squareBackup[] = {
//Square1 pos                  textid   text Coord       color
    -100.0f, -100.0f, -5.0f, 1.0f,  1,  0.0f,   100.0f,    1.0f, 1.0f, 0.5f, 0.0f,
     100.0f, -100.0f, -5.0f, 1.0f,  1,  100.0f, 100.0f,    1.0f, 1.0f, 0.5f, 0.0f,
     100.0f,  100.0f, -5.0f, 1.0f,  1,  100.0f, 0.0f,      1.0f, 1.0f, 0.5f, 0.0f,
    -100.0f,  100.0f, -5.0f, 1.0f,  1,  0.0f,   0.0f,      1.0f, 1.0f, 0.5f, 0.0f,

    -2.0f, -2.0f, 0.0f, 1.0f,  0,       0.0f, 1.0f,      1.0f, 0.0f, 0.5f, 0.5f,       //bottom left
     2.0f, -2.0f, 0.0f, 1.0f,  0,       1.0f, 1.0f,      1.0f, 0.0f, 0.5f, 0.5f,       //bottom right
     2.0f,  2.0f, 0.0f, 1.0f,  0,       1.0f, 0.0f,      1.0f, 0.0f, 0.5f, 0.5f,       //top right
    -2.0f,  2.0f, 0.0f, 1.0f,  0,       0.0f, 0.0f,      1.0f, 0.0f, 0.5f, 0.5f,       //top left
};

GLfloat outerRect[] = {
    -2.5f, -2.5f, 0.0f, 1.0f,   0.0f, 0.0f, 0.0f, 1.0f,     //left col
    -2.0f, -2.5f, 0.0f, 1.0f,   0.0f, 0.0f, 0.0f, 1.0f,
    -2.0f,  2.5f, 0.0f, 1.0f,   0.0f, 0.0f, 0.0f, 1.0f,
    -2.5f,  2.5f, 0.0f, 1.0f,   0.0f, 0.0f, 0.0f, 1.0f,

    2.0f, -2.5f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f, 1.0f,     //right col
    2.5f, -2.5f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f, 1.0f,
    2.5f,  2.5f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f, 1.0f,
    2.0f,  2.5f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f, 1.0f,

    -2.5f, -2.5f, 0.0f, 1.0f,   0.0f, 0.0f, 0.0f, 1.0f,      //bottom row
     2.5f, -2.5f, 0.0f, 1.0f,   0.0f, 0.0f, 0.0f, 1.0f,
     2.5f, -2.0f, 0.0f, 1.0f,   0.0f, 0.0f, 0.0f, 1.0f,
    -2.5f, -2.0f, 0.0f, 1.0f,   0.0f, 0.0f, 0.0f, 1.0f,

    -2.5f,  2.0f, 0.0f, 1.0f,   0.0f, 0.0f, 0.0f, 1.0f,     //top row
     2.5f,  2.0f, 0.0f, 1.0f,   0.0f, 0.0f, 0.0f, 1.0f,
     2.5f,  2.5f, 0.0f, 1.0f,   0.0f, 0.0f, 0.0f, 1.0f,
    -2.5f,  2.5f, 0.0f, 1.0f,   0.0f, 0.0f, 0.0f, 1.0f,
};

GLfloat outerRect2[] = {
    -2.5f, -2.5f, 0.0f, 1.0f,   0.0f, 0.0f, 0.0f, 1.0f,     //left col
    -2.0f, -2.5f, 0.0f, 1.0f,   0.0f, 0.0f, 0.0f, 1.0f,
    -2.0f,  2.5f, 0.0f, 1.0f,   0.0f, 0.0f, 0.0f, 1.0f,
    -2.5f,  2.5f, 0.0f, 1.0f,   0.0f, 0.0f, 0.0f, 1.0f,

    2.0f, -2.5f, 0.0f, 1.0f,    1.0f, 1.0f, 1.0f, 1.0f,     //right col
    2.5f, -2.5f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f, 1.0f,
    2.5f,  2.5f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f, 1.0f,
    2.0f,  2.5f, 0.0f, 1.0f,    1.0f, 1.0f, 1.0f, 1.0f,

    -2.5f, -2.5f, 0.0f, 1.0f,   0.0f, 0.0f, 0.0f, 1.0f,      //bottom row
     2.5f, -2.5f, 0.0f, 1.0f,   0.0f, 0.0f, 0.0f, 1.0f,
     2.5f, -2.0f, 0.0f, 1.0f,   0.0f, 0.0f, 0.0f, 1.0f,
    -2.5f, -2.0f, 0.0f, 1.0f,   0.0f, 0.0f, 0.0f, 1.0f,

    -2.5f,  2.0f, 0.0f, 1.0f,   0.0f, 0.0f, 0.0f, 1.0f,     //top row
     2.5f,  2.0f, 0.0f, 1.0f,   0.0f, 0.0f, 0.0f, 1.0f,
     2.5f,  2.5f, 0.0f, 1.0f,   1.0f, 1.0f, 1.0f, 1.0f,
    -2.5f,  2.5f, 0.0f, 1.0f,   1.0f, 1.0f, 1.0f, 1.0f,
};

//GLfloat test[] = {
//    2.5f, 2.5f, 0.5f,
//}

GLuint squareIndeces[] = {
    0,  1,  2,      0,  3,  2,
    4,  5,  6,      4,  7,  6,
    8,  9,  10,     8,  11, 10,
    12, 13, 14,     12, 15, 14,
//        0, 1, 1, 2, 2, 3, 3, 0    //square wire frame
};

int horizShift;
int vertShift;

int indeceSize = sizeof(squareIndeces) / sizeof(squareIndeces[0]);
int stride = 11 * sizeof(GLfloat);
int stride2 = 8 * sizeof(GLfloat);


MyOpenGLWidget::MyOpenGLWidget(QImage img, QWidget *parent)
    : QOpenGLWidget(parent)
    , m_program(new QOpenGLShaderProgram(nullptr))
    , m_program2(new QOpenGLShaderProgram(nullptr))
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
    delete m_program2;
    delete m_program;
    if(m_texture1 != nullptr)
        delete m_texture1;
    if(m_texture2 != nullptr)
        delete m_texture2;

    m_vbo3.destroy();
    m_vbo2.destroy();
    m_vao.destroy();
    m_vbo.destroy();
    m_vao.destroy();
    doneCurrent();
}

void MyOpenGLWidget::initializeGL()
{
    qDebug() << "Initializing opengl for myOpenglWidget";
    emit enableSliders();
    initializeOpenGLFunctions();
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    m_vao.create();
    if (m_vao.isCreated())
        m_vao.bind();

    m_vbo.create();
    m_vbo.bind();
    m_vbo.setUsagePattern(QOpenGLBuffer::DynamicDraw);
//    m_vbo.allocate((void*)square, sizeof(square));
//    m_texture1->create();

    updateTexture(frontImg, m_texture1);            // must before allocating vbo data because of the function changing the global square variable
    m_vbo.allocate((void*)square, sizeof(square));

    initShader(":/Shaders/default.vert", ":/Shaders/default.frag", m_program);

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

    m_texture1->release();
    m_vbo.release();
    m_program->release();
    m_vao.release();
    initialized = true;


    m_vao2.create();
    m_vao2.bind();
    m_vbo2.create();
    m_vbo2.bind();
    m_vbo2.setUsagePattern(QOpenGLBuffer::DynamicDraw);
    m_vbo2.allocate((void*)outerRect, sizeof(outerRect));




    initShader(":/Shaders/default.vert", ":/Shaders/default.frag", m_program2);
    m_program2->enableAttributeArray(attributePos);
    m_program2->enableAttributeArray(attributeColor);

    m_program2->setAttributeBuffer(attributePos, GL_FLOAT, 0, 4, stride2);
    m_program2->setAttributeBuffer(attributeColor, GL_FLOAT, 4 * sizeof(GLfloat), 4, stride2);

    m_program2->release();
    m_vbo2.release();
    m_vao2.release();

    emit readyForBackTexture();
}

void MyOpenGLWidget::updateTexture(QImage img, QOpenGLTexture *&texture)
{
    horizShift = 0;
    vertShift = 0;
    if(texture == nullptr && initialized == false){
        qDebug() << "Updating Texture and Square";
        transformSquare(img);
    }
    initTexture(img, texture);

}

void MyOpenGLWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_program->bind();
    m_vao.bind();
    m_vbo.bind();
//    m_texture1->bind();

    QMatrix4x4 model;
    QMatrix4x4 view;
    QMatrix4x4 projection;

    model.rotate(rotationVec.x(), QVector3D(1, 0, 0));
    model.rotate(rotationVec.y(), QVector3D(0, 1, 0));
    view.lookAt(QVector3D(0.0f, 0.0f, 5.0f), QVector3D(0.0f, 0.0f, 0.0f), QVector3D(0.0f, 1.0f, 0.0f));
    projection.perspective(45.0f, width() / float(height()), 0.01f, 200.0f);
    QMatrix4x4 mvp = projection * view * model;

//  check if there is a back texture and draw it
    if(m_texture2 != nullptr){
        m_texture2->bind();
        m_program->setUniformValue("u_hasTexture", 1);
        m_program->setUniformValue("u_Texture", 0);
        m_program->setUniformValue("u_MVP", mvp);
        glDrawElements(GL_TRIANGLES, indeceSize / 4, GL_UNSIGNED_INT, &squareIndeces[0]);
        m_texture2->release();
    }

//  Draw main texture
    mvp = projection * view * QMatrix4x4();
    m_texture1->bind();
    m_program->setUniformValue("u_hasTexture", 1);
    m_program->setUniformValue("u_Texture", 0);
    m_program->setUniformValue("u_MVP", mvp);
    glDrawElements(GL_TRIANGLES, indeceSize / 4, GL_UNSIGNED_INT, &squareIndeces[indeceSize / 4]);

    m_vbo.release();
    m_vao.release();
    m_texture1->release();
    m_program->release();

    m_program2->bind();
    m_vao2.bind();
    m_vbo2.bind();

//  draw sides
    m_program2->setUniformValue("u_MVP", mvp);
    m_program2->setUniformValue("u_hasTexture", 0);
    m_program->setUniformValue("u_Texture", 0);
    glDrawElements(GL_TRIANGLES, indeceSize, GL_UNSIGNED_INT, &squareIndeces[0]);

    m_vbo2.release();
    m_vao2.release();
    m_program2->release();
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

void MyOpenGLWidget::initShader(const QString &fp1, const QString &fp2, QOpenGLShaderProgram *prog){
    if(!prog->addShaderFromSourceFile(QOpenGLShader::Vertex, fp1)){
        qDebug() << "Problem compiling vertex shader\n" << __FILE__;
        close();
    }

    // Compile fragment shader
    if (!prog->addShaderFromSourceFile(QOpenGLShader::Fragment, fp2)){
        qDebug() << "Problem compiling Frag shader\n" << __FILE__;
        close();
    }

    // Link shader pipeline
    if (!prog->link()){
        qDebug() << "Problem linking shader\n" << __FILE__;
        close();
    }

    // Bind shader pipeline for use
    if (!prog->bind()){
        qDebug() << "Problem binding shader\n" << __FILE__;
        close();
    }
}

void MyOpenGLWidget::updateSize(double val)
{
    if(val < 0.02)
        val = 0.04;
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
    for(int i = 0; i < sizeof(outerRect) / outerRect[0]; i++){
        outerRect[i] = outerRect[i];
        outerRect[i] = outerRect2[i];
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
    double sVal = qAbs(square[index - increment]);
//  need to change outer square min vals, if statment below is
//  true must change y vals equal to +- sVal and vice versa for less then 1
    if(imgWRatio >= 1){
        outerRect[81]  = -sVal;
        outerRect[89]  = -sVal;
        outerRect[97] = sVal;
        outerRect[105] = sVal;
    }
    else{
        outerRect[8]  = -sVal;
        outerRect[16] = -sVal;
        outerRect[32] = sVal;
        outerRect[56] = sVal;
    }
}
