<?php
define('SCOPES','https://www.googleapis.com/auth/analytics.readonly');
//private key required for service accounts authentication
define('PRIVATE_KEY','be3c3443dfb041d42ceb33ef76937b24878fe9c2-privatekey.p12');
//clientid of the service account
define('CLIENT_ID','1076290322756-mgfner7ir4gq87t88mqlq77ps8tp93sv.apps.googleusercontent.com');
//this defines the access type which is by default online unless specified as offline
define('ACCESS_TYPE','offline_access');
//the gmail of the service account holder
define('SERVICE_GMAIL','1076290322756-mgfner7ir4gq87t88mqlq77ps8tp93sv@developer.gserviceaccount.com');
//analyticsid of the account
define('ANALYTICS_ID','ga:35141798');
//the start date of the report
define('START_DATE','2014-03-26');
//the end date of the report
define('END_DATE','2014-04-16');
//the type of report : pageviews or visits
define('METRICS_PAGEVIEWS','ga:pageviews' );
define('METRICS_VISITS','ga:visits');
define('SORT_PAGEVIEWS', '-ga:pageviews');
define('SORT_VISITS', '-ga:visits');
define('HEADER_VISITS', 'Most Visited Sites');
define('HEADER_VIEWS','Most viewed pages');
define('VISITED_NUMBER','Number Visited');
define('APP_HEADING','OpenScholar Board');
define('DIMENSIONS','ga:hostname');
define('MAX_RESULTS','25');

/*
 * design_output
 * parameter: type [visits,pageviews]
 * output: results/data acquired from googleanalytics api
 * main work of getting report data and for visits and pageviews done here and
 * results sent to individual functions
 */
function design_output($type){
    //variables definition block starts
    $output ='';
    //path to the private key
    $file_contents = file_get_contents(drupal_get_path('module', 'os_board') . '/'.PRIVATE_KEY);
    //variables definition block ends

    //create a new instance of Google_client
    $client = new Google_Client();
    // set the application name
    $client->setApplicationName(APP_HEADING);
    //set the credentials, clientid and accesstype
    $client->setAssertionCredentials(new Google_AssertionCredentials(SERVICE_GMAIL, array(SCOPES), $file_contents));
    $client->setClientId(CLIENT_ID);
    $client->setAccessType(ACCESS_TYPE);

    //create a new instance of google_analyticsservice
    $service = new Google_AnalyticsService($client);
    if ($type == 'visits'){
        $sort = SORT_VISITS;
        $metrics = METRICS_VISITS;
        $header = HEADER_VISITS;
    }
    else {
        $sort = SORT_PAGEVIEWS;
        $metrics = METRICS_PAGEVIEWS;
        $header = HEADER_VIEWS;
    }

    //set optional parameters like sort, dimensions etc
    $optparams = array ('dimensions' => DIMENSIONS,'sort' => $sort,'max-results' => MAX_RESULTS);
    //get result (analytics object
    $results = $service->data_ga->get(ANALYTICS_ID, START_DATE, END_DATE, $metrics, $optparams);
    //create the header for the table
    return $results;
}
