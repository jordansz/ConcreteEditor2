#include <QtTest>
#include <QCoreApplication>

// add necessary includes here

class OpenglWidgetTest : public QObject
{
    Q_OBJECT

public:
    OpenglWidgetTest();
    ~OpenglWidgetTest();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();

};

OpenglWidgetTest::OpenglWidgetTest()
{

}

OpenglWidgetTest::~OpenglWidgetTest()
{

}

void OpenglWidgetTest::initTestCase()
{

}

void OpenglWidgetTest::cleanupTestCase()
{

}

void OpenglWidgetTest::test_case1()
{

}

QTEST_MAIN(OpenglWidgetTest)

#include "tst_openglwidgettest.moc"
