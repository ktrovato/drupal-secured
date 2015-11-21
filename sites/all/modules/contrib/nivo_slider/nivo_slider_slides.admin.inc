<?php

/**
 * @file
 * Generate configuration form and save settings.
 */

/**
 * Configuration form for slider slides.
 */
function nivo_slider_slide_configuration_form($form, &$form_state) {
  // Upload
  $form['upload'] = array(
    '#type' => 'file',
    '#title' => t('Upload a new slide image'),
  );

  // Draggable table
  $form['order'] = array();

  // Vertical tab
  $form['images'] = array(
    '#type' => 'vertical_tabs',
    '#title' => t('Slider images'),
    '#tree' => TRUE,
  );

  // Get all available slides
  $slides = variable_get('nivo_slider_banner_settings', array());

  // Create a vertical tab for each slide
  foreach ($slides as $slide => $settings) {
    $form['images'][$slide] = array(
      '#type' => 'fieldset',
      '#title' => t('Image !number: !title', array(
        '!number' => $slide + 1,
        '!title' => isset($settings['title']) ? $settings['title'] : '',
        )
      ),
      '#weight' => $slide,
    );
    $form['images'][$slide]['name'] = array(
      '#markup' => t('Image !number: !title', array(
        '!number' => $slide + 1,
        '!title' => isset($settings['title']) ? $settings['title'] : '',
        )
      ),
    );
    $form['images'][$slide]['weight'] = array(
      '#type' => 'weight',
      '#delta' => 10,
      '#default_value' => isset($settings['weight']) ? $settings['weight'] : 1,
      '#attributes' => array(
        'class' => array('slide-weight'),
      ),
    );
    $form['images'][$slide]['published'] = array(
      '#type' => 'checkbox',
      '#default_value' => isset($settings['published']) ? $settings['published'] : '',
    );
    $form['images'][$slide]['delete'] = array(
      '#type' => 'checkbox',
      '#default_value' => FALSE,
    );

    // Load the slide's image file
    $file = file_load($settings['fid']);

    // Create a preview image of the slide using an image style if appropriate
    if (variable_get('nivo_slider_image_style', 0) == FALSE) {
      $variables = array(
        'path' => file_create_url($file->uri),
      );
      $image = theme('image', $variables);
    }
    else {
      $variables = array(
        'path' => $file->uri,
        'style_name' => variable_get('nivo_slider_image_style_slide', 'large')
      );
      $image = theme('image_style', $variables);
    }

    $form['images'][$slide]['preview'] = array(
      '#markup' =>  $image,
    );
    $form['images'][$slide]['fid'] = array(
      '#type' => 'hidden',
      '#value' => isset($settings['fid']) ? $settings['fid'] : '',
    );
    $form['images'][$slide]['title'] = array(
      '#type' => 'textfield',
      '#title' => t('Title'),
      '#default_value' => isset($settings['title']) ? $settings['title'] : '',
      '#description' => t('The title is used as alternative text for the slide image.'),
    );
    $form['images'][$slide]['description'] = array(
      '#type' => 'text_format',
      '#title' => t('Description'),
      '#default_value' => isset($settings['description']['value']) ? $settings['description']['value'] : '',
      '#format' => isset($settings['description']['format']) ? $settings['description']['format'] : NULL,
      '#description' => t('The description will be displayed with the slide image.'),
    );
    $form['images'][$slide]['url'] = array(
      '#type' => 'textfield',
      '#title' => t('Link slide to URL'),
      '#default_value' => isset($settings['url']) ? $settings['url'] : '',
      '#description' => t('Specify a path or an absolute URL. An example path is %blog for the blog page. An example absolute URL is %url for the Drupal website. %front is the front page.', array('%blog' => 'blog', '%url' => 'http://drupal.org', '%front' => '<front>')),
    );
    $form['images'][$slide]['visibility'] = array(
      '#type' => 'textarea',
      '#title' => t('Show slide on specific pages'),
      '#description' => t("Specify pages by using their paths. Enter one path per line. The '*' character is a wildcard. Example paths are %blog for the blog page and %blog-wildcard for every personal blog. %front is the front page.", array('%blog' => 'blog', '%blog-wildcard' => 'blog/*', '%front' => '<front>')),
      '#default_value' => isset($settings['visibility']) ? $settings['visibility'] : '*',
    );
    $form['images'][$slide]['transition'] = array(
      '#type' => 'select',
      '#title' => t('Transition'),
      '#options' => array(
        '' => t('- Default -'),
        'sliceDown' => t('Slice Down'),
        'sliceDownLeft' => t('Slice Down Left'),
        'sliceUp' => t('Slice Up'),
        'sliceUpLeft' => t('Slice Up Left'),
        'sliceUpDown' => t('Slice Up Down'),
        'sliceUpDownLeft' => t('Slice Up Down Left'),
        'fold' => t('Fold'),
        'fade' => t('Fade'),
        'random' => t('Random'),
        'slideInRight' => t('Slide In Right'),
        'slideInLeft' => t('Slide in Left'),
        'boxRandom' => t('Box Random'),
        'boxRain' => t('Box Rain'),
        'boxRainReverse' => t('Box Rain Reverse'),
        'boxRainGrow' => t('Box Rain Grow'),
        'boxRainGrowReverse' => t('Box Rain Grow Reverse'),
      ),
      '#description' => t('Select a transition. Selecting an option other than %default will force this slide to use the selected transition every time it appears. It overrides all other effect settings.', array('%default' => '- Default -')),
      '#default_value' => isset($settings['transition']) ? $settings['transition'] : '',
    );
  }

  // Add a theme function to theme the form
  $form['#theme'][] = 'nivo_slider_slide_configuration_form';

  // Add a submit handler to save the slide settings
  $form['#submit'][] = 'nivo_slider_settings_submit';

  return system_settings_form($form);
}

