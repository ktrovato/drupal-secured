<?php


/**
 * API object to be used as an argument for hook_crumbs_plugins()
 * This is a sandbox class, currently not used..
 */
class crumbs_InjectedAPI_hookCrumbsPlugins {

  /**
   * @var string $module
   *   The module for the current hook implementation.
   */
  protected $module;

  /**
   * @var crumbs_PluginInterface[]
   *
   */
  protected $plugins = array();

  /**
   * @var array
   *   Nested array of callbacks, with this format:
   *   $this->callbacks[$this->module][$callbackType][$key] = $callback;
   *   Where $callbackType can be 'routeParent', 'routeTitle', 'entityParent',
   *   or 'entityTitle'.
   */
  protected $callbacks = array();

  /**
   * @var string[]
   *   Array of routes, with this format:
   *   $this->pluginRoutes[$key] = $route
   */
  protected $pluginRoutes = array();

  /**
   * @var array
   *   Default weights for some plugin keys, with this format:
   *   $this->defaultValues[$key] = $weight.
   */
  protected $defaultValues = array();

  /**
   * @var array
   *   Known routes for entity types, e.g.:
   *   $this->entityRoutes['node/%'] = array('node', 'type', 'Node type');
   */
  protected $entityRoutes = array();

  /**
   * @var array
   *   Collection of entity plugins. Format:
   *   $this->entityPlugins[$type][$module . '.' . $key] = array($entity_plugin, $types);
   */
  protected $entityPlugins = array();

  /**
   * @var bool&
   *   While TRUE, some methods are blocked.
   */
  protected $discoveryOngoing;

  /**
   * @param bool $discovery_ongoing
   *   Switch to prevent some methods from being called from hook
   *   implementations.
   */
  function __construct(&$discovery_ongoing) {
    $this->discoveryOngoing = &$discovery_ongoing;
  }

  /**
   * @return array
   * @throws Exception
   */
  function getPlugins() {
    if ($this->discoveryOngoing) {
      throw new Exception("getPlugins() cannot be called from an implementation of hook_crumbs_plugins().");
    }
    return $this->plugins;
  }

  /**
   * @return array
   * @throws Exception
   */
  function getPluginRoutes() {
    if ($this->discoveryOngoing) {
      throw new Exception(__METHOD__ . "() cannot be called from an implementation of hook_crumbs_plugins().");
    }
    return $this->pluginRoutes;
  }

  /**
   * @return array
   * @throws Exception
   */
  function getDefaultValues() {
    if ($this->discoveryOngoing) {
      throw new Exception(__METHOD__ . "() cannot be called from an implementation of hook_crumbs_plugins().");
    }
    return $this->defaultValues;
  }

  /**
   * @param string $module
   * @return array
   * @throws Exception
   */
  function getModuleCallbacks($module) {
    if ($this->discoveryOngoing) {
      throw new Exception(__METHOD__ . "() cannot be called from an implementation of hook_crumbs_plugins().");
    }
    return isset($this->callbacks[$module]) ? $this->callbacks[$module] : array();
  }

  /**
   * @throws Exception
   */
  function finalize() {
    if ($this->discoveryOngoing) {
      throw new Exception(__METHOD__ . "() cannot be called from an implementation of hook_crumbs_plugins().");
    }

    $build = array();
    foreach ($this->entityPlugins as $type => $plugins) {
      foreach ($plugins as $key => $y) {
        list($entity_plugin, $types) = $y;
        if (!isset($types)) {
          foreach ($this->entityRoutes as $route => $x) {
            list($entity_type) = $x;
            $build[$entity_type][$type][$key . '.' . $entity_type] = $entity_plugin;
          }
        }
        elseif (is_array($types)) {
          foreach ($types as $entity_type) {
            $build[$entity_type][$type][$key . '.' . $entity_type] = $entity_plugin;
          }
        }
        elseif (is_string($types)) {
          $entity_type = $types;
          $build[$entity_type][$type][$key] = $entity_plugin;
        }
      }
    }

    foreach ($this->entityRoutes as $route => $x) {
      list($entity_type, $bundle_key, $bundle_name) = $x;
      if (!empty($build[$entity_type])) {
        foreach ($build[$entity_type] as $type => $plugins) {
          foreach ($plugins as $key => $entity_plugin) {
            if ('parent' === $type) {
              $this->plugins[$key] = new crumbs_MultiPlugin_EntityParent($entity_plugin, $entity_type, $bundle_key, $bundle_name);
            }
            else {
              $this->plugins[$key] = new crumbs_MultiPlugin_EntityTitle($entity_plugin, $entity_type, $bundle_key, $bundle_name);
            }
            $this->pluginRoutes[$key] = $route;
          }
        }
      }
    }
  }

  /**
   * This is typically called before each invocation of hook_crumbs_plugins(),
   * to let the object know about the module implementing the hook.
   * Modules can call this directly if they want to let other modules talk to
   * the API object.
   *
   * @param string $module
   *   The module name.
   */
  function setModule($module) {
    $this->module = $module;
  }

