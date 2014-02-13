<?php

class crumbs_Container_LazyData {

  /**
   * @var array
   */
  protected $data = array();

  /**
   * @var stdClass
   */
  protected $source;

  /**
   * @param object $source
   */
  function __construct($source) {
    $this->source = $source;
  }

  /**
   * @param string $key
   * @return mixed
   */
  function __get($key) {
    if (!array_key_exists($key, $this->data)) {
      $this->data[$key] = $this->source->$key($this);
    }
    return $this->data[$key];
  }

  /**
   * @param string $key
   * @param mixed $value
   */
  function set($key, $value) {
    $this->data[$key] = $value;
  }

  /**
   * @param string $key
   */
  function reset($key) {
    unset($this->data[$key]);
  }
}
