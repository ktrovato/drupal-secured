Read Me (README.txt)
---------------------------------------------------------

 *
 * Implementation of http:BL for Drupal. It provides IP-based
 * blacklisting through http:BL and allows linking to a honeypot.
 *
 * @author Mark Janssen (praseodym)
 * @link http://drupal.org/project/httpbl
 * @link http://httpbl.org/
 *
 **
 * Version 7.x
 *
 * Drupal 7 port + additional settings and Views support.
 * Contact: Bryan Lewellen (bryrock) (http://drupal.org/user/346823)
 *
 * Additional code support by David Norman (deekayen)
 *

Key Features:

 * Project Honeypot Blacklist lookups for visitor IPs
 * Blocking of current and future requests from blacklisted IPs
 * Local database caching, decreases DNS lookups on repeated visit attempts
 * Honeypot link placement on ban page and optionally in footer
 * Session and cached Whitelisting
 * Greylisting: Intermediate blocking of medium-threat IPs, grants user access after passing a simple test
 * Optional Comment checking only (re-writes comments from bad IPs and bans from future visits)
 * Optional 3 levels of logging (Error only, Positive Lookups or Verbose)
 * Length of time cached visits are held are determined by configurable settings.
 * Two Default Views included (see blocked and whitelisted IPs with links to their Honeypot profiles)
 * Basic statistics on the number of blocked visits
 * Can be used for Honeypot link placement only (no blocking)

Http:BL stops reputed email harvesters, dictionary attackers, comment spammers and other
disreputable, nuisance traffic from visiting your site by using the centralized DNS blacklist at
Project Honeypot (http://www.projecthoneypot.org/).

Http:BL requires a free Project Honey Pot membership. Http:BL provides fast and efficient blacklist lookups and blocks first-time malicious visitors.  IPs of previously blocked visitors are stored locally and kept from returning for admin configurable periods of time, without additional lookups being required during that time.  Blacklisted IPs are added to Drupal's "blocked_ips" table.  Likewise, non-threatening IPs are also stored locally for configurable periods of time, during which additional DNS lookups are not required for their return visits.

Http:BL includes optional logging on three levels: Off - (errors only), Positive Lookups (when IP's are grey or blacklisted), and Verbose (useful for testing and gaining trust).

Http:BL also includes two default Views pages, one for blocked IPs and one for cleared IPs.  You can use these instead of logging.  IPs are listed along with their status, and the IP links directly to its profile in Project Honeypot, so you can quickly see where it came from and why it was blocked.  Requires the Views module and any of its dependencies.

Http:BL can also be configured to lookup IPs only for commenters when comments are placed.  If commenter is found in blacklist lookup, comment is re-written (queuing for moderation is also available, depending on Drupal's core comment permissions). In the event the commenter is actually human, error messages and the re-written comment will alert and inform them as to why their comment was blocked.

Http:BL can also place hidden Honeypot links in page footers.  These make it possible for you to participate and "give back" to Project Honeypot, by catching newer nuisance IPs that may not yet be ranked as threats in Project Honeypot profiles.  They find these links irresistible,  and "clicking" these links reports them and their ill-intent.  

  
 *
 ** Some Notes About Testing **
 *
 
Because this module works so quietly in the background, it may need some help to gain your trust.  That's why I included the 3 levels of logging and the Views pages, to help you see the results of what it does.  Otherwise, unless you have direct access to your database tables, it's difficult to tell if it's really blocking suspicious visitors or not.

Typically, if your site gets any regular traffic at all, you should start seeing grey-listed IPs being blocked within 24-48 hours (blacklisting is less common, but even low traffic sites will see them eventually).  Both kinds will show up in the "Honeypot Blocked Hosts" admin report.  Cleared IPs will appear immediately in the "Honeypot Cleared" admin report.

If you're really impatient (like me), you can turn on the Verbose logging and watch Http:BL in action.  This will show you how each IP is getting looked up, and what happens depending on the results (most IPs are harmless and cached as friendly).  It will always query its own cache first, then only do the DNS lookup if it doesn't find anything in cache.  If it finds no profile it will treat the IP as safe.  If it does find a profile, but one that is not threatening, it will also treat those as safe.  Otherwise, if it doesn't like what it finds it will grey or black-list that IP.  Blacklisted IPs are stored in Http:BLs cache and also added to Drupal's core list of Blocked IP addresses (if you chose that option).

Keep in mind though that verbose logging is very verbose and resource expensive. You don't want to leave that on, especially if you receive heavy traffic.  If you do receive heavy traffic, you should start seeing grey and blacklisted IPs in the admin report in no time at all.

If you're really brave and want to "force" a bad IP hit, well, that's a tricky one to test, unless you know an easy way to spoof visits from evil IP addresses.  However, I have left two (bad) IPs commented in the code, for testing purposes.  You can un-comment one of those (and comment out the actual line that retrieves your real IP, and force a bad hit.  This is especially useful if you want to see what happens when one of these evil IPs tries to leave a comment.

If you want to simulate what happens during the grey-listing challenge, the best way to do that is to find your own IP in the httpbl table (with a status of 0) and tweak that to be a 2.  Then try to access your site.  You'll see the simple challenge form.  If you pass your status will go back to 0.  If you fail it will turn to 1 (blacklisted) and also add you to the blocked_ips table.  IPs in that table are banned before even httpBL has a chance to review them.

BUT BE CAREFUL!  Use at least two browsers (two machines is better) and always keep a window open to your database so you can un-blacklist yourself, otherwise you can get yourself banned and locked out from your own web site, because banning really works!  Don't say I didn't warn you.

When you're done testing, put the code back the way you found it and dial back the logging at least to the second level (positive hits only)

--
One other thing:  I've found sometimes that Project Honeypot may be down for brief periods (for maintenance or other reasons that they don't share) and not returning positive hits on IPs I know are bad.  This has burned me a couple of times, making me think I broke something.  But I resisted the urge to panic or make unnecessary changes, and tried again later and got the expected results.

However, this brings up an interesting point that's relevant to considering how long you choose to cache white-listed visitors.  It may be tempting to cache them for a long time so that they don't have to be re-checked as often, but it's probably best to keep them cached for shorter time periods, on the off-chance that some of them are actually bad IPs that slipped through while Project Honeypot not reporting them.

Bryrock

 