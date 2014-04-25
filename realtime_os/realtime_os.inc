<?php
define('REALTIME_SCOPES','https://www.googleapis.com/auth/analytics.readonly');
//private key required for service accounts authentication
define('REALTIME_PRIVATE_KEY','be3c3443dfb041d42ceb33ef76937b24878fe9c2-privatekey.p12');
//clientid of the service account
define('REALTIME_CLIENT_ID','1076290322756-mgfner7ir4gq87t88mqlq77ps8tp93sv.apps.googleusercontent.com');
//this defines the access type which is by default online unless specified as offline
define('REALTIME_ACCESS_TYPE','offline_access');
//the gmail of the service account holder
define('REALTIME_SERVICE_GMAIL','1076290322756-mgfner7ir4gq87t88mqlq77ps8tp93sv@developer.gserviceaccount.com');
//analyticsid of the account
define('REALTIME_ANALYTICS_ID','ga:35141798');
//the start date of the report


function check_credentials(){
    //variables definition block starts
    $output ='';
    //path to the private key
    $file_contents = file_get_contents(drupal_get_path('module', 'realtime_os') . '/'.REALTIME_PRIVATE_KEY);
    //variables definition block ends

    //create a new instance of Google_client
    $client = new Google_Client();
    // set the application name
    $client->setApplicationName('Realtime OS board');
    //set the credentials, clientid and accesstype
    $client->setAssertionCredentials(new Google_AssertionCredentials(REALTIME_SERVICE_GMAIL, array(REALTIME_SCOPES),
        $file_contents));
    $client->setClientId(REALTIME_CLIENT_ID);
    $client->setAccessType(REALTIME_ACCESS_TYPE);
	$client->getAccessToken();
	
    //create a new instance of google_analyticsservice
    $service = new Google_AnalyticsService($client);
    //set optional parameters like sort, dimensions etc
	return $service;
	
	}
	
	
function os_design_output($type){
    //variables definition block starts
    $output ='';
	$app_name = 'OS Board';
	$metrics_pageviews = 'ga:pageviews';
    $metrics_visits = 'ga:visits';
    $sort_pageviews = '-ga:pageviews';
    $sort_visits = '-ga:visits';
   
    $dimensions = 'ga:hostname';
    $max_results = 5;
    //path to the private key
    $file_contents = file_get_contents(drupal_get_path('module', 'os_board') . '/'.REALTIME_PRIVATE_KEY);
    //variables definition block ends

    //create a new instance of Google_client
    $client = new Google_Client();
    // set the application name
    $client->setApplicationName($app_name);
    //set the credentials, clientid and accesstype
    $client->setAssertionCredentials(new Google_AssertionCredentials(REALTIME_SERVICE_GMAIL, array(REALTIME_SCOPES), $file_contents));
    $client->setClientId(REALTIME_CLIENT_ID);
    $client->setAccessType('offline_access');
    $client->setAccessType('offline_access');

    //create a new instance of google_analyticsservice
    $service = new Google_AnalyticsService($client);
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
    $results = $service->data_ga->get(ANALYTICS_ID, START_DATE, END_DATE, $metrics, $optparams);
    //create the header for the table
    return $results;
}

function return_users(){
        $service = check_credentials();
		$optparams = array ('dimensions' => 'rt:source');
		//get result (analytics object
		$results = $service->data_realtime->get(REALTIME_ANALYTICS_ID,'rt:activeUsers');
		return $results;
	
}

function return_pages(){
        $service = check_credentials();
        $optparams = array ('dimensions' => 'rt:pagePath,rt:pageTitle', 'sort' => '-rt:pageviews', 'max-results' => 5);
		//get result (analytics object
		$results = $service->data_realtime->get(REALTIME_ANALYTICS_ID,'rt:pageviews', $optparams);
        return $results;
}
