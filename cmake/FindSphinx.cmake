find_program(SPHINX_EXECUTABLE
        NAME sphinx-build
        DOC "Path to sphinx-build executable")

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(Sphinx
        "Failed to find sphinx-build"
        SPHINX_EXECUTABLE)