/**
 * Save settings data.
 */
function nivo_slider_settings_submit($form, &$form_state) {
  // Create an array to hold slides
  $slides = array();

  // Create a file object to hold the slide image file
  $file = new stdClass;

  // Process the available slides
  foreach ($form_state['values']['images'] as $slide => $settings) {
    // Ensure that only slide settings are processed
    if (is_numeric($slide)) {
      if (is_array($settings)) {
        // Delete the slide if required otherwise add it to the array of slides
        if ($settings['delete']) {
          // Load the file with the file ID
          if (isset($settings['fid'])) {
            $file = file_load($settings['fid']);

            // Delete the file
            if (!empty($file)) {
              file_delete($file);
            }
          }
        }
        else {
          $slides[] = $settings;
        }
      }
    }
  }

  // Update / create translation source for user defined slide strings
  if (function_exists('i18n_string_update')) {
    nivo_slider_locale_refresh($slides);
  }

  // Create a new slide if an image was uploaded
  if ($file = file_save_upload('upload')) {
    // Store slide images in a folder named 'banner'
    $banner_folder = 'public://banner';

    // Create the banner directory if it does not currently exist
    file_prepare_directory($banner_folder, FILE_CREATE_DIRECTORY);

    // Find information about the file
    $parts = pathinfo($file->filename);

    // Create a destination for the slide image
    $destination = $banner_folder . '/' . $parts['basename'];

    // Indicate that the slide image is permanent
    $file->status = FILE_STATUS_PERMANENT;

    // Copy the slide image into the banner folder
    $file = file_copy($file, $destination, FILE_EXISTS_REPLACE);

    // Create a new slide
    $slides[] = array(
      'fid' => $file->fid,
      'title' => '',
      'description' => array(
        'value' => '',
        'format' => filter_fallback_format(),
      ),
      'url' => '',
      'visibility' => '*',
      'transition' => '',
      'weight' => 1,
      'published' => 1,
      'delete' => 0,
    );
  }

  // Sort the slides by weight
  usort($slides, 'drupal_sort_weight');

  // Save the slides
  variable_set('nivo_slider_banner_settings', $slides);
}
