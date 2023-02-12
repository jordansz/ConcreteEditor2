#include <QtTest>
#include <QCoreApplication>

// add necessary includes here

class MainWindowTest : public QObject
{
    Q_OBJECT

public:
    MainWindowTest();
    ~MainWindowTest();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();

};

MainWindowTest::MainWindowTest()
{

}

MainWindowTest::~MainWindowTest()
{

}

void MainWindowTest::initTestCase()
{

}

void MainWindowTest::cleanupTestCase()
{

}

void MainWindowTest::test_case1()
{

}

QTEST_MAIN(MainWindowTest)

#include "tst_mainwindowtest.moc"
