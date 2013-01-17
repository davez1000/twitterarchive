<?php
/**
 * @file
 * Defines 'import-twitterarchive' drush command.
 */

/**
 * Implements hook_drush_help().
 */
function twitterarchive_drush_help($section) {
  switch ($section) {
    case 'drush:import-twitterarchive':
      return dt('Imports the data from twitterarchive into nodes');
      break;
  }
}

/**
 * Implements hook_drush_command().
 */
function twitterarchive_drush_command() {
  return array(
    'import-twitterarchive' => array(
      'description' => 'Imports the twitterarchive data',
      'aliases' => array('imptwa'),
      'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
      'examples' => array('drush imptwa' => 'Start twitterarchive import process.'),
      'arguments' => array(),
    ),
  );
}

/**
 * Implements drush_COMMANDFILE_COMMANDNAME().
 */
function drush_twitterarchive_import_twitterarchive() {
  $start = microtime(TRUE);
  $status = twitterarchive_drush_import();
  $end = microtime(TRUE);
  drush_log('twitterarchive import process completed in ' . ($end - $start) . ' sec.', 'ok');
  if ($status) {
    drush_print("\nImport done successfully.\n");
  }
  else {
    drush_print("\nAn error encountered during import. Please see watchdog logs for details.\n");
  }
}
