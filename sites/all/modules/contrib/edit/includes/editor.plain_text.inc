<?php

/**
 * @file
 * Defines the "plain text" in-place editor.
 *
 * @see Drupal 8's \Drupal\edit\Plugin\InPlaceEditor\PlainTextEditor.
 */

function _edit_editor_plain_text_is_compatible(array $instance, array $items) {
  $field = field_info_field($instance['field_name']);

  // This editor is incompatible with multivalued fields.
  $cardinality_allows = $field['cardinality'] == 1;
  // This editor is incompatible with processed ("rich") text fields.
  $no_text_processing = empty($instance['settings']['text_processing']);

  return $cardinality_allows && $no_text_processing;
}

function _edit_editor_plain_text_metadata(array $instance, array $items) {
  return array();
}

function _edit_editor_plain_text_attachments() {
  return array(
    'library' => array(
      array('edit', 'edit.inPlaceEditor.plainText'),
    ),
  );
}
