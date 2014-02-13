<?php

/**
 * Data provider object to plug into a crumbs_Container_LazyData.
 */
class crumbs_PluginInfo {

  /**
   * Which keys to load from persistent cache.
   *
   * @return array
   */
  function keysToCache() {
    return array('weights', 'pluginsCached', 'defaultWeights', 'pluginRoutes', 'pluginOrder');
  }

  /**
   * Combination of user-defined weights and default weights
   *
   * @param crumbs_Container_CachedLazyPluginInfo $container
   * @return array
   */
  function weights($container) {
    $weights = $container->defaultWeights;
    foreach ($container->userWeights as $key => $weight) {
      // Make sure to skip NULL values.
      if (isset($weight)) {
        $weights[$key] = $weight;
      }
    }
    return $weights;
  }

  /**
   * Object that can calculate rule weights based on the weight settings.
   * (which are often wildcards)
   *
   * @param crumbs_Container_CachedLazyPluginInfo $container
   * @return crumbs_Container_WildcardDataSorted
   */
  function weightKeeper($container) {
    return new crumbs_Container_WildcardDataSorted($container->weights);
  }

  /**
   * Default weights without the user configuration
   *
   * @param crumbs_Container_CachedLazyPluginInfo $container
   * @return array
   */
  function defaultWeights($container) {
    return $container->discovery->getDefaultValues();
  }

  /**
   * @param crumbs_Container_CachedLazyPluginInfo $container
   * @return array
   */
  function pluginRoutes($container) {
    return $container->discovery->getPluginRoutes();
  }

  /**
   * User-defined weights
   *
   * @param crumbs_Container_CachedLazyPluginInfo $container
   * @return array
   */
  function userWeights($container) {
    $user_weights = variable_get('crumbs_weights', array(
      // The user expects the crumbs.home_title plugin to be dominant.
      // @todo There must be a better way to do this.
      'crumbs.home_title' => 0,
    ));
    // '*' always needs to be set.
    if (!isset($user_weights['*'])) {
      // Put '*' last.
      $max = -1;
      foreach ($user_weights as $k => $v) {
        if ($v >= $max) {
          $max = $v;
        }
      }
      $user_weights['*'] = $max + 1;
    }
    return $user_weights;
  }

  /**
   * @param crumbs_Container_CachedLazyPluginInfo $container
   * @return crumbs_Container_MultiWildcardData
   */
  function availableKeysMeta($container) {
    $op = new crumbs_PluginOperation_describe($container->pluginRoutes);
    /**
     * @var crumbs_PluginInterface $plugin
     */
    foreach ($container->plugins as $plugin_key => $plugin) {
      $op->invoke($plugin, $plugin_key);
    }
    foreach ($container->defaultWeights as $key => $default_weight) {
      $op->setDefaultWeight($key, $default_weight);
    }
    return $op->collectedInfo();
  }

  /**
   * Prepared list of plugins and methods for a given operation.
   *
   * @param crumbs_Container_CachedLazyPluginInfo $container
   * @param string $method
   * @return array
   */
  function basicPluginMethods($container, $method) {
    $type = ('decorateBreadcrumb' === $method) ? 'alter' : 'find';
    $plugin_routes = $container->pluginRoutes;
    $result = array();
    /**
     * @var crumbs_PluginInterface $plugin
     */
    foreach ($container->pluginsSorted[$type] as $plugin_key => $plugin) {
      if (method_exists($plugin, $method)) {
        if (!isset($plugin_routes[$plugin_key])) {
          $result[$plugin_key] = $method;
        }
      }
    }
    return $result;
  }

  /**
   * Prepared list of plugins and methods for a given find operation and route.
   *
   * @param crumbs_Container_CachedLazyPluginInfo $container
   * @param string $method
   * @param string $route
   * @return array
   */
  function routePluginMethods($container, $method, $route) {
    $plugin_methods = $container->routePluginMethodsCached($method, $route);
    return (FALSE !== $plugin_methods) ? $plugin_methods : $container->basicPluginMethods($method);
  }

  /**
   * Prepared list of plugins and methods for a given find operation and route.
   * This is the version to be cached.
   *
   * @param crumbs_Container_CachedLazyPluginInfo $container
   * @param string $method
   * @param string $route
   * @return array|bool
   */
  function routePluginMethodsCached($container, $method, $route) {
    if (empty($route)) {
      return FALSE;
    }
    $only_basic = TRUE;
    $plugin_routes = $container->pluginRoutes;
    $method_suffix = crumbs_Util::buildMethodSuffix($route);
    if (!empty($method_suffix)) {
      $method_with_suffix = $method . '__' . $method_suffix;
    }
    $result = array();
    foreach ($container->pluginOrder['find'] as $plugin_key => $weight) {
      $plugin = $container->plugins[$plugin_key];
      if (isset($method_with_suffix) && method_exists($plugin, $method_with_suffix)) {
        $result[$plugin_key] = $method_with_suffix;
        $only_basic = FALSE;
      }
      elseif (method_exists($plugin, $method)) {
        if (!isset($plugin_routes[$plugin_key])) {
          $result[$plugin_key] = $method;
        }
        elseif ($route === $plugin_routes[$plugin_key]) {
          $only_basic = FALSE;
          $result[$plugin_key] = $method;
        }
      }
    }
    return $only_basic ? FALSE : $result;
  }

