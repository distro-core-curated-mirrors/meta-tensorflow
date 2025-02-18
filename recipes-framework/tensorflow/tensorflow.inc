DESCRIPTION = "TensorFlow C/C++ Libraries"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=4158a261ca7f2525513e31ba9c50ae98"

DEPENDS = "bazel-native protobuf-native util-linux-native protobuf"
SRCREV = "359c3cdfc5fabac82b3c70b3b6de2b0a8c16874f"
SRC_URI = "git://github.com/tensorflow/tensorflow.git;branch=r2.10;protocol=https \
    file://0001-support-musl.patch \
    file://0002-use-local-bazel-to-workaround-bazel-paralle-issue.patch \
    file://0003-third_party-eigen_archive-workaround-ice-failure-whi.patch \
    file://0004-drop-v2-config.patch \
    file://0005-drop-bazel_toolchains_repositories-to-support-offlin.patch \
    file://0006-Replace-distutils.sysconfig.get_python_lib-with-sysc.patch \
"
S = "${WORKDIR}/git"

DEPENDS += " \
    python3 \
    python3-requests-native \
    python3-numpy-native \
    python3-keras-applications-native \
    python3-keras-preprocessing-native \
    python3-pip-native \
    python3-wheel-native \
    python3-packaging-native \
"

inherit python3native bazel

TF_CONFIG ?= " \
    TF_NEED_CUDA=0 \
    TF_NEED_OPENCL_SYCL=0 \
    TF_NEED_OPENCL=0 \
    TF_CUDA_CLANG=0 \
    TF_DOWNLOAD_CLANG=0 \
    TF_ENABLE_XLA=0 \
    TF_NEED_MPI=0 \
    TF_SET_ANDROID_WORKSPACE=0 \
"

inherit tensorflow_ver

do_compile:append() {
    chmod a+w ${BAZEL_DIR}/output_base/execroot/org_tensorflow/bazel-out/*/bin/tensorflow/lite/python/schema_py_srcs_no_include_all || true
    chmod a+w ${BAZEL_DIR}/output_base/execroot/org_tensorflow/bazel-out/*/bin/tensorflow/lite/python/schema_py_srcs_no_include_all/tflite || true
}
