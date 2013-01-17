
<?php foreach($tweets as $tweet): ?>
  <p>
    <div><?php echo $tweet['text']; ?></div>
    <div><?php echo $tweet['created']; ?></div>
    <div><?php echo l('view on twitter', 'https://twitter.com/' . $tweet['name'] . '/statuses/' . $tweet['id'], array('absolute' => TRUE)); ?></div>
  </p>
<?php endforeach; ?>
