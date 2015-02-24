<?php
/**
 * @file
 *   Describes our data to views and defines handlers and plugins.
 */

/**
 * Implements hook_views_data().
 *
 * Exposes all mailfish data to the views system.
 */
function mailfish_views_data() {
  $data['mailfish']['table']['group']  = t('Mailfish Subscriptions');
  $data['mailfish']['table']['base'] = array(
    'field' => 'id',
    'title' => t('MailFish'),
    'help' => t('Mailfish subscriptions on your site.'),
  );
  $data['mailfish']['table']['join'] = array(
    'node' => array(
      'left_field' => 'nid',
      'field' => 'nid',
    ),
    'user' => array(
      'left_field' => 'uid',
      'field' => 'uid',
    ),
  );
  $data['users']['table']['join']['mailfish'] = array(
    'left_field' => 'uid',
    'field' => 'uid',
    'type' => 'LEFT',
  );
  $data['node']['table']['join']['mailfish'] = array(
    'left_field' => 'nid',
    'field' => 'nid',
    'type' => 'LEFT',
  );

  $data['mailfish']['mail'] = array(
    'title' => t('E-mail'), // The item it appears as on the UI,
    'help' => t('Email address for a given user. This field is normally not shown to users, so be cautious when using it.'), // The help that appears on the UI,
    'field' => array(
      'handler' => 'views_handler_field_user_mail',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
  );

  $data['mailfish']['uid'] = array(
    'title' => t('User'),
    'help' => t('Relate a Mailfish subscription to the user who created it.'),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => 'users',
      'base field' => 'uid',
      'label' => t('user'),
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_user_uid',
      'name field' => 'name',
    ),
  );
  $data['mailfish']['nid'] = array(
    'title' => t('Node'),
    'help' => t('Relate a Mailfish subscription to the node it was created on.'),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => 'node',
      'base field' => 'nid',
      'label' => t('node'),
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_node_nid',
      'parent' => 'views_handler_argument_numeric',
      'name field' => 'title',
      'numeric' => TRUE,
      'validate type' => 'nid',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
  ); 
  $data['mailfish']['created'] = array(
    'title' => t('Created date'),
    'help' => t('The date the node revision was created.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );
  return $data;
}

