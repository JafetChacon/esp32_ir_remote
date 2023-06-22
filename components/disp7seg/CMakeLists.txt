#set(COMPONENT_SRCS "disp7seg.c")
#set(COMPONENT_ADD_INCLUDEDIRS ".")
#register_component()

idf_component_register(SRCS "disp7seg.c"
                       INCLUDE_DIRS "."
                       REQUIRES driver)
