#pragma once

class Settings
{
public:
	static Settings& get()
	{
		static Settings instance;
		return instance;
	}

	int		numFlights;
	int		modelWidth;
	int		modelHeight;
	int		sidePaneWidth;
	int		smallMapPlaneSize;
	QString	planeImageRes;

	bool	showDebugInfo;

private:
	Settings()
	{
		numFlights		= 10;
		modelWidth		= 1000;
		modelHeight		= 1000;
		sidePaneWidth	= 300;
		smallMapPlaneSize = 6;
		planeImageRes = ":/QtTestTask/Plane.png";
#ifdef _DEBUG
		showDebugInfo = true;
#else
		showDebugInfo = false;
#endif
	};
};
