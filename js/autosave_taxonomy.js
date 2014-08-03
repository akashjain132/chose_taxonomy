(function (jQuery) {
Drupal.behaviors.autosave_taxonomy = {
  attach: function (context, settings) {
    jQuery(document).ready(function() {
      var clicked_image   = Drupal.settings.autosave_taxonomy.cliked_image;
      var unclicked_image = Drupal.settings.autosave_taxonomy.uncliked_image;

      jQuery('.field-widget-autosave-taxonomy input').each(function() {
        if (jQuery(this).is(':checked')) {
          jQuery(this).siblings('label').addClass('like-taxonomy-term');
          jQuery(this).siblings('label').removeClass('unlike-taxonomy-term');
        }
        else {
          jQuery(this).siblings('label').removeClass('like-taxonomy-term');
          jQuery(this).siblings('label').addClass('unlike-taxonomy-term');
        }
      });

      jQuery('.unlike-taxonomy-term').css('background', 'url(/' + clicked_image + ') no-repeat scroll right center transparent');
      jQuery('.like-taxonomy-term').css('background', 'url(/' + unclicked_image + ') no-repeat scroll right center transparent');

      jQuery('.like-taxonomy-term').hover(function() {
        jQuery(this).css('background', 'url(/' + clicked_image + ') no-repeat scroll right center transparent');
      },function() {
        jQuery(this).css('background', 'url(/' + unclicked_image + ') no-repeat scroll right center transparent');
      });

      jQuery('.unlike-taxonomy-term').hover(function() {
        jQuery(this).css('background', 'url(/' + unclicked_image + ') no-repeat scroll right center transparent');
      },function() {
        jQuery(this).css('background', 'url(/' + clicked_image + ') no-repeat scroll right center transparent');
      });

    });
  }};

})(jQuery);
