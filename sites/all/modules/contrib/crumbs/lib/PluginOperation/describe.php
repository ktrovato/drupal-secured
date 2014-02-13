<?php

/**
 * This class uses the PluginOperation pattern, but it does not implement any of
 * the PluginOperation interfaces. This is because it is not supposed to be used
 * with the PluginEngine, but rather from a custom function (see above).
 */
class crumbs_PluginOperation_describe {

  //                                                                Initial data
  // ---------------------------------------------------------------------------

  /**
   * @var array
   */
  protected $pluginRoutes;

  //                                                              Collected data
  // ---------------------------------------------------------------------------

  /**
   * @var array
   */
  protected $keys = array('*' => TRUE);

  /**
   * @var array
   */
  protected $keysByPlugin = array();

  /**
   * @var array
   */
  protected $collectedInfo = array();

  //                                                             State variables
  // ---------------------------------------------------------------------------

  /**
   * @var string
   *   Temporary variable.
   */
  protected $pluginKey;

  /**
   * @var crumbs_InjectedAPI_describeMonoPlugin
   */
  protected $injectedAPI_mono;

  /**
   * @var crumbs_InjectedAPI_describeMultiPlugin
   */
  protected $injectedAPI_multi;

  /**
   * @param array $plugin_routes
   */
  function __construct($plugin_routes) {
    $this->injectedAPI_mono = new crumbs_InjectedAPI_describeMonoPlugin($this);
    $this->injectedAPI_multi = new crumbs_InjectedAPI_describeMultiPlugin($this);
    $this->pluginRoutes = $plugin_routes;
  }

  /**
   * @param crumbs_PluginInterface $plugin
   * @param string $plugin_key
   */
  function invoke($plugin, $plugin_key) {
    $this->pluginKey = $plugin_key;

    $basic_methods = array();
    $route_methods = array();
    $rf_class = new ReflectionClass($plugin);
    foreach ($rf_class->getMethods() as $rf_method) {
      $method = $rf_method->name;
      $pos = strpos($method, '__');
      if (FALSE !== $pos && 0 !== $pos) {
        $method_base = substr($method, 0, $pos);
        if (in_array($method_base, array('findParent', 'findTitle'))) {
          $method_suffix = substr($method, $pos + 2);
          $route = crumbs_Util::routeFromMethodSuffix($method_suffix);
          $route_methods[$method_base][$route] = $method;
        }
      }
      else {
        if (in_array($method, array('findParent', 'findTitle', 'decorateBreadcrumb'))) {
          if (!isset($this->pluginRoutes[$plugin_key])) {
            $basic_methods[$method] = $method;
          }
          else {
            $route = $this->pluginRoutes[$plugin_key];
            if (!isset($route_methods[$method][$route])) {
              $route_methods[$method][$route] = $method;
            }
          }
        }
      }
    }

    if ($plugin instanceof crumbs_MonoPlugin) {
      $this->collectedInfo['basicMethods'][$plugin_key] = $basic_methods;
      $this->collectedInfo['routeMethods'][$plugin_key] = $route_methods;
      $result = $plugin->describe($this->injectedAPI_mono);
      if (is_string($result)) {
        $this->setTitle($result);
      }
    }
    elseif ($plugin instanceof crumbs_MultiPlugin) {
      $this->collectedInfo['basicMethods']["$plugin_key.*"] = $basic_methods;
      $this->collectedInfo['routeMethods']["$plugin_key.*"] = $route_methods;
      $result = $plugin->describe($this->injectedAPI_multi);
      if (is_array($result)) {
        foreach ($result as $key_suffix => $title) {
          $this->addRule($key_suffix, $title);
        }
      }
    }
  }

  /**
   * To be called from crumbs_InjectedAPI_describeMultiPlugin::addRule()
   *
   * @param string $key_suffix
   * @param string $title
   */
  function addRule($key_suffix, $title) {
    $key = $this->pluginKey . '.' . $key_suffix;
    $this->_addRule($key);
    $this->_addDescription($key, $title );
  }

  /**
   * Add a description at an arbitrary wildcard key.
   * To be called from crumbs_InjectedAPI_describeMultiPlugin::addDescription()
   *
   * @param string $description
   * @param string $key_suffix
   */
  function addDescription($description, $key_suffix) {
    if (isset($key_suffix)) {
      $key = $this->pluginKey . '.' . $key_suffix;
    }
    else {
      $key = $this->pluginKey;
    }
    $this->_addDescription($key, $description);
  }

  /**
   * @param array $paths
   * @param string $key_suffix
   */
  function setRoutes(array $paths, $key_suffix) {
    if (isset($key_suffix)) {
      $key = $this->pluginKey . '.' . $key_suffix;
    }
    else {
      $key = $this->pluginKey;
    }
    $this->collectedInfo['routes'][$key] = $paths;
  }

  /**
   * @param string $key
   * @param string $description
   */
  protected function _addDescription($key, $description) {
    $this->collectedInfo['descriptions'][$key][] = $description;
  }

  /**
   * To be called from crumbs_InjectedAPI_describeMonoPlugin::setTitle()
   *
   * @param string $title
   */
  function setTitle($title) {
    $this->_addRule($this->pluginKey);
    $this->_addDescription($this->pluginKey, $title);
  }

  /**
   * @param string $key
   */
  protected function _addRule($key) {
    $fragments = explode('.', $key);
    $partial_key = array_shift($fragments);
    while (TRUE) {
      if (empty($fragments)) break;
      $wildcard_key = $partial_key .'.*';
      $this->keys[$wildcard_key] = TRUE;
      $this->keysByPlugin[$this->pluginKey][$wildcard_key] = TRUE;
      $partial_key .= '.'. array_shift($fragments);
    }
    $this->keys[$key] = $key;
    $this->keysByPlugin[$this->pluginKey][$key] = $key;
  }

  /**
   * @return array
   */
  function getKeys() {
    return $this->keys;
  }

  /**
   * @return array
   */
  function getKeysByPlugin() {
    return $this->keysByPlugin;
  }

  /**
   * @param string $key
   * @param int $weight
   */
  function setDefaultWeight($key, $weight) {
    $this->keys[$key] = $key;
  }

  /**
   * @return crumbs_Container_MultiWildcardData
   */
  function collectedInfo() {
    $container = new crumbs_Container_MultiWildcardData($this->keys);
    $container->__set('key', $this->keys);
    foreach ($this->collectedInfo as $key => $data) {
      $container->__set($key, $data);
    }
    return $container;
  }
}
