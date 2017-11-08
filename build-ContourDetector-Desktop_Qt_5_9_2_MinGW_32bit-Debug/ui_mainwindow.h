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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
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
    QLineEdit *pathLineEdit;
    QToolButton *pathButton;
    QLabel *imageLabel;
    QLabel *trashholdLabel;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *trashHoldSliderMinLabel;
    QSlider *trashholSlider;
    QLabel *trashholdSliderMaxLabel;
    QPushButton *blackAndWhiteButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(498, 402);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pathLineEdit = new QLineEdit(centralWidget);
        pathLineEdit->setObjectName(QStringLiteral("pathLineEdit"));

        horizontalLayout->addWidget(pathLineEdit);

        pathButton = new QToolButton(centralWidget);
        pathButton->setObjectName(QStringLiteral("pathButton"));

        horizontalLayout->addWidget(pathButton);


        verticalLayout->addLayout(horizontalLayout);

        imageLabel = new QLabel(centralWidget);
        imageLabel->setObjectName(QStringLiteral("imageLabel"));
        imageLabel->setMinimumSize(QSize(480, 300));
        imageLabel->setStyleSheet(QStringLiteral("background: rgb(255, 255, 255)"));

        verticalLayout->addWidget(imageLabel);

        trashholdLabel = new QLabel(centralWidget);
        trashholdLabel->setObjectName(QStringLiteral("trashholdLabel"));

        verticalLayout->addWidget(trashholdLabel);

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

        blackAndWhiteButton = new QPushButton(centralWidget);
        blackAndWhiteButton->setObjectName(QStringLiteral("blackAndWhiteButton"));

        horizontalLayout_3->addWidget(blackAndWhiteButton);


        verticalLayout->addLayout(horizontalLayout_3);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        pathButton->setText(QApplication::translate("MainWindow", "...", Q_NULLPTR));
        imageLabel->setText(QString());
        trashholdLabel->setText(QApplication::translate("MainWindow", "\320\237\320\276\321\200\320\276\320\263\320\276\320\262\320\276\320\265 \320\267\320\275\320\260\321\207\320\265\320\275\320\270\320\265 \320\261\320\270\320\275\320\260\321\200\320\270\320\267\320\260\321\206\320\270\320\270", Q_NULLPTR));
        trashHoldSliderMinLabel->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        trashholdSliderMaxLabel->setText(QApplication::translate("MainWindow", "255", Q_NULLPTR));
        blackAndWhiteButton->setText(QApplication::translate("MainWindow", "Make B&W", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
