AUTOMAKE_OPTIONS = subdir-objects
# ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

ACLOCAL_AMFLAGS = -I m4
bin_PROGRAMS = devmem2

devmem2_SOURCES = src/dfmc/devmem2/devmem2.c

lib_LTLIBRARIES = libdfmcframework-@DFMCFRAMEWORK_API_VERSION@.la
libdfmcframework_@DFMCFRAMEWORK_API_VERSION@_la_SOURCES = src/dfmc/base/Exceptions.cpp \
	src/dfmc/base/getopt/OptionParser.cpp \
	src/dfmc/base/getopt/OptionUtil.cpp \
	src/dfmc/base/graphics/ColorUtil.cpp \
	src/dfmc/base/graphics/RawBitmap.cpp \
	src/dfmc/base/graphics/RawBitmapEx.cpp \
	src/dfmc/base/graphics/RawBitmapUtil.cpp \
	src/dfmc/base/graphics/RenderConfig.cpp \
	src/dfmc/base/io/FileUtil.cpp \
	src/dfmc/base/log/Logger.cpp \
	src/dfmc/base/log/LogKeyValueStringBuilder.cpp \
	src/dfmc/base/log/LogLocation.cpp \
	src/dfmc/base/log/LogStringEncoder.cpp \
	src/dfmc/base/log/adapter/LogAdapterCout.cpp \
	src/dfmc/base/math/Box.cpp \
	src/dfmc/base/math/Math.cpp \
	src/dfmc/base/math/Matrix.cpp \
	src/dfmc/base/math/Rect.cpp \
	src/dfmc/base/math/Rectangle.cpp \
	src/dfmc/base/rtti/TypeInfo.cpp \
	src/dfmc/base/string/ParseUtil.cpp \
	src/dfmc/base/system/HighResolutionTimer.cpp \
	src/dfmc/base/system/ProcessAffinity.cpp \
	src/dfmc/base/system/SystemMemoryAccess.cpp \
	src/dfmc/base/system/adapter/ScopedSystemMemoryAccessLinux.cpp \
	src/dfmc/base/thread/Thread.cpp \
	src/dfmc/cbase/ParseString.c \
	src/dfmc/demo/ADemoApp.cpp \
	src/dfmc/demo/DemoAppController.cpp \
	src/dfmc/demo/DemoConfig.cpp \
	src/dfmc/demo/DemoDataProvider.cpp \
	src/dfmc/demo/directfb/DemoDirectFB.cpp \
	src/dfmc/demo/egl/DemoEGL.cpp \
	src/dfmc/eglhelper/NativeWindowManager.cpp \
	src/dfmc/eglhelper/androidlinux/NativeWindowAndroidLinux.cpp \
	src/dfmc/eglhelper/directfb/NativeWindowDirectFB.cpp \
	src/dfmc/eglhelper/surfaceflinger/NativeWindowSurfaceFlinger.cpp \
	src/dfmc/eglhelper/win32/NativeWindowWin32.cpp \
	src/dfmc/eglhelper/x11/NativeWindowX11.cpp \
	src/dfmc/graphics/procedural/IndexUtil.cpp \
	src/dfmc/graphics/procedural/ModelBuilder.cpp \
	src/dfmc/graphics/procedural/Quad.cpp \
	src/dfmc/graphics/procedural/Torus.cpp \
	src/dfmc/graphics/procedural/Util.cpp \
	src/dfmc/graphics/procedural/VertexUtil.cpp \
	src/dfmc/graphics/render3D/IndexBuffer.cpp \
  src/dfmc/graphics/render3D/CompiledShader.cpp \
	src/dfmc/graphics/render3D/ShaderBase.cpp \
  src/dfmc/graphics/render3D/ShaderCompiler.cpp \
	src/dfmc/graphics/render3D/SimpleModel.cpp \
	src/dfmc/graphics/render3D/Texture.cpp \
	src/dfmc/graphics/render3D/TextureArea.cpp \
	src/dfmc/graphics/render3D/TextureRect.cpp \
	src/dfmc/graphics/render3D/TextureUtil.cpp \
	src/dfmc/graphics/render3D/VertexBuffer.cpp \
	src/dfmc/graphics/render3D/VirtualTextureRect.cpp \
	src/dfmc/graphics/render3D/gl/GLUtil.cpp \
	src/dfmc/graphics/render3D/shaders/TextureShader.cpp \
	src/dfmc/graphics/render3D/shaders/WhiteShader.cpp \
	src/dfmc/graphics/render3D/util/ModelRender.cpp \
	src/dfmc/graphics/render3D/util/ModelRenderBasic.cpp \
	src/dfmc/graphics/render3D/util/ModelRenderNormals.cpp \
	src/dfmc/graphics/render3D/util/ModelRenderVB.cpp \
	src/dfmc/graphics/renderVG/PathBuffer.cpp
  
#libdfmcframework_@DFMCFRAMEWORK_API_VERSION@_la_LDFLAGS = -version-info $(EXAMPLE_SO_VERSION)

dfmcframework_includedir = $(includedir)/dfmcframework-$(DFMCFRAMEWORK_API_VERSION)
nobase_dfmcframework_include_HEADERS =\
	include/dfmc/base/*.hpp \
	include/dfmc/base/getopt/*.hpp \
	include/dfmc/base/graphics/*.hpp \
	include/dfmc/base/io/*.hpp \
	include/dfmc/base/log/*.hpp \
	include/dfmc/base/math/*.hpp \
	include/dfmc/base/rtti/*.hpp \
	include/dfmc/base/string/*.hpp \
	include/dfmc/base/system/*.hpp \
	include/dfmc/base/system/adapter/*.hpp \
	include/dfmc/base/thread/*.hpp \
	include/dfmc/cbase/*.h \
	include/dfmc/cbase/getopt/*.h \
	include/dfmc/demo/*.hpp \
	include/dfmc/demo/directfb/*.hpp \
	include/dfmc/demo/egl/*.hpp \
	include/dfmc/demo/glut/*.hpp \
	include/dfmc/eglhelper/*.hpp \
	include/dfmc/graphics/procedural/*.hpp \
	include/dfmc/graphics/render3D/*.hpp \
	include/dfmc/graphics/render3D/shaders/*.hpp \
	include/dfmc/graphics/render3D/util/*.hpp \
	include/dfmc/graphics/renderVG/*.hpp

dfmcframework_libincludedir = $(libdir)/dfmcframework-$(DFMCFRAMEWORK_API_VERSION)/include
# nodist_dfmcframework_libinclude_HEADERS = dfmcframeworkconfig.h

# XEXTRA_DIST = autogen.sh

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = dfmcframework-$(DFMCFRAMEWORK_API_VERSION).pc

dist_noinst_SCRIPTS = autogen.sh
