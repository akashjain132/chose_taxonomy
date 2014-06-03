<?php

/**
 * @file
 * Have some API functions used in chose taxonomy.
 */

/**
 * Get all taxonomy term name with its tid by vocabulary machine name.
 *
 * @param  String $vocabulary_machine_name
 *   Vocabulary machine name.
 * @return Array
 *   Return an array having all taxonomy id as its value and term name as its value.
 */
function get_taxonomy_term_by_vocabulary_machine_name($vocabulary_machine_name) {
  $vocabulary = taxonomy_vocabulary_machine_name_load($vocabulary_machine_name);
  $vocabulary_id = $vocabulary->vid;
  $vocabulary_taxonomy_term = taxonomy_get_tree($vocabulary_id);
  foreach ($vocabulary_taxonomy_term as $key => $value) {
    $vocabulary_taxonomy_name = $vocabulary_taxonomy_term[$key]->name;
    $vocabulary_taxonomy_id = $vocabulary_taxonomy_term[$key]->tid;
    $taxonomy_name[$vocabulary_taxonomy_id] = $vocabulary_taxonomy_name;
  }
  return $taxonomy_name;
}

/**
 * callback of chose_taxonomy element.
 * @param  Array $element
 *   Having information about elements.
 * @return Array
 *   Return newly created form element.
 */
function chose_taxonomy_element_process($element) {

  $field_name = $element['#field_name'];
  $field_info = field_info_field($field_name);
  $vocabulary_machine_name = $field_info['settings']['allowed_values'][0]['vocabulary'];

  $taxonomy_name = get_taxonomy_term_by_vocabulary_machine_name($vocabulary_machine_name);

  $element['chosen_taxonomy_list'] = array(
    '#type' => 'checkboxes',
    '#attributes' => array('class' => array('chose-taxonomy-form'), 'id' => array('chose-taxonomy-form-element')),
    '#prefix' => '<div id=chose_taxonomy_wrapper>',
    '#suffix' => '</div>',
    '#options' => $taxonomy_name,
  );

  return $element;
}
