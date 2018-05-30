MGR = billmgr
PLUGIN = pmvalenock

CFLAGS += -I/usr/local/mgr5/include/billmgr
CXXFLAGS += -I/usr/local/mgr5/include/billmgr

PKGNAMES = billmanager-plugin-pmvalenock
RPM_PKGNAMES ?= $(PKGNAMES)
DEB_PKGNAMES ?= $(PKGNAMES)

WRAPPER += pmvalenock valenockpayment valenockresult

pmvalenock_SOURCES = pmvalenock.cpp
pmvalenock_LDADD = -lbase -lpaymentmodule
pmvalenock_FOLDER = paymethods

valenockpayment_SOURCES = valenockpayment.cpp
valenockpayment_LDADD = -lpaymentcgi
valenockpayment_FOLDER = cgi

valenockresult_SOURCES = valenockresult.cpp
valenockresult_LDADD = -lpaymentcgi
valenockresult_FOLDER = cgi

BASE ?= /usr/local/mgr5
include $(BASE)/src/isp.mk
