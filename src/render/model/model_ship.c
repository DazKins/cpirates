#include "model_ship.h"

#include "render/model/model_builder.h"
#include "render/shader.h"

Model *model_ship;

Model *ModelShip_build() {
  if (model_ship != NULL) {
    return model_ship;
  }

  ModelBuilder model_builder = ModelBuilder_new();

  float outer_length = 3.0f;
  float inner_length = 2.7f;

  float outer_width = 2.0f;
  float inner_width = 1.8f;

  float outer_height = 2.0f;
  float inner_height = 0.5f;

  float overhang_length = 0.1f;
  float overhang_depth = 0.2f;

  float ix0 = -inner_width / 2.0f;
  float ix1 = inner_width / 2.0f;

  float iy0 = outer_height / 2.0f - inner_height;
  float iy1 = outer_height / 2.0f;

  float iz0 = -inner_length / 2.0f;
  float iz1 = inner_length / 2.0f;

  float ox0 = -outer_width / 2.0f;
  float ox1 = outer_width / 2.0f;

  float oy0 = -outer_height / 2.0f;
  float oy1 = outer_height / 2.0f;

  float oz0 = -outer_length / 2.0f;
  float oz1 = outer_length / 2.0f;

  float over_y0 = iy1 - overhang_depth;
  float over_y1 = iy1;

  float over_ix0 = ix0;
  float over_ix1 = ix1;

  float over_iz0 = iz0;
  float over_iz1 = iz1;

  float over_oz0 = oz0 - overhang_length;
  float over_oz1 = oz1 + overhang_length;

  float over_ox0 = ox0 - overhang_length;
  float over_ox1 = ox1 + overhang_length;

  V ibfr = V_new(ix1, iy0, iz1);
  V ibfl = V_new(ix0, iy0, iz1);
  V ibbr = V_new(ix1, iy0, iz0);
  V ibbl = V_new(ix0, iy0, iz0);
  V itfr = V_new(ix1, iy1, iz1);
  V itfl = V_new(ix0, iy1, iz1);
  V itbr = V_new(ix1, iy1, iz0);
  V itbl = V_new(ix0, iy1, iz0);

  V obfr = V_new(ox1, oy0, oz1);
  V obfl = V_new(ox0, oy0, oz1);
  V obbr = V_new(ox1, oy0, oz0);
  V obbl = V_new(ox0, oy0, oz0);
  V otfr = V_new(ox1, oy1, oz1);
  V otfl = V_new(ox0, oy1, oz1);
  V otbr = V_new(ox1, oy1, oz0);
  V otbl = V_new(ox0, oy1, oz0);

  V over_ibfr = V_new(over_ix1, over_y0, over_iz1);
  V over_ibfl = V_new(over_ix0, over_y0, over_iz1);
  V over_ibbr = V_new(over_ix1, over_y0, over_iz0);
  V over_ibbl = V_new(over_ix0, over_y0, over_iz0);
  V over_itfr = V_new(over_ix1, over_y1, over_iz1);
  V over_itfl = V_new(over_ix0, over_y1, over_iz1);
  V over_itbr = V_new(over_ix1, over_y1, over_iz0);
  V over_itbl = V_new(over_ix0, over_y1, over_iz0);

  V over_obfr = V_new(over_ox1, over_y0, over_oz1);
  V over_obfl = V_new(over_ox0, over_y0, over_oz1);
  V over_obbr = V_new(over_ox1, over_y0, over_oz0);
  V over_obbl = V_new(over_ox0, over_y0, over_oz0);
  V over_otfr = V_new(over_ox1, over_y1, over_oz1);
  V over_otfl = V_new(over_ox0, over_y1, over_oz1);
  V over_otbr = V_new(over_ox1, over_y1, over_oz0);
  V over_otbl = V_new(over_ox0, over_y1, over_oz0);

  float tex_size = 16.0f / 512.0f;

  V2 uv00 = V2_new(2 * tex_size, 0 * tex_size);
  V2 uv01 = V2_new(2 * tex_size, 1 * tex_size);
  V2 uv10 = V2_new(3 * tex_size, 0 * tex_size);
  V2 uv11 = V2_new(3 * tex_size, 1 * tex_size);

  ModelBuilder_push_quad(&model_builder, ibfl, uv00, ibfr, uv01, ibbr, uv11,
                         ibbl, uv10);

  ModelBuilder_push_quad(&model_builder, itfl, uv00, itfr, uv01, ibfr, uv11,
                         ibfl, uv10);

  ModelBuilder_push_quad(&model_builder, ibbl, uv00, ibbr, uv01, itbr, uv11,
                         itbl, uv10);

  ModelBuilder_push_quad(&model_builder, itfl, uv00, itbl, uv01, ibbl, uv11,
                         ibfl, uv10);

  ModelBuilder_push_quad(&model_builder, itfr, uv00, itbr, uv01, ibbr, uv11,
                         ibfr, uv10);

  ModelBuilder_push_quad(&model_builder, obfl, uv00, obfr, uv01, obbr, uv11,
                         obbl, uv10);

  ModelBuilder_push_quad(&model_builder, otfl, uv00, otfr, uv01, obfr, uv11,
                         obfl, uv10);

  ModelBuilder_push_quad(&model_builder, obbl, uv00, obbr, uv01, otbr, uv11,
                         otbl, uv10);

  ModelBuilder_push_quad(&model_builder, otfl, uv00, otbl, uv01, obbl, uv11,
                         obfl, uv10);

  ModelBuilder_push_quad(&model_builder, otfr, uv00, otbr, uv01, obbr, uv11,
                         obfr, uv10);

  ModelBuilder_push_quad(&model_builder, over_ibfl, uv00, over_ibfr, uv01,
                         over_obfr, uv11, over_obfl, uv10);

  ModelBuilder_push_quad(&model_builder, over_itfl, uv00, over_itfr, uv01,
                         over_otfr, uv11, over_otfl, uv10);

  ModelBuilder_push_quad(&model_builder, over_ibbl, uv00, over_ibfl, uv01,
                         over_obfl, uv11, over_obbl, uv10);

  ModelBuilder_push_quad(&model_builder, over_itbl, uv00, over_itfl, uv01,
                         over_otfl, uv11, over_otbl, uv10);

  ModelBuilder_push_quad(&model_builder, over_ibbr, uv00, over_ibbl, uv01,
                         over_obbl, uv11, over_obbr, uv10);

  ModelBuilder_push_quad(&model_builder, over_itbr, uv00, over_itbl, uv01,
                         over_otbl, uv11, over_otbr, uv10);

  ModelBuilder_push_quad(&model_builder, over_itfr, uv00, over_itbr, uv01,
                         over_otbr, uv11, over_otfr, uv10);

  ModelBuilder_push_quad(&model_builder, over_ibfr, uv00, over_ibbr, uv01,
                         over_obbr, uv11, over_obfr, uv10);

  ModelBuilder_push_quad(&model_builder, over_obfl, uv00, over_obfr, uv01,
                         over_otfr, uv11, over_otfl, uv10);

  ModelBuilder_push_quad(&model_builder, over_obbl, uv00, over_obfl, uv01,
                         over_otfl, uv11, over_otbl, uv10);

  ModelBuilder_push_quad(&model_builder, over_obbr, uv00, over_obbl, uv01,
                         over_otbl, uv11, over_otbr, uv10);

  ModelBuilder_push_quad(&model_builder, over_otfr, uv00, over_otbr, uv01,
                         over_obbr, uv11, over_obfr, uv10);

  model_ship = ModelBuilder_build(&model_builder);

  return model_ship;
}
