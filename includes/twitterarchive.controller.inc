<?php

/**
 * @file
 *
 * Controller class for Twitterarchive entity
 */

class twitterarchiveEntityController extends EntityAPIController {

  /**
   * Permanently saves the given entity.
   *
   * In case of failures, an exception is thrown.
   *
   * @param $entity
   *   The entity to save.
   * @param $transaction
   *   An optional transaction object to pass thru. If passed the caller is
   *   responsible for rolling back the transaction if something goes wrong.
   * @return
   *   SAVED_NEW or SAVED_UPDATED depending on the operation performed.
   */
  public function save($entity, DatabaseTransaction $transaction = NULL) {
    if (!isset($transaction)) {
      $transaction = db_transaction();
      $started_transaction = TRUE;
    }

    try {
      global $user;

      // Give modules the opportunity to prepare field data for saving.
      field_attach_presave('twitterarchive', $entity);

      // If this is a new record
      if ($entity->is_new) {
        // Save the new record.
        $ret = drupal_write_record('twitterarchive', $entity);
        $op = 'insert';
      }
      else {
        // Save the updated record
        $ret = drupal_write_record('twitterarchive', $entity, 'id');
        $op = 'update';
      }

      // Save fields
      $function = 'field_attach_' . $op;
      $function('twitterarchive', $entity);

      module_invoke_all('entity_' . $op, $entity, 'twitterarchive');

      // Clear internal properties.
      unset($entity->is_new);

      // Ignore slave server temporarily to give time for the saved order to be
      // propagated to the slave.
      db_ignore_slave();

      // return the value returned by drupal_write_record
      return $ret;
    }
    catch (Exception $e) {
      $transaction->rollback();
      watchdog_exception('twitterarchive', $e, NULL, WATCHDOG_ERROR);
      return FALSE;
    }
  }


}
