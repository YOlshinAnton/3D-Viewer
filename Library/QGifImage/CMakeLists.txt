add_library(QGifImage STATIC
    giflib/gif_hash.h
    giflib/gif_lib_private.h
    giflib/gif_lib.h
    giflib/egif_lib.c
    giflib/gif_err.c
    giflib/gif_font.c
    giflib/gifalloc.c
    giflib/gif_hash.c
    giflib/quantize.c
    giflib/dgif_lib.c
    qgifglobal.h
    qgifimage.h
    qgifimage_p.h
    qgifimage.cpp)
target_include_directories(QGifImage PUBLIC $<INSTALL_INTERFACE:giflib>)
target_link_libraries(QGifImage PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(QGifImage PRIVATE Qt${QT_VERSION_MAJOR}::Gui)
