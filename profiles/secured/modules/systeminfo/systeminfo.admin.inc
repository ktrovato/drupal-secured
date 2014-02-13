<?php

/**
 * @file
 * Admin page callbacks for the systeminfo module.
 */


/**
 * Menu callback; displays the overview page.
 */
function systeminfo_admin_overview() {

  drupal_add_css(drupal_get_path('module', 'systeminfo') .'/styles/systeminfo.css');

  $toc = array(
    array(
      '<a href="#drupal">'. t('Drupal') .'</a>',
      'children' => array(
        '<a href="#nodes">'. t('Content') .'</a>',
        '<a href="#users">'. t('Users') .'</a>',
        '<a href="#modules">'. t('Modules') .'</a>',
        '<a href="#themes">'. t('Themes') .'</a>',
      ),
    ),
    '<a href="#php">'. t('PHP') .'</a>',
    '<a href="#database">'. t('Database system') .'</a>',
    '<a href="#webserver">'. t('Web server') .'</a>',
  );

  $output = '<h3 id="toc">' . t('Table of contents') . '</h3>';
  $output .= theme('item_list', array('items' => $toc, 'type' => 'ul', 'attributes' => array('class' => array('systeminfo', 'systeminfo-toc'))));
  $output .= '<h3 id="drupal">' . t('Drupal') . '</h3>';
  $output .= _systeminfo_admin_overview_drupal();
  $output .= '<h4 id="nodes">' . t('Content') . '</h4>';
  $output .= _systeminfo_admin_overview_drupal_content();
  $output .= '<h4 id="users">' . t('Users') . '</h4>';
  $output .= _systeminfo_admin_overview_drupal_users();
  $output .= '<h4 id="modules">' . t('Modules') . '</h4>';
  $output .= _systeminfo_admin_overview_drupal_modules();
  $output .= '<h4 id="themes">' . t('Themes') . '</h4>';
  $output .= _systeminfo_admin_overview_drupal_themes();
  $output .= '<p>' . t('More information about the current state of the Drupal installation can be found <a href="@drupal" title="View current state of the Drupal installation.">here</a>.', array('@drupal' => url('admin/reports/systeminfo/drupal'))) . '</p>';
  $output .= '<h3 id="php">' . t('PHP') . '</h3>';
  $output .= _systeminfo_admin_overview_php();
  $output .= '<p>' . t('More information about the current state of PHP can be found <a href="@php" title="View current state of PHP.">here</a>.', array('@php' => url('admin/reports/systeminfo/php'))) . '</p>';
  $output .= '<h3 id="database">' . t('Database system') . '</h3>';
  $output .= _systeminfo_admin_overview_database();
  $output .= '<p>' . t('More information about the current state of the database system can be found <a href="@database" title="View current state the database system.">here</a>.', array('@database' => url('admin/reports/systeminfo/database'))) . '</p>';
  $output .= '<h3 id="webserver">' . t('Web server') . '</h3>';
  $output .= _systeminfo_admin_overview_webserver();

  return $output;
}

function _systeminfo_admin_overview_drupal() {

  $rows = array();
  $rows[] = array(t('Version'), VERSION);
  $rows[] = array(t('Configuration file'), conf_path() .'/settings.php');
  $cron_last = variable_get('cron_last');
  if (!is_numeric($cron_last)) {
    $cron_last = variable_get('install_time', 0);
  }
  $rows[] = array(t('Cron maintenance tasks'), t('Last run !time ago', array('!time' => format_interval(REQUEST_TIME - $cron_last))));
  $system_info = system_get_info('module', variable_get('install_profile', 'standard'));
  $rows[] = array(t('Install profile'), $system_info['name']);
  $rows[] = array(t('Install time'), format_date(variable_get('install_time', 0), 'small'));
  $rows[] = array(t('Public file system path'), variable_get('file_public_path', conf_path() . '/files'));
  $rows[] = array(t('Private file system path'), variable_get('file_private_path', ''));

  return theme('table', array('header' => array(), 'rows' => $rows, 'attributes' => array('class' => array('systeminfo', 'systeminfo-width50'))));
}

function _systeminfo_admin_overview_drupal_content() {

  $rows = array();
  $rows[] = array(t('Total'), format_plural(db_query('SELECT COUNT(nid) FROM {node}')->fetchField(), '1 node', '@count nodes'));
  $node_types = array();
  $result = db_query('SELECT n.type, nt.name, COUNT(n.nid) AS count FROM {node} n LEFT JOIN {node_type} nt ON n.type = nt.type GROUP BY n.type');
  foreach ($result as $record) {
    if (!$record->name) {
      $record->name = $record->type;
    }
    $node_types[$record->name] = $record;
  }
  ksort($node_types);
  foreach ($node_types as $node_type) {
    $rows[] = array(array('data' => check_plain($node_type->name), 'class' => 'text1'), format_plural($node_type->count, '1 node', '@count nodes'));
  }

  return theme('table', array('header' => array(), 'rows' => $rows, 'attributes' => array('class' => array('systeminfo', 'systeminfo-width50'))));
}

