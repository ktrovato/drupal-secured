<?php

/**
 * Can recover anonymous functions registered with hook_crumbs_plugins() via
 * e.g. $api->routeParentCallback() or $api->entityParentCallback()
 *
 * On an average request, Crumbs plugins are not defined via
 * hook_crumbs_plugins() but loaded from cache. Since anonymouse function are
 * not serializable, they need to be loaded explicitly by calling the respective
 * implementation of hook_crumbs_plugins().
 */
class crumbs_CallbackRestoration {

  /**
   * @var array
   *   Callbacks by module and "key", where
   *   $module . '.' . $key === $plugin_key
   *   $this->callbacks[$module][$key] = $callback
   */
  protected $callbacks = array();

  /**
   * @var crumbs_InjectedAPI_hookCrumbsPlugins
   */
  protected $api;

  /**
   * @var bool
   */
  protected $discoveryOngoing = FALSE;

  /**
   * Constructor
   */
  function __construct() {
    $this->api = new crumbs_InjectedAPI_hookCrumbsPlugins($this->discoveryOngoing);
  }

  /**
   * @param string $module
   * @param string $key
   * @param string $callback_type
   *   E.g. 'routeParent'.
   *
   * @return callback
   */
  function restoreCallback($module, $key, $callback_type) {
    if (!isset($this->callbacks[$module])) {
      $this->restoreModuleCallbacks($module);
    }
    return isset($this->callbacks[$module][$callback_type][$key])
      ? $this->callbacks[$module][$callback_type][$key]
      : FALSE;
  }

  /**
   * Restore/load all callbacks declared in the given module's implementation of
   * hook_crumbs_plugins(), e.g. via $api->routeParentCallback().
   *
   * @param string $module
   */
  protected function restoreModuleCallbacks($module) {
    $f = $module . '_crumbs_plugins';
    if (!function_exists($f)) {
      // The module may have been disabled in the meantime,
      // or the function has been removed by a developer.
      $this->callbacks[$module] = array();
      return;
    }
    $this->discoveryOngoing = TRUE;
    $this->api->setModule($module);
    $f($this->api);
    $this->discoveryOngoing = FALSE;
    $this->callbacks[$module] = $this->api->getModuleCallbacks($module);
  }
}