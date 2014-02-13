<?php
/**
 * @file
 * secured_permissions.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function secured_permissions_defaultconfig_features() {
  return array(
    'secured_permissions' => array(
      'user_default_permissions' => 'user_default_permissions',
    ),
  );
}

/**
 * Implements hook_defaultconfig_user_default_permissions().
 */
function secured_permissions_defaultconfig_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access administration menu'.
  $permissions['access administration menu'] = array(
    'name' => 'access administration menu',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'admin_menu',
  );

  // Exported permission: 'access administration pages'.
  $permissions['access administration pages'] = array(
    'name' => 'access administration pages',
    'roles' => array(
      'administrator' => 'administrator',
      'developer' => 'developer',
      'editor' => 'editor',
    ),
    'module' => 'system',
  );

  // Exported permission: 'access all views'.
  $permissions['access all views'] = array(
    'name' => 'access all views',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'views',
  );

  // Exported permission: 'access all webform results'.
  $permissions['access all webform results'] = array(
    'name' => 'access all webform results',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'webform',
  );

  // Exported permission: 'access apc statistics'.
  $permissions['access apc statistics'] = array(
    'name' => 'access apc statistics',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'apc',
  );

  // Exported permission: 'access backup and migrate'.
  $permissions['access backup and migrate'] = array(
    'name' => 'access backup and migrate',
    'roles' => array(
      'administrator' => 'administrator',
      'developer' => 'developer',
    ),
    'module' => 'backup_migrate',
  );

  // Exported permission: 'access backup files'.
  $permissions['access backup files'] = array(
    'name' => 'access backup files',
    'roles' => array(
      'administrator' => 'administrator',
      'developer' => 'developer',
    ),
    'module' => 'backup_migrate',
  );

  // Exported permission: 'access ckeditor link'.
  $permissions['access ckeditor link'] = array(
    'name' => 'access ckeditor link',
    'roles' => array(
      'administrator' => 'administrator',
      'contributor' => 'contributor',
      'developer' => 'developer',
      'editor' => 'editor',
    ),
    'module' => 'ckeditor_link',
  );

  // Exported permission: 'access comments'.
  $permissions['access comments'] = array(
    'name' => 'access comments',
    'roles' => array(
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
      'contributor' => 'contributor',
      'developer' => 'developer',
      'editor' => 'editor',
    ),
    'module' => 'comment',
  );

  // Exported permission: 'access content'.
  $permissions['access content'] = array(
    'name' => 'access content',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
      'developer' => 'developer',
    ),
    'module' => 'node',
  );

  // Exported permission: 'access content overview'.
  $permissions['access content overview'] = array(
    'name' => 'access content overview',
    'roles' => array(
      'administrator' => 'administrator',
      'developer' => 'developer',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'access contextual links'.
  $permissions['access contextual links'] = array(
    'name' => 'access contextual links',
    'roles' => array(
      'administrator' => 'administrator',
      'developer' => 'developer',
      'editor' => 'editor',
    ),
    'module' => 'contextual',
  );

  // Exported permission: 'access dashboard'.
  $permissions['access dashboard'] = array(
    'name' => 'access dashboard',
    'roles' => array(
      'administrator' => 'administrator',
      'contributor' => 'contributor',
      'developer' => 'developer',
      'editor' => 'editor',
    ),
    'module' => 'dashboard',
  );

  // Exported permission: 'access devel information'.
  $permissions['access devel information'] = array(
    'name' => 'access devel information',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'devel',
  );

  // Exported permission: 'access own webform results'.
  $permissions['access own webform results'] = array(
    'name' => 'access own webform results',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'webform',
  );

  // Exported permission: 'access own webform submissions'.
  $permissions['access own webform submissions'] = array(
    'name' => 'access own webform submissions',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'webform',
  );

  // Exported permission: 'access rules debug'.
  $permissions['access rules debug'] = array(
    'name' => 'access rules debug',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'rules',
  );

  // Exported permission: 'access security review list'.
  $permissions['access security review list'] = array(
    'name' => 'access security review list',
    'roles' => array(
      'administrator' => 'administrator',
      'developer' => 'developer',
    ),
    'module' => 'security_review',
  );

  // Exported permission: 'access site in maintenance mode'.
  $permissions['access site in maintenance mode'] = array(
    'name' => 'access site in maintenance mode',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'system',
  );

  // Exported permission: 'access site map'.
  $permissions['access site map'] = array(
    'name' => 'access site map',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
      'developer' => 'developer',
    ),
    'module' => 'site_map',
  );

  // Exported permission: 'access site reports'.
  $permissions['access site reports'] = array(
    'name' => 'access site reports',
    'roles' => array(
      'administrator' => 'administrator',
      'developer' => 'developer',
    ),
    'module' => 'system',
  );

  // Exported permission: 'access site-wide contact form'.
  $permissions['access site-wide contact form'] = array(
    'name' => 'access site-wide contact form',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
      'developer' => 'developer',
    ),
    'module' => 'contact',
  );

  // Exported permission: 'access statistics'.
  $permissions['access statistics'] = array(
    'name' => 'access statistics',
    'roles' => array(
      'administrator' => 'administrator',
      'developer' => 'developer',
    ),
    'module' => 'statistics',
  );

  // Exported permission: 'access system information'.
  $permissions['access system information'] = array(
    'name' => 'access system information',
    'roles' => array(
      'administrator' => 'administrator',
      'developer' => 'developer',
    ),
    'module' => 'systeminfo',
  );

  // Exported permission: 'access user contact forms'.
  $permissions['access user contact forms'] = array(
    'name' => 'access user contact forms',
    'roles' => array(
      'administrator' => 'administrator',
      'contributor' => 'contributor',
      'developer' => 'developer',
      'editor' => 'editor',
    ),
    'module' => 'contact',
  );

  // Exported permission: 'access user profiles'.
  $permissions['access user profiles'] = array(
    'name' => 'access user profiles',
    'roles' => array(
      'administrator' => 'administrator',
      'contributor' => 'contributor',
      'developer' => 'developer',
      'editor' => 'editor',
    ),
    'module' => 'user',
  );

  // Exported permission: 'administer accessibility tests'.
  $permissions['administer accessibility tests'] = array(
    'name' => 'administer accessibility tests',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'accessibility',
  );

  // Exported permission: 'administer actions'.
  $permissions['administer actions'] = array(
    'name' => 'administer actions',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'system',
  );

  // Exported permission: 'administer advanced pane settings'.
  $permissions['administer advanced pane settings'] = array(
    'name' => 'administer advanced pane settings',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'panels',
  );

  // Exported permission: 'administer autologout'.
  $permissions['administer autologout'] = array(
    'name' => 'administer autologout',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'autologout',
  );

  // Exported permission: 'administer backup and migrate'.
  $permissions['administer backup and migrate'] = array(
    'name' => 'administer backup and migrate',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'backup_migrate',
  );

  // Exported permission: 'administer block classes'.
  $permissions['administer block classes'] = array(
    'name' => 'administer block classes',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'block_class',
  );

  // Exported permission: 'administer blocks'.
  $permissions['administer blocks'] = array(
    'name' => 'administer blocks',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'block',
  );

  // Exported permission: 'administer ckeditor link'.
  $permissions['administer ckeditor link'] = array(
    'name' => 'administer ckeditor link',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'ckeditor_link',
  );

  // Exported permission: 'administer comments'.
  $permissions['administer comments'] = array(
    'name' => 'administer comments',
    'roles' => array(
      'administrator' => 'administrator',
      'developer' => 'developer',
      'editor' => 'editor',
    ),
    'module' => 'comment',
  );

  // Exported permission: 'administer contact forms'.
  $permissions['administer contact forms'] = array(
    'name' => 'administer contact forms',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'contact',
  );

  // Exported permission: 'administer content security policies'.
  $permissions['administer content security policies'] = array(
    'name' => 'administer content security policies',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'content_security_policy',
  );

  // Exported permission: 'administer content types'.
  $permissions['administer content types'] = array(
    'name' => 'administer content types',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'node',
  );

  // Exported permission: 'administer contexts'.
  $permissions['administer contexts'] = array(
    'name' => 'administer contexts',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'context_ui',
  );

  // Exported permission: 'administer crumbs'.
  $permissions['administer crumbs'] = array(
    'name' => 'administer crumbs',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'crumbs',
  );

  // Exported permission: 'administer css3pie'.
  $permissions['administer css3pie'] = array(
    'name' => 'administer css3pie',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'css3pie',
  );

  // Exported permission: 'administer date tools'.
  $permissions['administer date tools'] = array(
    'name' => 'administer date tools',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'date_tools',
  );

  // Exported permission: 'administer default config'.
  $permissions['administer default config'] = array(
    'name' => 'administer default config',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'defaultconfig',
  );

  // Exported permission: 'administer exclude node title'.
  $permissions['administer exclude node title'] = array(
    'name' => 'administer exclude node title',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'exclude_node_title',
  );

  // Exported permission: 'administer features'.
  $permissions['administer features'] = array(
    'name' => 'administer features',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'features',
  );

  // Exported permission: 'administer fieldgroups'.
  $permissions['administer fieldgroups'] = array(
    'name' => 'administer fieldgroups',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'field_group',
  );

  // Exported permission: 'administer filters'.
  $permissions['administer filters'] = array(
    'name' => 'administer filters',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'filter',
  );

  // Exported permission: 'administer honeypot'.
  $permissions['administer honeypot'] = array(
    'name' => 'administer honeypot',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'honeypot',
  );

  // Exported permission: 'administer image styles'.
  $permissions['administer image styles'] = array(
    'name' => 'administer image styles',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'image',
  );

  // Exported permission: 'administer imce'.
  $permissions['administer imce'] = array(
    'name' => 'administer imce',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'imce',
  );

  // Exported permission: 'administer masquerade'.
  $permissions['administer masquerade'] = array(
    'name' => 'administer masquerade',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'masquerade',
  );

  // Exported permission: 'administer menu'.
  $permissions['administer menu'] = array(
    'name' => 'administer menu',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'menu',
  );

  // Exported permission: 'administer menu attributes'.
  $permissions['administer menu attributes'] = array(
    'name' => 'administer menu attributes',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'menu_attributes',
  );

  // Exported permission: 'administer meta tags'.
  $permissions['administer meta tags'] = array(
    'name' => 'administer meta tags',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'metatag',
  );

  // Exported permission: 'administer module filter'.
  $permissions['administer module filter'] = array(
    'name' => 'administer module filter',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'module_filter',
  );

  // Exported permission: 'administer modules'.
  $permissions['administer modules'] = array(
    'name' => 'administer modules',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'system',
  );

  // Exported permission: 'administer nodes'.
  $permissions['administer nodes'] = array(
    'name' => 'administer nodes',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'node',
  );

  // Exported permission: 'administer pane access'.
  $permissions['administer pane access'] = array(
    'name' => 'administer pane access',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'panels',
  );

  // Exported permission: 'administer panels layouts'.
  $permissions['administer panels layouts'] = array(
    'name' => 'administer panels layouts',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'panels',
  );

  // Exported permission: 'administer panels styles'.
  $permissions['administer panels styles'] = array(
    'name' => 'administer panels styles',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'panels',
  );

  // Exported permission: 'administer password policies'.
  $permissions['administer password policies'] = array(
    'name' => 'administer password policies',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'password_policy',
  );

  // Exported permission: 'administer pathauto'.
  $permissions['administer pathauto'] = array(
    'name' => 'administer pathauto',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'pathauto',
  );

  // Exported permission: 'administer permissions'.
  $permissions['administer permissions'] = array(
    'name' => 'administer permissions',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'user',
  );

  // Exported permission: 'administer profiler builder'.
  $permissions['administer profiler builder'] = array(
    'name' => 'administer profiler builder',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'profiler_builder',
  );

  // Exported permission: 'administer redirects'.
  $permissions['administer redirects'] = array(
    'name' => 'administer redirects',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'redirect',
  );

  // Exported permission: 'administer rules'.
  $permissions['administer rules'] = array(
    'name' => 'administer rules',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'rules',
  );

  // Exported permission: 'administer search'.
  $permissions['administer search'] = array(
    'name' => 'administer search',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'search',
  );

  // Exported permission: 'administer session limits by role'.
  $permissions['administer session limits by role'] = array(
    'name' => 'administer session limits by role',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'session_limit',
  );

  // Exported permission: 'administer session limits per user'.
  $permissions['administer session limits per user'] = array(
    'name' => 'administer session limits per user',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'session_limit',
  );

  // Exported permission: 'administer site configuration'.
  $permissions['administer site configuration'] = array(
    'name' => 'administer site configuration',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'system',
  );

  // Exported permission: 'administer software updates'.
  $permissions['administer software updates'] = array(
    'name' => 'administer software updates',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'system',
  );

  // Exported permission: 'administer statistics'.
  $permissions['administer statistics'] = array(
    'name' => 'administer statistics',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'statistics',
  );

  // Exported permission: 'administer system information'.
  $permissions['administer system information'] = array(
    'name' => 'administer system information',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'systeminfo',
  );

  // Exported permission: 'administer taxonomy'.
  $permissions['administer taxonomy'] = array(
    'name' => 'administer taxonomy',
    'roles' => array(
      'administrator' => 'administrator',
      'developer' => 'developer',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'administer themes'.
  $permissions['administer themes'] = array(
    'name' => 'administer themes',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'system',
  );

  // Exported permission: 'administer url aliases'.
  $permissions['administer url aliases'] = array(
    'name' => 'administer url aliases',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'path',
  );

  // Exported permission: 'administer users'.
  $permissions['administer users'] = array(
    'name' => 'administer users',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'user',
  );

  // Exported permission: 'administer views'.
  $permissions['administer views'] = array(
    'name' => 'administer views',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'views',
  );

  // Exported permission: 'administer wysiwyg templates'.
  $permissions['administer wysiwyg templates'] = array(
    'name' => 'administer wysiwyg templates',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'wysiwyg_template',
  );

  // Exported permission: 'administer xmlsitemap'.
  $permissions['administer xmlsitemap'] = array(
    'name' => 'administer xmlsitemap',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'xmlsitemap',
  );

  // Exported permission: 'block IP addresses'.
  $permissions['block IP addresses'] = array(
    'name' => 'block IP addresses',
    'roles' => array(
      'administrator' => 'administrator',
      'developer' => 'developer',
    ),
    'module' => 'system',
  );

  // Exported permission: 'bypass advanced aggregation'.
  $permissions['bypass advanced aggregation'] = array(
    'name' => 'bypass advanced aggregation',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'advagg',
  );

  // Exported permission: 'bypass honeypot protection'.
  $permissions['bypass honeypot protection'] = array(
    'name' => 'bypass honeypot protection',
    'roles' => array(
      'administrator' => 'administrator',
      'contributor' => 'contributor',
      'developer' => 'developer',
      'editor' => 'editor',
    ),
    'module' => 'honeypot',
  );

  // Exported permission: 'bypass node access'.
  $permissions['bypass node access'] = array(
    'name' => 'bypass node access',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'node',
  );

  // Exported permission: 'bypass rules access'.
  $permissions['bypass rules access'] = array(
    'name' => 'bypass rules access',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'rules',
  );

  // Exported permission: 'cancel account'.
  $permissions['cancel account'] = array(
    'name' => 'cancel account',
    'roles' => array(
      'administrator' => 'administrator',
      'developer' => 'developer',
    ),
    'module' => 'user',
  );

  // Exported permission: 'change layouts in place editing'.
  $permissions['change layouts in place editing'] = array(
    'name' => 'change layouts in place editing',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'panels',
  );

  // Exported permission: 'change own logout threshold'.
  $permissions['change own logout threshold'] = array(
    'name' => 'change own logout threshold',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'autologout',
  );

  // Exported permission: 'change own username'.
  $permissions['change own username'] = array(
    'name' => 'change own username',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'user',
  );

  // Exported permission: 'check content for accessibility'.
  $permissions['check content for accessibility'] = array(
    'name' => 'check content for accessibility',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'accessibility_content',
  );

  // Exported permission: 'context ajax block access'.
  $permissions['context ajax block access'] = array(
    'name' => 'context ajax block access',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'context_ui',
  );

  // Exported permission: 'create article content'.
  $permissions['create article content'] = array(
    'name' => 'create article content',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create landing_page content'.
  $permissions['create landing_page content'] = array(
    'name' => 'create landing_page content',
    'roles' => array(
      'administrator' => 'administrator',
      'developer' => 'developer',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create page content'.
  $permissions['create page content'] = array(
    'name' => 'create page content',
    'roles' => array(
      'administrator' => 'administrator',
      'contributor' => 'contributor',
      'developer' => 'developer',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create section_page content'.
  $permissions['create section_page content'] = array(
    'name' => 'create section_page content',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create url aliases'.
  $permissions['create url aliases'] = array(
    'name' => 'create url aliases',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'path',
  );

  // Exported permission: 'create webform content'.
  $permissions['create webform content'] = array(
    'name' => 'create webform content',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete all webform submissions'.
  $permissions['delete all webform submissions'] = array(
    'name' => 'delete all webform submissions',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'webform',
  );

  // Exported permission: 'delete any article content'.
  $permissions['delete any article content'] = array(
    'name' => 'delete any article content',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any landing_page content'.
  $permissions['delete any landing_page content'] = array(
    'name' => 'delete any landing_page content',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any page content'.
  $permissions['delete any page content'] = array(
    'name' => 'delete any page content',
    'roles' => array(
      'administrator' => 'administrator',
      'developer' => 'developer',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any section_page content'.
  $permissions['delete any section_page content'] = array(
    'name' => 'delete any section_page content',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any webform content'.
  $permissions['delete any webform content'] = array(
    'name' => 'delete any webform content',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete backup files'.
  $permissions['delete backup files'] = array(
    'name' => 'delete backup files',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'backup_migrate',
  );

  // Exported permission: 'delete own article content'.
  $permissions['delete own article content'] = array(
    'name' => 'delete own article content',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own landing_page content'.
  $permissions['delete own landing_page content'] = array(
    'name' => 'delete own landing_page content',
    'roles' => array(
      'administrator' => 'administrator',
      'developer' => 'developer',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own page content'.
  $permissions['delete own page content'] = array(
    'name' => 'delete own page content',
    'roles' => array(
      'administrator' => 'administrator',
      'developer' => 'developer',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own section_page content'.
  $permissions['delete own section_page content'] = array(
    'name' => 'delete own section_page content',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own webform content'.
  $permissions['delete own webform content'] = array(
    'name' => 'delete own webform content',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own webform submissions'.
  $permissions['delete own webform submissions'] = array(
    'name' => 'delete own webform submissions',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'webform',
  );

  // Exported permission: 'delete revisions'.
  $permissions['delete revisions'] = array(
    'name' => 'delete revisions',
    'roles' => array(
      'developer' => 'developer',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'display drupal links'.
  $permissions['display drupal links'] = array(
    'name' => 'display drupal links',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'admin_menu',
  );

  // Exported permission: 'edit all webform submissions'.
  $permissions['edit all webform submissions'] = array(
    'name' => 'edit all webform submissions',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'webform',
  );

  // Exported permission: 'edit any article content'.
  $permissions['edit any article content'] = array(
    'name' => 'edit any article content',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any landing_page content'.
  $permissions['edit any landing_page content'] = array(
    'name' => 'edit any landing_page content',
    'roles' => array(
      'administrator' => 'administrator',
      'developer' => 'developer',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any page content'.
  $permissions['edit any page content'] = array(
    'name' => 'edit any page content',
    'roles' => array(
      'administrator' => 'administrator',
      'developer' => 'developer',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any section_page content'.
  $permissions['edit any section_page content'] = array(
    'name' => 'edit any section_page content',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any webform content'.
  $permissions['edit any webform content'] = array(
    'name' => 'edit any webform content',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit meta tags'.
  $permissions['edit meta tags'] = array(
    'name' => 'edit meta tags',
    'roles' => array(
      'contributor' => 'contributor',
      'developer' => 'developer',
      'editor' => 'editor',
    ),
    'module' => 'metatag',
  );

  // Exported permission: 'edit own article content'.
  $permissions['edit own article content'] = array(
    'name' => 'edit own article content',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own comments'.
  $permissions['edit own comments'] = array(
    'name' => 'edit own comments',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
      'contributor' => 'contributor',
      'developer' => 'developer',
      'editor' => 'editor',
    ),
    'module' => 'comment',
  );

  // Exported permission: 'edit own landing_page content'.
  $permissions['edit own landing_page content'] = array(
    'name' => 'edit own landing_page content',
    'roles' => array(
      'administrator' => 'administrator',
      'developer' => 'developer',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own page content'.
  $permissions['edit own page content'] = array(
    'name' => 'edit own page content',
    'roles' => array(
      'administrator' => 'administrator',
      'contributor' => 'contributor',
      'developer' => 'developer',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own section_page content'.
  $permissions['edit own section_page content'] = array(
    'name' => 'edit own section_page content',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own webform content'.
  $permissions['edit own webform content'] = array(
    'name' => 'edit own webform content',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own webform submissions'.
  $permissions['edit own webform submissions'] = array(
    'name' => 'edit own webform submissions',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'webform',
  );

  // Exported permission: 'edit revisions'.
  $permissions['edit revisions'] = array(
    'name' => 'edit revisions',
    'roles' => array(
      'developer' => 'developer',
      'editor' => 'editor',
    ),
    'module' => 'revisioning',
  );


  // Exported permission: 'exclude any node title'.
  $permissions['exclude any node title'] = array(
    'name' => 'exclude any node title',
    'roles' => array(
      'administrator' => 'administrator',
      'developer' => 'developer',
      'editor' => 'editor',
    ),
    'module' => 'exclude_node_title',
  );

  // Exported permission: 'exclude own node title'.
  $permissions['exclude own node title'] = array(
    'name' => 'exclude own node title',
    'roles' => array(
      'administrator' => 'administrator',
      'developer' => 'developer',
      'editor' => 'editor',
    ),
    'module' => 'exclude_node_title',
  );

  // Exported permission: 'execute php code'.
  $permissions['execute php code'] = array(
    'name' => 'execute php code',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'devel',
  );

  // Exported permission: 'flush caches'.
  $permissions['flush caches'] = array(
    'name' => 'flush caches',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'admin_menu',
  );

  // Exported permission: 'force password change'.
  $permissions['force password change'] = array(
    'name' => 'force password change',
    'roles' => array(
      'administrator' => 'administrator',
      'developer' => 'developer',
    ),
    'module' => 'password_policy',
  );

  // Exported permission: 'generate features'.
  $permissions['generate features'] = array(
    'name' => 'generate features',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'features',
  );

  // Exported permission: 'import wysiwyg templates'.
  $permissions['import wysiwyg templates'] = array(
    'name' => 'import wysiwyg templates',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'wysiwyg_template',
  );

  // Exported permission: 'manage features'.
  $permissions['manage features'] = array(
    'name' => 'manage features',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'features',
  );

  // Exported permission: 'masquerade as admin'.
  $permissions['masquerade as admin'] = array(
    'name' => 'masquerade as admin',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'masquerade',
  );

  // Exported permission: 'masquerade as user'.
  $permissions['masquerade as user'] = array(
    'name' => 'masquerade as user',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'masquerade',
  );

  // Exported permission: 'notify of path changes'.
  $permissions['notify of path changes'] = array(
    'name' => 'notify of path changes',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'pathauto',
  );

  // Exported permission: 'perform backup'.
  $permissions['perform backup'] = array(
    'name' => 'perform backup',
    'roles' => array(
      'administrator' => 'administrator',
      'developer' => 'developer',
    ),
    'module' => 'backup_migrate',
  );

  // Exported permission: 'post comments'.
  $permissions['post comments'] = array(
    'name' => 'post comments',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'comment',
  );

  // Exported permission: 'publish revisions'.
  $permissions['publish revisions'] = array(
    'name' => 'publish revisions',
    'roles' => array(
      'developer' => 'developer',
      'editor' => 'editor',
    ),
    'module' => 'revisioning',
  );

  // Exported permission: 'restore from backup'.
  $permissions['restore from backup'] = array(
    'name' => 'restore from backup',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'backup_migrate',
  );

  // Exported permission: 'revert revisions'.
  $permissions['revert revisions'] = array(
    'name' => 'revert revisions',
    'roles' => array(
      'developer' => 'developer',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'run security checks'.
  $permissions['run security checks'] = array(
    'name' => 'run security checks',
    'roles' => array(
      'administrator' => 'administrator',
      'developer' => 'developer',
    ),
    'module' => 'security_review',
  );

  // Exported permission: 'search content'.
  $permissions['search content'] = array(
    'name' => 'search content',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
      'developer' => 'developer',
    ),
    'module' => 'search',
  );

  // Exported permission: 'select account cancellation method'.
  $permissions['select account cancellation method'] = array(
    'name' => 'select account cancellation method',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'user',
  );

  // Exported permission: 'show format selection for accessibility_test'.
  $permissions['show format selection for accessibility_test'] = array(
    'name' => 'show format selection for accessibility_test',
    'roles' => array(),
    'module' => 'better_formats',
  );

  // Exported permission: 'show format selection for comment'.
  $permissions['show format selection for comment'] = array(
    'name' => 'show format selection for comment',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'better_formats',
  );

  // Exported permission: 'show format selection for node'.
  $permissions['show format selection for node'] = array(
    'name' => 'show format selection for node',
    'roles' => array(
      'administrator' => 'administrator',
      'developer' => 'developer',
    ),
    'module' => 'better_formats',
  );

  // Exported permission: 'show format selection for rules_config'.
  $permissions['show format selection for rules_config'] = array(
    'name' => 'show format selection for rules_config',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'better_formats',
  );

  // Exported permission: 'show format selection for taxonomy_term'.
  $permissions['show format selection for taxonomy_term'] = array(
    'name' => 'show format selection for taxonomy_term',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'better_formats',
  );

  // Exported permission: 'show format selection for user'.
  $permissions['show format selection for user'] = array(
    'name' => 'show format selection for user',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'better_formats',
  );

  // Exported permission: 'show format tips'.
  $permissions['show format tips'] = array(
    'name' => 'show format tips',
    'roles' => array(
      'administrator' => 'administrator',
      'contributor' => 'contributor',
      'developer' => 'developer',
      'editor' => 'editor',
    ),
    'module' => 'better_formats',
  );

  // Exported permission: 'show more format tips link'.
  $permissions['show more format tips link'] = array(
    'name' => 'show more format tips link',
    'roles' => array(
      'administrator' => 'administrator',
      'developer' => 'developer',
      'editor' => 'editor',
    ),
    'module' => 'better_formats',
  );

  // Exported permission: 'skip comment approval'.
  $permissions['skip comment approval'] = array(
    'name' => 'skip comment approval',
    'roles' => array(
      'administrator' => 'administrator',
      'contributor' => 'contributor',
      'developer' => 'developer',
      'editor' => 'editor',
    ),
    'module' => 'comment',
  );

  // Exported permission: 'skip revision log message'.
  $permissions['skip revision log message'] = array(
    'name' => 'skip revision log message',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'enforce_revlog',
  );

  // Exported permission: 'switch users'.
  $permissions['switch users'] = array(
    'name' => 'switch users',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'devel',
  );

  // Exported permission: 'unblock expired accounts'.
  $permissions['unblock expired accounts'] = array(
    'name' => 'unblock expired accounts',
    'roles' => array(
      'administrator' => 'administrator',
      'developer' => 'developer',
    ),
    'module' => 'password_policy',
  );

  // Exported permission: 'unpublish current revision'.
  $permissions['unpublish current revision'] = array(
    'name' => 'unpublish current revision',
    'roles' => array(
      'developer' => 'developer',
      'editor' => 'editor',
    ),
    'module' => 'revisioning',
  );

  // Exported permission: 'use advanced search'.
  $permissions['use advanced search'] = array(
    'name' => 'use advanced search',
    'roles' => array(
      'contributor' => 'contributor',
      'developer' => 'developer',
    ),
    'module' => 'search',
  );

  // Exported permission: 'use exclude node title'.
  $permissions['use exclude node title'] = array(
    'name' => 'use exclude node title',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
      'developer' => 'developer',
    ),
    'module' => 'exclude_node_title',
  );

  // Exported permission: 'use panels caching features'.
  $permissions['use panels caching features'] = array(
    'name' => 'use panels caching features',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'panels',
  );

  // Exported permission: 'use panels dashboard'.
  $permissions['use panels dashboard'] = array(
    'name' => 'use panels dashboard',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'panels',
  );

  // Exported permission: 'use panels in place editing'.
  $permissions['use panels in place editing'] = array(
    'name' => 'use panels in place editing',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'panels',
  );

  // Exported permission: 'use panels locks'.
  $permissions['use panels locks'] = array(
    'name' => 'use panels locks',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'panels',
  );

  // Exported permission: 'use text format filtered_html'.
  $permissions['use text format filtered_html'] = array(
    'name' => 'use text format filtered_html',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
      'contributor' => 'contributor',
      'developer' => 'developer',
      'editor' => 'editor',
    ),
    'module' => 'filter',
  );

  // Exported permission: 'use text format full_html'.
  $permissions['use text format full_html'] = array(
    'name' => 'use text format full_html',
    'roles' => array(
      'administrator' => 'administrator',
      'developer' => 'developer',
    ),
    'module' => 'filter',
  );

  // Exported permission: 'use text format textbook_editor'.
  $permissions['use text format textbook_editor'] = array(
    'name' => 'use text format textbook_editor',
    'roles' => array(),
    'module' => 'filter',
  );

  // Exported permission: 'view accessibility tests'.
  $permissions['view accessibility tests'] = array(
    'name' => 'view accessibility tests',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'accessibility',
  );

  // Exported permission: 'view diffs of changed files'.
  $permissions['view diffs of changed files'] = array(
    'name' => 'view diffs of changed files',
    'roles' => array(
      'developer' => 'developer',
      'editor' => 'editor',
    ),
    'module' => 'hacked',
  );

  // Exported permission: 'view own unpublished content'.
  $permissions['view own unpublished content'] = array(
    'name' => 'view own unpublished content',
    'roles' => array(
      'administrator' => 'administrator',
      'contributor' => 'contributor',
      'developer' => 'developer',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'view pane admin links'.
  $permissions['view pane admin links'] = array(
    'name' => 'view pane admin links',
    'roles' => array(
      'developer' => 'developer',
    ),
    'module' => 'panels',
  );

  // Exported permission: 'view post access counter'.
  $permissions['view post access counter'] = array(
    'name' => 'view post access counter',
    'roles' => array(
      'administrator' => 'administrator',
      'developer' => 'developer',
      'editor' => 'editor',
    ),
    'module' => 'statistics',
  );

  // Exported permission: 'view revision status messages'.
  $permissions['view revision status messages'] = array(
    'name' => 'view revision status messages',
    'roles' => array(
      'administrator' => 'administrator',
      'contributor' => 'contributor',
      'developer' => 'developer',
      'editor' => 'editor',
    ),
    'module' => 'revisioning',
  );

  // Exported permission: 'view revisions'.
  $permissions['view revisions'] = array(
    'name' => 'view revisions',
    'roles' => array(
      'contributor' => 'contributor',
      'developer' => 'developer',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'view the administration theme'.
  $permissions['view the administration theme'] = array(
    'name' => 'view the administration theme',
    'roles' => array(
      'administrator' => 'administrator',
      'developer' => 'developer',
    ),
    'module' => 'system',
  );

  return $permissions;
}
