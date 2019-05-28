# ofps-sam-applauncher
Tools used to launch and package standalone R Shiny apps for macOS for the MSE workshop. This may be adapted and reused for other OSes and purposes.

## Prerequisites
You need GCC as well as command lines compilation tools for Xcode. If the ``make`` command is not available you may install it from Homebrew.
You also need to make sure that your R Shiny app is working OK on macOS.

## Launcher
This C++ based tool allows to launch a script through a native executable. One of the issue we've had is that on macOS, ``.sh`` files are either opened in text editor or in XCode if installed.
It's possible to bypass this issue by renaning the script using the ``.command`` file extension. However when this is done, macOS starts the script from the home directory of the end user instead of the directory where the script is located. This causes the script to fail starting the R Shiny app as it cannot find the R interpreter and other resources needed for the application to run.

### Compilation
In order to compile ``launcher``, open a **Terminal** and ``cd`` to the proper location. Then invoke the following command: 

```make```

This should produce an executable named ``launcher``.

The following command removes all objects files from the compilation folder:
```make clean```

The following command removes all objects files as well as the compiled excutable from the compilation folder:
```make clean-all```

### Usage
Once the program has been compiled, you need to copy the files ``launcher`` and ``config.ini`` from the ``launcher`` folder to your portable Shiny project.
Both files should be located in the folder where your startup script and other files and folders for your portable R Shiny app are located.

**config.ini**
This file is a text file that contains a single key pair value. You need to edit this file in order to setup the proper value for your startup script.
The key should always be ``app``
The value should be the exact name of the startup script for your standalone shiny app similar to:

```
app=IntroHCR.sh
```

Feel free to change the value for other apps.

**launcher**
This binary is the pre-compiled launcher, it will seek the ``config.ini file``, load it to learn the value of the command and then attempt to run the command from the current directory where it is located. 
The program exits when the command ends (usually when the browser window is closed).

### Test
If everything is setup properly, you can should have a directory layout similar to:

```
|-- IntroHCR.sh
|-- R-Portable-Mac
|   |-- COPYING
|   |-- Info.plist
|   |-- R
|   |-- Rscript
|   |-- SVN-REVISION
|   |-- bin
|   |-- doc
|   |-- etc
|   |-- fontconfig
|   |-- include
|   |-- lib
|   |-- library
|   |-- man1
|   |-- modules
|   |-- share
|   `-- tests
|-- config.ini
|-- launcher
`-- shiny
    |-- AMPED
    `-- runIntroHCR.R
```

You can now either run ``launcher`` from the command line in the **Terminal** or you may double-click on the ``launcher`` executable in **Finder**. In both cases this should launch the R Shiny app in **Safari**.

From the command line, the app should work straight in the same fashion when you run the shell script directly. The command ends when the **Safari** window is closed.

When starting by double-click in the UI, it’ll open a terminal and then run the command in it. When the browser is closed the terminal ends but the window will remain on screen and needs to be manually closed.

## Packager
Most users on macOS have no experience of **Terminal** or UNIX-style commands and are usually accustomed to double-clicking an app icon in order to start a program. On macOS, apps are just special folders that contain everything needed to run a self-enclosed application.

In order to create an app folder, you need to copy the script file ``createApp.sh`` from the ``packager`` folder to your portable Shiny project.
This file should be located in the folder where your startup script and other files and folders for your portable R Shiny app are located. The files ``launcher`` and ``config.ini`` should also be present in this folder.

**createApp.sh**
This script creates and then launches a macOS app folder (in order to test it), that is a fully redistributable application for macOS. 

Note: the app is not digitally signed as of now and has no icon and very little publisher information.

In order to support additional apps, you may customize variables that are defined ahead of the script. This includes the following variables you may want to customize:

**``APP``**
The name of the application. This will show up as the name of the folder (``<APP>.app``), the name of the application as shown in macOS and other places where this value comes from. The launcher exec will be renamed to this value as well when copied into the app folder (in ``<APP>.app/Contents/MacOS/``). I.e.:

```
APP=HCR
```

**``SCRIPT``**
The exact name of your Shiny app startup script. I.e.:

```
SCRIPT=IntroHCR.sh
```

The rest of the script can remained untouched.

### Test
If everything is setup properly, you can should have a directory layout similar to:

```
|-- IntroHCR.sh
|-- R-Portable-Mac
|   |-- COPYING
|   |-- Info.plist
|   |-- R
|   |-- Rscript
|   |-- SVN-REVISION
|   |-- bin
|   |-- doc
|   |-- etc
|   |-- fontconfig
|   |-- include
|   |-- lib
|   |-- library
|   |-- man1
|   |-- modules
|   |-- share
|   `-- tests
|-- config.ini
|-- createApp.sh
|-- launcher
`-- shiny
    |-- AMPED
    `-- runIntroHCR.R
```

When running `createApp.sh`, it should create a new directory called ``HCR.app`` with the following inner layout:

```
`-- Contents
    |-- Info.plist
    |-- MacOS
    |   |-- HCR
    |   |-- IntroHCR.sh
    |   |-- R-Portable-Mac
    |   |   |-- COPYING
    |   |   |-- Info.plist
    |   |   |-- R
    |   |   |-- Rscript
    |   |   |-- SVN-REVISION
    |   |   |-- bin
    |   |   |-- doc
    |   |   |-- etc
    |   |   |-- fontconfig
    |   |   |-- include
    |   |   |-- lib
    |   |   |-- library
    |   |   |-- man1
    |   |   |-- modules
    |   |   |-- share
    |   |   `-- tests
    |   |-- config.ini
    |   `-- shiny
    |       |-- AMPED
    |       `-- runIntroHCR.R
    |-- Resources
    `-- version.plist
```

You can now either start the application from the command line in a **Terminal** or in **Finder**.

From the command line in **Terminal**, run the following command:

```
open HCR.app
```

From **Finder**, double-click the HCR icon to start the application.