  /**
   * Register an entity route.
   * This should be called by those modules that define entity types and routes.
   *
   * @param string $entity_type
   * @param string $route
   * @param string $bundle_key
   * @param string $bundle_name
   */
  function entityRoute($entity_type, $route, $bundle_key, $bundle_name) {
    $this->entityRoutes[$route] = array($entity_type, $bundle_key, $bundle_name);
  }

  /**
   * Register an entity parent plugin.
   *
   * @param string $key
   * @param string|crumbs_EntityPlugin $entity_plugin
   * @param array $types
   *   An array of entity types, or a single entity type, or NULL to allow all
   *   entity types.
   */
  function entityParentPlugin($key, $entity_plugin = NULL, $types = NULL) {
    $this->entityPlugin('parent', $key, $entity_plugin, $types);
  }

  /**
   * Register a callback that will determine a parent path for a breadcrumb item
   * with an entity route. The behavior will be available for all known entity
   * routes, e.g. node/% or taxonomy/term/%, with different plugin keys.
   *
   * @param string $key
   * @param callable $callback
   * @param array $types
   *   An array of entity types, or a single entity type, or NULL to allow all
   *   entity types.
   */
  function entityParentCallback($key, $callback, $types = NULL) {
    $entity_plugin = new crumbs_EntityPlugin_Callback($callback, $this->module, $key, 'entityParent');
    $this->entityPlugin('parent', $key, $entity_plugin, $types);
    $this->callbacks[$this->module]['entityParent'][$key] = $callback;
  }

  /**
   * Register an entity title plugin.
   *
   * @param string $key
   * @param string|crumbs_EntityPlugin $entity_plugin
   * @param array $types
   *   An array of entity types, or a single entity type, or NULL to allow all
   *   entity types.
   */
  function entityTitlePlugin($key, $entity_plugin = NULL, $types = NULL) {
    $this->entityPlugin('title', $key, $entity_plugin, $types);
  }

  /**
   * Register a callback that will determine a title for a breadcrumb item with
   * an entity route. The behavior will be available for all known entity
   * routes, e.g. node/% or taxonomy/term/%, with different plugin keys.
   *
   * @param string $key
   *   The plugin key under which this callback will be listed on the weights
   *   configuration form.
   * @param callback $callback
   *   The callback, e.g. an anonymous function. The signature must be
   *   $callback(stdClass $entity, string $entity_type, string $distinction_key),
   *   like the findCandidate() method of a typical crumbs_EntityPlugin.
   * @param array $types
   *   An array of entity types, or a single entity type, or NULL to allow all
   *   entity types.
   */
  function entityTitleCallback($key, $callback, $types = NULL) {
    $entity_plugin = new crumbs_EntityPlugin_Callback($callback, $this->module, $key, 'entityTitle');
    $this->entityPlugin('title', $key, $entity_plugin, $types);
    $this->callbacks[$this->module]['entityTitle'][$key] = $callback;
  }

  /**
   * @param string $type
   *   Either 'title' or 'parent'.
   * @param string $key
   *   The plugin key under which this callback will be listed on the weights
   *   configuration form.
   * @param string|crumbs_EntityPlugin $entity_plugin
   * @param string[]|string|NULL $types
   *   An array of entity types, or a single entity type, or NULL to allow all
   *   entity types.
   */
  protected function entityPlugin($type, $key, $entity_plugin, $types) {
    if (!isset($entity_plugin)) {
      $class = $this->module . '_CrumbsEntityPlugin';
      $entity_plugin = new $class();
    }
    elseif (is_string($entity_plugin)) {
      $class = $this->module . '_CrumbsEntityPlugin_' . $entity_plugin;
      $entity_plugin = new $class();
    }
    if ($entity_plugin instanceof crumbs_EntityPlugin) {
      $this->entityPlugins[$type][$this->module . '.' . $key] = array($entity_plugin, $types);
    }
  }

  /**
   * Register a "Mono" plugin.
   * That is, a plugin that defines exactly one rule.
   *
   * @param string $key
   *   Rule key, relative to module name.
   * @param Crumbs_MonoPlugin $plugin
   *   Plugin object. Needs to implement crumbs_MultiPlugin.
   *   Or NULL, to have the plugin object automatically created based on a
   *   class name guessed from the $key parameter and the module name.
   * @throws Exception
   */
  function monoPlugin($key = NULL, crumbs_MonoPlugin $plugin = NULL) {
    if (!isset($key)) {
      $class = $this->module . '_CrumbsMonoPlugin';
      $plugin = new $class();
      $key = $this->module;
    }
    elseif (!isset($plugin)) {
      $class = $this->module . '_CrumbsMonoPlugin_' . $key;
      $plugin = new $class();
      $key = $this->module . '.' . $key;
    }
    else {
      $class = get_class($plugin);
      $key = $this->module . '.' . $key;
    }
    if (!($plugin instanceof crumbs_MonoPlugin)) {
      throw new Exception("$class must implement class_MonoPlugin.");
    }
    if (isset($this->plugins[$key])) {
      throw new Exception("There already is a plugin with key '$key'.");
    }
    $this->plugins[$key] = $plugin;
  }

