$Id: README.txt,v 1.3.2.1 2010/12/26 22:18:16 yukare Exp $

Custom filter module provides an ability to create some filter without writing
any module.
When we create a new Input format, we will be asked to choose the filters we
want. Some modules hook into filter module and provide additional filters here,
e.g. Textile, GeshiFilter, MathFilter. This module does the same thing, except
that it allows the users with the right permission to define their own filters.

How do we define our own filters?
First, we need to create a filter; a filter is a container for filter rules.
When we create/configure a new input format, every defined filter will appear in
the filters list.

A filter is only a container. We need to define some filter rules if we want it
to work. So, an input format contains one or more filters, each of those has its
own filter rules.

The project page for this module in drupal is http://drupal.org/project/customfilter

Documentation and some examples are in http://drupal.org/node/210551

=INSTALLATION=

1. Just copy the entire Custom filter directory into the module directory, and
   enable it at Administer/Site building/Modules.
2. The settings page is at admin/settings/customfilter.
   Non-administrator users need to have "administer customfilter" permission to
   use this.

=NOTES=

1. The PHP code used in the replacement rules must set the variable $result, which
   is then used from the module.
2. The variable $vars is an instance of stdClass(); therefore it cannot be used
   as an array.
3. The module defines a new constant that allows PHP code used in the
   replacement rules to know the version of the API implemented from the module.
