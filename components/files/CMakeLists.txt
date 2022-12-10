include_directories(${CMAKE_SOURCE_DIR}/components/files/)
include_directories(${CMAKE_SOURCE_DIR}/components/picture/)
include_directories(${CMAKE_SOURCE_DIR}/components/util/)

set(ODV_FILES_SRC
    odv_file.c
    odv_fxg_handler.c

    odv_fnt_handler.c
    odv_map_handler.c
    odv_dvd_handler.c
    odv_dvf_handler.c
    odv_dvm_handler.c

    resource/odv_resource_handler.c
    resource/odv_resource_text.c
    resource/odv_resource_wave.c
    resource/odv_resource_picc.c
    resource/odv_resource_togl.c
    resource/odv_resource_bttn.c
    resource/odv_resource_cur.c
    resource/odv_resource_nptf.c
    resource/odv_resource_rdo.c

    odv_sxt_handler.c
    odv_scb_disassembler.c
    odv_scb_handler.c
)

add_library(odv_component_files ${ODV_FILES_SRC})