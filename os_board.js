(function ($) {
  Drupal.behaviors.os_board = {
    attach: function(context,settings) {
     setInterval(function() {
	  $( "#realtime_users" ).load( "os_board/active_users_pages #realtime_users", function() {
				})
       }, 1000);
	   
	 setInterval(function() {
	  $( "#realtime_pages" ).load( "os_board/active_users_pages #realtime_pages", function() {
 
			})
       }, 1000);
		
    }
  };
})(jQuery);
