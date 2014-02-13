<?php

/**
 * Class crumbs_Container_CachedLazyPluginInfo
 *
 * @property array $weights
 * @property crumbs_Container_WildcardDataSorted $weightKeeper
 * @property array $defaultWeights
 * @property array $pluginRoutes
 * @property array $userWeights
 * @property crumbs_Container_MultiWildcardData $availableKeysMeta
 *
 * @property array $plugins
 * @property array $pluginsCached
 * @property crumbs_InjectedAPI_hookCrumbsPlugins $discovery
 * @property array $pluginOrder
 * @property array $pluginsSorted
 * @property bool $includePluginFiles
 */
class crumbs_Container_CachedLazyPluginInfo {

  /**
   * @var array
   */
  protected $data = array();

  /**
   * @var crumbs_PluginInfo
   */
  protected $source;

  /**
   * @var array
   */
  protected $keysToCache = array();

  /**
   * @todo Add an interface for $source.
   *   Don't restrict it to crumbs_PluginInfo.
   *
   * @param crumbs_PluginInfo $source
   */
  function __construct($source) {
    $this->source = $source;
    foreach ($source->keysToCache() as $key) {
      $this->keysToCache[$key] = TRUE;
    }

    // Plugin cache is special, because these are objects.
    // If this fails, we want to totally circumvent the cache.
    $callback_before = ini_get('unserialize_callback_func');
    ini_set('unserialize_callback_func', '_crumbs_unserialize_failure');
    try {
      $this->plugins;
    }
    catch (crumbs_UnserializeException $exception) {
      // Don't cache anything this round.
      $this->keysToCache = array();
    }
    ini_set('unserialize_callback_func', $callback_before);
  }

  /**
   * Flush cached data.
   */
  function flushCaches() {
    $this->data = array();
    cache_clear_all('crumbs:', 'cache', TRUE);
  }

  /**
   * @param string $key
   * @return mixed
   * @throws Exception
   */
  function __get($key) {
    if (array_key_exists($key, $this->data)) {
      return $this->data[$key];
    }

    // Load without persistent cache
    if (empty($this->keysToCache[$key])) {
      if (!method_exists($this->source, $key)) {
        throw new Exception("Key $key not supported.");
      }
      $result = $this->source->$key($this);
      return $this->data[$key] = isset($result) ? $result : FALSE;
    }

    // Load from persistent cache
    $cache = cache_get("crumbs:$key");
    if (isset($cache->data)) {
      // We do the serialization manually,
      // to prevent Drupal from intercepting exceptions.
      // However, from previous versions we might still have non-serialized data.
      if (is_array($cache->data)) {
        return $this->data[$key] = $cache->data;
      }
      else {
        return $this->data[$key] = unserialize($cache->data);
      }
    }

    // Load from source, write the result to persistent cache.
    if (!method_exists($this->source, $key)) {
      throw new Exception("Key $key not supported.");
    }
    $result = $this->source->$key($this);
    $this->data[$key] = isset($result) ? $result : FALSE;

    if (!is_array($this->data[$key])) {
      throw new Exception("Only arrays can be cached in crumbs_CachedLazyPluginInfo.");
    }
    cache_set("crumbs:$key", serialize($this->data[$key]));

    return $this->data[$key];
  }

  /**
   * @param string $method
   * @return array
   */
  function basicPluginMethods($method) {

    $key = __FUNCTION__ . ':' . $method;
    if (array_key_exists($key, $this->data)) {
      return $this->data[$key];
    }

    $cache = cache_get("crumbs:$key");
    if (isset($cache->data) && is_array($cache->data)) {
      return $this->data[$key] = $cache->data;
    }

    $this->data[$key] = $this->source->basicPluginMethods($this, $method);
    cache_set("crumbs:$key", $this->data[$key]);
    return $this->data[$key];
  }

  /**
   * @param string $method
   * @param string $route
   * @return array
   */
  function routePluginMethods($method, $route) {

    $key = __FUNCTION__ . ':' . $method . ':' . $route;
    if (array_key_exists($key, $this->data)) {
      return $this->data[$key];
    }

    return $this->data[$key] = $this->source->routePluginMethods($this, $method, $route);
  }

  /**
   * @param string $method
   * @param string $route
   * @return array
   */
  function routePluginMethodsCached($method, $route) {

    $key = __FUNCTION__ . ':' . $method . ':' . $route;
    if (array_key_exists($key, $this->data)) {
      return $this->data[$key];
    }

    $cache = cache_get("crumbs:$key");
    if (isset($cache->data) && is_array($cache->data)) {
      return $this->data[$key] = $cache->data;
    }

    $this->data[$key] = $this->source->routePluginMethodsCached($this, $method, $route);
    cache_set("crumbs:$key", $this->data[$key]);
    return $this->data[$key];
  }
}
