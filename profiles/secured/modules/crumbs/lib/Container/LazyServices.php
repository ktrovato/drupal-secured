<?php

/**
 * Little brother of a dependency injection container (DIC)
 *
 * @property crumbs_BreadcrumbBuilder $breadcrumbBuilder
 * @property crumbs_TrailFinder $trailFinder
 * @property crumbs_ParentFinder $parentFinder
 * @property crumbs_PluginEngine $pluginEngine
 * @property crumbs_CallbackRestoration $callbackRestoration
 * @property crumbs_Container_CachedLazyPluginInfo $pluginInfo
 * @property crumbs_Container_LazyPageData $page
 * @property crumbs_Container_LazyDataByPath $trails
 * @property crumbs_Router $router
 */
class crumbs_Container_LazyServices extends crumbs_Container_LazyData {}
