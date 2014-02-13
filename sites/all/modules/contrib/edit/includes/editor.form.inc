<?php

/**
 * @file
 * Defines the "form" in-place editor.
 *
 * @see Drupal 8's \Drupal\edit\Plugin\InPlaceEditor\FormEditor.
 */

function _edit_editor_form_is_compatible(array $instance, array $items) {
  return TRUE;
}

function _edit_editor_form_metadata(array $instance, array $items) {
  return array();
}

function _edit_editor_form_attachments() {
  return array(
    'library' => array(
      array('edit', 'edit.inPlaceEditor.form'),
    ),
  );
}
