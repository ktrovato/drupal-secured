<?php

/**
 * Page callback for the policies overview page.
 */
function content_security_policy_overview_page($form, &$form_state) {
  $query = db_query('SELECT * FROM {content_security_policy}');
  $query->execute();

  if ($result = $query->fetchAll()) {
    $header = array(
      'title' => t('Title'),
      'mode' => t('Mode'),
      'operations' => t('Operations'),
    );

    foreach ($result as $policy) {
      $options[$policy->pid]['title'] = check_plain($policy->title);
      $options[$policy->pid]['mode'] = $policy->mode == CONTENT_SECURITY_POLICY_MODE_REPORT_ONLY ?t('Report only') : t('Full (enforce and report)');
      $options[$policy->pid]['operations'] = array(
        'data' => l(t('edit policy'), 'admin/config/people/content-security-policy/' . $policy->name . '/edit') . ' ' . l(t('delete policy'), 'admin/config/people/content-security-policy/' . $policy->name . '/delete'),
      );
    }
  
    $form['policies'] = array(
      '#type' => 'tableselect',
      '#header' => $header,
      '#options' => $options,
      '#js_select' => FALSE,
      '#default_value' => variable_get('content_security_policy_active_policies', array()),
    );
  
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save'),
    );
  }
  else {
    $form['policies'] = array(
      '#markup' => t('No content security policies have been defined. You can add policies via the <a href="!link">Add policy</a>-tab.', array('!link' => url('admin/config/people/content-security-policy/add'))),
    );
  }

  return $form;
}

/**
 * Submit handler for the policies overview page.
 */
function content_security_policy_overview_page_submit($form, &$form_state) {
  $selected_policies = array_filter($form_state['values']['policies']);
  variable_set('content_security_policy_active_policies', $selected_policies);
  drupal_set_message(t("Changes have been saved."));
}

function content_security_policy_add_form($form, &$form_state) {
  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Policy title'),
    '#required' => TRUE,
  );

  $form['name'] = array(
    '#type' => 'machine_name',
    '#title' => t('Policy name'),
    '#maxlength' => 255,
    '#description' => t('A unique name for the policy. It must only contain lowercase letters, numbers and hyphens.'),
    '#machine_name' => array(
      'exists' => 'content_security_policy_name_load',
      'source' => array('title'),
      'replace_pattern' => '[^a-z0-9-]+',
      'replace' => '-',
    ),
  );

  $form['description'] = array(
    '#type' => 'textarea',
    '#title' => t('Description'),
  );
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

/**
 * Submit handler for the "Add Policy" form.
 */
function content_security_policy_add_form_submit($form, &$form_state) {
  $result = db_insert('content_security_policy')
    ->fields(array(
      'name' => $form_state['values']['name'],
      'title' => $form_state['values']['title'],
      'description' => $form_state['values']['description'],
  ))->execute();

  $form_state['redirect'] = 'admin/config/people/content-security-policy/' . $form_state['values']['name'] . '/edit'; 
}

function content_security_policy_edit_form($form, &$form_state, $policy) {
  $form['#tree'] = TRUE;
  $form['pid'] = array(
    '#type' => 'hidden',
    '#value' => $policy->pid,
  );
  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Policy title'),
    '#default_value' => $policy->title,
    '#required' => TRUE,
  );
  $form['name'] = array(
    '#type' => 'machine_name',
    '#title' => t('Policy name'),
    '#maxlength' => 255,
    '#default_value' => $policy->name,
    '#disabled' => TRUE,
    '#description' => t('A unique name for the policy. It must only contain lowercase letters, numbers and hyphens.'),
    '#machine_name' => array(
      'exists' => 'content_security_policy_name_load',
      'source' => array('title'),
      'replace_pattern' => '[^a-z0-9-]+',
      'replace' => '-',
    ),
  );

  $form['description'] = array(
    '#type' => 'textarea',
    '#title' => t('Description'),
    '#default_value' => $policy->description,  
  );
  $form['operation_mode'] = array(
    '#type' => 'checkboxes',
    '#description' => t('When running in report-only mode, user agents report policy violations but <strong>do not enforce the policy</strong>.'),
    '#options' => array(CONTENT_SECURITY_POLICY_MODE_REPORT_ONLY => t('Report only')),
    '#default_value' => array($policy->mode),
  );
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  $form['directives'] = array(
    '#title' => t('Policy directives'),
    '#type' => 'vertical_tabs',
  );
  foreach (_content_security_policy_directives() as $directive) {
    $form['directives'][$directive['name']] = array(
      '#type' => 'fieldset',
      '#title' => $directive['label'],
    );
    $form['directives'][$directive['name']]['input'] = content_security_policy_subform($directive); 

    if (isset($policy->data[$directive['name']])) {
      switch($directive['type']) {
        case CONTENT_SECURITY_POLICY_DIRECTIVE_TYPE_HOST_LIST:
        case CONTENT_SECURITY_POLICY_DIRECTIVE_TYPE_URI:
          $form['directives'][$directive['name']]['input']['#default_value'] = $policy->data[$directive['name']];
          break;

        case CONTENT_SECURITY_POLICY_DIRECTIVE_TYPE_OPTIONS:
          $form['directives'][$directive['name']]['input']['#default_value'] = array_values($policy->data[$directive['name']]);
          break;
      }
    }
  }
  
  return $form;
}

/**
 * Validation handler for the policy edit form. 
 */
