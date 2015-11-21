<?php

/**
 * @file
 * Default Views for Honeyblock for Drupal. Provides easy monitoring
 * of IPs greylisted or blacklisted through Honeyblock and linking to ProjectHoneypot.org
 * to review why these IPs have been blocked.
 *
 * @author Bryan Lewellen (bryrock)
 * @link http://drupal.org/project/httpbl
 * @link http://httpbl.org/
 *
 */

/**
 *
 * Version 7.x-dev
 * Contact: Bryan Lewellen (bryrock) (http://drupal.org/user/346823)
 *
 * Feel free to improve this module, but please contact the authors with any
 * changes you make so they can be implemented into the 'official' version.
 *
 */

/**
 * Default Blocked Hosts Report (View)
 */
 
function httpbl_views_default_views() {
  // Thanks to Lullabot's clear and concise API docs at
  // http://api.lullabot.com/group/views_hooks
  //
  // Begin copy and paste of output from the Export tab of a view.
$view = new view();
$view->name = 'httpbl_blocked_hosts';
$view->description = 'Blocked Visitors via Honeypot.org.  This requires caching to be enabled at admin >> config >> people >> httpbl.';
$view->tag = 'default';
$view->base_table = 'httpbl';
$view->human_name = 'Honeypot Blocked Hosts';
$view->core = 0;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Defaults */
$handler = $view->new_display('default', 'Defaults', 'default');
$handler->display->display_options['title'] = 'Honeypot Blocked Hosts';
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['access']['type'] = 'perm';
$handler->display->display_options['access']['perm'] = 'access site reports';
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['query']['options']['query_comment'] = FALSE;
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'full';
$handler->display->display_options['pager']['options']['items_per_page'] = '25';
$handler->display->display_options['pager']['options']['offset'] = '0';
$handler->display->display_options['pager']['options']['id'] = '0';
$handler->display->display_options['style_plugin'] = 'table';
$handler->display->display_options['style_options']['columns'] = array(
  'counter' => 'counter',
  'hostname' => 'hostname',
  'status' => 'status',
  'expire' => 'expire',
);
$handler->display->display_options['style_options']['default'] = '-1';
$handler->display->display_options['style_options']['info'] = array(
  'counter' => array(
    'align' => '',
    'separator' => '',
  ),
  'hostname' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
  ),
  'status' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
  ),
  'expire' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
  ),
);
/* Field: HttpBL: Hostname */
$handler->display->display_options['fields']['hostname']['id'] = 'hostname';
$handler->display->display_options['fields']['hostname']['table'] = 'httpbl';
$handler->display->display_options['fields']['hostname']['field'] = 'hostname';
$handler->display->display_options['fields']['hostname']['alter']['make_link'] = TRUE;
$handler->display->display_options['fields']['hostname']['alter']['path'] = 'http://www.projecthoneypot.org/search_ip.php?ip=[hostname]';
$handler->display->display_options['fields']['hostname']['hide_alter_empty'] = FALSE;
/* Field: HttpBL: Status */
$handler->display->display_options['fields']['status']['id'] = 'status';
$handler->display->display_options['fields']['status']['table'] = 'httpbl';
$handler->display->display_options['fields']['status']['field'] = 'status';
/* Field: HttpBL: Expires */
$handler->display->display_options['fields']['expire']['id'] = 'expire';
$handler->display->display_options['fields']['expire']['table'] = 'httpbl';
$handler->display->display_options['fields']['expire']['field'] = 'expire';
$handler->display->display_options['fields']['expire']['hide_alter_empty'] = FALSE;
$handler->display->display_options['fields']['expire']['date_format'] = 'long';
/* Sort criterion: HttpBL: Expires */
$handler->display->display_options['sorts']['expire']['id'] = 'expire';
$handler->display->display_options['sorts']['expire']['table'] = 'httpbl';
$handler->display->display_options['sorts']['expire']['field'] = 'expire';
/* Filter criterion: HttpBL: Status */
$handler->display->display_options['filters']['status']['id'] = 'status';
$handler->display->display_options['filters']['status']['table'] = 'httpbl';
$handler->display->display_options['filters']['status']['field'] = 'status';
$handler->display->display_options['filters']['status']['operator'] = '>';
$handler->display->display_options['filters']['status']['value']['value'] = '0';
$handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;

/* Display: Page */
$handler = $view->new_display('page', 'Page', 'page_1');
$handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
$handler->display->display_options['defaults']['header'] = FALSE;
/* Header: Global: Text area */
$handler->display->display_options['header']['text']['id'] = 'text';
$handler->display->display_options['header']['text']['table'] = 'views';
$handler->display->display_options['header']['text']['field'] = 'area';
$handler->display->display_options['header']['text']['empty'] = TRUE;
$handler->display->display_options['header']['text']['content'] = 'IP addresses blocked from access based on suspicious activity per Project Honeypot.
		
		Status of 1 = Blacklisted IPs (also inserted as banned hosts in Blocked_IPs table)
		Status of 2 = Greylisted IPs
		<hr / >';
