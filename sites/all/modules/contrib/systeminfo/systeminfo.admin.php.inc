<?php

/**
 * @file
 * Admin PHP page callbacks for the systeminfo module.
 */


/**
 * Menu callback; displays the PHP page.
 */
function systeminfo_admin_php() {

  if (function_exists('phpinfo')) {

    ob_start();
    phpinfo(variable_get('systeminfo_php_phpinfo_parameter', INFO_ALL));
    $phpinfo = ob_get_contents();
    ob_end_clean();

    preg_match_all('#<body[^>]*>(.*)</body>#siU', $phpinfo, $output);
    $output = preg_replace('#<table[^>]*>#', '<table class="adminlist">', $output[1][0]);
    $output = preg_replace('#(\w),(\w)#', '\1, \2', $output);
    $output = preg_replace('#<hr />#', '', $output);
    $output = str_replace('<div class="center">', '', $output);
    $output = preg_replace('#<tr class="h">(.*)<\/tr>#', '<thead><tr class="h">$1</tr></thead><tbody>', $output);
    $output = str_replace('</table>', '</tbody></table>', $output);
    $output = str_replace('</div>', '', $output);
    $output = str_replace('h2>', 'h3>', $output);
    $output = str_replace('h1>', 'h2>', $output);

    return $output;
  }
  else {

    return '<p>' . t('The phpinfo() function has been disabled for security reasons. To see your server\'s phpinfo() information, change your PHP settings or contact your server administrator. For more information, <a href="@phpinfo">Enabling and disabling phpinfo()</a> handbook page.', array('@phpinfo' => 'http://drupal.org/node/243993')) . '</p>';
  }
}


/**
 * Menu callback; configures the display.
 */
function systeminfo_admin_php_settings($form, &$form_state) {

  $form['systeminfo_php_phpinfo_parameter'] = array(
    '#type' => 'radios',
    '#title' => t('PHPinfo'),
    '#description' => t('Outputs a large amount of information about the current state of PHP.'),
    '#default_value' => variable_get('systeminfo_php_phpinfo_parameter', INFO_ALL),
    '#options' => array(
      INFO_GENERAL => t('The configuration line, php.ini location, build date, Web Server, System and more.'),
      INFO_CONFIGURATION => t('Current Local and Master values for PHP directives.'),
      INFO_MODULES => t('Loaded modules and their respective settings.'),
      INFO_ENVIRONMENT => t("Environment Variable information that's also available in \$_ENV."),
      INFO_VARIABLES => t('Shows all predefined variables from EGPCS (Environment, GET, POST, Cookie, Server).'),
      INFO_ALL => t('Shows all of the above.'),
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
    '#markup' => l(t('Cancel'), 'admin/reports/systeminfo/php'),
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
