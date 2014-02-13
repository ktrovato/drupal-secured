<?php

/**
 * Page callback for the CSP reporting violations overview page.
 */
function content_security_policy_reporting_violations_overview() {
  $rows = array();

  $header = array(
    array('data' => t('Date'), 'field' => 'vr.vrid', 'sort' => 'desc'),
    t('Violated directive'),
    array('data' => t('Operations')),
  );

  $query = db_select('content_security_policy_violation_report', 'vr')->extend('PagerDefault')->extend('TableSort');
  $query->fields('vr', array('vrid', 'timestamp', 'request', 'violated_directive'));
  $result = $query
    ->limit(50)
    ->orderByHeader($header)
    ->execute();

  foreach ($result as $violation) {
    $rows[] = array('data' =>
      array(
        format_date($violation->timestamp, 'short'),
        $violation->violated_directive . '<br />' . $violation->request,
        l(t('View details'), 'admin/reports/content-security-policy/' . $violation->vrid),
      ),
    );
  }

  $build['violations_table'] = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
    '#empty' => t('No content security policy violations reported.'),
  );
  $build['violations_pager'] = array('#theme' => 'pager');

  return $build;
}

function content_security_policy_reporting_violation_detail($violation_report) {
  $rows = array(
    array(
      array('data' => t('Request'), 'header' => TRUE),
        check_plain($violation_report->request),
      ),
      array(
        array('data' => t('Date'), 'header' => TRUE),
        format_date($violation_report->timestamp, 'long'),
      ),
      array(
        array('data' => t('Request headers'), 'header' => TRUE),
        '<pre>' . check_plain($violation_report->request_headers) . '</pre>',
      ),
      array(
        array('data' => t('Violated directive'), 'header' => TRUE),
        check_plain($violation_report->violated_directive),
      ),
      array(
        array('data' => t('Blocked uri'), 'header' => TRUE),
          check_plain($violation_report->blocked_uri),
        ),

    );

  $build['dblog_table'] = array(
    '#theme' => 'table',
    '#rows' => $rows,
  );

  return $build;
}