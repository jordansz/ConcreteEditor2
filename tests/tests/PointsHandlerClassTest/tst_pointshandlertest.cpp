#include <QtTest>
#include <QCoreApplication>

// add necessary includes here

class PointsHandlerTest : public QObject
{
    Q_OBJECT

public:
    PointsHandlerTest();
    ~PointsHandlerTest();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();

};

PointsHandlerTest::PointsHandlerTest()
{

}

PointsHandlerTest::~PointsHandlerTest()
{

}

void PointsHandlerTest::initTestCase()
{

}

void PointsHandlerTest::cleanupTestCase()
{

}

void PointsHandlerTest::test_case1()
{

}

QTEST_MAIN(PointsHandlerTest)

#include "tst_pointshandlertest.moc"