$handler->display->display_options['header']['text']['format'] = 'filtered_html';
$handler->display->display_options['defaults']['empty'] = FALSE;
/* No results behavior: Global: Text area */
$handler->display->display_options['empty']['text']['id'] = 'text';
$handler->display->display_options['empty']['text']['table'] = 'views';
$handler->display->display_options['empty']['text']['field'] = 'area';
$handler->display->display_options['empty']['text']['content'] = 'No blocked IPs at this time.';
$handler->display->display_options['empty']['text']['format'] = 'filtered_html';
$handler->display->display_options['path'] = 'admin/reports/blocked_hosts';
$handler->display->display_options['menu']['type'] = 'normal';
$handler->display->display_options['menu']['title'] = 'Honeypot Blocked Hosts';
$handler->display->display_options['menu']['description'] = 'Visitors blocked via Project Honeypot';
$handler->display->display_options['menu']['weight'] = '0';
$handler->display->display_options['menu']['name'] = 'management';  // End copy and paste of Export tab output.

  // Add view to list of views to provide.
  $views[$view->name] = $view;

  // ...Repeat all of the above for each view the module should provide.

  // Begin copy and paste of output from the Export tab of a view.
$view = new view();
$view->name = 'httpbl_cleared_hosts';
$view->description = 'Cleared Visitors via Honeypot.org.  This requires caching to be enabled at admin >> config >> people >> httpbl.';
$view->tag = 'default';
$view->base_table = 'httpbl';
$view->human_name = 'Honeypot Cleared Hosts';
$view->core = 0;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Defaults */
$handler = $view->new_display('default', 'Defaults', 'default');
$handler->display->display_options['title'] = 'Honeypot Cleared Hosts';
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['access']['type'] = 'perm';
$handler->display->display_options['access']['perm'] = 'access site reports';
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['query']['options']['query_comment'] = FALSE;
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'full';
$handler->display->display_options['pager']['options']['items_per_page'] = '25';
$handler->display->display_options['pager']['options']['offset'] = '0';
$handler->display->display_options['pager']['options']['id'] = '0';
$handler->display->display_options['style_plugin'] = 'table';
$handler->display->display_options['style_options']['columns'] = array(
  'nothing' => 'nothing',
  'hostname' => 'hostname',
  'status' => 'status',
  'expire' => 'expire',
);
$handler->display->display_options['style_options']['default'] = '-1';
$handler->display->display_options['style_options']['info'] = array(
  'nothing' => array(
    'align' => '',
    'separator' => '',
  ),
  'hostname' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
  ),
  'status' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
  ),
  'expire' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
  ),
);
/* No results behavior: Global: Text area */
$handler->display->display_options['empty']['text']['id'] = 'text';
$handler->display->display_options['empty']['text']['table'] = 'views';
$handler->display->display_options['empty']['text']['field'] = 'area';
$handler->display->display_options['empty']['text']['content'] = 'No cleared IPs at this time.';
$handler->display->display_options['empty']['text']['format'] = 'filtered_html';
/* Field: HttpBL: Hostname */
$handler->display->display_options['fields']['hostname']['id'] = 'hostname';
$handler->display->display_options['fields']['hostname']['table'] = 'httpbl';
$handler->display->display_options['fields']['hostname']['field'] = 'hostname';
$handler->display->display_options['fields']['hostname']['alter']['make_link'] = TRUE;
$handler->display->display_options['fields']['hostname']['alter']['path'] = 'http://www.projecthoneypot.org/search_ip.php?ip=[hostname]';
$handler->display->display_options['fields']['hostname']['hide_alter_empty'] = FALSE;
/* Field: HttpBL: Status */
$handler->display->display_options['fields']['status']['id'] = 'status';
$handler->display->display_options['fields']['status']['table'] = 'httpbl';
$handler->display->display_options['fields']['status']['field'] = 'status';
$handler->display->display_options['fields']['status']['hide_alter_empty'] = FALSE;
/* Field: HttpBL: Expires */
$handler->display->display_options['fields']['expire']['id'] = 'expire';
$handler->display->display_options['fields']['expire']['table'] = 'httpbl';
$handler->display->display_options['fields']['expire']['field'] = 'expire';
/* Sort criterion: HttpBL: Expires */
$handler->display->display_options['sorts']['expire']['id'] = 'expire';
$handler->display->display_options['sorts']['expire']['table'] = 'httpbl';
$handler->display->display_options['sorts']['expire']['field'] = 'expire';
/* Filter criterion: HttpBL: Status */
$handler->display->display_options['filters']['status']['id'] = 'status';
$handler->display->display_options['filters']['status']['table'] = 'httpbl';
$handler->display->display_options['filters']['status']['field'] = 'status';
$handler->display->display_options['filters']['status']['operator'] = '<=';
$handler->display->display_options['filters']['status']['value']['value'] = '0';
$handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;

/* Display: Page */
$handler = $view->new_display('page', 'Page', 'page_1');
$handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
$handler->display->display_options['defaults']['header'] = FALSE;
/* Header: Global: Text area */
$handler->display->display_options['header']['text']['id'] = 'text';
$handler->display->display_options['header']['text']['table'] = 'views';
$handler->display->display_options['header']['text']['field'] = 'area';
$handler->display->display_options['header']['text']['empty'] = TRUE;
$handler->display->display_options['header']['text']['content'] = 'IP addresses checked and cleared from suspicious activity per Project Honeypot.
		
		Status of 0 = No known suspicious activity
		<hr / >';
$handler->display->display_options['header']['text']['format'] = 'filtered_html';
$handler->display->display_options['path'] = 'admin/reports/cleared_hosts';
$handler->display->display_options['menu']['type'] = 'normal';
$handler->display->display_options['menu']['title'] = 'Honeypot Cleared';
$handler->display->display_options['menu']['description'] = 'Visitors cleared via Project Honeypot';
$handler->display->display_options['menu']['weight'] = '0';
$handler->display->display_options['menu']['name'] = 'management';
  // End copy and paste of Export tab output.

  // Add view to list of views to provide.
  $views[$view->name] = $view;


  // At the end, return array of default views.
  return $views;
}
