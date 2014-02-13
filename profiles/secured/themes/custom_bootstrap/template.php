<?php

/**
 * @file template.php
 */
/**
* Implements theme_html_head_alter().
* Removes the Generator tag from the head for Drupal 7
*/
function custom_bootstrap_html_head_alter(&$head_elements) {
  unset($head_elements['system_meta_generator']);
}