function content_security_policy_edit_form_validate($form, &$form_state) {
  foreach ($form_state['values']['directives']['options']['input'] as $key => $value) {
    if ($value) {
      $form_state['values']['directives']['options']['input'][] = $value;
    }
    unset($form_state['values']['directives']['options']['input'][$key]);
  }
}

/**
 * Submit handler for the policy edit form. 
 */
function content_security_policy_edit_form_submit($form, &$form_state) {
  $policy_data = $form_state['values']['directives'];
  $valid_directives = _content_security_policy_directives();

  foreach ($policy_data as $key => $value) {
    if (isset($valid_directives[$key])) {
      $policy_data[$key] = $value['input'];
    }
    else {
      unset($policy_data[$key]);
    }
  }

  db_update('content_security_policy')
    ->fields(array(
      'title' => $form_state['values']['title'],
      'description' => $form_state['values']['description'],
      'mode' => $form_state['values']['operation_mode'], 
      'data' => serialize($policy_data)
  ))->condition('pid', $form_state['values']['pid'])
    ->execute();

  drupal_set_message(t("The content security policy %title has been saved.", array('%title' => $form_state['values']['title'])));
  $form_state['redirect'] = 'admin/config/people/content-security-policy';
}

function content_security_policy_delete_form($form, &$form_state, $policy) {
  $form['pid'] = array(
    '#type' => 'hidden',
    '#value' => $policy->pid,
  );  
  $question = t('Are you sure you want to delete the policy %policy_title?', array('%policy_title' => $policy->title));
  $path = 'admin/config/people/content-security-policy';
  return confirm_form($form, $question, $path);
}

/**
 * Submit handler for the policy delete form. 
 */
function content_security_policy_delete_form_submit($form, &$form_state) {  
  db_delete('content_security_policy')
    ->condition('pid', $form_state['values']['pid'])
    ->execute();

  // If the deleted policy is active, remove it from the list of active
  // policies.
  $active_policies = variable_get('content_security_policy_active_policies' ,array());
  if (isset($active_policies[$form_state['values']['pid']])) {
    unset($active_policies[$form_state['values']['pid']]);
    variable_set('content_security_policy_active_policies', $active_policies);
  }

  drupal_set_message(t("The content security policy has been deleted."));
  $form_state['redirect'] = 'admin/config/people/content-security-policy';
}

/**
 * Returns a form for a specific directive.
 */
function content_security_policy_subform($directive) {
  $form['#title'] = $directive['label'];
  $form['#description'] = $directive['description'];
  $form['#required'] = (isset($directive['required']) && $directive['required']);

  switch ($directive['type']) {
    case CONTENT_SECURITY_POLICY_DIRECTIVE_TYPE_HOST_LIST:
      $form = array(
        '#element_validate' => array('content_security_policy_source_directive_validate'),
        '#type' => 'textarea',
        '#description' => '<p>' . $form['#description'] . '</p>' . t('Valid values are: "none" (mutually exclusive with any other value), "self" and sources. Examples: <ul><li>http://www.example.com/</li><li>*.example.com:8080</li><li>https://*</li></ul>'),
      );
      break;

    case CONTENT_SECURITY_POLICY_DIRECTIVE_TYPE_URI:
      $form = array(
        '#type' => 'textfield',
        '#element_validate' => array('content_security_policy_uri_directive_validate'),
      );
      break;

    case CONTENT_SECURITY_POLICY_DIRECTIVE_TYPE_OPTIONS:
      $csp_options = _content_security_policy_options();
      $options = array();
      
      foreach ($csp_options as $option_key => $option_value) {
        $options[$option_key] = $option_value['label'];
      }
      
      $form = array(
        '#type' => 'checkboxes',
        '#options' => $options,
        '#multiple' => TRUE,
      );
      break;
  }

  return $form;
}

/**
 * Validation handler for directives of type 'source'. 
 */
function content_security_policy_source_directive_validate($element, &$form_state) {
  $source_list = array_unique(preg_split('/\s+/', $element['#value']));
  $malformed_sources = array();

  if (in_array("'none'", $source_list) && count($source_list) > 1) {
    form_error($element, t("The value 'none' cannot be used in combination with other sources in a source directive such as the %label directive.", array('%label' => $element['#title'])));
  }

  foreach ($source_list as $source) {
    // Partial regexes:
    //   scheme ([a-zA-Z][a-zA-Z\.\+\-]*\:\/{0,2})?
    //   host   (\*|[a-zA-Z0-9\-]+(\.[a-zA-Z0-9\-]+)*)?
    //   port   (:\*|:\d+)?
    if (!preg_match("/^('none'|'self'|([a-zA-Z][a-zA-Z\.\+\-]*\:\/{0,2})?(\*|[a-zA-Z0-9\-]+(\.[a-zA-Z0-9\-]+)*)?(:\*|:\d+)?)$/", $source)) {
      $malformed_sources[] = $source;
    }
  }

  if ($malformed_sources) {
    form_error($element, t('The following values for the %label directive are not valid as source directive values: %list', array('%label' => $element['#title'], '%list' => join(', ', $malformed_sources))));
  }
}

/**
 * Validation handler for directives of type 'uri'. 
 */
function content_security_policy_uri_directive_validate($element, &$form_state) {
  // @TODO: Implement this. Specs are a bit unclear though, as they claim that
  // relative URLs are allowed, yet FF 4 beta rejects them ("can't parse URI").
}
