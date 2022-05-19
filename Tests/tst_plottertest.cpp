#include <QtTest>
#include "../headers/evaluatePostfix.h"

// add necessary includes here

class PlotterTest : public QObject
{
    Q_OBJECT

public:
    PlotterTest();
    ~PlotterTest();

private slots:
    void test_isValid_data();
    void test_isValid();
    void test_evaluate_data();
    void test_evaluate();
};

PlotterTest::PlotterTest()
{

}

PlotterTest::~PlotterTest()
{

}

void PlotterTest::test_isValid_data(){
    QTest::addColumn<QString>("string");
    QTest::addColumn<int>("result");

    QTest::newRow("Valid Given Example") << "5*x^3+2*x" << 0;
    QTest::newRow("Unbalanced Parentheses") << "(x" << 1;
    QTest::newRow("Valid Expression") << "x" << 0;
    QTest::newRow("Valid Expression") << "-x" << 0;
    QTest::newRow("No operation between elements") << "5x" << 1;
    QTest::newRow("misplaced operator") << "x/" << 1;
    QTest::newRow("Invalid Division by zero") << "5/0" << 1;
    QTest::newRow("Invalid Arithmetic Operation") << "0^0" << 1;
    QTest::newRow("Unbalanced Parentheses") << "(-5*x)^1" << 0;
}

void PlotterTest::test_isValid()
{
    QFETCH(QString, string);
    QFETCH(int, result);

    QCOMPARE(isValid(string).size(), result);
}

void PlotterTest::test_evaluate_data(){
    QTest::addColumn<QVector<QString>>("expression");
    QTest::addColumn<double>("value");
    QTest::addColumn<double>("Result");

    QTest::newRow("test \"5*x^3+2*x\"") << infix2Postfix("5*x^3+2*x") << 2.0 << 44.0;
    QTest::newRow("test \"x/5\"") << infix2Postfix("x/5") << 2.0 << 0.4;
    QTest::newRow("test \"x+5\"") << infix2Postfix("x+5") << 2.0 << 7.0;
    QTest::newRow("test \"5*x\"") << infix2Postfix("5*x") << 10.0 << 50.0;
    QTest::newRow("test \"x^3\"") << infix2Postfix("x^3") << 2.0 << 8.0;
    QTest::newRow("test \"1-x\"") << infix2Postfix("1-x") << 1.5 << -0.5;
}

void PlotterTest::test_evaluate()
{
    QFETCH(QVector<QString>, expression);
    QFETCH(double, value);
    QFETCH(double, Result);

    QCOMPARE(evaluate(expression, value), Result);
}


QTEST_MAIN(PlotterTest)

#include "tst_plottertest.moc"
