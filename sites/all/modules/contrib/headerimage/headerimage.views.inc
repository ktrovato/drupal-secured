<?php

/**
 * @file
 * This file contains the views hooks for headerimage.
 */

function headerimage_views_plugins() {
  return array(
    'argument default' => array(
      'headerimage' => array(
        'title' => 'Header image node',
        'handler' => 'views_plugin_argument_default_headerimage',
      ),
    ),
  );
}

