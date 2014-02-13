<?php

/**
 * @file headerimage.admin.inc
 * @see headerimage.module
 */

/**
 * Overview of all image blocks
 */
function headerimage_settings_block_add() {
  $blocks = headerimage_get_blocks();

  // Table of image sets
  $rows = array();
  foreach ($blocks as $delta => $block) {
    $rows[] = array(
      'name' => check_plain($block),
      'edit' => l(t('Edit'), "admin/structure/headerimage/edit/$delta"),
      'delete' => l(t('Delete'), "admin/structure/headerimage/delete/$delta"),
      'block' => l(t('Configure block'), "admin/structure/block/manage/headerimage/$delta/configure"),
    );
  }
  if (empty($rows)) {
    $rows[] = array(array('data' => t('No Header Image blocks available.'), 'colspan' => '4'));
  }
  $header = array(t('Name'), array('data' => t('Operation'), 'colspan' => '3'));
  $output = theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('id' => 'imageblock')));

  $form = array();
  $form['list'] = array(
    '#type' => 'fieldset',
    '#title' => t('Header Image blocks'),
  );
  $form['list']['table'] = array(
    '#prefix' => '<div>',
    '#markup' => $output,
    '#suffix' => '</div>',
  );
  $form['block'] = array(
    '#type' => 'fieldset',
    '#title' => t('Add Header Image block'),
  );
  $form['block']['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Block title'),
    '#description' => t('A block with this same name will be created. Header Image nodes assigned to this block will be displayed in it.'),
    '#default_value' => '',
    '#required' => true,
  );
  $form['block']['op'] = array(
    '#type' => 'submit',
    '#value' => t('Add block'),
  );

  return $form;
}

function headerimage_settings_block_add_validate($form, &$form_state) {
  $blocks = headerimage_get_blocks();

  if (!empty($blocks)) {
    // Check if name is unique
    if (in_array($form_state['values']['title'], $blocks)) {
      form_set_error('', t('Header Image block %s already exists. Please use a different name.', array('%s' => $form_state['values']['title'])));
    }
  }
}

function headerimage_settings_block_add_submit($form, &$form_state) {
  db_insert('headerimage_block')->fields(array('title' => $form_state['values']['title']))->execute();
  drupal_set_message(t('Header Image block %s added.', array('%s' => $form_state['values']['title'])));
}

/**
 * Header Image settings form
 */
function headerimage_settings_form() {
  $form = array();
  $nodetype = array();
  $nodes = node_type_get_types();
  foreach ($nodes as $node) {
    $nodetype[$node->type] = check_plain($node->name);
  }

  $form['headerimage_node_type'] = array(
   '#type' => 'checkboxes',
   '#title' => t('Content type'),
   '#description' => t('The Content type(s) that can be used with Header Image module.'),
   '#default_value' => variable_get('headerimage_node_type', array()),
   '#options' => $nodetype,
   '#multiple' => true,
   '#required' => true,
  );

  $form['headerimage_condition_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Condition types'),
    '#description' => t('Types of conditions by which nodes can be selected to be displayed.'),
    '#default_value' => variable_get('headerimage_condition_types', array('nid')),
    '#options' => headerimage_get_condition_types(),
    '#required' => true,
  );

  $form['headerimage_teaser'] = array(
    '#type' => 'checkbox',
    '#title' => t('Teaser'),
    '#description' => t('Display the Header Image node as teaser or full node.'),
    '#default_value' => variable_get('headerimage_teaser', true),
  );

  if (module_exists('ds')) {
    $form['headerimage_module_ds'] = array(
      '#type' => 'checkbox',
      '#title' => t('Use Display Suite module'),
      '#description' => t('Display the Header Image with Display Suite settings'),
      '#default_value' => variable_get('headerimage_module_ds', true),
    );
  }

  if (module_exists('locale')) {
    $form['headerimage_language_support'] = array(
      '#type' => 'checkbox',
      '#title' => t('Show only nodes in current language'),
      '#description' => t('Display only header images in the current language.'),
      '#default_value' => variable_get('headerimage_language_support', FALSE),
    );

    $form['headerimage_language_support_neutral'] = array(
      '#type' => 'checkbox',
      '#title' => t('Respect language neutral'),
      '#description' => t('Display only header images in the current language and respect language neutral. Both checkboxes need to be active to support this.'),
      '#default_value' => variable_get('headerimage_language_support_neutral', FALSE),
    );
  }

  return system_settings_form($form);
}

/**
 * Delete block form
 */
function headerimage_block_confirm_delete($form, &$form_state, $delta) {
  $blocks = headerimage_get_blocks();
  $form['delta'] = array('#type' => 'value', '#value' => $delta);
    return confirm_form(
      $form,
      t('Are you sure you want to delete the block %title?', array('%title' => $blocks[$delta])),
      'admin/structure/headerimage',
      t('All Header Image assignments to this block will be deleted, the nodes will not be deleted. This action cannot be undone.'),
      t('Delete'), t('Cancel')
    );
}

function headerimage_block_confirm_delete_submit($form, &$form_state) {
  db_delete('headerimage_block')->condition('delta', $form_state['values']['delta'])->execute();
  db_delete('headerimage')->condition('block', $form_state['values']['delta'])->execute();

  drupal_set_message(t('Header Image block deleted'));
  $form_state['redirect'] = 'admin/structure/headerimage';
}
