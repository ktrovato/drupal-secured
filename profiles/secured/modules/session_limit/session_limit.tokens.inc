<?php
/**
 * @file
 *
 * Provide tokens for session limit.
 */

/**
 * Implements hook_token_info().
 *
 * Create tokens for the current user.
 */
function session_limit_token_info() {
  $type = array(
    'name' => t('Session limit'),
    'description' => t('Tokens related to session limit module.'),
    'needs-data' => 'user',
  );

  $session_limit['default'] = array(
    'name' => t('Default sessions'),
    'description' => t('Maximum number of active sessions configured specific to the user.'),
  );
  $session_limit['max'] = array(
    'name' => t('Maximum sessions'),
    'description' => t('Maximum number of active sessions allowed, accounting for all configuration possibilities.'),
  );
  $session_limit['role'] = array(
    'name' => t('Maximum sessions by role'),
    'description' => t('Maximum number of active sessions allowed by role.'),
  );
  $session_limit['user'] = array(
    'name' => t('Maximum sessions for user'),
    'description' => t('Maximum number of active sessions configured specific to the user.'),
  );

  return array(
    'types' => array('session_limit' => $type),
    'tokens' => array('session_limit' => $session_limit),
  );
}

/**
 * Implements hook_tokens().
 */
function session_limit_tokens($type, $tokens, array $data = array(), array $options = array()) {
  $replacements = array();
  // The session limit variable does not need the user context.
  if ($type == 'session_limit') {
    foreach ($tokens as $name => $original) {
      if ($name == 'default') {
        $replacements[$original] = variable_get('session_limit_max', 1);
      }
    }
  }
  if ($type == 'session_limit' && !empty($data['user'])) {
    $account = user_load($data['user']->uid);
    foreach ($tokens as $name => $original) {
      switch ($name) {
        case 'max':
          $replacements[$original] = session_limit_user_max_sessions($account);
          break;
        case 'role':
          $replacements[$original] = session_limit_user_max_sessions_byrole($account);
          break;
        case 'user':
          $replacements[$original] = empty($account->session_limit) ? 0 : check_plain($account->session_limit);
          break;
      }
    }
  }
  return $replacements;
}
