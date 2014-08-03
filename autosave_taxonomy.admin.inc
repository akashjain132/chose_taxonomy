<?php

/**
 * @file
 * Have some functions used in Autosave taxonomy.
 */

/**
 * Create a form for module configuration.
 */
function autosave_taxonomy_configuration_page($form, $form_state) {

  $autosave_taxonomy_path = drupal_get_path('module', AUTOSAVE_TAXONOMY) . '/images/';

  $default_image_options = array(
    'star' => '<img src="/' . $autosave_taxonomy_path . 'positive-star.png" />',
    'heart' => '<img src="/' . $autosave_taxonomy_path . 'positive-heart.png" />',
    'smile' => '<img src="/' . $autosave_taxonomy_path . 'positive-smile.png" />',
  );

  $form[AUTOSAVE_TAXONOMY . '_image_option'] = array(
    '#type' => 'radios',
    '#title' => t('Chose default image'),
    '#options' => $default_image_options,
    '#default_value' => variable_get(AUTOSAVE_TAXONOMY . '_image_option', ''),
    '#description' => t('Chose image which will shown with taxonomy term list'),
  );

  $form[AUTOSAVE_TAXONOMY . '_type_image_unclicked'] = array(
    '#title' => t('UnClicked Icons'),
    '#type' => 'managed_file',
    '#description' => t('The uploaded image will be displayed on this page align to taxonomy label when is not clicked or not checked.'),
    '#default_value' => variable_get(AUTOSAVE_TAXONOMY . '_type_image_unclicked', ''),
    '#upload_location' => 'public://'. AUTOSAVE_TAXONOMY .'/',
    '#upload_validators' => array(
      'file_validate_extensions' => array('gif png jpg jpeg'),
    ),
  );

  $form[AUTOSAVE_TAXONOMY . '_type_image_clicked'] = array(
    '#title' => t('Clicked Icons'),
    '#type' => 'managed_file',
    '#description' => t('The uploaded image will be displayed on this page align to taxonomy label when is clicked or checked.'),
    '#default_value' => variable_get(AUTOSAVE_TAXONOMY . '_type_image_clicked', ''),
    '#upload_location' => 'public://'. AUTOSAVE_TAXONOMY .'/',
    '#upload_validators' => array(
      'file_validate_extensions' => array('gif png jpg jpeg'),
    ),
  );

  //@TODO
  //Check both should be uploaded and user should upload upload maximum size.

  return system_settings_form($form);
}

/**
 * It return all field which has autosave taxonomy widget.
 */
function get_autosave_taxonomy_terms() {
  $autosave_taxonomy_config_field_name = variable_get(AUTOSAVE_TAXONOMY . '_field_machine_name', '');
  $autosave_taxonomy_config_field_name = trim($autosave_taxonomy_config_field_name);
  $autosave_taxonomy_config_field_name = explode(",", $autosave_taxonomy_config_field_name);

  return $autosave_taxonomy_config_field_name;
}