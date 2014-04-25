
 (function ($) {
  $(document).ready(function(){
    
    setInterval(function() {
	  $( "#realtime_users" ).load( "realtime_os/active_users #realtime_users", function() {
				})
       }, 1000);
	   
	 setInterval(function() {
	  $( "#realtime_pages" ).load( "realtime_os/active_users #realtime_pages", function() {
 
})
       }, 1000);
	   
  });
  
})(jQuery);  


