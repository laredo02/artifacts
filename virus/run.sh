#!/bin/bash

eval time javac -cp .:../libs/MyProtocol.jar:opencv-4.1.1/build/bin/opencv-411.jar Main.java && time java -cp .:../libs/MyProtocol.jar:opencv-4.1.1/build/bin/opencv-411.jar -Djava.library.path=opencv-4.1.1/build/lib/ Main

