#include "SettingsDialog.h"
#include "Settings.h"

SettingsDialog::SettingsDialog(QWidget* parent)
	: QDialog(parent) 
{
	ui.setupUi(this);
}

void SettingsDialog::accept()
{
	Settings::get().numFlights  = ui.flightsNumber->value();
	Settings::get().modelWidth  = ui.modelWidth->value();
	Settings::get().modelHeight = ui.modelHeight->value();
	close();

	int x = Settings::get().modelHeight;
	int y = Settings::get().modelWidth;
	int n = Settings::get().numFlights;


	emit settingsChanged();
}

void SettingsDialog::closeEvent(QCloseEvent* event)
{
	int a = 1;

}

void SettingsDialog::showEvent(QShowEvent* event)
{
	ui.flightsNumber->setValue(Settings::get().numFlights);
	ui.modelWidth->setValue(Settings::get().modelWidth);
	ui.modelHeight->setValue(Settings::get().modelHeight);
}

