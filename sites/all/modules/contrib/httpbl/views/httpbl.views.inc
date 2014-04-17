<?php

// httpbl.views.inc,v 1.0 2011/06/27 11:34:00 bryrock Exp 

/**
 * @file
 * Views exposure of http:BL for Drupal. Provides easy monitoring
 * of IPs greylisted or blacklisted through http:BL and linking to honeypot
 * to review why these IPs have been blocked.
 *
 * For this includes only
 * @author Bryan Lewellen (bryrock)
 * @link http://drupal.org/project/httpbl
 * @link http://httpbl.org/
 *
 * For http:BL for Drupal module
 * @author Mark Janssen (praseodym)
 * @link http://drupal.org/project/httpbl
 * @link http://httpbl.org/
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

function httpbl_views_data() {
  // Thanks to Lullabot's clear and concise API docs at
  // http://api.lullabot.com/group/views_hooks
  //
  // The 'group' index will be used as a prefix in the UI for any of this
  // table's fields, sort criteria, etc. so it's easy to tell where they came
  // from.
  $data['httpbl']['table']['group'] = t('HttpBL');

  // Define this as a base table.
  $data['httpbl']['table']['base'] = array(
	  'field' => 'hostname',
      'title' => t('HttpBL'),
      'help' => t("Cache table of IP addresses successfully blocked by HttpBL (and ProjectHoneypot.org)."),
      'weight' => -10,
  );
  
  // Next, describe each of the individual fields in this table to Views. For
  // each field, you may define what field, sort, argument, and/or filter
  // handlers it supports. This will determine where in the Views interface you
  // may use the field.

  // Hostname field.
  $data['httpbl']['hostname'] = array(
    'title' => t('Hostname'),
    'help' => t('Host IP in plain text.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  // Status field.
  $data['httpbl']['status'] = array(
    'title' => t('Status'),
    'help' => t('Status in a numeric field.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
     ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // Expires timestamp field.
  $data['httpbl']['expire'] = array(
    'title' => t('Expires'),
    'help' => t('Expiration date for this item in a timestamp field.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );

  return $data;
}

/**
 * Implementation of hook_views_handlers().
 */
function httpbl_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'httpbl') . '/includes/views/handlers',
    ),
    'handlers' => array(

      // argument handlers
      'httpbl_handler_argument' => array(
        'parent' => 'views_handler_argument',
      ),
      'httpbl_handler_argument_string' => array(
        'parent' => 'views_handler_argument_string',
      ),
      'httpbl_handler_argument_numeric' => array(
        'parent' => 'views_handler_argument_numeric',
      ),
      'httpbl_handler_argument_reference' => array(
        'parent' => 'httpbl_handler_argument_numeric',
      ),
      'httpbl_handler_argument_many_to_one' => array(
        'parent' => 'views_handler_argument_many_to_one',
      ),

      // field handlers
      'httpbl_handler_field' => array(
        'parent' => 'views_handler_field_node',
      ),
      'httpbl_handler_field_multiple' => array(
        'parent' => 'httpbl_handler_field',
      ),

      // filter handlers
      'httpbl_handler_filter_string' => array(
        'parent' => 'views_handler_filter_string',
      ),
      'httpbl_handler_filter_numeric' => array(
        'parent' => 'views_handler_filter_numeric',
      ),
      'httpbl_handler_filter_float' => array(
        'parent' => 'views_handler_filter_float',
      ),
      'httpbl_handler_filter_many_to_one' => array(
        'parent' => 'views_handler_filter_many_to_one',
      ),

      // relationship handlers
      'httpbl_handler_relationship' => array(
        'parent' => 'views_handler_relationship',
      ),

      // sort handlers
      'httpbl_handler_sort' => array(
        'parent' => 'views_handler_sort',
      ),
    ),
  );
}

