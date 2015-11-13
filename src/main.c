#include <pebble.h>

static Window *s_window;
// static ScrollLayer *s_scroll_layer;
// static TextLayer *s_content_layer;
// static ContentIndicator *s_indicator;
// static Layer *s_indicator_up_layer, *s_indicator_down_layer;

static MenuLayer *s_menu_layer;
#define NUM_WINDOWS 5
#define CHECKBOX_WINDOW_CELL_HEIGHT 30
#define COLOUR_MENU_HIGHLIGHT_BACKGROUND GColorFromHEX(0xE31837)
#define COLOUR_MENU_HIGHLIGHT_FOREGROUND GColorWhite

// static char s_content[] = "Cupcake\n\nDonut\n\nEclair\n\nFroyo\n\nGingerbread\n\nHoneycomb\n\nIce Cream Sandwich\n\nJelly Bean\n\nKitKat\n\nLollipop\n\nMarshmallow\n\n";

static uint16_t get_num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *context) {
  return NUM_WINDOWS;
}

static void draw_row_callback(GContext *ctx, Layer *cell_layer, MenuIndex *cell_index, void *context) {
  switch(cell_index->row) {
    case 0:
      menu_cell_basic_draw(ctx, cell_layer, "1: Awesome!", NULL, NULL);
      break;
    case 1:
      menu_cell_basic_draw(ctx, cell_layer, "2: Alright", NULL, NULL);
      break;
    case 2:
      menu_cell_basic_draw(ctx, cell_layer, "3: Somewhere in Between", NULL, NULL);
      break;
    case 3:
      menu_cell_basic_draw(ctx, cell_layer, "4: A bit down", NULL, NULL);
      break;
    case 4:
      menu_cell_basic_draw(ctx, cell_layer, "5: Really bad!", NULL, NULL);
      break;

    default:
      break;
  }
}

static int16_t get_cell_height_callback(struct MenuLayer *menu_layer, MenuIndex *cell_index, void *context) {
  return CHECKBOX_WINDOW_CELL_HEIGHT;
}

static void select_callback(struct MenuLayer *menu_layer, MenuIndex *cell_index, void *context) {
  switch(cell_index->row) {
    case 0:
      break;
    case 1:
      break;
    case 2:
    case 3:
      break;
    case 4:
      break;
    case 5:
      break;
    default:
      break;
  }
}

static void draw_header_callback(GContext *ctx, const Layer *cell_layer, uint16_t section_index, void *context) {
  menu_cell_basic_header_draw(ctx, cell_layer, "How's it Going? Rate 1-5.");
}

static int16_t get_header_height_callback(struct MenuLayer *menu_layer, uint16_t section_index, void *context) {
  return MENU_CELL_BASIC_HEADER_HEIGHT;
}

static uint16_t get_num_sections_callback(struct MenuLayer *menu_layer, void *context) {
  return 1;
}
// static void window_load(Window *window) {
//   Layer *window_layer = window_get_root_layer(window);
//   GRect bounds = layer_get_bounds(window_layer);

//   s_scroll_layer = scroll_layer_create(bounds);
//   scroll_layer_set_click_config_onto_window(s_scroll_layer, window);
//   scroll_layer_set_shadow_hidden(s_scroll_layer, true);
//   layer_add_child(window_layer, scroll_layer_get_layer(s_scroll_layer));

//   s_content_layer = text_layer_create(GRect(bounds.origin.x, bounds.origin.y, bounds.size.w, 2000));
//   text_layer_set_text(s_content_layer, s_content);
//   text_layer_set_text_alignment(s_content_layer, GTextAlignmentCenter);
//   text_layer_set_font(s_content_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
//   scroll_layer_add_child(s_scroll_layer, text_layer_get_layer(s_content_layer));

//   GSize text_size = text_layer_get_content_size(s_content_layer);
//   layer_set_frame(text_layer_get_layer(s_content_layer), 
//                   GRect(bounds.origin.x, bounds.origin.y, bounds.size.w, text_size.h));
//   scroll_layer_set_content_size(s_scroll_layer, text_size);

//   // Get the ContentIndicator from the ScrollLayer
//   s_indicator = scroll_layer_get_content_indicator(s_scroll_layer);
  
//   // Create two Layers to draw the arrows
//   s_indicator_up_layer = layer_create(GRect(bounds.origin.x, bounds.origin.y, 
//                                       bounds.size.w, STATUS_BAR_LAYER_HEIGHT));
//   s_indicator_down_layer = layer_create(GRect(0, bounds.size.h - STATUS_BAR_LAYER_HEIGHT, 
//                                         bounds.size.w, STATUS_BAR_LAYER_HEIGHT));
//   layer_add_child(window_layer, s_indicator_up_layer);
//   layer_add_child(window_layer, s_indicator_down_layer);

//   // Configure the properties of each indicator
//   const ContentIndicatorConfig up_config = (ContentIndicatorConfig) {
//     .layer = s_indicator_up_layer,
//     .times_out = false,
//     .alignment = GAlignCenter,
//     .colors = {
//       .foreground = GColorBlack,
//       .background = GColorWhite
//     }
//   };
//   content_indicator_configure_direction(s_indicator, ContentIndicatorDirectionUp, 
//                                         &up_config);

//   const ContentIndicatorConfig down_config = (ContentIndicatorConfig) {
//     .layer = s_indicator_down_layer,
//     .times_out = false,
//     .alignment = GAlignCenter,
//     .colors = {
//       .foreground = GColorBlack,
//       .background = GColorWhite
//     }
//   };
//   content_indicator_configure_direction(s_indicator, ContentIndicatorDirectionDown, 
//                                         &down_config);
// }

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  s_menu_layer = menu_layer_create(bounds);
  menu_layer_set_highlight_colors(s_menu_layer, COLOUR_MENU_HIGHLIGHT_BACKGROUND, COLOUR_MENU_HIGHLIGHT_FOREGROUND);
  menu_layer_set_click_config_onto_window(s_menu_layer, window);
  menu_layer_set_callbacks(s_menu_layer, NULL, (MenuLayerCallbacks) {
      .get_num_rows = (MenuLayerGetNumberOfRowsInSectionsCallback)get_num_rows_callback,
      .draw_row = (MenuLayerDrawRowCallback)draw_row_callback,
      .get_cell_height = (MenuLayerGetCellHeightCallback)get_cell_height_callback,
      .select_click = (MenuLayerSelectCallback)select_callback,
      .draw_header = (MenuLayerDrawHeaderCallback)draw_header_callback,
      .get_header_height = (MenuLayerGetHeaderHeightCallback)get_header_height_callback,
      .get_num_sections = (MenuLayerGetNumberOfSectionsCallback)get_num_sections_callback,
  });
  layer_add_child(window_layer, menu_layer_get_layer(s_menu_layer));
}

// static void window_unload(Window *window) {
//   scroll_layer_destroy(s_scroll_layer);
//   text_layer_destroy(s_content_layer);
//   layer_destroy(s_indicator_up_layer);
//   layer_destroy(s_indicator_down_layer);
// }

static void window_unload(Window *window) {
  menu_layer_destroy(s_menu_layer);
}

static void init() {
  s_window = window_create();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  window_stack_push(s_window, true);
}

static void deinit() {
  window_destroy(s_window);
}

int main() {
  init();
  app_event_loop();
  deinit();
}
