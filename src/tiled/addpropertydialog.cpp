/*
 * addpropertydialog.cpp
 * Copyright 2015, CaptainFrog <jwilliam.perreault@gmail.com>
 * Copyright 2016, Thorbjørn Lindeijer <thorbjorn@lindeijer.nl>
 *
 * This file is part of Tiled.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "addpropertydialog.h"
#include "ui_addpropertydialog.h"

#include "preferences.h"
#include "properties.h"
#include "utils.h"
#include "documentmanager.h"

#include <QPushButton>
#include <QSettings>

using namespace Tiled;

static const char * const TYPE_KEY = "AddPropertyDialog/PropertyType";
static const char * const NAME_KEY = "AddPropertyDialog/PropertyName";

AddPropertyDialog::AddPropertyDialog(const QString& type, QWidget *parent)
    : QDialog(parent),
      // JUMPARIO
      mType(type),
      mUi(new Ui::AddPropertyDialog)
{
#if QT_VERSION < QT_VERSION_CHECK(5, 10, 0)
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
#endif

    mUi->setupUi(this);
    resize(Utils::dpiScaled(size()));



    // JUMPARIO
    {
        mUi->name->clear();
        qDebug(qUtf8Printable(type));
        if (type == QLatin1String("physics")) {
            QString defaultName = QStringLiteral("hue");
            mUi->name->addItem(defaultName, defaultName);
            mUi->name->setCurrentText(defaultName);

            nameChanged(defaultName);
        } else if (type == QLatin1String("slick")) {
            QString defaultName = QStringLiteral("hue");
            mUi->name->addItem(defaultName, defaultName);
            mUi->name->setCurrentText(defaultName);

            nameChanged(defaultName);
        } else if (type == QLatin1String("dynamic")) {
            QString defaultName = QStringLiteral("delay");
            mUi->name->addItem(defaultName, defaultName);
            mUi->name->addItem(QStringLiteral("interval"), QStringLiteral("interval"));
            mUi->name->addItem(QStringLiteral("density"), QStringLiteral("density"));
            mUi->name->addItem(QStringLiteral("friction"), QStringLiteral("friction"));
            mUi->name->setCurrentText(defaultName);

            nameChanged(defaultName);
        } else if (type == QLatin1String("spawn")) {
            nameChanged(QStringLiteral(""));
        } else if (type == QLatin1String("goal")) {
            nameChanged(QStringLiteral(""));
        } else if (type == QLatin1String("water")) {
            nameChanged(QStringLiteral(""));
        } else if (type == QLatin1String("spawn")) {
            nameChanged(QStringLiteral(""));
        } else if (type == QLatin1String("safe")) {
            nameChanged(QStringLiteral(""));
        } else if (type == QLatin1String("color")) {
            QString defaultName = QStringLiteral("hue");
            mUi->name->addItem(defaultName, defaultName);
            mUi->name->setCurrentText(defaultName);

            nameChanged(defaultName);
        } else if (type == QLatin1String("particlespawn")) {
            QString defaultName = QStringLiteral("lifetime");
            mUi->name->addItem(defaultName, defaultName);
            mUi->name->addItem(QStringLiteral("rate"), QStringLiteral("rate"));
            mUi->name->setCurrentText(defaultName);

            nameChanged(defaultName);
        } else if (type == QLatin1String("xpboundary")) {
            QString defaultName = QStringLiteral("direction");
            mUi->name->addItem(defaultName, defaultName);
            mUi->name->setCurrentText(defaultName);

            nameChanged(defaultName);
        } else if (type == QLatin1String("xpspawn")) {
            nameChanged(QStringLiteral(""));
        } else if (type == QLatin1String("cover")) {
            QString defaultName = QStringLiteral("cover");
            mUi->name->addItem(defaultName, defaultName);
            mUi->name->setCurrentText(defaultName);

            nameChanged(defaultName);
        } else if (type == QLatin1String("render")) {
            nameChanged(QStringLiteral(""));
        } else if (type == QLatin1String("anchor")) {
            nameChanged(QStringLiteral(""));
        } else if (type == QLatin1String("rope")) {
            QString defaultName = QStringLiteral("segmentlength");
            mUi->name->addItem(defaultName, defaultName);
            mUi->name->addItem(QStringLiteral("segmentwidth"), QStringLiteral("segmentwidth"));
            mUi->name->addItem(QStringLiteral("delay"), QStringLiteral("delay"));
            mUi->name->addItem(QStringLiteral("interval"), QStringLiteral("interval"));
            mUi->name->setCurrentText(defaultName);

            nameChanged(defaultName);
        } else if (type == QLatin1String("collidablerope")) {
            QString defaultName = QStringLiteral("delay");
            mUi->name->addItem(defaultName, defaultName);
            mUi->name->addItem(QStringLiteral("interval"), QStringLiteral("interval"));
            mUi->name->setCurrentText(defaultName);

            nameChanged(defaultName);
        } else if (type == QLatin1String("joint")) {
            QString defaultName = QStringLiteral("torque");
            mUi->name->addItem(defaultName, defaultName);
            mUi->name->addItem(QStringLiteral("delay"), QStringLiteral("delay"));
            mUi->name->addItem(QStringLiteral("interval"), QStringLiteral("interval"));
            mUi->name->setCurrentText(defaultName);

            nameChanged(defaultName);
        } else {
            nameChanged(QStringLiteral(""));
        }

        connect(mUi->name, &QComboBox::currentTextChanged,
                this, &AddPropertyDialog::nameChanged);
    }



    connect(mUi->typeBox, &QComboBox::currentTextChanged,
            this, &AddPropertyDialog::typeChanged);

    mUi->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
}

AddPropertyDialog::~AddPropertyDialog()
{
    delete mUi;
}

QString AddPropertyDialog::propertyName() const
{
    return mUi->name->currentData().toString();
}

QVariant AddPropertyDialog::propertyValue() const
{
    return mUi->typeBox->currentData();
}

void AddPropertyDialog::nameChanged(const QString &text) {
    mUi->typeBox->clear();
    qDebug(qUtf8Printable(text));
    if (text == QLatin1String("hue")) {
        mUi->typeBox->addItem(typeToName(QVariant::Int), 0);
        mUi->typeBox->setCurrentText(typeToName(QVariant::Int));
    } else if (text == QLatin1String("delay")) {
        mUi->typeBox->addItem(typeToName(QVariant::Int), 0);
        mUi->typeBox->setCurrentText(typeToName(QVariant::Int));
    } else if (text == QLatin1String("interval")) {
        mUi->typeBox->addItem(typeToName(QVariant::Int), 0);
        mUi->typeBox->setCurrentText(typeToName(QVariant::Int));
    } else if (text == QLatin1String("lifetime")) {
        mUi->typeBox->addItem(typeToName(QVariant::Int), 0);
        mUi->typeBox->setCurrentText(typeToName(QVariant::Int));
    } else if (text == QLatin1String("rate")) {
        mUi->typeBox->addItem(typeToName(QVariant::Double), 0.0);
        mUi->typeBox->setCurrentText(typeToName(QVariant::Double));
    } else if (text == QLatin1String("direction")) {
        mUi->typeBox->addItem(typeToName(QVariant::String), QString());
        mUi->typeBox->setCurrentText(typeToName(QVariant::String));
    } else if (text == QLatin1String("cover")) {
        mUi->typeBox->addItem(typeToName(QVariant::Int), 0);
        mUi->typeBox->setCurrentText(typeToName(QVariant::Int));
    } else if (text == QLatin1String("segmentlength")) {
        mUi->typeBox->addItem(typeToName(QVariant::Double), 0.0);
        mUi->typeBox->setCurrentText(typeToName(QVariant::Double));
    } else if (text == QLatin1String("segmentwidth")) {
        mUi->typeBox->addItem(typeToName(QVariant::Double), 0.0);
        mUi->typeBox->setCurrentText(typeToName(QVariant::Double));
    } else if (text == QLatin1String("torque")) {
        mUi->typeBox->addItem(typeToName(QVariant::Double), 0.0);
        mUi->typeBox->setCurrentText(typeToName(QVariant::Double));
    } else if (text == QLatin1String("density")) {
        mUi->typeBox->addItem(typeToName(QVariant::Double), 0.0);
        mUi->typeBox->setCurrentText(typeToName(QVariant::Double));
    } else if (text == QLatin1String("friction")) {
        mUi->typeBox->addItem(typeToName(QVariant::Double), 0.0);
        mUi->typeBox->setCurrentText(typeToName(QVariant::Double));
    } else {
        mUi->typeBox->setCurrentText(QStringLiteral(""));
    }
}

void AddPropertyDialog::typeChanged(const QString &text) {

}

std::list<AddPropertyDialog::ItemTypeInfo> AddPropertyDialog::getItemTypeInfoList(const QString& name) {
    std::list<ItemTypeInfo> infoList;

    infoList.push_back({typeToName(QVariant::String), QString()});
}
