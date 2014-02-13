# Attention

The Navbar module is incompatible with Drupal 7 core's Toolbar module. Toolbar
module should be disabled before the Navbar module is enabled.

# Special installation instructions

## Modernizr

You will need a build of Modernzr in your libraries directory for this module. Follow the steps below to create this build.

(from Devin Carlson in [#2119945](https://drupal.org/comment/8015709#comment-8015709))

1. Grab a [preconfigured version of Modernizr](http://modernizr.com/download/#-inputtypes-svg-touch-cssclasses-addtest-teststyles-prefixes-elem_details)
1. Rename the resulting file to modernizer.js
1. Place the file in sites/all/libraries/modernizr (or a site specific folder as required), so the modernizr file can be found at sites/all/libraries/modernizr/modernizr.js

## Backbone

1. Download backbone.js from [GitHub](https://github.com/jashkenas/backbone).
1. Place the file in sites/all/libraries/backbone (or a site specific folder as required).

## Underscore

1. Download underscore.js from [GitHub](https://github.com/jashkenas/underscore).
1. lace the file in sites/all/libraries/underscore (or a site specific folder as required).
