/*
    UTimeEdit - small utility to manipulate Unix timestamps
    Copyright (C) 2020  Nick Korotysh <nick.korotysh@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "utimeeditwidget.h"
#include "ui_utimeeditwidget.h"

#include <QApplication>
#include <QClipboard>
#include <QDateTime>
#include <QRegularExpressionValidator>


inline QString timestamp2datetime(const QString& timestamp, bool is_utc)
{
  return QDateTime::fromSecsSinceEpoch(timestamp.toLongLong(), is_utc ? Qt::UTC : Qt::LocalTime).toString();
}


UTimeEditWidget::UTimeEditWidget(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::UTimeEditWidget)
{
  ui->setupUi(this);

  ui->src_timestamp_edit->setValidator(new QRegularExpressionValidator(QRegularExpression("\\d+"), this));

  ui->unit_combo_box->addItem(tr("Sec"), 1);
  ui->unit_combo_box->addItem(tr("Min"), 60);
  ui->unit_combo_box->addItem(tr("Hour"), 3600);
  ui->unit_combo_box->addItem(tr("Day"), 24 * 3600);
  ui->unit_combo_box->addItem(tr("Week"), 7 * 24 * 3600);

  ui->unit_combo_box->setCurrentIndex(0);

  ui->delta_edit->setMaximum(std::numeric_limits<int>::max());
}

UTimeEditWidget::~UTimeEditWidget()
{
  delete ui;
}

void UTimeEditWidget::on_now_button_clicked()
{
  ui->src_timestamp_edit->setText(QString::number(QDateTime::currentSecsSinceEpoch()));
}

void UTimeEditWidget::on_add_button_clicked()
{
  doCalculation(std::plus<qint64>());
}

void UTimeEditWidget::on_sub_button_clicked()
{
  doCalculation(std::minus<qint64>());
}

void UTimeEditWidget::on_copy_timestamp_button_clicked()
{
  QApplication::clipboard()->setText(ui->res_timestamp_edit->text());
}

void UTimeEditWidget::on_src_timestamp_edit_textChanged(const QString& arg1)
{
  ui->src_datetime_edit->setText(timestamp2datetime(arg1, ui->src_is_utc_button->isChecked()));
}

void UTimeEditWidget::on_res_timestamp_edit_textChanged(const QString& arg1)
{
  ui->res_datetime_edit->setText(timestamp2datetime(arg1, ui->res_is_utc_button->isChecked()));
}

void UTimeEditWidget::on_src_is_utc_button_toggled(bool checked)
{
  if (ui->src_timestamp_edit->text().isEmpty()) return;
  ui->src_datetime_edit->setText(timestamp2datetime(ui->src_timestamp_edit->text(), checked));
}

void UTimeEditWidget::on_res_is_utc_button_toggled(bool checked)
{
  if (ui->res_timestamp_edit->text().isEmpty()) return;
  ui->res_datetime_edit->setText(timestamp2datetime(ui->res_timestamp_edit->text(), checked));
}

void UTimeEditWidget::doCalculation(std::function<qint64(qint64, qint64)> op)
{
  qint64 src_timestamp = ui->src_timestamp_edit->text().toLongLong();
  qint64 delta = ui->delta_edit->value() * ui->unit_combo_box->currentData().toLongLong();
  qint64 result_timestamp = op(src_timestamp, delta);
  ui->res_timestamp_edit->setText(QString::number(result_timestamp));
  if (QApplication::keyboardModifiers() & Qt::ShiftModifier)
    ui->src_timestamp_edit->setText(ui->res_timestamp_edit->text());
}