function _systeminfo_admin_overview_drupal_users() {

  $rows = array();
  $rows[] = array(t('Total'), format_plural(db_query('SELECT COUNT(uid) FROM {users} WHERE uid <> 0')->fetchField(), '1 account', '@count accounts'));
  $rows[] = array(array('data' => t('Active'), 'class' => 'text1'), format_plural(db_query('SELECT COUNT(uid) FROM {users} WHERE uid <> 0 AND status = 1')->fetchField(), '1 account', '@count accounts'));
  $rows[] = array(array('data' => t('Blocked'), 'class' => 'text1'), format_plural(db_query('SELECT COUNT(uid) FROM {users} WHERE uid <> 0 AND status = 0')->fetchField(), '1 account', '@count accounts'));

  return theme('table', array('header' => array(), 'rows' => $rows, 'attributes' => array('class' => array('systeminfo', 'systeminfo-width50'))));
}

function _systeminfo_admin_overview_drupal_modules() {

  $rows = array();
  $install_profile = variable_get('install_profile', 'standard');
  foreach (module_list() as $module) {
    if ($module != $install_profile) {
      $module_info = system_get_info('module', $module);
      $module_version = variable_get('systeminfo_overview_modules_datestamp', 0) && isset($module_info['datestamp']) ? $module_info['version'] . ' ' . drupal_placeholder('(' . format_date($module_info['datestamp'], 'small') . ')') : $module_info['version'];
      $rows[$module_info['name']] = array($module_info['name'], $module_version);
    }
  }
  ksort($rows);

  return theme('table', array('header' => array(), 'rows' => $rows, 'attributes' => array('class' => array('systeminfo', 'systeminfo-width50'))));
}

function _systeminfo_admin_overview_drupal_themes() {

  $rows = array();
  foreach (list_themes() as $theme) {
    if ($theme->status) {
      $themes_version = variable_get('systeminfo_overview_themes_datestamp', 0) && isset($theme->info['datestamp']) ? $theme->info['version'] . ' ' . drupal_placeholder('(' . format_date($theme->info['datestamp'], 'small') . ')') : $theme->info['version'];
      $rows[$theme->name] = array($theme->info['name'], $themes_version);
    }
  }
  ksort($rows);

  return theme('table', array('header' => array(), 'rows' => $rows, 'attributes' => array('class' => array('systeminfo', 'systeminfo-width50'))));
}

function _systeminfo_admin_overview_php() {

  $rows = array();
  $rows[] = array(t('Version'), phpversion());
  $rows[] = array(t('Magic quotes GPC'), ini_get('magic_quotes_gpc') ? t('On') : t('Off'));
  $rows[] = array(t('Magic quotes runtime'), ini_get('magic_quotes_runtime') ? t('On') : t('Off'));
  $rows[] = array(t('Max execution time'), ini_get('max_execution_time'));
  $rows[] = array(t('Max input time'), ini_get('max_input_time'));
  $rows[] = array(t('Memory limit'), ini_get('memory_limit'));
  $rows[] = array(t('Post max size'), ini_get('post_max_size'));
  $rows[] = array(t('Register globals'), ini_get('register_globals') ? t('On') : t('Off'));
  $rows[] = array(t('Safe mode'), ini_get('safe_mode') ? t('On') : t('Off'));
  $cookie_params = session_get_cookie_params();
  $rows[] = array(t('Session cookie domain'), $cookie_params['domain']);
  $rows[] = array(t('Upload max filesize'), ini_get('upload_max_filesize'));

  return theme('table', array('header' => array(), 'rows' => $rows, 'attributes' => array('class' => array('systeminfo', 'systeminfo-width50'))));
}

function _systeminfo_admin_overview_database() {

  $rows = array();


  return theme('table', array('header' => array(), 'rows' => $rows, 'attributes' => array('class' => array('systeminfo', 'systeminfo-width50'))));
}

function _systeminfo_admin_overview_webserver() {

  $rows = array();
  $rows[] = array(t('IP address'), $_SERVER['SERVER_ADDR']);
  $rows[] = array(t('Host'), $_SERVER['HTTP_HOST']);
  $rows[] = array(t('Server'), $_SERVER['SERVER_SOFTWARE']);
  $rows[] = array(t('System'), function_exists('php_uname') ? php_uname() : theme('placeholder', t('n/a')));

  return theme('table', array('header' => array(), 'rows' => $rows, 'attributes' => array('class' => array('systeminfo', 'systeminfo-width50'))));
}


/**
 * Menu callback; configures the display.
 */
function systeminfo_admin_overview_settings($form, &$form_state) {

  $form['systeminfo_overview_modules_datestamp'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display date stamp of modules.'),
    '#default_value' => variable_get('systeminfo_overview_modules_datestamp', 0),
  );
  $form['systeminfo_overview_themes_datestamp'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display date stamp of themes.'),
    '#default_value' => variable_get('systeminfo_overview_themes_datestamp', 0),
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
    '#markup' => l(t('Cancel'), 'admin/reports/systeminfo'),
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
