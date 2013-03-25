/********************************************************************************
** Form generated from reading UI file 'authentication_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTHENTICATION_DIALOG_H
#define UI_AUTHENTICATION_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_AuthenticationDialog
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *userEdit;
    QLabel *label_3;
    QLineEdit *passwordEdit;
    QDialogButtonBox *buttonBox;
    QLabel *label_4;
    QLabel *siteDescription;
    QSpacerItem *spacerItem;

    void setupUi(QDialog *AuthenticationDialog)
    {
        if (AuthenticationDialog->objectName().isEmpty())
            AuthenticationDialog->setObjectName(QStringLiteral("AuthenticationDialog"));
        AuthenticationDialog->resize(419, 146);
        AuthenticationDialog->setSizeGripEnabled(true);
        gridLayout = new QGridLayout(AuthenticationDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(AuthenticationDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setWordWrap(false);

        gridLayout->addWidget(label, 0, 0, 1, 2);

        label_2 = new QLabel(AuthenticationDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        userEdit = new QLineEdit(AuthenticationDialog);
        userEdit->setObjectName(QStringLiteral("userEdit"));

        gridLayout->addWidget(userEdit, 2, 1, 1, 1);

        label_3 = new QLabel(AuthenticationDialog);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 3, 0, 1, 1);

        passwordEdit = new QLineEdit(AuthenticationDialog);
        passwordEdit->setObjectName(QStringLiteral("passwordEdit"));

        gridLayout->addWidget(passwordEdit, 3, 1, 1, 1);

        buttonBox = new QDialogButtonBox(AuthenticationDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 5, 0, 1, 2);

        label_4 = new QLabel(AuthenticationDialog);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 1, 0, 1, 1);

        siteDescription = new QLabel(AuthenticationDialog);
        siteDescription->setObjectName(QStringLiteral("siteDescription"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        siteDescription->setFont(font);
        siteDescription->setWordWrap(true);

        gridLayout->addWidget(siteDescription, 1, 1, 1, 1);

        spacerItem = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(spacerItem, 4, 0, 1, 1);


        retranslateUi(AuthenticationDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), AuthenticationDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), AuthenticationDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(AuthenticationDialog);
    } // setupUi

    void retranslateUi(QDialog *AuthenticationDialog)
    {
        AuthenticationDialog->setWindowTitle(QApplication::translate("AuthenticationDialog", "HTTP Authentication Required", 0));
        label->setText(QApplication::translate("AuthenticationDialog", "You need to supply a Username and a Password to access this site", 0));
        label_2->setText(QApplication::translate("AuthenticationDialog", "Username:", 0));
        label_3->setText(QApplication::translate("AuthenticationDialog", "Password:", 0));
        label_4->setText(QApplication::translate("AuthenticationDialog", "Site:", 0));
        siteDescription->setText(QApplication::translate("AuthenticationDialog", "%1 at %2", 0));
    } // retranslateUi

};

namespace Ui {
    class AuthenticationDialog: public Ui_AuthenticationDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTHENTICATION_DIALOG_H