  /**
   * @param string $route
   * @param string $key
   * @param crumbs_MonoPlugin $plugin
   */
  function routeMonoPlugin($route, $key = NULL, crumbs_MonoPlugin $plugin = NULL) {
    $this->monoPlugin($key, $plugin);
    $plugin_key = empty($key) ? $this->module : $this->module . '.' . $key;
    $this->pluginRoutes[$plugin_key] = $route;
  }

  /**
   * Register a "Multi" plugin.
   * That is, a plugin that defines more than one rule.
   *
   * @param $key
   *   Rule key, relative to module name.
   * @param crumbs_MultiPlugin $plugin
   *   Plugin object. Needs to implement crumbs_MultiPlugin.
   *   Or NULL, to have the plugin object automatically created based on a
   *   class name guessed from the $key parameter and the module name.
   * @throws Exception
   */
  function multiPlugin($key, crumbs_MultiPlugin $plugin = NULL) {
    if (!isset($key)) {
      $class = $this->module . '_CrumbsMultiPlugin';
      $plugin = new $class();
      $plugin_key = $this->module;
    }
    elseif (!isset($plugin)) {
      $class = $this->module . '_CrumbsMultiPlugin_' . $key;
      $plugin = new $class();
      $plugin_key = $this->module . '.' . $key;
    }
    else {
      $class = get_class($plugin);
      $plugin_key = $this->module . '.' . $key;
    }
    if (!($plugin instanceof crumbs_MultiPlugin)) {
      throw new Exception("$class must implement class_MultiPlugin.");
    }
    $this->plugins[$plugin_key] = $plugin;
  }

  /**
   * @param string $route
   * @param string $key
   * @param crumbs_MultiPlugin $plugin
   */
  function routeMultiPlugin($route, $key = NULL, crumbs_MultiPlugin $plugin = NULL) {
    $this->multiPlugin($key, $plugin);
    $plugin_key = empty($key) ? $this->module : $this->module . '.' . $key;
    $this->pluginRoutes[$plugin_key] = $route;
  }

  /**
   * @param string $route
   * @param string $key
   * @param string $parent_path
   */
  function routeParentPath($route, $key, $parent_path) {
    $this->routeMonoPlugin($route, $key, new crumbs_MonoPlugin_FixedParentPath($parent_path));
  }

  /**
   * Register a callback that will determine a parent for a breadcrumb item.
   *
   * @param string $route
   *   The route where this callback should be used, e.g. "node/%".
   * @param string $key
   *   The plugin key under which this callback will be listed on the weights
   *   configuration form.
   * @param callback $callback
   *   The callback, e.g. an anonymous function. The signature must be
   *   $callback(string $path, array $item), like the findParent() method of
   *   a typical crumbs_MonoPlugin.
   */
  function routeParentCallback($route, $key, $callback) {
    $this->routeMonoPlugin($route, $key, new crumbs_MonoPlugin_ParentPathCallback($callback, $this->module, $key));
    $this->callbacks[$this->module]['routeParent'][$key] = $callback;
  }

  /**
   * @param string $route
   * @param string $key
   * @param string $title
   */
  function routeTranslateTitle($route, $key, $title) {
    $this->routeMonoPlugin($route, $key, new crumbs_MonoPlugin_TranslateTitle($title));
  }

  /**
   * Register a callback that will determine a title for a breadcrumb item.
   *
   * @param string $route
   *   The route where this callback should be used, e.g. "node/%".
   * @param string $key
   *   The plugin key under which this callback will be listed on the weights
   *   configuration form.
   * @param callback $callback
   *   The callback, e.g. an anonymous function. The signature must be
   *   $callback(string $path, array $item), like the findParent() method of
   *   a typical crumbs_MonoPlugin.
   */
  function routeTitleCallback($route, $key, $callback) {
    $this->routeMonoPlugin($route, $key, new crumbs_MonoPlugin_TitleCallback($callback, $this->module, $key));
    $this->callbacks[$this->module]['routeTitle'][$key] = $callback;
  }

  /**
   * @param string $route
   * @param string $key
   */
  function routeSkipItem($route, $key) {
    $this->routeMonoPlugin($route, $key, new crumbs_MonoPlugin_SkipItem());
  }

  /**
   * Set specific rules as disabled by default.
   *
   * @param array|string $keys
   *   Array of keys, relative to the module name, OR
   *   a single string key, relative to the module name.
   */
  function disabledByDefault($keys = NULL) {
    if (is_array($keys)) {
      foreach ($keys as $key) {
        $this->_disabledByDefault($key);
      }
    }
    else {
      $this->_disabledByDefault($keys);
    }
  }

  /**
   * @param string|NULL $key
   */
  protected function _disabledByDefault($key) {
    $key = isset($key) ? ($this->module . '.' . $key) : $this->module;
    $this->defaultValues[$key] = FALSE;
  }
}
