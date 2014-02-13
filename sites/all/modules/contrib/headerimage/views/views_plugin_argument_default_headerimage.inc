<?php

/**
 * @file
 * Contains the Header image argument default plugin.
 */

/**
 * This class provides an argument default plugin that returns the header image
 * for the page it is displayed on.
 */
class views_plugin_argument_default_headerimage extends views_plugin_argument_default {
  function option_definition() {
    $options = parent::option_definition();
    $options['block'] = array('default' => NULL);

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['block'] = array(
      '#type' => 'select',
      '#title' => t('The Header Image Block'),
      '#options' => headerimage_get_blocks(),
      '#default_value' => $this->options['block'],
      '#description' => t('Choose the Header Image Block to get the Node ID (nid) from'),
    );
  }

  function get_argument() {
    return headerimage_select_node($this->options['block']);
  }
}
