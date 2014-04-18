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


function realtime_users(){
    //variables definition block starts
    $output ='';
    //path to the private key
    $file_contents = file_get_contents(drupal_get_path('module', 'os_board') . '/'.REALTIME_PRIVATE_KEY);
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
	/*if($client->isAccessTokenExpired()){
	   $newAccessToken = drupal_json_decode($client->getAccessToken());
	   $client->refreshToken($newAccessToken->refresh_token);} */

    //create a new instance of google_analyticsservice
    $service = new Google_AnalyticsService($client);
    //set optional parameters like sort, dimensions etc
    $optparams = array ('dimensions' => 'rt:source');
    //get result (analytics object
    $results = $service->data_realtime->get(REALTIME_ANALYTICS_ID,'rt:activeUsers');
    //create the header for the table
    return $results;
}