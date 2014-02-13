<?php

/**
 * @file
 * Admin Drupal page callbacks for the systeminfo module.
 */


/**
 * Menu callback; displays the Drupal page.
 */
function systeminfo_admin_drupal() {

  drupal_add_css(drupal_get_path('module', 'systeminfo') .'/styles/systeminfo.css');

  $toc = array(
    '<a href="#nodes">'. t('Content') .'</a>',
    '<a href="#users">'. t('Users') .'</a>',
    '<a href="#roles">'. t('Roles') .'</a>',
    '<a href="#modules">'. t('Modules') .'</a>',
    '<a href="#themes">'. t('Themes') .'</a>',
  );

  $output = '<h3 id="toc">' . t('Table of contents') . '</h3>';
  $output .= theme('item_list', array('items' => $toc, 'type' => 'ul', 'attributes' => array('class' => array('systeminfo', 'systeminfo-toc'))));
  $output .= '<h3 id="nodes">' . t('Content') . '</h3>';
  $output .= _systeminfo_admin_drupal_content();
  $output .= '<h3 id="users">' . t('Users') . '</h3>';
  $output .= _systeminfo_admin_drupal_users();
  $output .= '<h3 id="roles">' . t('Roles') . '</h3>';
  $output .= _systeminfo_admin_drupal_roles();
  $output .= '<h3 id="modules">' . t('Modules') . '</h3>';
  $output .= _systeminfo_admin_drupal_modules();
  $output .= '<h3 id="themes">' . t('Themes') . '</h3>';
  $output .= _systeminfo_admin_drupal_themes();

  return $output;
}

function _systeminfo_admin_drupal_content() {

  $header = array();
  $header[] = t('Group');
  $header[] = t('Nodes');

  $node_types_active = array();
  $node_types_deleted = array();
  $result = db_query('SELECT n.type, nt.name, COUNT(n.nid) AS count FROM {node} n LEFT JOIN {node_type} nt ON n.type = nt.type GROUP BY n.type');
  foreach ($result as $record) {
    if ($record->name) {
      $node_types_active[$record->name] = $record;
    }
    else {
      $node_types_deleted[$record->type] = $record;
    }
  }
  ksort($node_types_active);
  ksort($node_types_deleted);

  $rows = array();
  $rows[] = array(t('Total'), db_query('SELECT COUNT(nid) FROM {node}')->fetchField());
  if ($node_types_active) {
    $rows[] = array(array('data' => t('Active content types'), 'class' => 'title1', 'colspan' => '2'));

    foreach ($node_types_active as $node_type) {
      $rows[] = array(array('data' => check_plain($node_type->name), 'class' => 'text1'), $node_type->count);
      $rows[] = array(array('data' => t('Published'), 'class' => 'text2'), db_query('SELECT COUNT(nid) FROM {node} WHERE type = :type AND status = 1', array(':type' => $node_type->type))->fetchField());
      $rows[] = array(array('data' => t('Promoted to front page'), 'class' => 'text2'), db_query('SELECT COUNT(nid) FROM {node} WHERE type = :type AND promote = 1', array(':type' => $node_type->type))->fetchField());
      $rows[] = array(array('data' => t('Sticky at top of lists'), 'class' => 'text2'), db_query('SELECT COUNT(nid) FROM {node} WHERE type = :type AND sticky = 1', array(':type' => $node_type->type))->fetchField());
    }
  }
  if ($node_types_deleted) {
    $rows[] = array(array('data' => t('Deleted content types'), 'class' => 'title1', 'colspan' => '2'));

    foreach ($node_types_deleted as $node_type) {
      $rows[] = array(array('data' => check_plain($node_type->type), 'class' => 'text1'), $node_type->count);
      $rows[] = array(array('data' => t('Published'), 'class' => 'text2'), db_query('SELECT COUNT(nid) FROM {node} WHERE type = :type AND status = 1', array(':type' => $node_type->type))->fetchField());
      $rows[] = array(array('data' => t('Promoted to front page'), 'class' => 'text2'), db_query('SELECT COUNT(nid) FROM {node} WHERE type = :type AND promote = 1', array(':type' => $node_type->type))->fetchField());
      $rows[] = array(array('data' => t('Sticky at top of lists'), 'class' => 'text2'), db_query('SELECT COUNT(nid) FROM {node} WHERE type = :type AND sticky = 1', array(':type' => $node_type->type))->fetchField());
    }
  }

  return theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('class' => array('systeminfo', 'systeminfo-width50'))));
}




