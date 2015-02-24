<?php

/**
 * @file
 * Provide the admin related functions for the Mailfish module.
 */

/**
 * Defines the Mailfish admin settings form.
 */
function mailfish_admin_settings_form() {
  $form = array();
  $form['mailfish_types'] = array(
    '#title' => t('The content types to enable Mailfish subscriptions for'),
    '#description' => t('On the specified node types, a Mailfish subscription option will
    be available and can be enabled while that node is being edited.'),
    '#type' => 'checkboxes',
    '#options' => node_type_get_names(),
    '#default_value' => variable_get('mailfish_types', array()),
  );
  return system_settings_form($form);
}

/**
 * Menu callback.
 *
 * Displays mailfish signups.
 */
function mailfish_signups() {
  $output = '';
  $rows = array();
  $header = array(
   'User',
   'Node',
   'Email',
   'Created',
  );

  // Dynamically load the schema for this table 
  $fields = drupal_get_schema('mailfish');

  // Intantiate a query object by using the db_select wrapper 
  $query = db_select('mailfish', 'm');

  // Add a join on the node table.
  $table_alias = $query->innerJoin('node', 'n', 'n.nid = m.nid', array());

  // Add our desired fields to the query, loading the fields for our table dynamically.
  $results = $query->fields('m', array_keys($fields['fields']))
    ->fields($table_alias, array('title'))
    ->orderBy('m.created', $direction = 'ASC')
    ->execute()
    ->fetchAll();

  foreach ($results as $value) {
    $account = $value->uid ? user_load($value->uid) : '';
    $rows[] = array(
      $value->uid ? theme('username', array('account' => $account)) : '',
      $value->nid ? l($value->title, 'node/' . $value->nid) : '',
      $value->mail,
      date('F j, Y g:i A', $value->created),
    );
  }

  $output .= theme('table', array('header' => $header, 'rows' => $rows));
  return $output;
}
