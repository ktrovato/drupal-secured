<!DOCTYPE html>
<html lang="<?php print $language->language; ?>" dir="<?php print $language->dir; ?>"<?php print $rdf_namespaces;?>>
<head profile="<?php print $grddl_profile; ?>">
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <?php print $head; ?>
  <title><?php print $head_title; ?></title>
  <?php print $styles; ?>
  <!-- HTML5 element support for IE6-8 -->
  <!--[if lt IE 9]>
    <script src="//html5shiv.googlecode.com/svn/trunk/html5.js"></script>
  <![endif]-->
  <?php print $scripts; ?>
    <!--delete on production site-->
  <meta name="robots" content="noindex" />
  <meta name="robots" content="nofollow" />
  <meta name="robots" content="noarchive" />
  <meta name="robots" content="nosnippet" />
  <meta name="googlebot" content="noindex" />
  <meta name="googlebot" content="nofollow" />
  <meta name="googlebot" content="noarchive" />
  <meta name="googlebot" content="nosnippet" />
  <!--[if gte IE 9]>
  <style type="text/css">
    .gradient {
       filter: none;
    }
  </style>
<![endif]-->
<!--this makes sure that blocks in a row are the same height-->
  <script type="text/javascript">
	function equalHeight(group) {
	tallest = 0;
	group.each(function() {
	thisHeight = $(this).height();
	if(thisHeight > tallest) {
	tallest = thisHeight;
	}
	});
	group.height(tallest);
	}
	$(document).ready(function() {
	equalHeight($(".eqpanel"));
	});
</script>

<script src="https://ajax.googleapis.com/ajax/libs/jquery/1.8.3/jquery.min.js">
</script> 

</head>
<body class="<?php print $classes; ?>" <?php print $attributes;?>>
  <div id="skip-link">
    <a href="#main-content" class="element-invisible element-focusable"><?php print t('Skip to main content'); ?></a>
  </div>
  <?php print $page_top; ?>
  <?php print $page; ?>
  <?php print $page_bottom; ?>
</body>
</html>
