function makeApiCall() {
  console.log('Starting Request Process...');
  queryAccounts();
}


function queryAccounts() {
  console.log('Querying Accounts.');

  // Get a list of all Google Analytics accounts for this user
  gapi.client.analytics.management.accounts.list().execute(handleAccounts);
}


function handleAccounts(results) {
  if (!results.code) {
    if (results && results.items && results.items.length) {

      // Get the first Google Analytics account
      var firstAccountId = results.items[0].id;

      // Query for Web Properties
      queryWebproperties(firstAccountId);

    } else {
      console.log('No accounts found for this user.')
    }
  } else {
    console.log('There was an error querying accounts: ' + results.message);
  }
}


function queryWebproperties(accountId) {
  console.log('Querying Webproperties.');

  // Get a list of all the Web Properties for the account
  gapi.client.analytics.management.webproperties.list({'accountId': accountId}).execute(handleWebproperties);
}


function handleWebproperties(results) {
  if (!results.code) {
    if (results && results.items && results.items.length) {

      // Get the first Google Analytics account
      var firstAccountId = results.items[0].accountId;

      // Get the first Web Property ID
      var firstWebpropertyId = results.items[0].id;

      // Query for Views (Profiles)
      queryProfiles(firstAccountId, firstWebpropertyId);

    } else {
      console.log('No webproperties found for this user.');
    }
  } else {
    console.log('There was an error querying webproperties: ' + results.message);
  }
}


function queryProfiles(accountId, webpropertyId) {
  console.log('Querying Views (Profiles).');

  // Get a list of all Views (Profiles) for the first Web Property of the first Account
  gapi.client.analytics.management.profiles.list({
      'accountId': accountId,
      'webPropertyId': webpropertyId
  }).execute(handleProfiles);
}


function handleProfiles(results) {
  if (!results.code) {
    if (results && results.items && results.items.length) {

      // Get the first View (Profile) ID
      var firstProfileId = results.items[0].id;

      // Step 3. Query the Core Reporting API
      queryCoreReportingApi(firstProfileId);

    } else {
      console.log('No views (profiles) found for this user.');
    }
  } else {
    console.log('There was an error querying views (profiles): ' + results.message);
  }
}


function queryCoreReportingApi(profileId) {
  console.log('Querying Core Reporting API.');

  // Use the Analytics Service Object to query the Core Reporting API
  gapi.client.analytics.data.ga.get({
    'ids': 'ga:' + profileId,
    'start-date': '2014-03-26',
    'end-date': '2014-04-09',
    'metrics': 'ga:visits',
	'dimensions' : 'ga:hostname',
	'sort' : '-ga:visits',
	'max-results' : '50'
  }).execute(handleCoreReportingResults);
}


function handleCoreReportingResults(results) {
  if (results.error) {
    console.log('There was an error querying core reporting API: ' + results.message);
  } else {
    printResults(results);
	printDrupalTable(results);
  }
}


function printResults(results) {
  if (results.rows && results.rows.length) {
    console.log('View (Profile) Name: ', results.profileInfo.profileName);
    console.log('Most Visited Website: ', results.rows[0][0]);
	console.log('Visited Number ', results.rows[0][1]);
  } else {
    console.log('No results found');
  }
}


function printDrupalTable(results) {

  var len = results.rows.length;
  var table = document.getElementById('statistics');
  
  for (var i=0; i<len; i++) {
    var row = table.insertRow(-1);
	var cell1 = row.insertCell(0);
	var cell2 = row.insertCell(1);
	cell1.innerHTML = results.rows[i][0];
    cell2.innerHTML = results.rows[i][1];
  }
}









