TARGET       = pbcopy
CONFIG      += sailfishapp
QT          += gui
SOURCES     += src/pbcopy.cpp
HEADERS     += src/pbcopy.h
OTHER_FILES += rpm/pbcopy.changes \
               rpm/pbcopy.spec \
               rpm/pbcopy.yaml
