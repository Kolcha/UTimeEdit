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
#ifndef UTIMEEDITWIDGET_H
#define UTIMEEDITWIDGET_H

#include <functional>

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class UTimeEditWidget; }
QT_END_NAMESPACE

class UTimeEditWidget : public QWidget
{
  Q_OBJECT

public:
  UTimeEditWidget(QWidget *parent = nullptr);
  ~UTimeEditWidget();

private slots:
  void on_now_button_clicked();

  void on_add_button_clicked();
  void on_sub_button_clicked();

  void on_copy_timestamp_button_clicked();

private:
  void doCalculation(std::function<qint64(qint64, qint64)> op);

  Ui::UTimeEditWidget *ui;
};

#endif // UTIMEEDITWIDGET_H
