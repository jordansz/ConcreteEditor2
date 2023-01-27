#include "myopenglwidget.h"
#include <QDebug>
#include <QSurfaceFormat>
#include <QMatrix4x4>
#include <QImage>

GLfloat cube[] = {
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

    GLuint cubeIndeces[] = {
        0, 1, 2, 0, 3, 2,
        4, 5, 6, 4, 7, 6,
//        0, 1, 1, 2, 2, 3, 3, 0    //cube wire frame
    };


MyOpenGLWidget::MyOpenGLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
    , m_program(new QOpenGLShaderProgram(nullptr))
{
//    set opengl version to #330
    QSurfaceFormat format;
    format.setVersion(3, 3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    setFormat(format);
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
    qDebug() << "changing texture: ";
    initTextures(img, img);

}

void MyOpenGLWidget::initializeGL()
{
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
    m_vbo.allocate((void*)cube, sizeof(cube));

//    QImage img1(":/Images/homeButton.png");
//    QImage img2(":/Images/homeButton.png");
//    if(img1.isNull() || img2.isNull()){
//        qDebug() << "Error loading images." << __FILE__;
//    }

    initShader(":/Shaders/default.vert", ":/Shaders/default.frag");
//    qDebug() << "before initing";
//    initTextures(img1, img2);

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

    m_program->setUniformValue("u_Texture", 0);

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
    QMatrix4x4 projection;
    projection.perspective(45.0f, width() / float(height()), 0.01f, 200.0f);
    QMatrix4x4 mvp = projection * view * model;

    m_program->setUniformValue("u_MVP", mvp);

    glDrawElements(GL_TRIANGLES, sizeof(cubeIndeces), GL_UNSIGNED_INT, (void*)cubeIndeces);

    m_vao.release();
    m_program->release();
}


void MyOpenGLWidget::resizeGL(int w, int h){
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    QSize size(w, h);
    QSize imgSize(1, 1);
//    qDebug() << "Viewport: " << size << "   Widget: " << this->size() << " Image: " << imgSize;
//    qDebug() << "w: " << w << "h: " << h;
//    if(w >= h){

//    }
}


void MyOpenGLWidget::mousePressEvent(QMouseEvent *event){
    qDebug() << "Point clicked: " << event->pos();
}

void MyOpenGLWidget::keyPressEvent(QKeyEvent *event)
{
    tansformCube();
}

void MyOpenGLWidget::showEvent(QShowEvent *event)
{
    QOpenGLWidget::showEvent(event);
}

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

void MyOpenGLWidget::tansformCube(){
//    cube[0] -= 0.1f;

    m_vbo.bind();
    m_vbo.write(0, (void*)cube, sizeof(cube));

    m_program->enableAttributeArray(attributePos);
    m_program->setAttributeBuffer(attributePos, GL_FLOAT, 0, 4, 10*sizeof(GLfloat) );
    m_vbo.release();
    update();
}
