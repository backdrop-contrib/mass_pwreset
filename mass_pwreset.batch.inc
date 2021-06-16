<?php

/**
 * Batch process callback
 */
function mass_pwreset_batch_process($data, &$context) {
  if (!isset($context['sandbox']['progress'])) {
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['current_row'] = 0;
    $context['sandbox']['max'] = count($data['uids']);
  }

  $i = $context['sandbox']['current_row'];

  if (isset($data['uids'][$i])) {
    $account = user_load($data['uids'][$i]);

    mass_pwreset_execute_reset($account);
    $context['results'][] = t('Reset user %user', array('%mail' => $account->name));

    if ($data['notify_users'] == '1') {
      mass_pwreset_notify($account);
      $context['results'][] = t('The e-mail has been sent to %mail', array('%mail' => $account->mail));
    }
  }

  $context['sandbox']['progress'] += 1;
  $context['sandbox']['current_row'] += 1;

  if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
    $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
  }
}

/**
 * Batch finish callback
 */
function mass_pwreset_batch_finished($success, $results, $operations) {
  if ($success) {
    backdrop_set_message(t('!count processed.', array('!count' => count($results))));
  }
  else {
    $error_operation = reset($operations);
    $message = t('An error occurred while processing %error_operation with arguments: @arguments', array('%error_operation' => $error_operation[0], '@arguments' => print_r($error_operation[1], TRUE)));
    backdrop_set_message($message, 'error');
  }
}

/**
 * Callback: Reset User password
 */
function mass_pwreset_execute_reset($account) {
  $new_pass = _mass_pwreset_generate_password(12, TRUE);
  $account->pass = $new_pass;
  user_save($account);
  backdrop_set_message(t('Users passwords reset.'), 'status', FALSE);
}

/**
 * Callback: Notify User
 */
function mass_pwreset_notify($account) {
  _user_mail_notify('password_reset', $account);
  backdrop_set_message(t('Users notified via email.'), 'status', FALSE);
}

