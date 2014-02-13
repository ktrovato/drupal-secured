<?php

/**
 * @file
 * Hooks provided by the Edit module.
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Declare editors that can be used with CreateJS.
 *
 * @return array
 */
function hook_edit_editor_info() {
  $editors['form'] = array(
    'widget' => 'drupalFormWidget',
    'compatibility check callback' => '_edit_editor_form_is_compatible',
    'metadata callback' => '_edit_editor_form_metadata',
    'attachments callback' => '_edit_editor_form_attachments',
    'file' => 'includes/editor.form.inc',
    'file path' => drupal_get_path('module', 'edit'),
  );

  return $editors;
}

/**
 * Allow modules to alter in-place editor plugin metadata.
 *
 * @param array &$editors
 *   An array of metadata on existing in-place editors.
 */
function hook_edit_editor_info_alter(&$editors) {

}

/**
 * Alter a field metadata that is used by the front-end.
 *
 * @param $metadata
 *   Information used by the front-end to make the field in-place editable.
 * @param array $context
 *   An array with the following key-value pairs:
 *     - 'entity_type': the entity type
 *     - 'entity': the entity object
 *     - 'field': the field instance as returned by field_info_instance()
 *     - 'items': the items of this field on this entity
 */
function hook_edit_editor_metadata_alter(&$metadata, $context) {

}

/**
 * Alter the list of attached files for the editor depending on the fields conf.
 *
 * @param $attachments
 *   #attached array returned by the editor attachments callback.
 * @param $editor_id
 *   ID of the currently used editor.
 */
function hook_edit_editor_attachments_alter(&$attachments, $editor_id) {
  if ($editor_id === 'ckeditor') {
    $attachments['library'][] = array('mymodule', 'myjslibrary');
  }
}

/**
 * Returns a renderable array for the value of a single field in an entity.
 *
 * To integrate with in-place field editing when a non-standard render pipeline
 * is used (field_view_field() is not sufficient to render back the field
 * following in-place editing in the exact way it was displayed originally),
 * implement this hook.
 *
 * Edit module integrates with HTML elements with data-edit-field-id attributes.
 * For example:
 *   data-edit-field-id="node/1/<field-name>/und/<module-name>-<custom-id>"
 * After the editing is complete, this hook is invoked on the module with
 * the custom render pipeline identifier (last part of data-edit-field-id) to
 * re-render the field. Use the same logic used when rendering the field for
 * the original display.
 *
 * The implementation should take care of invoking the prepare_view steps. It
 * should also respect field access permissions.
 *
 * @param string $entity_type
 *   The type of the entity containing the field to display.
 * @param stdClass $entity
 *   The entity containing the field to display.
 * @param string $field_name
 *   The name of the field to display.
 * @param string $view_mode_id
 *   View mode ID for the custom render pipeline this field view was destined
 *   for. This is not a regular view mode ID for the Entity/Field API render
 *   pipeline and is provided by the renderer module instead. An example could
 *   be Views' render pipeline. In the example of Views, the view mode ID would
 *   probably contain the View's ID, display and the row index. Views would
 *   know the internal structure of this ID. The only structure imposed on this
 *   ID is that it contains dash separated values and the first value is the
 *   module name. Only that module's hook implementation will be invoked. Eg.
 *   'views-...-...'.
 * @param string $langcode
 *   (Optional) The language code the field values are to be shown in.
 *
 * @return
 *   A renderable array for the field value.
 *
 * @see field_view_field()
 */
function hook_edit_render_field($entity_type, $entity, $field_name, $view_mode_id, $langcode) {
  return array(
    '#prefix' => '<div class="example-markup">',
    'field' => field_view_field($entity_type, $entity, $field_name, $view_mode_id, $langcode),
    '#suffix' => '</div>',
  );
}

/**
 * @} End of "addtogroup hooks".
 */
