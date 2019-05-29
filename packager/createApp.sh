#!/bin/sh
########################################################################
#  Copyright - Pacific Community                                       #
#  Droit de copie - Communauté du Pacifique                            #
#  http://www.spc.int/                                                 #
########################################################################
APP=<Name of your application here>
VERSION=1.0.0
LAUNCHER=launcher
CONFIG=config.ini
SCRIPT=<Name of your startup script here>
SHINY=shiny
R_PORTABLE=R-Portable-Mac
ICON=SPC-icon.icns
COPYRIGHT="(c) Pacific Community, 2019"

# Create required folders.
mkdir -vp ${APP}.app/Contents/MacOS ${APP}.app/Contents/Resources

# Make sure PlistBuddy is in the PATH.
PATH="$PATH:/usr/libexec"

# Copy app bits.
cp ${LAUNCHER} ${APP}.app/Contents/MacOS/${APP}
cp ${CONFIG} ${APP}.app/Contents/MacOS/
cp ${SCRIPT} ${APP}.app/Contents/MacOS/
cp -R ${SHINY} ${APP}.app/Contents/MacOS/
cp -R ${R_PORTABLE} ${APP}.app/Contents/MacOS/
cp ${ICON} ${APP}.app/Contents/Resources/

# Prepare app description.
PlistBuddy ${APP}.app/Contents/Info.plist -c "add CFBundleName string ${APP}"
PlistBuddy ${APP}.app/Contents/Info.plist -c "add CFBundleDisplayName string ${APP}"
PlistBuddy ${APP}.app/Contents/Info.plist -c "add CFBundleIconFile string ${ICON}"
PlistBuddy ${APP}.app/Contents/Info.plist -c "add CFBundleVersion string ${VERSION}"
PlistBuddy ${APP}.app/Contents/Info.plist -c "add CFBundleShortVersionString string ${VERSION}"
PlistBuddy ${APP}.app/Contents/Info.plist -c "add NSHumanReadableCopyright string ${COPYRIGHT}"
PlistBuddy ${APP}.app/Contents/version.plist -c "add ProjectName string ${APP}"

# Verify the files.
find ${APP}.app

# Run the app.
open ${APP}.app
