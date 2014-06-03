(function (jQuery) {
Drupal.behaviors.taxonomy = {
    attach: function (context, settings) {
    jQuery(document).ready(function(){
    jQuery('.field-widget-chose-taxonomy input').each(function() {
      if (jQuery(this).is(':checked')) {
        jQuery(this).siblings('label').addClass('like-taxonomy-term');
        jQuery(this).siblings('label').removeClass('unlike-taxonomy-term');
      }
      else {
        jQuery(this).siblings('label').removeClass('like-taxonomy-term');
        jQuery(this).siblings('label').addClass('unlike-taxonomy-term');
      }
    });
    });
  }};

})(jQuery);
