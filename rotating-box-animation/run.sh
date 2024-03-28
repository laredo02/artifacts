#!/bin/bash

eval javac --module-path=/opt/OpenJFX/openjfx-14.0.2.1_linux-x64_bin-sdk/javafx-sdk-14.0.2.1/lib/ --add-modules=javafx.base,javafx.controls,javafx.fxml,javafx.graphics,javafx.media,javafx.swing,javafx.web Main.java && java --module-path=/opt/OpenJFX/openjfx-14.0.2.1_linux-x64_bin-sdk/javafx-sdk-14.0.2.1/lib/ --add-modules=javafx.base,javafx.controls,javafx.fxml,javafx.graphics,javafx.media,javafx.swing,javafx.web -Dprism.forceGPU=true Main
