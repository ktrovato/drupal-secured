<?php

/**
 * Page callback for 'admin/structure/crumbs/debug'.
 *
 * @return string
 *   The rendered HTML for the debug page.
 */
function crumbs_debug_page() {
  drupal_set_title('Crumbs debug');

  $path_to_test = '';
  if (isset($_GET['path_to_test'])) {
    $path_to_test = $_GET['path_to_test'];
  }
  elseif (!empty($_SESSION['crumbs.admin.debug.history'])) {
    foreach ($_SESSION['crumbs.admin.debug.history'] as $path => $true) {
      if ('admin' !== substr($path, 0, 5)) {
        $path_to_test = $path;
      }
      elseif ('admin/structure/crumbs' !== substr($path, 0, 22)) {
        $admin_path_to_test = $path;
      }
    }
    if (empty($path_to_test) && !empty($admin_path_to_test)) {
      $path_to_test = $admin_path_to_test;
    }
  }

  $path_checked = check_plain($path_to_test);
  $form_action = url('admin/structure/crumbs/debug');

  $input_html = <<<EOT
<input id="crumbs-admin-debug-path" type="text" class="form-text" size="40" name="path_to_test" value="$path_checked" />
<input type="submit" value="Go" class="form-submit" />
EOT;
  $input_html = t('Breadcrumb for: !text_field', array('!text_field' => $input_html));
  $text = <<<EOT
<p>This page allows to have a look "behind the scenes", so you can analyse
which crumbs plugins and rules are responsible for the "crumbs parent" to a
given system path.</p>
<p>Crumbs will "ask" different plugins, until one of them responds with a parent
path candidate. The candidate with the highest weight wins.</p>
<p>Crumbs will stop invoking any more plugins, once it is clear that further
candidates will only have smaller weights.</p>
EOT;
  $text = t($text);

  $html = <<<EOT
    <form method="get" action="$form_action">
      $text
      <label for="path">$input_html</label>
    </form>
EOT;

  if (strlen($path_to_test)) {
    $path_to_test = drupal_get_normal_path($path_to_test);
    $html .= _crumbs_admin_debug_matrix($path_to_test);
  }

  if (!empty($_SESSION['crumbs.admin.debug.history'])) {
    $recently_visited = '';
    foreach (array_reverse($_SESSION['crumbs.admin.debug.history']) as $path => $true) {
      if ('admin/structure/crumbs/debug' !== substr($path, 0, 28)) {
        // We can't use l() directly, since this would add an "active" class.
        $url = url('admin/structure/crumbs/debug', array('query' => array('path_to_test' => $path)));
        $link = l($path, $url, array('external' => TRUE));
        $recently_visited .= '<li>' . $link . '</li>';
      }
    }
    if ($recently_visited) {
      $html .= t('Recently visited') . ':<ol>' . $recently_visited . '</ol>';
    }
  }

  return $html;
}

/**
 * Helper function for crumbs_admin_debug_page().
 *
 * @param string $path_to_test
 *   Test path to build a Crumbs breadcrumb.
 * @return string
 *   The debug matrix as rendered html.
 */
function _crumbs_admin_debug_matrix($path_to_test) {

  // Create a local version of the service factory.
  $service_factory = new crumbs_ServiceFactory();
  $services = new crumbs_Container_LazyServices($service_factory);
  $candidate_logger = new crumbs_Debug_CandidateLogger();
  $services->pluginEngine->setCandidateLogger($candidate_logger);
  $page_info = $services->page;
  $page_info->set('path', $path_to_test);
  // Trigger breadcrumb calculation.
  $trail = $page_info->trail;
  $breadcrumb_items = $page_info->rawBreadcrumbItems;
  $titles = array();
  foreach ($breadcrumb_items as $item) {
    $path = $item['link_path'];
    if (isset($trail[$path]) && isset($item['title'])) {
      $titles[$path] = $item['title'];
    }
  }

  list($matrix, $best_cells, $weights) = $candidate_logger->getAsMatrix(array_reverse($trail));

  $matrix_thead_tr_first = '<td></td><td></td>';
  $matrix_thead_tr_second = '<td></td><td></td>';
  $matrix_thead_tr_third = '<th>' . t('Candidate key') . '</th><th>' . t('Weight') . '</th>';

  foreach (array_reverse(array_keys($trail)) as $i => $path) {
    $title = isset($titles[$path]) ? l($titles[$path], $path) : FALSE;
    $separator = ($i > 0) ? '&laquo;' : ':';
    $matrix_thead_tr_first .= '<td rowspan="' . (count($matrix) + 3) . '">' . $separator . '</td>';
    $matrix_thead_tr_third .= '<th>' . t('Title') . '</th>';

    if ($i + 1 < count($trail)) {
      $td_opening = '<td colspan="2"';
      $path_eff = $path;
      $matrix_thead_tr_third .= '<th>' . t('Parent') . '</th>';
    }
    else {
      $td_opening = '<td';
      $path_eff = '<front>';
    }

    if (FALSE !== $title) {
      $matrix_thead_tr_first .= $td_opening . '>' . $title . '</td>';
      $matrix_thead_tr_second .= $td_opening . '><code>' . check_plain($path_eff) . '</code></td>';
    }
    else {
      $matrix_thead_tr_first .= $td_opening . ' rowspan="2"><strike><code>' . l($path_eff, $path_eff) . '</code></strike></td>';
    }
  }
  $matrix_thead = '<tr>' . $matrix_thead_tr_first . '</tr>';
  $matrix_thead .= '<tr>' . $matrix_thead_tr_second . '</tr>';
  $matrix_thead .= '<tr>' . $matrix_thead_tr_third . '</tr>';

  $matrix_tbody = '';
  $odd = TRUE;
  foreach ($matrix as $key => $row_cells) {
    $row_html = '<td>' . $key . '</td><td>' . $weights[$key] . '</td>';
    foreach ($row_cells as $col_key => $cell) {
      if (':parent' === substr($col_key, -7)) {
        $cell = '<code>' . $cell . '</code>';
      }
      if (!empty($best_cells[$key][$col_key])) {
        $cell = '<strong>' . $cell . '</strong>';
      }
      $row_html .= '<td>' . $cell . '</td>';
    }
    $class = $odd ? 'odd' : 'even';
    $odd = !$odd;
    $matrix_tbody .= '<tr class="' . $class . '">' . $row_html . '</tr>';
  }

  $table = '<table>' . $matrix_thead . $matrix_tbody . '</table>';
  return '<div style="overflow-x: auto;">' . $table . '</div>';
}