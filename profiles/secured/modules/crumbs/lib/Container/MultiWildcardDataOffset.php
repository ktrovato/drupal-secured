<?php

/**
 * Class crumbs_Container_MultiWildcardDataOffset
 *
 * @property array $basicMethods
 * @property array $routeMethods
 * @property array $routes
 */
class crumbs_Container_MultiWildcardDataOffset {

  /**
   * @var crumbs_Container_MultiWildcardData
   */
  protected $container;

  /**
   * @var string
   */
  protected $key;

  /**
   * @param crumbs_Container_MultiWildcardData $container
   * @param string $key
   */
  function __construct($container, $key) {
    $this->container = $container;
    $this->key = $key;
  }

  /**
   * @param string $key
   * @return mixed
   */
  function __get($key) {
    return $this->container->__get($key)->valueAtKey($this->key);
  }

  /**
   * @param string $key
   * @return array
   */
  function getAll($key) {
    return $this->container->__get($key)->getAll($this->key);
  }

  /**
   * @param string $key
   * @return array
   */
  function getAllMerged($key) {
    return $this->container->__get($key)->getAllMerged($this->key);
  }
}
