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
    MyOpenGLWidget(QImage img, QWidget *parent = nullptr);
    ~MyOpenGLWidget();
    void updateTexture(QImage img, QOpenGLTexture *&texture);
    void restart();

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

private:
    void transformSquare(QImage img);
    void initTexture(QImage img, QOpenGLTexture *&texture);
    void initShader(const QString &fp1, const QString &fp2, QOpenGLShaderProgram *prog);
    void updateSize(double val);

public slots:
//    void hasTexturePicked();
    void updateSliderVals(QVector4D vec);
    void updateBackTexture(QImage img);

signals:
    void enableSliders();
    void readyForBackTexture();

private:
    QOpenGLVertexArrayObject m_vao;
    QOpenGLVertexArrayObject m_vao2;
    QOpenGLBuffer m_vbo;
    QOpenGLBuffer m_vbo2;
    QOpenGLBuffer m_vbo3;

    QOpenGLShaderProgram *m_program;
    QOpenGLShaderProgram *m_program2;
    int attributePos;
    int attributePos2;
    int attributeColor;
    int attributeColor2;
    int attributeTextCoord;
    int attributeTextIndex;
    QOpenGLTexture *m_texture1;
    QOpenGLTexture *m_texture2;

//    double prev;
    QVector3D rotationVec;
    double scaleSize;
    QImage frontImg;
    bool initialized;
//    double imgRatio;
};

#endif // MYOPENGLWIDGET_H
