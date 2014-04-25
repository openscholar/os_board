/* 
 * Refresh pages and users by loading the div with tag= "#realtime_users" and
 * #realtime_pages" for users and pages respectively inside their tags
 * The refresh rate is set at 5 * 60000 (currently) as there is a quota enabled
 */
(function ($) {
  Drupal.behaviors.os_board = {
    attach: function(context,settings) {
	//declare variables
	var time_interval = 1000;
	var element_users = "#realtime_users";
	var element_pages = "#realtime_pages" ;
	var page_user_url = "os_board/active_users_pages #realtime_users";
	var page_page_url = "os_board/active_users_pages #realtime_pages";
	
	//setInterval function for both users and pages
     setInterval(function() {
	  $(element_users).load(page_user_url, function() {
				})
       }, time_interval);
	   
	 setInterval(function() {
	  $(element_pages).load(page_page_url, function() {
 			})
       }, time_interval);
		
    }
  };
})(jQuery);
