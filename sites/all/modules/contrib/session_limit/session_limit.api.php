<?php

/**
 * @file
 * This file contains no working PHP code; it exists to provide additional
 * documentation for doxygen as well as to document hooks in the standard
 * Drupal manner.
 */

/**
 * Prevent session limitation checks at page load.
 *
 * Session limit module checks for active sessions during hook_init. If
 * a particular path or page load or context may mean that session
 * checks should not occur.
 *
 * @return bool
 *   TRUE if the current page request should bypass session limitation
 *   restrictions.
 */
function hook_session_limit_bypass() {
  if ((arg(0) == 'session' && arg(1) == 'limit') || arg(0) == 'logout') {
    return TRUE;
  }
}

/**
 * Notify other modules that a session imitation event has occured.
 *
 * When a session limit is reached, this hook is invoked. There are
 * two types of event. Collision events happen when a new session
 * causes an old session to close. Disconnect events happen when
 * a new session is prevented by an existing session.
 *
 * @param string $sid
 *   The session id of the session which caused the event. In a
 *   collision, this is not the session which was ended.
 * @param string $op
 *   Either 'disconnect' or 'collision'.
 */
function hook_session_limit($sid, $op) {
  global $user;
  rules_invoke_event('session_limit_' . $op, $user, $sid);
}
