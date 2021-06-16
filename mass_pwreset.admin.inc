<?php

/**
 * @file
 * Admin page callbacks for the mass_pwreset module.
 */

/**
 * Form constructor for the mass password reset form.
 *
 * @see mass_pwreset_submit()
 * @ingroup forms
 */
function mass_pwreset_form($form, $form_state) {
  $form['options'] = array(
    '#type' => 'fieldset',
    '#title' => t('Password Reset Options'),
  );
  $form['options']['notify_users'] = array(
    '#type' => 'checkbox',
    '#title' => t('Notify users via email'),
    '#description' => t("Send Backdrop's password recovery email to users when their password is reset."),
    '#default_value' => 0,
  );
  $form['options']['include_admin_user'] = array(
    '#type' => 'checkbox',
    '#title' => t('Include admin user'),
    '#description' => t('Include the administrative superuser account (user id = 1) in the list of passwords being reset.'),
    '#default_value' => 0,
  );
  $form['options']['choose_roles'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Reset passwords for role(s)'),
    '#options' => user_roles(TRUE),
    '#required' => TRUE,
  );
  $form['actions']['#type'] = 'actions';
  $form['actions']['reset_passwords'] = array(
    '#type' => 'submit',
    '#value' => t('Reset passwords'),
    '#submit' => array('mass_pwreset_submit'),
  );

  return $form;
}

/**
 * Form submission handler for mass_pwreset_form().
 *
 * Reset paswords and notify users.
 */
function mass_pwreset_submit($form, &$form_state) {
  $roles = array_filter($form_state['values']['choose_roles']);
  $uids = mass_pwreset_get_uids_by_role($roles);

  if ($form_state['values']['include_admin_user'] != '1') {
    unset($uids[1]);
  }

  $uids = array_values($uids);

  $data = array(
    'uids' => $uids,
    'notify_users' => $form_state['values']['notify_users'],
  );

  mass_pwreset_multiple_reset($data);

}
