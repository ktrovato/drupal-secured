<?php
/**
 * @file
 * secured_permissions.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function secured_permissions_user_default_roles() {
  $roles = array();

  // Exported role: administrator.
  $roles['administrator'] = array(
    'name' => 'administrator',
    'weight' => 5,
  );

  // Exported role: contributor.
  $roles['contributor'] = array(
    'name' => 'contributor',
    'weight' => 3,
  );

  // Exported role: developer.
  $roles['developer'] = array(
    'name' => 'developer',
    'weight' => 6,
  );

  // Exported role: editor.
  $roles['editor'] = array(
    'name' => 'editor',
    'weight' => 4,
  );

  return $roles;
}
