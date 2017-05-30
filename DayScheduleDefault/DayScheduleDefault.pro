TEMPLATE = subdirs
CONFIG+=ordered
SUBDIRS = \
    DaySchedule \
    Tests

app.depends = src
tests.depends = src

OTHER_FILES += \
    defaults.pri
