#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>
#include <QOpenGLShaderProgram>
#include <QOpenGLShader>

#include <QMouseEvent>
#include <QKeyEvent>

class MyOpenGLWidget : public QOpenGLWidget, public QOpenGLFunctions
{
    Q_OBJECT
public:
    MyOpenGLWidget(QWidget *parent = nullptr);
    ~MyOpenGLWidget();

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;
    void mousePressEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    void tansformCube();
    void initTextures(const QString &fp1, const QString &fp2);
    void initShader(const QString &fp1, const QString &fp2);

    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer m_vbo;

    QOpenGLShaderProgram *m_program;
    int attributePos;
    int attributeColor;
    int attributeTextCoord;
    int attributeTextIndex;
    QOpenGLTexture *m_texture1;
//    QOpenGLTexture *m_texture2;
//    double imgRatio;
};

#endif // MYOPENGLWIDGET_H