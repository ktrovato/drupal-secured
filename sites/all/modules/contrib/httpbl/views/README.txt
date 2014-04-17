Read Me (README.txt)
---------------------------------------------------------

 * Version 7.x-dev
 * Contact: Bryan Lewellen (bryrock) (http://drupal.org/user/346823)
 *
 *

  httpbl.views.inc 			- provides exposure of httpbl table to Views
  httpbl.views_default.inc	- provides a simple default view/report of IPs blocked via Project Honeypot

------------
INSTALLATION
------------
	These views will be installed when the module is installed.

Accessing these default Views reports
--------------------------------------------
Reports are available in admin/reports
and are accessible to anyone with proper permissions.

There are two reports:
	Honeypot Blocked Hosts
	Honeypot Cleared

In order to see these reports,
some level of caching must be set in admin >> config >> people >> httpbl.

If "Http:BL cache and Drupal blocked_ips table" is set, then items shown
with a status of 1 should also be found in the blocked_ips table, to be
removed in both tables when the expiry date has passed.

Items with a status of 2 are found only in the database cache for httpbl, and
this also would apply to status 1 items if caching is set only to
"Http:BL cache."

Items with a status of 0 (safe IPs) are in Honeypot Cleared.

The IP addresses in the report include links to ProjectHoneyPot.org that
will allow you to see their current information profile for that IP.


KNOWN ISSUES
------------
