
set(ODV_FILES_SRC
    odv_file.c
    odv_fxg_handler.c
    odv_resource_handler.c
    odv_resource_text.c
    odv_resource_wave.c
    odv_resource_picc.c
    odv_resource_togl.c
    odv_resource_bttn.c
    odv_resource_cur.c
    odv_resource_nptf.c
    odv_resource_rdo.c
    odv_image.c
    odv_map_handler.c
    odv_dvd_handler.c
    odv_dvm_handler.c
    odv_sxt_handler.c
    odv_scb_disassembler.c
    odv_scb_handler.c
    odv_utils.c)
    
add_library(odv_component_files ${ODV_FILES_SRC})

