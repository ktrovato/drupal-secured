<?php

/**
 * Can determine a weight for a rule key based on wildcard weights.
 *
 * E.g. if the weight settings are
 *   * = 0
 *   crumbs.* = 4
 *   crumbs.nodeParent.* = 5
 * and then we are looking for a weight for
 *   crumbs.nodeParent.page
 * then the weight keeper will return 5, because crumbs.nodeParent.* is the best
 * matching wildcard.
 */
class crumbs_Container_WildcardDataSorted extends crumbs_Container_WildcardData {

  /**
   * @param array $data
   *   Weights with wildcards, as saved in the configuration form.
   */
  function __construct(array $data) {
    asort($data);
    parent::__construct($data);
  }

  /**
   * Get the smallest weight in range.
   *
   * @return int
   *   The smallest weight..
   */
  function smallestValue() {
    foreach ($this->data as $value) {
      if ($value !== FALSE) {
        return $value;
      }
    }
    return FALSE;
  }
}
