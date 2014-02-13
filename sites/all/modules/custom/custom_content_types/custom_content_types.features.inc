<?php
/**
 * @file
 * custom_content_types.features.inc
 */

/**
 * Implements hook_views_api().
 */
function custom_content_types_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function custom_content_types_node_info() {
  $items = array(
    'landing_page' => array(
      'name' => t('Landing page'),
      'base' => 'node_content',
      'description' => t('Use <em>landing pages</em> for your main section pages.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'section_page' => array(
      'name' => t('Section page'),
      'base' => 'node_content',
      'description' => t('Use <em>section pages</em> attached to a landing page.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
