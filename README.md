drupal-secured
==============
Drupal Secured will NOT guarantee that your site does not get hacked. Drupal Secured provides a hardened, 508 compliant, old browser support for IE8 and responsive theme out of the box. It is up to you to maintain security and other provided functionality during the development, deployment and maintenance of your site. Regular audits are required to maintain the features provided. Drupal Secured give you a solid starting point for sites requiring security and 508 compliance.

This distribution is actively maintained by Peerless design, inc. New features and distributions for specific markets will be released as they become available. If you need a distribution for you organization, please feel free to reach out to us we will be happy to consult on any Drupal and security related projects.

Planned releases for Higher Ed will be available soon. For a full set of features and configurations see the readme.txt file. Install is easy and themes are just provided as a starting point and can be replaced or customized. This distribution uses Drupal and industry best practices to ensure the integrity of the project.

Always looking for co-maintainers with a passion for Drupal and security.

Post Install

Add the following to the settings.php. Make any necessary changes to path to suit the environmet.

$conf['cache_backends'] = array('sites/all/modules/filecache/filecache.inc');
$conf['cache_default_class'] = 'DrupalFileCache';