  /**
   * Plugins, not sorted, but already with the weights information.
   *
   * @param crumbs_Container_CachedLazyPluginInfo $container
   * @return array
   */
  function plugins($container) {
    // We use a trick to always include the plugin files, even if the plugins
    // are coming from the cache.
    $container->includePluginFiles;
    return $container->pluginsCached;
  }

  /**
   * Plugins, not sorted, but already with the weights information.
   *
   * @param crumbs_Container_CachedLazyPluginInfo $container
   * @return array
   */
  function pluginsCached($container) {
    $plugins = $container->discovery->getPlugins();
    foreach ($plugins as $plugin_key => $plugin) {
      // Let plugins know about the weights, if they want to.
      if (method_exists($plugin, 'initWeights')) {
        $plugin->initWeights($container->weightKeeper->prefixedContainer($plugin_key));
      }
    }
    return $plugins;
  }

  /**
   * Information returned from hook_crumbs_plugins()
   *
   * @param crumbs_Container_CachedLazyPluginInfo $container
   * @return crumbs_InjectedAPI_hookCrumbsPlugins
   */
  function discovery($container) {
    $container->includePluginFiles;
    $discovery_ongoing = TRUE;
    $api = new crumbs_InjectedAPI_hookCrumbsPlugins($discovery_ongoing);
    foreach (module_implements('crumbs_plugins') as $module) {
      $function = $module .'_crumbs_plugins';
      $api->setModule($module);
      $function($api);
    }
    $discovery_ongoing = FALSE;
    $api->finalize();
    return $api;
  }

  /**
   * Order of plugins, for 'find' and 'alter' operations.
   *
   * @param crumbs_Container_CachedLazyPluginInfo $container
   * @return array
   */
  function pluginOrder($container) {

    $order = array(
      'find' => array(),
      'alter' => array(),
    );

    // Sort the plugins, using the weights from weight keeper.
    /**
     * @var crumbs_Container_WildcardData $weight_keeper
     */
    $weight_keeper = $container->weightKeeper;
    foreach ($container->plugins as $plugin_key => $plugin) {
      if ($plugin instanceof crumbs_MultiPlugin) {
        /**
         * @var crumbs_Container_WildcardDataSorted $keeper
         */
        $keeper = $weight_keeper->prefixedContainer($plugin_key);
        $w_find = $keeper->smallestValue();
        if ($w_find !== FALSE) {
          $order['find'][$plugin_key] = $w_find;
        }
        // Multi plugins cannot participate in alter operations.
      }
      else {
        $weight = $weight_keeper->valueAtKey($plugin_key);
        if ($weight !== FALSE) {
          $order['find'][$plugin_key] = $weight;
          $order['alter'][$plugin_key] = $weight;
        }
      }
    }

    // Lowest weight first = highest priority first
    asort($order['find']);

    // Lowest weight last = highest priority last
    arsort($order['alter']);

    return $order;
  }

  /**
   * Sorted plugins for 'find' and 'alter' operations.
   *
   * @param crumbs_Container_CachedLazyPluginInfo $container
   * @return array
   */
  function pluginsSorted($container) {
    $sorted = $container->pluginOrder;
    $plugins = $container->plugins;
    foreach (array('find', 'alter') as $type) {
      foreach ($sorted[$type] as $plugin_key => &$x) {
        $x = $plugins[$plugin_key];
      }
    }
    return $sorted;
  }

  /**
   * Include files in the /plugin/ folder.
   * We use the cache mechanic to make sure this happens exactly once.
   *
   * @param crumbs_Container_CachedLazyPluginInfo $container
   * @return bool
   */
  function includePluginFiles($container) {

    $dir = drupal_get_path('module', 'crumbs') . '/plugins';

    $files = array();
    foreach (scandir($dir) as $candidate) {
      if (preg_match('/^crumbs\.(.+)\.inc$/', $candidate, $m)) {
        if (module_exists($m[1])) {
          $files[$m[1]] = $dir . '/' . $candidate;
        }
      }
    }

    // Organic groups is a special case,
    // because 7.x-2.x behaves different from 7.x-1.x.
    if (1
      && isset($files['og'])
      && !function_exists('og_get_group')
    ) {
      // We are using the og-7.x-1.x branch.
      $files['og'] = $dir . '/crumbs.og.2.inc';
    }

    // Since the directory order may be anything, sort alphabetically.
    ksort($files);
    foreach ($files as $file) {
      require_once $file;
    }

    return TRUE;
  }
}
