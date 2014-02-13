<?php

/**
 * @file
 * Admin database page callbacks for the systeminfo module.
 */


/**
 * Menu callback; displays the database system page.
 */
function systeminfo_admin_database() {

  $output = '';


  return $output;
}


/**
 * Menu callback; configures the display.
 */
function systeminfo_admin_database_settings($form, &$form_state) {


  // Buttons
  $form['actions'] = array(
    '#type' => 'actions',
  );
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );
  $form['actions']['cancel'] = array(
    '#markup' => l(t('Cancel'), 'admin/reports/systeminfo/database'),
  );

  $form['#submit'][] = 'system_settings_form_submit';
  if (!isset($form['#theme'])) {
    $form['#theme'] = 'system_settings_form';
  }

  if (!empty($_POST) && form_get_errors()) {
    drupal_set_message(t('The settings have not been saved because of the errors.'), 'error');
  }

  return $form;
}
