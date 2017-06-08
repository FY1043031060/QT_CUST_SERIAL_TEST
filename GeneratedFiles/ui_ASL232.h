/********************************************************************************
** Form generated from reading UI file 'ASL232.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ASL232_H
#define UI_ASL232_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ASL232
{
public:
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_12;
    QVBoxLayout *verticalLayout_5;
    QLabel *labelDevName;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *comboBoxChannelSend;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QComboBox *comboBoxBaudrate;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QComboBox *comboBoxDataBit;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QComboBox *comboBoxStopBit;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QComboBox *comboBoxParityBit;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonConfig;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout;
    QLabel *label_6;
    QLabel *labelSendLength;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_3;
    QTextEdit *textEditSend;
    QHBoxLayout *horizontalLayout_9;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButtonClear;
    QLineEdit *lineEditTimerSet;
    QCheckBox *checkBoxFixData;
    QCheckBox *checkBoxTimerSet;
    QPushButton *pushButtonSend;
    QHBoxLayout *horizontalLayout_11;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_8;
    QComboBox *comboBoxChannelRecv;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_7;
    QLabel *labelRecvLength;
    QSpacerItem *verticalSpacer_2;
    QTextEdit *textEditRecv;

    void setupUi(QWidget *ASL232)
    {
        if (ASL232->objectName().isEmpty())
            ASL232->setObjectName(QStringLiteral("ASL232"));
        ASL232->resize(800, 600);
        verticalLayout_6 = new QVBoxLayout(ASL232);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        labelDevName = new QLabel(ASL232);
        labelDevName->setObjectName(QStringLiteral("labelDevName"));

        verticalLayout_5->addWidget(labelDevName);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(ASL232);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        comboBoxChannelSend = new QComboBox(ASL232);
        comboBoxChannelSend->setObjectName(QStringLiteral("comboBoxChannelSend"));

        horizontalLayout->addWidget(comboBoxChannelSend);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 1);

        verticalLayout_5->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(ASL232);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        comboBoxBaudrate = new QComboBox(ASL232);
        comboBoxBaudrate->setObjectName(QStringLiteral("comboBoxBaudrate"));

        horizontalLayout_2->addWidget(comboBoxBaudrate);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 1);

        verticalLayout_5->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(ASL232);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_3->addWidget(label_3);

        comboBoxDataBit = new QComboBox(ASL232);
        comboBoxDataBit->setObjectName(QStringLiteral("comboBoxDataBit"));

        horizontalLayout_3->addWidget(comboBoxDataBit);

        horizontalLayout_3->setStretch(0, 1);
        horizontalLayout_3->setStretch(1, 1);

        verticalLayout_5->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_4 = new QLabel(ASL232);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_4->addWidget(label_4);

        comboBoxStopBit = new QComboBox(ASL232);
        comboBoxStopBit->setObjectName(QStringLiteral("comboBoxStopBit"));

        horizontalLayout_4->addWidget(comboBoxStopBit);

        horizontalLayout_4->setStretch(0, 1);
        horizontalLayout_4->setStretch(1, 1);

        verticalLayout_5->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_5 = new QLabel(ASL232);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_5->addWidget(label_5);

        comboBoxParityBit = new QComboBox(ASL232);
        comboBoxParityBit->setObjectName(QStringLiteral("comboBoxParityBit"));

        horizontalLayout_5->addWidget(comboBoxParityBit);

        horizontalLayout_5->setStretch(0, 1);
        horizontalLayout_5->setStretch(1, 1);

        verticalLayout_5->addLayout(horizontalLayout_5);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer);

        pushButtonConfig = new QPushButton(ASL232);
        pushButtonConfig->setObjectName(QStringLiteral("pushButtonConfig"));

        horizontalLayout_8->addWidget(pushButtonConfig);

        horizontalLayout_8->setStretch(0, 1);
        horizontalLayout_8->setStretch(1, 1);

        verticalLayout_5->addLayout(horizontalLayout_8);

        verticalLayout_5->setStretch(0, 1);
        verticalLayout_5->setStretch(1, 1);
        verticalLayout_5->setStretch(2, 1);
        verticalLayout_5->setStretch(3, 1);
        verticalLayout_5->setStretch(4, 1);
        verticalLayout_5->setStretch(5, 1);
        verticalLayout_5->setStretch(6, 1);

        horizontalLayout_12->addLayout(verticalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_6 = new QLabel(ASL232);
        label_6->setObjectName(QStringLiteral("label_6"));

        verticalLayout->addWidget(label_6);

        labelSendLength = new QLabel(ASL232);
        labelSendLength->setObjectName(QStringLiteral("labelSendLength"));

        verticalLayout->addWidget(labelSendLength);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout_6->addLayout(verticalLayout);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        textEditSend = new QTextEdit(ASL232);
        textEditSend->setObjectName(QStringLiteral("textEditSend"));

        verticalLayout_3->addWidget(textEditSend);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_2);

        pushButtonClear = new QPushButton(ASL232);
        pushButtonClear->setObjectName(QStringLiteral("pushButtonClear"));

        horizontalLayout_9->addWidget(pushButtonClear);

        lineEditTimerSet = new QLineEdit(ASL232);
        lineEditTimerSet->setObjectName(QStringLiteral("lineEditTimerSet"));

        horizontalLayout_9->addWidget(lineEditTimerSet);

        checkBoxFixData = new QCheckBox(ASL232);
        checkBoxFixData->setObjectName(QStringLiteral("checkBoxFixData"));

        horizontalLayout_9->addWidget(checkBoxFixData);

        checkBoxTimerSet = new QCheckBox(ASL232);
        checkBoxTimerSet->setObjectName(QStringLiteral("checkBoxTimerSet"));

        horizontalLayout_9->addWidget(checkBoxTimerSet);

        pushButtonSend = new QPushButton(ASL232);
        pushButtonSend->setObjectName(QStringLiteral("pushButtonSend"));

        horizontalLayout_9->addWidget(pushButtonSend);


        verticalLayout_3->addLayout(horizontalLayout_9);


        horizontalLayout_6->addLayout(verticalLayout_3);

        horizontalLayout_6->setStretch(0, 1);
        horizontalLayout_6->setStretch(1, 5);

        horizontalLayout_12->addLayout(horizontalLayout_6);

        horizontalLayout_12->setStretch(0, 1);
        horizontalLayout_12->setStretch(1, 3);

        verticalLayout_6->addLayout(horizontalLayout_12);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        label_8 = new QLabel(ASL232);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayout_10->addWidget(label_8);

        comboBoxChannelRecv = new QComboBox(ASL232);
        comboBoxChannelRecv->setObjectName(QStringLiteral("comboBoxChannelRecv"));

        horizontalLayout_10->addWidget(comboBoxChannelRecv);

        horizontalLayout_10->setStretch(0, 1);
        horizontalLayout_10->setStretch(1, 1);

        verticalLayout_4->addLayout(horizontalLayout_10);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_3);


        horizontalLayout_11->addLayout(verticalLayout_4);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_7 = new QLabel(ASL232);
        label_7->setObjectName(QStringLiteral("label_7"));

        verticalLayout_2->addWidget(label_7);

        labelRecvLength = new QLabel(ASL232);
        labelRecvLength->setObjectName(QStringLiteral("labelRecvLength"));

        verticalLayout_2->addWidget(labelRecvLength);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);


        horizontalLayout_7->addLayout(verticalLayout_2);

        textEditRecv = new QTextEdit(ASL232);
        textEditRecv->setObjectName(QStringLiteral("textEditRecv"));

        horizontalLayout_7->addWidget(textEditRecv);

        horizontalLayout_7->setStretch(0, 1);
        horizontalLayout_7->setStretch(1, 5);

        horizontalLayout_11->addLayout(horizontalLayout_7);

        horizontalLayout_11->setStretch(0, 1);
        horizontalLayout_11->setStretch(1, 3);

        verticalLayout_6->addLayout(horizontalLayout_11);


        retranslateUi(ASL232);

        QMetaObject::connectSlotsByName(ASL232);
    } // setupUi

    void retranslateUi(QWidget *ASL232)
    {
        ASL232->setWindowTitle(QApplication::translate("ASL232", "Form", Q_NULLPTR));
        labelDevName->setText(QApplication::translate("ASL232", "\344\270\262\345\217\243\350\260\203\350\257\225\350\256\276\345\244\207", Q_NULLPTR));
        label->setText(QApplication::translate("ASL232", "\351\200\232\351\201\223\345\217\267", Q_NULLPTR));
        label_2->setText(QApplication::translate("ASL232", "\346\263\242\347\211\271\347\216\207", Q_NULLPTR));
        label_3->setText(QApplication::translate("ASL232", "\346\225\260\346\215\256\344\275\215", Q_NULLPTR));
        label_4->setText(QApplication::translate("ASL232", "\345\201\234\346\255\242\344\275\215", Q_NULLPTR));
        label_5->setText(QApplication::translate("ASL232", "\346\240\241\351\252\214\344\275\215", Q_NULLPTR));
        pushButtonConfig->setText(QApplication::translate("ASL232", "\351\205\215\347\275\256", Q_NULLPTR));
        label_6->setText(QApplication::translate("ASL232", "\345\217\221\351\200\201", Q_NULLPTR));
        labelSendLength->setText(QApplication::translate("ASL232", "\346\225\260\351\207\217", Q_NULLPTR));
        pushButtonClear->setText(QApplication::translate("ASL232", "\346\270\205\347\251\272", Q_NULLPTR));
        checkBoxFixData->setText(QApplication::translate("ASL232", "\345\233\272\345\256\232\346\225\260\346\215\256", Q_NULLPTR));
        checkBoxTimerSet->setText(QApplication::translate("ASL232", "\345\256\232\346\227\266\345\217\221\351\200\201", Q_NULLPTR));
        pushButtonSend->setText(QApplication::translate("ASL232", "\345\217\221\351\200\201", Q_NULLPTR));
        label_8->setText(QApplication::translate("ASL232", "\351\200\232\351\201\223\345\217\267", Q_NULLPTR));
        label_7->setText(QApplication::translate("ASL232", "\346\216\245\346\224\266", Q_NULLPTR));
        labelRecvLength->setText(QApplication::translate("ASL232", "\346\225\260\351\207\217", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ASL232: public Ui_ASL232 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ASL232_H
