
 (function ($) {
  $(document).ready(function(){
    
    setInterval(function() {
	  $( "#realtime_users" ).load( "realtime_os/active_users #realtime_users", function() {
 // $('#realtime_users').html(result);;
})
       }, 1000);
  });
  
})(jQuery);  


(function ($) {
  $(document).ready(function(){
    
    setInterval(function() {
	  $( "#realtime_pages" ).load( "realtime_os/active_pages #realtime_pages", function() {
 // $('#realtime_users').html(result);;
})
       }, 1000);
  });
})(jQuery); 
