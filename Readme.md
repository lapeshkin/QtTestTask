<!DOCTYPE html>
<html xmlns="http://www.w3.org/1999/xhtml" lang="" xml:lang="">
<head>
  <meta charset="utf-8" />
  <meta name="generator" content="pandoc" />
  <meta name="viewport" content="width=device-width, initial-scale=1.0, user-scalable=yes" />
</head>
<body>
<p><strong>QtTestTask </strong>project is a test task for a position of
R&amp;D Engineer</p>
<p>The goal of the project is to create an application that displays
random airplane flights. Information about flight within the visible
area should be displayed in a side panel on the left.</p>
<p>The <strong>Flight </strong>class contains information about the
flight, including coordinates, direction, speed, and airplane color. It
recalculates its coordinates and redraws itself on the main scene and a
small map when a timer event occurs.</p>
<p>The <strong>FlightManager </strong>class holds a list of flights and,
upon a timer event, give a command to all the flights to recalculate
their coordinates and update themselves in the models. After
recalculating the coordinates, <strong>FlightManager </strong>creates a
list of flights that are in the visible area. If this list has changed
compared to the previous state, it isues signal to change the list
containing flight information on the side panel.</p>
<p>Information on the side panel is displayed using the
<strong>Model</strong>/<strong>View </strong>pattern. The
<strong>FlightsListModel </strong>class is used as the model, which uses
a list of <strong>Flight </strong>objects as its data source. The
<strong>QListView </strong>class is used as the view. To display
extended information about a flight, the <strong>FlightInfoDelegate
</strong>class is used. This class helps display rows in HTML
format.</p>
<p>The central class of the project, <strong>QtTestTask</strong>, is
inherited from <strong>QMainView </strong>and includes fields containing
objects of the <strong>FlightManager</strong>,
<strong>FlightsListModel</strong>, and <strong>FlightsView
</strong>classes. Upon launching the application, it initializes the
<strong>FlightManager </strong>object and starts a timer to begin
displaying airplane movements.</p>
</body>
</html>
