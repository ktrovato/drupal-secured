<?php


class crumbs_PluginEngine {

  /**
   * @var crumbs_Debug_CandidateLogger
   */
  protected $candidateLogger;

  /**
   * @var crumbs_Container_CachedLazyPluginInfo
   */
  protected $pluginInfo;

  /**
   * @var crumbs_Router
   */
  protected $router;

  /**
   * @var array
   */
  protected $plugins;

  /**
   * @var crumbs_Container_WildcardDataSorted
   */
  protected $weightKeeper;

  /**
   * @param crumbs_Container_CachedLazyPluginInfo $plugin_info
   * @param crumbs_Router $router
   */
  function __construct($plugin_info, $router) {
    $this->pluginInfo = $plugin_info;
    $this->router = $router;
    // These are for quicker access.
    $this->plugins = $plugin_info->plugins;
    $this->weightKeeper = $plugin_info->weightKeeper;
  }

  /**
   * @param crumbs_Debug_CandidateLogger $candidate_logger
   */
  function setCandidateLogger($candidate_logger) {
    $this->candidateLogger = $candidate_logger;
  }

  /**
   * Ask applicable plugins to "decorate" (alter) the breadcrumb.
   *
   * @param array $breadcrumb
   */
  function decorateBreadcrumb($breadcrumb) {
    $plugin_methods = $this->pluginInfo->basicPluginMethods('decorateBreadcrumb');
    foreach ($plugin_methods as $plugin_key => $method) {
      /**
       * @var crumbs_PluginInterface $plugin
       */
      $plugin = $this->plugins[$plugin_key];
      if (!method_exists($plugin, 'decorateBreadcrumb')) {
        // This means the code has changed, without the cache being cleared.
        // It is the user's responsibility to clear the cache.
        // Until then, we simply ignore and move on.
        continue;
      }
      $plugin->decorateBreadcrumb($breadcrumb);
    }
  }

  /**
   * Invoke all relevant plugins to find the parent for a given path.
   *
   * @param string $path
   * @param array $item
   * @return mixed|null|void
   */
  function findParent($path, $item) {
    $plugin_methods = $this->pluginInfo->routePluginMethods('findParent', $item['route']);
    $result = $this->find($plugin_methods, array($path, $item), TRUE);
    if ($this->candidateLogger) {
      $this->candidateLogger->endFindParent($path, $item);
    }
    return $result;
  }

  /**
   * @param string $parent_raw
   * @return string
   */
  protected function processFindParent($parent_raw) {
    if ($this->router->urlIsExternal($parent_raw)) {
      // Always discard external paths.
      return NULL;
    }
    return $this->router->getNormalPath($parent_raw);
  }

  /**
   * Invoke all relevant plugins to find the title for a given path.
   *
   * @param string $path
   * @param array $item
   * @param array $breadcrumb
   * @return mixed|null|void
   */
  function findTitle($path, $item, $breadcrumb) {
    $plugin_methods = $this->pluginInfo->routePluginMethods('findTitle', $item['route']);
    $result = $this->find($plugin_methods, array($path, $item, $breadcrumb), FALSE);
    if ($this->candidateLogger) {
      $this->candidateLogger->endFindTitle($path, $item, $breadcrumb);
    }
    return $result;
  }

  /**
   * Invoke all relevant plugins to find title or parent for a given path.
   *
   * @param array $plugin_methods
   * @param array $args
   * @param bool $processFindParent
   * @return mixed|null|void
   */
  protected function find($plugin_methods, $args, $processFindParent = FALSE) {
    $best_candidate = NULL;
    $best_candidate_weight = 999999;
    $best_candidate_key = NULL;
    foreach ($plugin_methods as $plugin_key => $method) {
      if (empty($this->plugins[$plugin_key])) {
        // Probably need a cache clear.
        continue;
      }
      $plugin = $this->plugins[$plugin_key];
      if ($plugin instanceof crumbs_MultiPlugin) {
        // That's a MultiPlugin
        /**
         * @var crumbs_Container_WildcardDataSorted $keeper
         */
        $keeper = $this->weightKeeper->prefixedContainer($plugin_key);
        if ($best_candidate_weight <= $keeper->smallestValue()) {
          return $best_candidate;
        }
        if (!method_exists($plugin, $method)) {
          // This means the code has changed, without the cache being cleared.
          // It is the user's responsibility to clear the cache.
          // Until then, we simply ignore and move on.
          continue;
        }
        $candidates = call_user_func_array(array($plugin, $method), $args);
        if (!empty($candidates)) {
          foreach ($candidates as $candidate_key => $candidate_raw) {
            if (isset($candidate_raw)) {
              $candidate_weight = $keeper->valueAtKey($candidate_key);
              if (FALSE === $candidate_weight) {
                continue;
              }
              $candidate = $processFindParent ? $this->processFindParent($candidate_raw) : $candidate_raw;
              if ($this->candidateLogger) {
                $this->candidateLogger->addCandidate("$plugin_key.$candidate_key", $candidate_weight, $candidate_raw, $candidate);
              }
              if ($best_candidate_weight > $candidate_weight && isset($candidate)) {
                $best_candidate = $candidate;
                $best_candidate_weight = $candidate_weight;
                if ($this->candidateLogger) {
                  $this->candidateLogger->setBestCandidateKey("$plugin_key.$candidate_key");
                }
              }
            }
          }
        }
      }
      elseif ($plugin instanceof crumbs_MonoPlugin) {
        // That's a MonoPlugin
        $candidate_weight = $this->weightKeeper->valueAtKey($plugin_key);
        if ($best_candidate_weight <= $candidate_weight) {
          return $best_candidate;
        }
        if (!method_exists($plugin, $method)) {
          // This means the code has changed, without the cache being cleared.
          // It is the user's responsibility to clear the cache.
          // Until then, we simply ignore and move on.
          continue;
        }
        $candidate_raw = call_user_func_array(array($plugin, $method), $args);
        if (isset($candidate_raw)) {
          $candidate = $processFindParent ? $this->processFindParent($candidate_raw) : $candidate_raw;
          if ($this->candidateLogger) {
            $this->candidateLogger->addCandidate($plugin_key, $candidate_weight, $candidate_raw, $candidate);
          }
          if (isset($candidate)) {
            $best_candidate = $candidate;
            $best_candidate_weight = $candidate_weight;
            if ($this->candidateLogger) {
              $this->candidateLogger->setBestCandidateKey($plugin_key);
            }
          }
        }
      }
    }
    return $best_candidate;
  }
}
