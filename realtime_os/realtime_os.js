

 (function ($) {
  $(document).ready(function(){
    
    setInterval(function() {
	  $( "#realtime_users" ).load( "realtime_os/active_users #realtime_users", function() {
  $('#realtime_users').html(result);;
})
       }, 60000);
  });
})(jQuery);  
