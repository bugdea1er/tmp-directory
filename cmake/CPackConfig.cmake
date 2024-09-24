set(CPACK_PACKAGING_INSTALL_PREFIX /usr)
set(CPACK_PACKAGE_CONTACT "Ilya Andreev <bugdealer@icloud.com>")

# Variables specific to CPack Debian (DEB) generator
set(CPACK_DEB_COMPONENT_INSTALL ON)
set(CPACK_DEBIAN_FILE_NAME DEB-DEFAULT)

set(CPACK_DEBIAN_RUNTIME_PACKAGE_NAME "libtmp${CPACK_PACKAGE_VERSION_MAJOR}")
set(CPACK_DEBIAN_DEVELOPMENT_PACKAGE_NAME "libtmp${CPACK_PACKAGE_VERSION_MAJOR}-dev")

set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
set(CPACK_DEBIAN_PACKAGE_GENERATE_SHLIBS ON)
set(CPACK_DEBIAN_PACKAGE_GENERATE_SHLIBS_POLICY ">=")
set(CPACK_DEBIAN_DEVELOPMENT_PACKAGE_DEPENDS
  "libstdc++-dev, libtmp${CPACK_PACKAGE_VERSION_MAJOR} (= ${CPACK_PACKAGE_VERSION})")

set(CPACK_DEBIAN_RUNTIME_DESCRIPTION "Runtime package")
set(CPACK_DEBIAN_DEVELOPMENT_DESCRIPTION "Development package")

# Variables specific to CPack RPM generator
set(CPACK_RPM_COMPONENT_INSTALL ON)
set(CPACK_RPM_PACKAGE_LICENSE "MIT")
set(CPACK_RPM_FILE_NAME RPM-DEFAULT)

set(CPACK_RPM_RUNTIME_PACKAGE_NAME "tmp")
set(CPACK_RPM_DEVELOPMENT_PACKAGE_NAME "tmp-devel")

set(CPACK_RPM_PACKAGE_AUTOREQPROV ON)
set(CPACK_RPM_DEVELOPMENT_PACKAGE_REQUIRES
  "libstdc++-devel, tmp = ${CPACK_PACKAGE_VERSION}")

set(CPACK_RPM_RUNTIME_PACKAGE_DESCRIPTION "Runtime package")
set(CPACK_RPM_DEVELOPMENT_PACKAGE_DESCRIPTION "Development package")