function _systeminfo_admin_drupal_users() {

  $header = array();
  $header[] = t('Group');
  $header[] = t('Accounts');

  $rows = array();
  $rows[] = array(t('Total'), db_query('SELECT COUNT(uid) FROM {users} WHERE uid <> 0')->fetchField());
  $rows[] = array(array('data' => t('Status'), 'class' => 'title1', 'colspan' => '2'));
  $rows[] = array(array('data' => t('Active'), 'class' => 'text1'), db_query('SELECT COUNT(uid) FROM {users} WHERE uid <> 0 AND status = 1')->fetchField());
  $rows[] = array(array('data' => t('Already logged in'), 'class' => 'text2'), db_query('SELECT COUNT(uid) FROM {users} WHERE uid <> 0 AND status = 1 AND login <> 0')->fetchField());
  $rows[] = array(array('data' => t('Not yet logged in'), 'class' => 'text2'), db_query('SELECT COUNT(uid) FROM {users} WHERE uid <> 0 AND status = 1 AND login = 0')->fetchField());
  $rows[] = array(array('data' => t('Blocked'), 'class' => 'text1'), db_query('SELECT COUNT(uid) FROM {users} WHERE uid <> 0 AND status = 0')->fetchField());
  $rows[] = array(array('data' => t('Already logged in'), 'class' => 'text2'), db_query('SELECT COUNT(uid) FROM {users} WHERE uid <> 0 AND status = 0 AND login <> 0')->fetchField());
  $rows[] = array(array('data' => t('Not yet logged in'), 'class' => 'text2'), db_query('SELECT COUNT(uid) FROM {users} WHERE uid <> 0 AND status = 0 AND login = 0')->fetchField());
  $rows[] = array(array('data' => t('Roles'), 'class' => 'title1', 'colspan' => '2'));
  $result = db_query('SELECT rid, name FROM {role} WHERE rid <> :rid ORDER BY weight, name', array(':rid' => DRUPAL_ANONYMOUS_RID));
  foreach ($result as $record) {
    $count = $record->rid != DRUPAL_AUTHENTICATED_RID ? db_query('SELECT COUNT(uid) FROM {users_roles} WHERE rid = :rid', array(':rid' => $record->rid))->fetchField() : db_query('SELECT COUNT(uid) FROM {users} WHERE uid <> 0')->fetchField();
    $rows[] = array(array('data' => check_plain($record->name), 'class' => 'text1'), $count);
  }

  return theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('class' => array('systeminfo', 'systeminfo-width50'))));
}

function _systeminfo_admin_drupal_roles() {

  $header = array();
  $header[] = t('Group');
  $header[] = t('Permissions');

  $perms = array();
  $result = db_query('SELECT r.name, rp.permission, rp.module FROM {role_permission} rp LEFT JOIN {role} r ON r.rid = rp.rid ORDER BY r.weight, r.name');
  foreach ($result as $record) {

    if ($permissions = module_invoke($record->module, 'permission')) {
      $perms[$record->name][] = !empty($permissions[$record->permission]['title']) ? $permissions[$record->permission]['title'] : $record->permission;
    }
  }

  $rows = array();
  foreach ($perms as $role => $perm) {
    asort($perm);

    $row = array();
    $row[] = check_plain($role);
    $row[] = theme('item_list', array('items' => $perm));

    $rows[] = $row;
  }

  return theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('class' => array('systeminfo', 'systeminfo-width50'))));
}

function _systeminfo_admin_drupal_modules() {

  $sort = variable_get('systeminfo_drupal_modules_sort', 'name');

  $header = array();
  $header[] = t('Name');
  $header[] = t('Version');
  $header[] = t('Date stamp');
  $header[] = t('Filename');
  $header[] = t('Schema');
  $header[] = t('Weight');

  $rows = array();
  $install_profile = variable_get('install_profile', 'standard');
  foreach (module_list() as $module) {
    if ($module != $install_profile) {

      $module_system = db_query('SELECT name, filename, schema_version, weight FROM {system} WHERE name = :name', array(':name' => $module))->fetchObject();
      $module_info = system_get_info('module', $module_system->name);

      $row = array();
      $row[] = $module_info['name'];
      $row[] = $module_info['version'];
      $row[] = isset($module_info['datestamp']) ? format_date($module_info['datestamp'], 'small') : '';
      $row[] = $module_system->filename;
      $row[] = $module_system->schema_version;
      $row[] = $module_system->weight;

      $key = $sort == 'name' ? $module_info['name'] : $module_system->filename;
      $rows[$key] = $row;
    }
  }
  if ($sort == 'name' || $sort == 'filename') {
    ksort($rows);
  }

  return theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('class' => array('systeminfo'))));
}

function _systeminfo_admin_drupal_themes() {

  $sort = variable_get('systeminfo_drupal_themes_sort', 'name');

  $header = array();
  $header[] = t('Name');
  $header[] = t('Version');
  $header[] = t('Date stamp');
  $header[] = t('Filename');
  $header[] = t('Base theme');

  $rows = array();
  foreach (list_themes() as $theme) {

    if ($theme->status) {

      $row = array();
      $row[] = $theme->info['name'];
      $row[] = $theme->info['version'];
      $row[] = isset($theme->info['datestamp']) ? format_date($theme->info['datestamp'], 'small') : '';
      $row[] = $theme->filename;
      $row[] = isset($theme->base_theme) ? $theme->base_theme : '';

      $key = $sort == 'name' ? $theme->name : $theme->filename;
      $rows[$key] = $row;
    }
  }
  if ($sort == 'name' || $sort == 'filename') {
    ksort($rows);
  }

  return theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('class' => array('systeminfo'))));
}


/**
 * Menu callback; configures the display.
 */
function systeminfo_admin_drupal_settings($form, &$form_state) {

  $form['systeminfo_drupal_modules_sort'] = array(
    '#type' => 'radios',
    '#title' => t('Modules list'),
    '#default_value' => variable_get('systeminfo_drupal_modules_sort', 'name'),
    '#options' => array(
      'name' => t("Ascending sorted by module's name."),
      'filename' => t("Ascending sorted by module's filename."),
      'callup' => t("Ascending sorted by module's call-up."),
    ),
  );
  $form['systeminfo_drupal_themes_sort'] = array(
    '#type' => 'radios',
    '#title' => t('Themes list'),
    '#default_value' => variable_get('systeminfo_drupal_themes_sort', 'name'),
    '#options' => array(
      'name' => t("Ascending sorted by theme's name."),
      'filename' => t("Ascending sorted by theme's filename."),
    ),
  );

  // Buttons
  $form['actions'] = array(
    '#type' => 'actions',
  );
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );
  $form['actions']['cancel'] = array(
    '#markup' => l(t('Cancel'), 'admin/reports/systeminfo/drupal'),
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
