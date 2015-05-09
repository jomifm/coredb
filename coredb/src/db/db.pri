HEADERS += \
    src/db/metadata/metadatatabs.h \
    src/db/metadata/metadatatable.h \
    src/db/metadata/metadatarow.h \
    src/db/metadata/metadatacolumn.h \
    src/db/manager/sqlfactory.h \
    src/db/manager/dbmanager.h \
    src/db/serializable/serializableobject.h
SOURCES += \
    src/db/manager/dbmanager.cpp \
    src/db/manager/sqlfactory.cpp \
    src/db/metadata/metadatacolumn.cpp \
    src/db/metadata/metadatarow.cpp \
    src/db/metadata/metadatatable.cpp \
    src/db/metadata/metadatatabs.cpp \
    src/db/serializable/serializableobject.cpp
