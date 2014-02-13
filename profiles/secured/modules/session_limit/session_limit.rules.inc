<?php

/**
* @file
* Rules integration with session_limit.
*/

/**
* Implements hook_rules_event_info().
*/
function session_limit_rules_event_info() {
  $items = array();

  $items['session_limit_collision'] = array(
    'label' => t('User logs in and has too many active sessions'),
    'variables' => array(
      'account' => array(
        'type' => 'user',
        'label' => t('The user who logged in.'),
      ),
      'session_id' => array(
        'type' => 'text',
        'label' => t('The session id.'),
      ),
    ),
    'group' => t('Session Limit'),
  );

  $items['session_limit_disconnect'] = array(
    'label' => t('User is logged out by a newer session'),
    'variables' => array(
      'account' => array(
        'type' => 'user',
        'label' => t('The user who was logged out.'),
      ),
      'session_id' => array(
        'type' => 'text',
        'label' => t('The session id.'),
      ),
    ),
    'group' => t('Session Limit'),
  );

  return $items;
}
