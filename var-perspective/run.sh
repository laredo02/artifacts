#!/bin/bash

eval javac -cp .:libs/jimObjModelImporterJFX.jar:libs/jimStlMeshImporterJFX.jar:/usr/java/opencv-4.1.1/build/bin/opencv-411.jar --module-path /usr/java/javafx-sdk-12.0.2/lib/ --add-modules=javafx.controls,javafx.swing src/Main.java -d build

 cd build

eval java -cp .:../libs/jimObjModelImporterJFX.jar:../libs/jimStlMeshImporterJFX.jar:/usr/java/opencv-4.1.1/build/bin/opencv-411.jar -Djava.library.path=/usr/java/opencv-4.1.1/build/lib --module-path=/usr/java/javafx-sdk-12.0.2/lib --add-modules=javafx.controls,javafx.swing Main &

cd -

