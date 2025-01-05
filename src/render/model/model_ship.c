#include "model_ship.h"

#include "render/model/model_builder.h"

void ModelShip_build(ModelBuilder *model_builder) {
  float outer_length = 3.0f;
  float inner_length = 2.7f;

  float outer_width = 2.0f;
  float inner_width = 1.8f;

  float outer_height = 1.0f;
  float inner_height = 0.9f;

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

  ModelBuilder_push_quad(model_builder, ibfl, V2_00, ibfr, V2_01, ibbr, V2_11,
                         ibbl, V2_10);

  ModelBuilder_push_quad(model_builder, itfl, V2_00, itfr, V2_01, ibfr, V2_11,
                         ibfl, V2_10);

  ModelBuilder_push_quad(model_builder, ibbl, V2_00, ibbr, V2_01, itbr, V2_11,
                         itbl, V2_10);

  ModelBuilder_push_quad(model_builder, itfl, V2_00, itbl, V2_01, ibbl, V2_11,
                         ibfl, V2_10);

  ModelBuilder_push_quad(model_builder, itfr, V2_00, itbr, V2_01, ibbr, V2_11,
                         ibfr, V2_10);

  ModelBuilder_push_quad(model_builder, obfl, V2_00, obfr, V2_01, obbr, V2_11,
                         obbl, V2_10);

  ModelBuilder_push_quad(model_builder, otfl, V2_00, otfr, V2_01, obfr, V2_11,
                         obfl, V2_10);

  ModelBuilder_push_quad(model_builder, obbl, V2_00, obbr, V2_01, otbr, V2_11,
                         otbl, V2_10);

  ModelBuilder_push_quad(model_builder, otfl, V2_00, otbl, V2_01, obbl, V2_11,
                         obfl, V2_10);

  ModelBuilder_push_quad(model_builder, otfr, V2_00, otbr, V2_01, obbr, V2_11,
                         obfr, V2_10);

  ModelBuilder_push_quad(model_builder, over_ibfl, V2_00, over_ibfr, V2_01,
                         over_obfr, V2_11, over_obfl, V2_10);

  ModelBuilder_push_quad(model_builder, over_itfl, V2_00, over_itfr, V2_01,
                         over_otfr, V2_11, over_otfl, V2_10);

  ModelBuilder_push_quad(model_builder, over_ibbl, V2_00, over_ibfl, V2_01,
                         over_obfl, V2_11, over_obbl, V2_10);

  ModelBuilder_push_quad(model_builder, over_itbl, V2_00, over_itfl, V2_01,
                         over_otfl, V2_11, over_otbl, V2_10);

  ModelBuilder_push_quad(model_builder, over_ibbr, V2_00, over_ibbl, V2_01,
                         over_obbl, V2_11, over_obbr, V2_10);

  ModelBuilder_push_quad(model_builder, over_itbr, V2_00, over_itbl, V2_01,
                         over_otbl, V2_11, over_otbr, V2_10);

  ModelBuilder_push_quad(model_builder, over_itfr, V2_00, over_itbr, V2_01,
                         over_otbr, V2_11, over_otfr, V2_10);

  ModelBuilder_push_quad(model_builder, over_ibfr, V2_00, over_ibbr, V2_01,
                         over_obbr, V2_11, over_obfr, V2_10);

  ModelBuilder_push_quad(model_builder, over_obfl, V2_00, over_obfr, V2_01,
                         over_otfr, V2_11, over_otfl, V2_10);

  ModelBuilder_push_quad(model_builder, over_obbl, V2_00, over_obfl, V2_01,
                         over_otfl, V2_11, over_otbl, V2_10);

  ModelBuilder_push_quad(model_builder, over_obbr, V2_00, over_obbl, V2_01,
                         over_otbl, V2_11, over_otbr, V2_10);

  ModelBuilder_push_quad(model_builder, over_otfr, V2_00, over_otbr, V2_01,
                         over_obbr, V2_11, over_obfr, V2_10);

  return;
}
