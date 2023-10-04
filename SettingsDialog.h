#pragma once

#include "ui_SettingsDialog.h"

class SettingsDialog :
    public QDialog
{
    Q_OBJECT
public:
    SettingsDialog(QWidget* parent = nullptr);

signals:
    void settingsChanged();

public slots:
    void accept();

protected:
    void closeEvent(QCloseEvent* event);
    void showEvent(QShowEvent* event);

private:
    Ui::settingsDialog ui;
};

