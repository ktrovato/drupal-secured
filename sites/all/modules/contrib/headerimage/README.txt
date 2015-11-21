This module allows you to display an image in a block where the selection
of the image is based on conditions per image.

Each image, included in a node, can be shown based on node id, path,
taxonomy, book or PHP code. Headerimage has an arbitrary content type to work
with.

Multiple images (nodes) can be displayed in one block, with each image
having its own conditions. Using a weight per node the order of selection
can be controlled.


-- INSTALLATION --

* Copy header image module to your modules directory and enable it on the
  admin modules page.

* Set access rights for admin and view on the access control page.

* If required create a content type to put your image in.
  Set content type(s) and conditions types on the header image settings page
  Structure > Header image > Settings

* Create one or more blocks for header image at the add block page.
  Structure > Header image > Add block

* Using the selected content type, upload one image into the node using an image
  field.
  Image header is designed to work with a node containing only one image.
  However with custom theming you can display any node content and any
  part of the node content. By default the node content without the
  title, taxonomy or links is shown in teaser view.

* Enter the display conditions to the node.
  Different type of conditions are available: node id, URL, taxonomy, etc.
  Select the conditions types you will use (site wide) on the header image
  settings page: Site configuration > Header image > Settings

  The header image node will be displayed when one of it's display conditions
  are met (evaluated to TRUE). Empty or not selected conditions are evaluated
  false.

  For testing purpose it may be convenient to show a block on all pages.
  See Troubleshooting below.

* Change the weight of the display condition to influence the order in which
  display conditions are evaluated from one node to another. For example,
  a header image node with weight 0 is evaluated before a header image with
  weight 1.

* Assign the block to the region of your choice in the Blocks administration
  page.
  Site building > Blocks


-- TROUBLESHOOTING --

* Use the condition weight to control the order in which the conditions are
  evaluated. The node with the smallest weight number will be evaluated
  first.
  Tip: To use one image as default give it a high weight (10) and a
  condition always evaluating to true.
  For example: path: '*' or PHP: <?php return true; ?>

* If the block is (partly) not visible, check the Display settings of your
  content type. Header image uses the teaser view or full view depending
  on the Teaser setting.
  Administer > Content management > Content types > MyHeaderImageContentType > Display fields


-- THEMING --

* By default the block will show the content of the node, without the
  title, taxonomy or links. The node is shown in teaser view or full view
  depending on the Teaser setting.


-- AUTHOR --

Erik Stielstra
For contact: http://drupal.org/user/73854
