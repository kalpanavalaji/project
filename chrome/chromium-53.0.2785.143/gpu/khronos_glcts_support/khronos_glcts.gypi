# Copyright 2014 The Chromium Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

{
  'variables': {

    # WA: Suppress [chromium-style] enforcement errors when compiled with
    # clang.  The third_party/khronos_glcts sourcecode does not comply with
    # the chromium-style standards.
    'clang_use_chrome_plugins': 0,

    'glcts_data_dirs': [
      '<(DEPTH)/third_party/khronos_glcts/cts/data',
    ],
    'glcts_gtf_data_dirs': [
        '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/GL',
        '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/GL2ExtensionTests',
        '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/GL2FixedTests',
        '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/GL2Tests',
        '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/GLCoverage',
    ],
    'glcts_gtf_runfiles': [
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/mustpass_es20.run',
    ],
    'gtf_core_srcs': [
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GTFArguments.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GTFFileReader.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GTFLog.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GTFMemFile.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GTFModelData.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GTFPort.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GTFStringUtils.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GTFTest.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GTFTestCompareGL.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GTFTestDriver.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GTFTestElement.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GTFTestUtil.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GTFgl.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/MIMG.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/XmlUtils.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/eglu.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/eglut.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/gl2Native.c',
    ],
    'gtf_gl_core_srcs': [
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL/GTFAttDataGL.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL/GTFDepthRangeParamGL.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL/GTFModelDataGL.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL/GTFPointParamGL.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL/GTFReadPixelsGL.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL/GTFShaderDataGL.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL/GTFShaderTextGL.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL/GTFStateDataGL.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL/GTFTestTextureFloatBase.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL/GTFTexDataGL.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL/GTFTexParamGL.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL/GTFUniDataGL.c',
    ],
    'gtf_gles2_srcs': [
      # Base
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2Tests/GTFGL2TestAttributeGL.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2Tests/GTFGL2TestBindAllAttributes.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2Tests/GTFGL2TestCreateObjectGL.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2Tests/GTFGL2TestDetachGL.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2Tests/GTFGL2TestFixedDataType.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2Tests/GTFGL2TestFramebufferObjects.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2Tests/GTFGL2TestGetAttachedObjects.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2Tests/GTFGL2TestGetAttributeLocation.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2Tests/GTFGL2TestGetBIFD.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2Tests/GTFGL2TestGetExtensions.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2Tests/GTFGL2TestGetProgramInfoLog.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2Tests/GTFGL2TestGetProgramiv.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2Tests/GTFGL2TestGetShaderInfoLog.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2Tests/GTFGL2TestGetShaderiv.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2Tests/GTFGL2TestGetUniform.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2Tests/GTFGL2TestGetVertexAttrib.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2Tests/GTFGL2TestMaxVertexAttrib.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2Tests/GTFGL2TestMultipleShaders.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2Tests/GTFGL2TestRelinkProgram.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2Tests/GTFGL2TestUniform.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2Tests/GTFGL2TestUniformQueryGL.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2Tests/GTFGL2TestVertexAttribPointer.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2Tests/GTFGL2TestVertexAttributes.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2Tests/GTFGL2TestVertexProgramPointSize.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GTFTestGL2Test.c',

      # Build
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GTFTestBuildGL.c',

      # Shader load
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GTFTestShaderLoadGL.c',

      # Rasterization
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GTFTestRasterizationGL.c',

      # Complexity
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GTFTestComplexityGL.c',

      # Coverage
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GTFCoverageDict.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GTFCoverageGL.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GTFTestCoverageGL.c',

      # Fixed-function
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2FixedTests/GTFFixedTestBlend.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2FixedTests/GTFFixedTestBufferClear.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2FixedTests/GTFFixedTestBufferColor.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2FixedTests/GTFFixedTestBufferCorners.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2FixedTests/GTFFixedTestBufferObjects.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2FixedTests/GTFFixedTestClip.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2FixedTests/GTFFixedTestColorRamp.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2FixedTests/GTFFixedTestCopyTexture.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2FixedTests/GTFFixedTestDepthBufferClear.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2FixedTests/GTFFixedTestDepthBufferFunctions.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2FixedTests/GTFFixedTestDither.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2FixedTests/GTFFixedTestDivideByZero.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2FixedTests/GTFFixedTestGets.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2FixedTests/GTFFixedTestMipmapsInterpolation.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2FixedTests/GTFFixedTestMipmapsSelection.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2FixedTests/GTFFixedTestPointRasterization.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2FixedTests/GTFFixedTestPointSprites.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2FixedTests/GTFFixedTestPolygonCull.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2FixedTests/GTFFixedTestScissor.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2FixedTests/GTFFixedTestStencilPlaneClear.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2FixedTests/GTFFixedTestStencilPlaneCorners.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2FixedTests/GTFFixedTestStencilPlaneFunction.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2FixedTests/GTFFixedTestStencilPlaneOperation.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2FixedTests/GTFFixedTestTextureEdgeClamp.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2FixedTests/GTFFixedTestTransformViewport.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2FixedTests/GTFFixedTestTriangleRasterization.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2FixedTests/GTFFixedTestTriangleTiling.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2FixedTests/GTFFixedTestUserClipPlanes.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2FixedTests/GTFFixedTestVertexOrder.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2FixedTests/GTFFixedTestViewportClamp.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2FixedTests/GTFFixedUtilg.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2FixedTests/GTFFixedUtilr.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GTFTestFixedGL.c',

      # Extensions
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2ExtensionTests/GTFExtensionTestConditionalQuery.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2ExtensionTests/GTFExtensionTestDataType1010102.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2ExtensionTests/GTFExtensionTestDebug.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2ExtensionTests/GTFExtensionTestDepth24.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2ExtensionTests/GTFExtensionTestDepth32.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2ExtensionTests/GTFExtensionTestDepthTexture.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2ExtensionTests/GTFExtensionTestDepthTextureCubeMap.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2ExtensionTests/GTFExtensionTestElementIndexUINT.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2ExtensionTests/GTFExtensionTestFBORenderMipmap.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2ExtensionTests/GTFExtensionTestFragmentPrecisionHigh.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2ExtensionTests/GTFExtensionTestFramebufferObject.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2ExtensionTests/GTFExtensionTestMapBuffer.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2ExtensionTests/GTFExtensionTestOcclusionQuery.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2ExtensionTests/GTFExtensionTestPackedDepthStencil.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2ExtensionTests/GTFExtensionTestPointSizeArray.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2ExtensionTests/GTFExtensionTestPointSprite.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2ExtensionTests/GTFExtensionTestReadFormat.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2ExtensionTests/GTFExtensionTestStencil1.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2ExtensionTests/GTFExtensionTestStencil4.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2ExtensionTests/GTFExtensionTestStencil8.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2ExtensionTests/GTFExtensionTestTexture3D.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2ExtensionTests/GTFExtensionTestTextureCompressionASTCLDR.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2ExtensionTests/GTFExtensionTestTextureFloat.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2ExtensionTests/GTFExtensionTestTextureFloatLinear.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2ExtensionTests/GTFExtensionTestTextureNPOT.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2ExtensionTests/GTFExtensionTestUtilp.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2ExtensionTests/GTFExtensionTestVertexArrayObject.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2ExtensionTests/GTFExtensionTestVertexHalfFloat.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GTFTestExtension.c',
    ],
    'gtf_gles2_es_only_srcs': [
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2ExtensionTests/GTFExtensionTestCompressedETC1RGB8Texture.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2ExtensionTests/GTFExtensionTestCompressedPalettedTexture.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2ExtensionTests/GTFExtensionTestEGLCreateContext.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2ExtensionTests/GTFExtensionTestEGLImage.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2ExtensionTests/GTFExtensionTestEGLImageExternal.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2ExtensionTests/GTFExtensionTestRGB8RGBA8.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2ExtensionTests/GTFExtensionTestRequiredInternalformat.c',
      '<(DEPTH)/third_party/khronos_glcts/GTF_ES/glsl/GTF/Source/GL2ExtensionTests/GTFExtensionTestSurfacelessContext.c',
    ],
    'glcts_common_sources': [
      '<(DEPTH)/third_party/khronos_glcts/cts/common/glcConfigList.cpp',
      '<(DEPTH)/third_party/khronos_glcts/cts/common/glcConfigList.hpp',
      '<(DEPTH)/third_party/khronos_glcts/cts/common/glcConfigListCase.cpp',
      '<(DEPTH)/third_party/khronos_glcts/cts/common/glcConfigListCase.hpp',
      '<(DEPTH)/third_party/khronos_glcts/cts/common/glcConfigPackage.cpp',
      '<(DEPTH)/third_party/khronos_glcts/cts/common/glcConfigPackage.hpp',
      '<(DEPTH)/third_party/khronos_glcts/cts/common/glcContext.cpp',
      '<(DEPTH)/third_party/khronos_glcts/cts/common/glcContext.hpp',
      '<(DEPTH)/third_party/khronos_glcts/cts/common/glcFragDepthTests.cpp',
      '<(DEPTH)/third_party/khronos_glcts/cts/common/glcFragDepthTests.hpp',
      '<(DEPTH)/third_party/khronos_glcts/cts/common/glcInfoTests.cpp',
      '<(DEPTH)/third_party/khronos_glcts/cts/common/glcInfoTests.hpp',
      '<(DEPTH)/third_party/khronos_glcts/cts/common/glcShaderIndexingTests.cpp',
      '<(DEPTH)/third_party/khronos_glcts/cts/common/glcShaderIndexingTests.hpp',
      '<(DEPTH)/third_party/khronos_glcts/cts/common/glcShaderIntegerMixTests.cpp',
      '<(DEPTH)/third_party/khronos_glcts/cts/common/glcShaderIntegerMixTests.hpp',
      '<(DEPTH)/third_party/khronos_glcts/cts/common/glcShaderLibrary.cpp',
      '<(DEPTH)/third_party/khronos_glcts/cts/common/glcShaderLibrary.hpp',
      '<(DEPTH)/third_party/khronos_glcts/cts/common/glcShaderLibraryCase.cpp',
      '<(DEPTH)/third_party/khronos_glcts/cts/common/glcShaderLibraryCase.hpp',
      '<(DEPTH)/third_party/khronos_glcts/cts/common/glcShaderLoopTests.cpp',
      '<(DEPTH)/third_party/khronos_glcts/cts/common/glcShaderLoopTests.hpp',
      '<(DEPTH)/third_party/khronos_glcts/cts/common/glcShaderRenderCase.cpp',
      '<(DEPTH)/third_party/khronos_glcts/cts/common/glcShaderRenderCase.hpp',
      '<(DEPTH)/third_party/khronos_glcts/cts/common/glcShaderStructTests.cpp',
      '<(DEPTH)/third_party/khronos_glcts/cts/common/glcShaderStructTests.hpp',
      '<(DEPTH)/third_party/khronos_glcts/cts/common/glcShaderSwitchTests.cpp',
      '<(DEPTH)/third_party/khronos_glcts/cts/common/glcShaderSwitchTests.hpp',
      '<(DEPTH)/third_party/khronos_glcts/cts/common/glcTestCase.cpp',
      '<(DEPTH)/third_party/khronos_glcts/cts/common/glcTestCase.hpp',
      '<(DEPTH)/third_party/khronos_glcts/cts/common/glcTestCaseWrapper.cpp',
      '<(DEPTH)/third_party/khronos_glcts/cts/common/glcTestCaseWrapper.hpp',
      '<(DEPTH)/third_party/khronos_glcts/cts/common/glcTestPackage.cpp',
      '<(DEPTH)/third_party/khronos_glcts/cts/common/glcTestPackage.hpp',
      '<(DEPTH)/third_party/khronos_glcts/cts/common/glcTestSubcase.cpp',
      '<(DEPTH)/third_party/khronos_glcts/cts/common/glcTestSubcase.hpp',
      '<(DEPTH)/third_party/khronos_glcts/cts/common/glcUniformBlockCase.cpp',
      '<(DEPTH)/third_party/khronos_glcts/cts/common/glcUniformBlockCase.hpp',
      '<(DEPTH)/third_party/khronos_glcts/cts/common/glcUniformBlockTests.cpp',
      '<(DEPTH)/third_party/khronos_glcts/cts/common/glcUniformBlockTests.hpp',
    ],
    'glcts_es2_srcs': [
      '<(DEPTH)/third_party/khronos_glcts/cts/gles2/es2cTestPackage.cpp',
      '<(DEPTH)/third_party/khronos_glcts/cts/gles2/es2cTestPackage.hpp',
    ],
    'glcts_gtf_srcs': [
      '<(DEPTH)/third_party/khronos_glcts/cts/gtf/gtfTestCase.cpp',
      '<(DEPTH)/third_party/khronos_glcts/cts/gtf/gtfTestCase.hpp',
      '<(DEPTH)/third_party/khronos_glcts/cts/gtf/gtfTestGroup.cpp',
      '<(DEPTH)/third_party/khronos_glcts/cts/gtf/gtfTestGroup.hpp',
    ],
    'glcts_gtf_wrapper_srcs': [
      '<(DEPTH)/third_party/khronos_glcts/cts/gtf/gtfTestContext.cpp',
      '<(DEPTH)/third_party/khronos_glcts/cts/gtf/gtfTestContext.hpp',
      '<(DEPTH)/third_party/khronos_glcts/cts/gtf/gtfWrapper.cpp',
      '<(DEPTH)/third_party/khronos_glcts/cts/gtf/gtfWrapper.h',
    ],
    'glcts_runner_srcs': [
      '<(DEPTH)/third_party/khronos_glcts/cts/runner/glcTestRunner.cpp',
      '<(DEPTH)/third_party/khronos_glcts/cts/runner/glcTestRunner.hpp',
    ],
    'qphelper_srcs': [
      '<(DEPTH)/third_party/khronos_glcts/framework/qphelper/qpCommandLine.c',
      '<(DEPTH)/third_party/khronos_glcts/framework/qphelper/qpCommandLine.h',
      '<(DEPTH)/third_party/khronos_glcts/framework/qphelper/qpCrashHandler.c',
      '<(DEPTH)/third_party/khronos_glcts/framework/qphelper/qpCrashHandler.h',
      '<(DEPTH)/third_party/khronos_glcts/framework/qphelper/qpDebugOut.c',
      '<(DEPTH)/third_party/khronos_glcts/framework/qphelper/qpDebugOut.h',
      '<(DEPTH)/third_party/khronos_glcts/framework/qphelper/qpInfo.c',
      '<(DEPTH)/third_party/khronos_glcts/framework/qphelper/qpInfo.h',
      '<(DEPTH)/third_party/khronos_glcts/framework/qphelper/qpTestLog.c',
      '<(DEPTH)/third_party/khronos_glcts/framework/qphelper/qpTestLog.h',
      '<(DEPTH)/third_party/khronos_glcts/framework/qphelper/qpWatchDog.c',
      '<(DEPTH)/third_party/khronos_glcts/framework/qphelper/qpWatchDog.h',
      '<(DEPTH)/third_party/khronos_glcts/framework/qphelper/qpXmlWriter.c',
      '<(DEPTH)/third_party/khronos_glcts/framework/qphelper/qpXmlWriter.h',
    ],
    'tcutil_srcs': [
      '<(DEPTH)/third_party/khronos_glcts/framework/common/tcuApp.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/common/tcuApp.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/common/tcuCommandLine.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/common/tcuCommandLine.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/common/tcuCompressedTexture.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/common/tcuCompressedTexture.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/common/tcuDefs.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/common/tcuDefs.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/common/tcuFloat.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/common/tcuFormatUtil.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/common/tcuFuzzyImageCompare.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/common/tcuFuzzyImageCompare.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/common/tcuImageCompare.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/common/tcuImageCompare.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/common/tcuImageIO.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/common/tcuImageIO.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/common/tcuMatrix.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/common/tcuMatrixUtil.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/common/tcuPixelFormat.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/common/tcuPlatform.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/common/tcuPlatform.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/common/tcuRandomValueIterator.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/common/tcuRandomValueIterator.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/common/tcuRenderTarget.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/common/tcuRenderTarget.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/common/tcuResource.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/common/tcuResource.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/common/tcuRGBA.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/common/tcuRGBA.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/common/tcuStringTemplate.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/common/tcuStringTemplate.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/common/tcuSurface.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/common/tcuSurface.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/common/tcuTestCase.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/common/tcuTestCase.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/common/tcuTestCaseWrapper.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/common/tcuTestCaseWrapper.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/common/tcuTestContext.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/common/tcuTestContext.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/common/tcuTestExecutor.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/common/tcuTestExecutor.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/common/tcuTestLog.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/common/tcuTestLog.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/common/tcuTestPackage.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/common/tcuTestPackage.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/common/tcuTexture.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/common/tcuTexture.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/common/tcuTextureUtil.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/common/tcuTextureUtil.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/common/tcuVector.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/common/tcuVectorType.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/common/tcuVectorUtil.hpp',
      # Not used by anything...
      #'<(DEPTH)/third_party/khronos_glcts/framework/common/tcuZipResource.cpp',
      #'<(DEPTH)/third_party/khronos_glcts/framework/common/tcuZipResource.hpp',
    ],
    'glutil_srcs': [
      '<(DEPTH)/third_party/khronos_glcts/framework/opengl/gluCallLogWrapper.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/opengl/gluCallLogWrapper.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/opengl/gluContextInfo.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/opengl/gluContextInfo.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/opengl/gluDefs.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/opengl/gluDefs.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/opengl/gluDrawUtil.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/opengl/gluDrawUtil.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/opengl/gluFboRenderContext.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/opengl/gluFboRenderContext.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/opengl/gluPixelTransfer.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/opengl/gluPixelTransfer.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/opengl/gluPlatform.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/opengl/gluProgram.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/opengl/gluProgram.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/opengl/gluRenderContext.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/opengl/gluRenderContext.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/opengl/gluShaderUtil.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/opengl/gluShaderUtil.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/opengl/gluStateReset.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/opengl/gluStateReset.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/opengl/gluStrUtil.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/opengl/gluStrUtil.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/opengl/gluTexture.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/opengl/gluTexture.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/opengl/gluTextureUtil.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/opengl/gluTextureUtil.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/opengl/gluVarType.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/opengl/gluVarType.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/opengl/gluVarTypeUtil.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/opengl/gluVarTypeUtil.hpp',
    ],
    'glwrapper_srcs': [
      '<(DEPTH)/third_party/khronos_glcts/framework/opengl/wrapper/glw.h',
      '<(DEPTH)/third_party/khronos_glcts/framework/opengl/wrapper/glwDefs.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/opengl/wrapper/glwDefs.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/opengl/wrapper/glwEnums.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/opengl/wrapper/glwFunctionLoader.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/opengl/wrapper/glwFunctions.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/opengl/wrapper/glwFunctions.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/opengl/wrapper/glwInitES20Direct.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/opengl/wrapper/glwInitES20Direct.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/opengl/wrapper/glwInitFunctions.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/opengl/wrapper/glwInitFunctions.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/opengl/wrapper/glwWrapper.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/opengl/wrapper/glwWrapper.hpp',
    ],
    'tcutil_egl_srcs': [
      '<(DEPTH)/third_party/khronos_glcts/framework/egl/tcuEgl.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/egl/tcuEgl.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/egl/tcuEglCallLogWrapper.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/egl/tcuEglCallLogWrapper.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/egl/tcuEglConfigFilter.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/egl/tcuEglConfigFilter.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/egl/tcuEglConfigInfo.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/egl/tcuEglConfigInfo.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/egl/tcuEglPlatform.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/egl/tcuEglPlatform.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/egl/tcuEglStrUtil.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/egl/tcuEglStrUtil.hpp',
    ],
    'debase_srcs': [
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/debase/deDefs.c',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/debase/deDefs.h',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/debase/deFloat16.c',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/debase/deFloat16.h',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/debase/deInt32.c',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/debase/deInt32.h',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/debase/deInt32Test.c',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/debase/deMath.c',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/debase/deMath.h',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/debase/deMemory.c',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/debase/deMemory.h',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/debase/deRandom.c',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/debase/deRandom.h',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/debase/deString.c',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/debase/deString.h',
    ],
    'depool_srcs': [
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/depool/deMemPool.c',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/depool/deMemPool.h',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/depool/dePoolArray.c',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/depool/dePoolArray.h',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/depool/dePoolHash.c',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/depool/dePoolHash.h',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/depool/dePoolHashArray.c',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/depool/dePoolHashArray.h',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/depool/dePoolHashSet.c',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/depool/dePoolHashSet.h',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/depool/dePoolHeap.c',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/depool/dePoolHeap.h',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/depool/dePoolMultiSet.c',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/depool/dePoolMultiSet.h',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/depool/dePoolSet.c',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/depool/dePoolSet.h',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/depool/dePoolStringBuilder.c',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/depool/dePoolStringBuilder.h',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/depool/dePoolTest.c',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/depool/dePoolTest.h',
    ],
    'dethread_srcs': [
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/dethread/deAtomic.c',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/dethread/deAtomic.h',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/dethread/deMutex.h',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/dethread/deSemaphore.h',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/dethread/deThread.h',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/dethread/deThreadLocal.h',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/dethread/deThreadTest.c',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/dethread/deThreadTest.h',
    ],
    'dethread_unix_srcs': [
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/dethread/unix/deMutexUnix.c',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/dethread/unix/deSemaphoreUnix.c',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/dethread/unix/deThreadLocalUnix.c',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/dethread/unix/deThreadUnix.c',
    ],
    'deutil_srcs': [
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/deutil/deClock.c',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/deutil/deClock.h',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/deutil/deCommandLine.c',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/deutil/deCommandLine.h',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/deutil/deDynamicLibrary.c',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/deutil/deDynamicLibrary.h',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/deutil/deFile.c',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/deutil/deFile.h',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/deutil/deProcess.c',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/deutil/deProcess.h',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/deutil/deSocket.c',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/deutil/deSocket.h',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/deutil/deTimer.c',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/deutil/deTimer.h',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/deutil/deTimerTest.c',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/deutil/deTimerTest.h',
    ],
    'decpp_srcs': [
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/decpp/deBlockBuffer.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/decpp/deBlockBuffer.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/decpp/deDefs.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/decpp/deDefs.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/decpp/deDirectoryIterator.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/decpp/deDirectoryIterator.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/decpp/deDynamicLibrary.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/decpp/deDynamicLibrary.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/decpp/deFilePath.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/decpp/deFilePath.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/decpp/deMemPool.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/decpp/deMemPool.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/decpp/deMutex.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/decpp/deMutex.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/decpp/dePoolArray.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/decpp/dePoolArray.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/decpp/dePoolString.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/decpp/dePoolString.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/decpp/deRandom.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/decpp/deRandom.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/decpp/deRingBuffer.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/decpp/deRingBuffer.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/decpp/deSemaphore.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/decpp/deSemaphore.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/decpp/deSharedPtr.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/decpp/deSharedPtr.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/decpp/deSocket.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/decpp/deSocket.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/decpp/deStringUtil.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/decpp/deStringUtil.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/decpp/deThread.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/decpp/deThread.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/decpp/deThreadSafeRingBuffer.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/decpp/deThreadSafeRingBuffer.hpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/decpp/deUniquePtr.cpp',
      '<(DEPTH)/third_party/khronos_glcts/framework/delibs/decpp/deUniquePtr.hpp',
    ],
  }
}
