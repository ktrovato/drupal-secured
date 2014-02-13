<?php


/**
 * Implements hook_crumbs_plugins().
 *
 * @param crumbs_InjectedAPI_hookCrumbsPlugins $api
 */
function views_crumbs_plugins($api) {
  $api->multiPlugin('argTitle');
}


class views_CrumbsMultiPlugin_argTitle implements crumbs_MultiPlugin_FindTitleInterface {

  /**
   * {@inheritdoc}
   */
  function describe($api) {
    // We try to get all views pages but avoid views_get_all_view() for performance.
    $q = db_select('menu_router', 'mr');
    $q->condition('page_callback', 'views_page');
    $q->fields('mr', array('path', 'page_arguments'));
    $paths_all = array();
    foreach ($q->execute() as $row) {
      $args = unserialize($row->page_arguments);
      if (count($args) > 2) {
        list($view_name, $view_display_id) = $args;
        $key = "$view_name.$view_display_id";
        $paths_all[$key][] = $row->path;
      }
    }
    foreach ($paths_all as $key => $paths) {
      $api->addRule($key, $key);
      $api->setRoutes($paths, $key);
    }
  }

  /**
   * {@inheritdoc}
   */
  function findTitle($path, $item) {

    if ('views_page' !== $item['page_callback']) {
      return;
    }

    if (count($item['page_arguments']) < 3) {
      return;
    }

    if (isset($item['title']) && is_string($item['title']) && '' !== $item['title']) {
      return;
    }

    $args = $item['page_arguments'];
    $view_name = array_shift($args);
    $view_display_id = array_shift($args);

    // Build and initialize the view.
    $view = views_get_view($view_name);
    $view->set_display($view_display_id);
    $view->set_arguments($args);

    // Trigger the argument calculation by calling build_title().
    $view->build_title();

    // Check the last argument for a breadcrumb item title.
    $argument = $view->argument;
    while (!empty($argument)) {
      $last_arg = array_pop($argument);
      if (1
        && is_object($last_arg)
        && !$last_arg->is_exception()
        && isset($last_arg->argument)
      ) {
        if ($last_arg_title = $last_arg->get_title()) {
          // Use decode_entities() to undo duplicate check_plain().
          // See https://drupal.org/comment/7916895#comment-7916895
          return array("$view_name.$view_display_id" => decode_entities($last_arg_title));
        }
        break;
      }
    }
  }
}
