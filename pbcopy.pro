TARGET             = pbcopy
CONFIG            += sailfishapp
QT                += quick
DEFINES           += APP_NAME=\"\\\"$${APPNAME}\\\"\" APP_AUTHOR=\"\\\"$${AUTHOR}\\\"\" APP_VERSION=\"\\\"$${VERSION}\\\"\"
SOURCES           += src/pbcopy.cpp
HEADERS           += src/pbcopy.h
OTHER_FILES       += rpm/pbcopy.changes        \
                     rpm/pbcopy.spec           \
                     rpm/pbcopy.yaml
