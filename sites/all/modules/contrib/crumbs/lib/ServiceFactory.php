<?php


class crumbs_ServiceFactory {

  /**
   * A service that can build a breadcrumb from a trail.
   *
   * Available as crumbs('breadcrumbBuilder').
   *
   * @param crumbs_Container_LazyServices $cache
   * @return crumbs_BreadcrumbBuilder
   */
  function breadcrumbBuilder($cache) {
    return new crumbs_BreadcrumbBuilder($cache->pluginEngine);
  }

  /**
   * A service that can build a trail for a given path.
   *
   * Available as crumbs('trailFinder').
   *
   * @param crumbs_Container_LazyServices $cache
   * @return crumbs_TrailFinder
   */
  function trailFinder($cache) {
    return new crumbs_TrailFinder($cache->parentFinder, $cache->router);
  }

  /**
   * A service that attempts to find a parent path for a given path.
   *
   * Available as crumbs('parentFinder').
   *
   * @param crumbs_Container_LazyServices $cache
   * @return crumbs_ParentFinder
   */
  function parentFinder($cache) {
    return new crumbs_ParentFinder($cache->pluginEngine, $cache->router);
  }

  /**
   * A service that knows all plugins and their configuration/weights,
   * and can run plugin operations on those plugins.
   *
   * Available as crumbs('pluginEngine').
   *
   * @param crumbs_Container_LazyServices $cache
   * @return crumbs_PluginEngine
   */
  function pluginEngine($cache) {
    return new crumbs_PluginEngine($cache->pluginInfo, $cache->router);
  }

  /**
   * @param crumbs_Container_LazyServices $cache
   * @return crumbs_CallbackRestoration
   */
  function callbackRestoration($cache) {
    return new crumbs_CallbackRestoration();
  }

  /**
   * A service that knows all plugins and their configuration/weights.
   *
   * Available as crumbs('pluginInfo').
   *
   * @param crumbs_Container_LazyServices $cache
   * @return crumbs_Container_CachedLazyPluginInfo
   */
  function pluginInfo($cache) {
    $source = new crumbs_PluginInfo();
    return new crumbs_Container_CachedLazyPluginInfo($source);
  }

  /**
   * Service that can provide information related to the current page.
   *
   * Available as crumbs('page').
   *
   * @param crumbs_Container_LazyServices $cache
   * @return crumbs_Container_LazyPageData
   */
  function page($cache) {
    $source = new crumbs_CurrentPageInfo($cache->trails, $cache->breadcrumbBuilder, $cache->router);
    return new crumbs_Container_LazyPageData($source);
  }

  /**
   * Service that can provide/calculate trails for different paths.
   *
   * Available as crumbs('trails').
   *
   * @param crumbs_Container_LazyServices $cache
   * @return crumbs_Container_LazyDataByPath
   */
  function trails($cache) {
    return new crumbs_Container_LazyDataByPath($cache->trailFinder);
  }

  /**
   * @param crumbs_Container_LazyServices $cache
   * @return crumbs_Router
   */
  function router($cache) {
    return new crumbs_Router();
  }
}
