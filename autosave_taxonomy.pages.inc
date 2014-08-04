<?php

/**
 * @file
 * Have some functions used in Autosave taxonomy.
 */

/**
 * Save taxonomy term id in entity field.
 */
function autosave_taxonomy_save_taxonomy_term($entity_type, $entity_id, $autosave_taxonomy_tid, $field_name) {
  if ($entity_type == 'node') {
    $entity_object = node_load($entity_id);
  }
  if ($entity_type == 'user') {
    $entity_object = user_load($entity_id);
  }

  foreach ($autosave_taxonomy_tid as $key => $tid) {
    $field_value['und'][]['tid'] = $tid;
  }

  $entity_object->$field_name = $field_value;

  field_attach_update($entity_type, $entity_object);
}

/**
 * Ajax callback function to get all tids.
 */
function autosave_taxonomy_save_taxonomy_term_by_ajax($form, $form_state) {
  $autosave_taxonomy_terms = $form_state['storage']['autosave_taxonomy'];

  foreach ($autosave_taxonomy_terms as $key => $field_name) {
    if (!isset($form_state['values'][$field_name]['und'])) {
      continue;
    }
    $taxonomy_terms = $form_state['values'][$field_name]['und'];
    $autosave_taxonomy_tid = array();
    foreach ($taxonomy_terms as $key => $value) {
      if ($value != 0) {
        if (isset($form_state['values'][$field_name]['und'][$key]['tid'])) {
          $autosave_taxonomy_tid[] = $form_state['values'][$field_name]['und'][$key]['tid'];
        }
      }
    }

    if (isset($autosave_taxonomy_tid) && !empty($autosave_taxonomy_tid)) {
      if (isset($form['#user'])) {
        $entity_type = 'user';
        $entity_id = $form['#user']->uid;
      }
      if (isset($form['#node'])) {
        $entity_type = 'node';
        $entity_id = $form['#node']->nid;
      }
      autosave_taxonomy_save_taxonomy_term($entity_type, $entity_id, $autosave_taxonomy_tid, $field_name);
    }

  }

}

/**
 * Save field machine name for which autosave taxonomy will be used.
 */
function autosave_taxonomy_save_field_name($form, $form_state) {

  if (isset($form_state['values']['instance']['autosave_taxonomy']) && isset($form_state['values']['instance']['field_name'])) {
    $autosave_taxonomy_field_name = $form_state['values']['instance']['field_name'];
    $autosave_taxonomy_value = $form_state['values']['instance']['autosave_taxonomy'] == 1 ? TRUE : FALSE;
    $autosave_taxonomy_config_field_name  = variable_get(AUTOSAVE_TAXONOMY . '_field_machine_name', '');
    if ($form_state['values']['instance']['autosave_taxonomy'] == 1 && strpos($autosave_taxonomy_config_field_name, $autosave_taxonomy_field_name) !== FALSE) {
      return;
    }
    if ($autosave_taxonomy_value) {
      $autosave_taxonomy_config_field_name .=  "," . $form['#field']['field_name'];
    }
    else {
      $autosave_taxonomy_config_field_name = str_replace("," . $autosave_taxonomy_field_name, "", $autosave_taxonomy_config_field_name);
    }
    variable_set(AUTOSAVE_TAXONOMY . '_field_machine_name', $autosave_taxonomy_config_field_name);
  }

}
