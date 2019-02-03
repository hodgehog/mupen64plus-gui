#include "cheatdialog.h"
#include "cheat.h"
#include "common.h"
#include "settingclasses.h"

#include <QButtonGroup>
#include <QLabel>
#include <QScrollArea>
#include <QVBoxLayout>

CheatDialog::CheatDialog()
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QScrollArea *scrollArea = new QScrollArea;
    QWidget *cheatSettings = new QWidget;
    QGridLayout *cheatLayout = new QGridLayout;
    QString cheatName;
    QString desc;
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowTitle("Cheats");
    int p = 0;
    if (l_RomFound && l_CheatCodesFound != 0) {
        sCheatInfo *pCur = l_CheatList;
        while (pCur != NULL)
        {
            cheatName = pCur->Name;
            QLabel* label = new QLabel(cheatName);
            if (pCur->Description != NULL) {
                desc = pCur->Description;
                desc.prepend("<span style=\"color:black;\">");
                desc.append("</span>");
                label->setToolTip(desc);
            }
            label->setStyleSheet("border: 1px solid; padding: 10px");
            cheatLayout->addWidget(label, p, 0);
            if(pCur->VariableLine == -1) {
                CheatCheckBox* checkBox = new CheatCheckBox();
                checkBox->setStyleSheet("border: 1px solid; padding: 10px");
                checkBox->setNumber(pCur->Number);
                checkBox->setOption(0);
                checkBox->setCheckState(pCur->active ? Qt::Checked : Qt::Unchecked);
                cheatLayout->addWidget(checkBox, p, 1);
            } else {
                int i;
                QButtonGroup *subGroup = new QButtonGroup;
                QCheckBox * faker = new QCheckBox;
                subGroup->addButton(faker);
                subGroup->setExclusive(true);
                for (i = 0; i < pCur->Codes[pCur->VariableLine].var_count; i++) {
                    ++p;
                    QLabel* subLabel = new QLabel(pCur->Codes[pCur->VariableLine].variable_names[i]);
                    subLabel->setStyleSheet("border: 1px solid; padding: 10px");
                    subLabel->setAlignment(Qt::AlignRight);
                    cheatLayout->addWidget(subLabel, p, 0);
                    CheatCheckBox* subCheckBox = new CheatCheckBox();
                    subCheckBox->setStyleSheet("border: 1px solid; padding: 10px");
                    subCheckBox->setNumber(pCur->Number);
                    subCheckBox->setOption(i);
                    subCheckBox->setCheckState((pCur->active && pCur->Codes[pCur->VariableLine].var_to_use == i) ? Qt::Checked : Qt::Unchecked);
                    subGroup->addButton(subCheckBox);
                    subCheckBox->setButtonGroup(faker);
                    cheatLayout->addWidget(subCheckBox, p, 1);
                }
            }
            pCur = pCur->Next;
            ++p;
        }
    }
    cheatSettings->setLayout(cheatLayout);
    scrollArea->setWidget(cheatSettings);
    scrollArea->setMinimumWidth(cheatSettings->sizeHint().width() + 20);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mainLayout->addWidget(scrollArea);
    this->setLayout(mainLayout);

}
