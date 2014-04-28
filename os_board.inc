<?php

/* authenticate credentials by creating a new Google_client object and 
* sending it to google analytics
* check_credentials
* no parameters
* creates the google_client object
* returns the validated service object
*/
function check_credentials(){
  // try-catch block for setting private key. 
  // If not set then redirect to a different url
  try {
    $fid = variable_get('os_board_private_key_fid', '');
    if (!empty($fid)) {
	  $uri = db_query('SELECT uri FROM {file_managed} WHERE fid = :fid', array(':fid' => $fid))->fetchColumn();
	  $fhandle = fopen($uri, 'r');
	  $result = fread($fhandle, filesize($uri));
	  fclose($fhandle);
	}
	else {
	  drupal_set_message(t('You are not authenticated. You are being redirected to a page where the credentials can be set. Thanks'), 'error');
	  drupal_goto("admin/config/openscholar_os_board");	
	}
	
    //variables definition block starts
    $output ='';
	$access_type = 'offline_access';
    $scope = 'https://www.googleapis.com/auth/analytics.readonly';
	
    //create a new instance of Google_client
    $client = new Google_Client();
    // set the application name
    $client->setApplicationName('OS board');
    //set the credentials, clientid and accesstype
	
	
	$client->setAssertionCredentials(new Google_AssertionCredentials(variable_get('os_board_service_gmail'), array($scope),
	                          $result));
							  
    $client->setClientId(variable_get('os_board_client_id'));
    $client->setAccessType($access_type);
	//$client->getAccessToken();
	 
    //create a new instance of google_analyticsservice
    $service = new Google_AnalyticsService($client);
	}
	catch (Exception $ex){
	  drupal_set_message(t('Issue authenticating and receiving data. Message = %message, query=%query', 
	           array('%message' =>$e->getMessage(),'%query' => $e->query_string)), 'error');		
	}
    //set optional parameters like sort, dimensions etc
	return $service;
	
	}	
	
/* 
* os_design_output
* parameters = $type which could be a pageview or visits
* taps into google analytics and retrieves the results for 
* most frequent page views and page visited
* returns the pageviews and visit object
*/
function os_design_output($type){
  try {
    //variables definition block starts
    $output ='';
	$app_name = 'OS Board';
	$metrics_pageviews = 'ga:pageviews';
    $metrics_visits = 'ga:visits';
    $sort_pageviews = '-ga:pageviews';
    $sort_visits = '-ga:visits';
    $dimensions = 'ga:hostname';
	$start_date = '04/20/2104' ;
	$end_date = '04/25/2104'  ;
	
    $max_results = 5;
    //get credentials 
     $service = check_credentials();
    if ($type == 'visits'){
        $sort = $sort_visits;
        $metrics = $metrics_visits;
     }
    else {
        $sort = $sort_pageviews;
        $metrics = $metrics_pageviews;
    }

    //set optional parameters like sort, dimensions etc
    $optparams = array ('dimensions' => $dimensions,'sort' => $sort,'max-results' => $max_results);
    //get result (analytics object
    $results = $service->data_ga->get(variable_get('os_board_analytics_id'), $start_date, $end_date, $metrics, $optparams);
	}
    catch (Exception $e){
	   drupal_set_message(t('Issue authenticating and receiving data. Message = %message, query=%query', 
	           array('%message' =>$e->getMessage(),'%query' => $e->query_string)), 'error');	
	}
    return $results;
}

/* 
* return_users
* no parameters 
* taps into google analytics and retrieves the results for 
* users that are currently active
*/
function return_users(){
     try {
        // declare variables
        $dimensions = 'rt:source';
		$rt_users = 'rt:activeUsers';
		
		//validate the credentials
        $service = check_credentials();
		$optparams = array ('dimensions' => $dimensions);
		
		//get result 
		$results = $service->data_realtime->get(variable_get('os_board_analytics_id'), $rt_users);
		}
		catch (Exception $e){
		   drupal_set_message(t('Issue authenticating and receiving data. Message = %message, query=%query', 
	           array('%message' =>$e->getMessage(),'%query' => $e->query_string)), 'error');	
		
		}
		//return the results
		return $results;	
}

/* 
* return_pages
* no parameters 
* taps into google analytics and retrieves the results for 
* pages that are currently active
*/
function return_pages(){
    try {
        // declare variables
        $dimensions = 'rt:pagePath,rt:pageTitle';
		$sort = '-rt:pageviews';
		$max_results = 5;
		$page_views = 'rt:pageviews';
		
		//validate the credentials
	    $service = check_credentials();
        $optparams = array ('dimensions' => $dimensions , 'sort' =>  $sort, 'max-results' => $max_results );
		
		//get result 
		$results = $service->data_realtime->get(variable_get('os_board_analytics_id'),$page_views, $optparams);
		}
		catch (Exception $e){
		   drupal_set_message(t('Issue authenticating and receiving data. Message = %message, query=%query', 
	           array('%message' =>$e->getMessage(),'%query' => $e->query_string)), 'error');	
		  
		}
		//return the results
        return $results;
}