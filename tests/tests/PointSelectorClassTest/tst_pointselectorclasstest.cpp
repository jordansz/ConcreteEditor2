#include <QtTest>
#include <QCoreApplication>

// add necessary includes here

class PointSelectorClassTest : public QObject
{
    Q_OBJECT

public:
    PointSelectorClassTest();
    ~PointSelectorClassTest();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();

};

PointSelectorClassTest::PointSelectorClassTest()
{

}

PointSelectorClassTest::~PointSelectorClassTest()
{

}

void PointSelectorClassTest::initTestCase()
{

}

void PointSelectorClassTest::cleanupTestCase()
{

}

void PointSelectorClassTest::test_case1()
{

}

QTEST_MAIN(PointSelectorClassTest)

#include "tst_pointselectorclasstest.moc"
