/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *pathLabel;
    QLineEdit *pathLineEdit;
    QToolButton *pathButton;
    QHBoxLayout *horizontalLayout_4;
    QLabel *trashholdLabel;
    QSpinBox *devesaionSpinBox;
    QSpacerItem *horizontalSpacer;
    QLabel *imageLabel;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *trashHoldSliderMinLabel;
    QSlider *trashholSlider;
    QLabel *trashholdSliderMaxLabel;
    QRadioButton *colorRadio;
    QRadioButton *bawDevide3Radio;
    QRadioButton *bawFormulaRadio;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(658, 613);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pathLabel = new QLabel(centralWidget);
        pathLabel->setObjectName(QStringLiteral("pathLabel"));
        pathLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(pathLabel);

        pathLineEdit = new QLineEdit(centralWidget);
        pathLineEdit->setObjectName(QStringLiteral("pathLineEdit"));
        pathLineEdit->setMinimumSize(QSize(300, 0));

        horizontalLayout->addWidget(pathLineEdit);

        pathButton = new QToolButton(centralWidget);
        pathButton->setObjectName(QStringLiteral("pathButton"));

        horizontalLayout->addWidget(pathButton);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        trashholdLabel = new QLabel(centralWidget);
        trashholdLabel->setObjectName(QStringLiteral("trashholdLabel"));

        horizontalLayout_4->addWidget(trashholdLabel);

        devesaionSpinBox = new QSpinBox(centralWidget);
        devesaionSpinBox->setObjectName(QStringLiteral("devesaionSpinBox"));
        devesaionSpinBox->setMinimumSize(QSize(100, 0));
        devesaionSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        devesaionSpinBox->setMaximum(255);

        horizontalLayout_4->addWidget(devesaionSpinBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_4);

        imageLabel = new QLabel(centralWidget);
        imageLabel->setObjectName(QStringLiteral("imageLabel"));
        imageLabel->setMinimumSize(QSize(640, 480));
        imageLabel->setStyleSheet(QLatin1String("background: rgb(255, 255, 255);\n"
"border-color: rgb(0, 0, 0);\n"
"border-size: 2px;"));

        verticalLayout->addWidget(imageLabel);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        trashHoldSliderMinLabel = new QLabel(centralWidget);
        trashHoldSliderMinLabel->setObjectName(QStringLiteral("trashHoldSliderMinLabel"));
        trashHoldSliderMinLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(trashHoldSliderMinLabel);

        trashholSlider = new QSlider(centralWidget);
        trashholSlider->setObjectName(QStringLiteral("trashholSlider"));
        trashholSlider->setMaximum(255);
        trashholSlider->setOrientation(Qt::Horizontal);
        trashholSlider->setInvertedAppearance(false);
        trashholSlider->setTickPosition(QSlider::TicksBelow);

        horizontalLayout_2->addWidget(trashholSlider);

        trashholdSliderMaxLabel = new QLabel(centralWidget);
        trashholdSliderMaxLabel->setObjectName(QStringLiteral("trashholdSliderMaxLabel"));

        horizontalLayout_2->addWidget(trashholdSliderMaxLabel);


        horizontalLayout_3->addLayout(horizontalLayout_2);

        colorRadio = new QRadioButton(centralWidget);
        colorRadio->setObjectName(QStringLiteral("colorRadio"));
        colorRadio->setChecked(true);

        horizontalLayout_3->addWidget(colorRadio);

        bawDevide3Radio = new QRadioButton(centralWidget);
        bawDevide3Radio->setObjectName(QStringLiteral("bawDevide3Radio"));

        horizontalLayout_3->addWidget(bawDevide3Radio);

        bawFormulaRadio = new QRadioButton(centralWidget);
        bawFormulaRadio->setObjectName(QStringLiteral("bawFormulaRadio"));

        horizontalLayout_3->addWidget(bawFormulaRadio);


        verticalLayout->addLayout(horizontalLayout_3);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        pathLabel->setText(QApplication::translate("MainWindow", "\320\237\321\203\321\202\321\214 \320\272 \320\272\320\260\321\200\321\202\320\270\320\275\320\272\320\265:", Q_NULLPTR));
        pathButton->setText(QApplication::translate("MainWindow", "...", Q_NULLPTR));
        trashholdLabel->setText(QApplication::translate("MainWindow", "\320\237\320\276\321\200\320\276\320\263\320\276\320\262\320\276\320\265 \320\267\320\275\320\260\321\207\320\265\320\275\320\270\320\265 \320\261\320\270\320\275\320\260\321\200\320\270\320\267\320\260\321\206\320\270\320\270:", Q_NULLPTR));
        imageLabel->setText(QString());
        trashHoldSliderMinLabel->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        trashholdSliderMaxLabel->setText(QApplication::translate("MainWindow", "255", Q_NULLPTR));
        colorRadio->setText(QApplication::translate("MainWindow", "\320\246\320\262\320\265\321\202\320\275\320\276\320\265", Q_NULLPTR));
        bawDevide3Radio->setText(QApplication::translate("MainWindow", "\320\247\320\221 / 3", Q_NULLPTR));
        bawFormulaRadio->setText(QApplication::translate("MainWindow", "\320\247\320\221 \321\204\320\276\321\200\320\274\321\203\320\273\320\260", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
