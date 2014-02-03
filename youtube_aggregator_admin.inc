<?php

function youtube_aggregator_form_feed($form , $form_state){


$list_of_feeds = db_query("SELECT fid, title, feed_custom_proc FROM {aggregator_feed}");
foreach($list_of_feeds as $feed_from_list){

$feeds_id_title[$feed_from_list->fid]= array ('id' => $feed_from_list->fid ,'title' => $feed_from_list->title);

$defaults[$feed_from_list->fid] =  $feed_from_list->feed_custom_proc;
}

  $header = array(
    'id' => t('id'),
    'title' => t('title'),
  );

$form['feeds_to_process'] = array(
    '#type' => 'tableselect',
	'#header' => $header,
      '#title' => t('List of feeds'),
      '#options' => $feeds_id_title,
	'#default_value' => $defaults,
      '#description' => t('Select feeds to process with your custom processor.'),
    );
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );
return $form;
}

function youtube_aggregator_form_feed_submit($form, &$form_state){

$result = db_update('aggregator_feed')
      ->fields(array(
 	'feed_custom_proc' => 0,
      ))
	      ->execute();

foreach ($form['feeds_to_process']['#value'] as $val){

$result = db_update('aggregator_feed')
      ->fields(array(
	'feed_custom_proc' => $val,
      ))
	->condition('fid', $val)
      ->execute();

}
 }
