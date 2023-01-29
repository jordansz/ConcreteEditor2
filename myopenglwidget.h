#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>
#include <QOpenGLShaderProgram>
#include <QOpenGLShader>
#include <QImage>
#include <QShowEvent>
#include <QMatrix4x4>
#include <QMouseEvent>
#include <QKeyEvent>

class MyOpenGLWidget : public QOpenGLWidget, public QOpenGLFunctions
{
    Q_OBJECT
public:
    MyOpenGLWidget(QWidget *parent = nullptr);
    ~MyOpenGLWidget();
    void updateTexture(QImage img);
    void restart();

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

private:
    void transformSquare(QImage img);
    void initTexture(QImage img1, QOpenGLTexture *&texture);
    void initShader(const QString &fp1, const QString &fp2);

public slots:
//    void hasTexturePicked();
    void updateRotation(QVector3D vec);

signals:
    void enableSliders();

private:
    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer m_vbo;

    QOpenGLShaderProgram *m_program;
    int attributePos;
    int attributeColor;
    int attributeTextCoord;
    int attributeTextIndex;
    QOpenGLTexture *m_texture1;
    QVector3D rotationVec;
//    bool hasTexture;
    double xRot;
    double yRot;
    double zRot;
//    QOpenGLTexture *m_texture2;
//    double imgRatio;
};

#endif // MYOPENGLWIDGET_H
