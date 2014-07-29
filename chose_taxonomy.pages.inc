<?php

/**
 * @file
 * Have some API functions used in chose taxonomy.
 */

/**
 * Save taxonomy term id in entity field.
 */
function chose_taxonomy_save_taxonomy_term($entity_type, $entity_id, $chose_taxonomy_tid, $field_name) {
  if ($entity_type == 'node') {
    $entity_object = node_load($entity_id);
  }
  if ($entity_type == 'user') {
    $entity_object = user_load($entity_id);
  }

  foreach ($chose_taxonomy_tid as $key => $tid) {
    $field_value['und'][]['tid'] = $tid;
  }

  $entity_object->$field_name = $field_value;

  field_attach_update($entity_type, $entity_object);
}

/**
 * Ajax callback function to get all tids.
 */
function chose_taxonomy_save_taxonomy_term_by_ajax($form, $form_state) {
  $chose_taxonomy_terms = $form_state['storage']['chose_taxonomy'];

  foreach ($chose_taxonomy_terms as $key => $field_name) {
    if (!isset($form_state['values'][$field_name]['und'])) {
      continue;
    }
    $taxonomy_terms = $form_state['values'][$field_name]['und'];
    $chose_taxonomy_tid = array();
    foreach ($taxonomy_terms as $key => $value) {
      if ($value != 0) {
        if (isset($form_state['values'][$field_name]['und'][$key]['tid'])) {
          $chose_taxonomy_tid[] = $form_state['values'][$field_name]['und'][$key]['tid'];
        }
      }
    }

    if (isset($chose_taxonomy_tid) && !empty($chose_taxonomy_tid)) {
      if (isset($form['#user'])) {
        $entity_type = 'user';
        $entity_id = $form['#user']->uid;
      }
      if (isset($form['#node'])) {
        $entity_type = 'node';
        $entity_id = $form['#node']->nid;
      }
      chose_taxonomy_save_taxonomy_term($entity_type, $entity_id, $chose_taxonomy_tid, $field_name);
    }

  }

}

/**
 * Save field machine name for which chosen taxonomy will be used.
 */
function chose_taxonomy_save_field_name($form, $form_state) {

  $chose_taxonomy_config_field_name  = variable_get(CHOSE_TAXONOMY . '_field_machine_name', '');
  $chose_taxonomy_config_field_name .=  "," . $form['#field']['field_name'];

  variable_set(CHOSE_TAXONOMY . '_field_machine_name', $chose_taxonomy_config_field_name);
}
