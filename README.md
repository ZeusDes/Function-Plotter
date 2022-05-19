# Function-Plotter

## Abstract Background

This Application simply take a mathematical expression as  an input from user and plot the corresponding graph with an interval taken from user and also user can specify the presicion by selecting the number of points used to plot the graph.

The Function Plotter has the following specifications:

- The plotter Support the following operators **(+, -, \*, /, ^)** only.

- The Entered Expression must be in terms of **x** only.

- The user is prompted to specify the minimum, maximum values of x.

- The user is prompted to specify the number of points used to plot the graph.

## Frameworks & Libraries

- Qt Creator: Used to make the GUI

- QCustomPlot: Used to make the graph

- QTest: Used in unit Testing

- cppcheck: Used for code Analysis

## Examples

> *Valid Example:* 5\*x^3+2\*x

![Valid Example](https://i.imgur.com/ncI41pI.png "Valid Example: 5*x^3+2*x")

> *Invalid Example:* 5\*x\*

![Invalid Example](https://i.imgur.com/X6LQfCy.png "Invalid Example: 5*x*")

# Testing & Analysis

This project has been tested by [QTest](https://doc.qt.io/qt-5/qtest-overview.html) framework, including the testing source code in [Tests](Tests) project.
This project has been analysed with [cppcheck](https://cppcheck.sourceforge.io/) static code analysis tool and has reported ***NO*** Errors nor warning.
