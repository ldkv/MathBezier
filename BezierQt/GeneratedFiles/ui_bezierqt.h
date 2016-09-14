/********************************************************************************
** Form generated from reading UI file 'bezierqt.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BEZIERQT_H
#define UI_BEZIERQT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BezierQtClass
{
public:
    QAction *newPointControlGroup;
    QAction *actionQuitter;
    QAction *actionChanger_le_pas;
    QAction *actionChanger_la_couleur;
    QAction *actionTransformation;
    QAction *actionRaccordement;
    QAction *actionCornerCutting;
    QAction *actionNouveau;
    QAction *actionParametrage;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *mainLayout;
    QMenuBar *menuBar;
    QMenu *menuFichier;
    QMenu *menuOptions;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *BezierQtClass)
    {
        if (BezierQtClass->objectName().isEmpty())
            BezierQtClass->setObjectName(QStringLiteral("BezierQtClass"));
        BezierQtClass->resize(948, 658);
        newPointControlGroup = new QAction(BezierQtClass);
        newPointControlGroup->setObjectName(QStringLiteral("newPointControlGroup"));
        actionQuitter = new QAction(BezierQtClass);
        actionQuitter->setObjectName(QStringLiteral("actionQuitter"));
        actionChanger_le_pas = new QAction(BezierQtClass);
        actionChanger_le_pas->setObjectName(QStringLiteral("actionChanger_le_pas"));
        actionChanger_la_couleur = new QAction(BezierQtClass);
        actionChanger_la_couleur->setObjectName(QStringLiteral("actionChanger_la_couleur"));
        actionTransformation = new QAction(BezierQtClass);
        actionTransformation->setObjectName(QStringLiteral("actionTransformation"));
        actionRaccordement = new QAction(BezierQtClass);
        actionRaccordement->setObjectName(QStringLiteral("actionRaccordement"));
        actionCornerCutting = new QAction(BezierQtClass);
        actionCornerCutting->setObjectName(QStringLiteral("actionCornerCutting"));
        actionCornerCutting->setCheckable(true);
        actionNouveau = new QAction(BezierQtClass);
        actionNouveau->setObjectName(QStringLiteral("actionNouveau"));
        actionParametrage = new QAction(BezierQtClass);
        actionParametrage->setObjectName(QStringLiteral("actionParametrage"));
        centralWidget = new QWidget(BezierQtClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        mainLayout = new QHBoxLayout();
        mainLayout->setSpacing(6);
        mainLayout->setObjectName(QStringLiteral("mainLayout"));

        horizontalLayout->addLayout(mainLayout);

        BezierQtClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(BezierQtClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 948, 31));
        menuFichier = new QMenu(menuBar);
        menuFichier->setObjectName(QStringLiteral("menuFichier"));
        menuOptions = new QMenu(menuBar);
        menuOptions->setObjectName(QStringLiteral("menuOptions"));
        BezierQtClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(BezierQtClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        BezierQtClass->setStatusBar(statusBar);

        menuBar->addAction(menuFichier->menuAction());
        menuBar->addAction(menuOptions->menuAction());
        menuFichier->addAction(actionNouveau);
        menuFichier->addAction(newPointControlGroup);
        menuFichier->addAction(actionCornerCutting);
        menuFichier->addSeparator();
        menuFichier->addAction(actionChanger_le_pas);
        menuFichier->addAction(actionQuitter);
        menuOptions->addAction(actionChanger_la_couleur);
        menuOptions->addAction(actionParametrage);
        menuOptions->addAction(actionTransformation);
        menuOptions->addAction(actionRaccordement);

        retranslateUi(BezierQtClass);

        QMetaObject::connectSlotsByName(BezierQtClass);
    } // setupUi

    void retranslateUi(QMainWindow *BezierQtClass)
    {
        BezierQtClass->setWindowTitle(QApplication::translate("BezierQtClass", "BezierQt", 0));
        newPointControlGroup->setText(QApplication::translate("BezierQtClass", "Ajouter des points de contr\303\264le", 0));
#ifndef QT_NO_TOOLTIP
        newPointControlGroup->setToolTip(QApplication::translate("BezierQtClass", "Cr\303\251er des nouveaux points de contr\303\264le", 0));
#endif // QT_NO_TOOLTIP
        newPointControlGroup->setShortcut(QApplication::translate("BezierQtClass", "Ctrl+A", 0));
        actionQuitter->setText(QApplication::translate("BezierQtClass", "Quitter", 0));
        actionQuitter->setShortcut(QApplication::translate("BezierQtClass", "Ctrl+Q", 0));
        actionChanger_le_pas->setText(QApplication::translate("BezierQtClass", "Changer le pas", 0));
        actionChanger_le_pas->setShortcut(QApplication::translate("BezierQtClass", "Ctrl+P", 0));
        actionChanger_la_couleur->setText(QApplication::translate("BezierQtClass", "Changer la couleur", 0));
        actionChanger_la_couleur->setShortcut(QApplication::translate("BezierQtClass", "Ctrl+C", 0));
        actionTransformation->setText(QApplication::translate("BezierQtClass", "Transformation", 0));
        actionTransformation->setShortcut(QApplication::translate("BezierQtClass", "Ctrl+T", 0));
        actionRaccordement->setText(QApplication::translate("BezierQtClass", "Raccordement", 0));
        actionRaccordement->setShortcut(QApplication::translate("BezierQtClass", "Ctrl+R", 0));
        actionCornerCutting->setText(QApplication::translate("BezierQtClass", "Corner Cutting", 0));
#ifndef QT_NO_TOOLTIP
        actionCornerCutting->setToolTip(QApplication::translate("BezierQtClass", "Technique Corner Cutting", 0));
#endif // QT_NO_TOOLTIP
        actionCornerCutting->setShortcut(QApplication::translate("BezierQtClass", "Ctrl+Shift+A", 0));
        actionNouveau->setText(QApplication::translate("BezierQtClass", "Nouveau/Effacer", 0));
        actionNouveau->setShortcut(QApplication::translate("BezierQtClass", "Ctrl+N", 0));
        actionParametrage->setText(QApplication::translate("BezierQtClass", "Espace param\303\251trage", 0));
        actionParametrage->setShortcut(QApplication::translate("BezierQtClass", "Ctrl+E", 0));
        menuFichier->setTitle(QApplication::translate("BezierQtClass", "Actions globales", 0));
        menuOptions->setTitle(QApplication::translate("BezierQtClass", "Options locales", 0));
    } // retranslateUi

};

namespace Ui {
    class BezierQtClass: public Ui_BezierQtClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BEZIERQT_H
