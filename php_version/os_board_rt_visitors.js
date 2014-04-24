(function ($) {
  Drupal.behaviors.yourBehaviorName = {
    attach: function (context, settings) {
      // Do your thing here.
	  var url = '?q=os_board/rt-visits'
	  setInterval(function() {
	  $( "#realtime_users" ).load( "?q=os_board/real-time-visitors #realtime_users", function() {
    //$('#realtime_users').html(result);;
})
       }, 1000); 
    }
  };
})(jQuery);