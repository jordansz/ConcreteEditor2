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
//    void mousePressEvent(QMouseEvent *event) override;
//    void keyPressEvent(QKeyEvent *event) override;
//    void showEvent(QShowEvent *event) override;

private:
    void transformSquare(QImage img);
    void initTextures(QImage img1, QImage img2);
    void initShader(const QString &fp1, const QString &fp2);

public slots:
    void hasTexturePicked();
    void updateTilt(double num);
    void updateWobble(double num);

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
    bool hasTexture;
    double xRot;
    double yRot;
    double zRot;
//    QOpenGLTexture *m_texture2;
//    double imgRatio;
};

#endif // MYOPENGLWIDGET_H
