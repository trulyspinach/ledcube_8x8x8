
mkdir /var/folders/8h/j4dtqqy13bs6dsrb5txzqmyr0000gn/T/arduino_build_839600

/Applications/Arduino.app/Contents/Java/arduino-builder -dump-prefs -logger=machine -hardware /Applications/Arduino.app/Contents/Java/hardware -hardware /Users/qihaoyan/Library/Arduino15/packages -tools /Applications/Arduino.app/Contents/Java/tools-builder -tools /Applications/Arduino.app/Contents/Java/hardware/tools/avr -tools /Users/qihaoyan/Library/Arduino15/packages -built-in-libraries /Applications/Arduino.app/Contents/Java/libraries -libraries /Users/qihaoyan/Documents/Arduino/libraries -fqbn=MightyCore:avr:32:pinout=standard,BOD=2v7,LTO=Os,clock=16MHz_external -ide-version=10801 -build-path /var/folders/8h/j4dtqqy13bs6dsrb5txzqmyr0000gn/T/arduino_build_839600 -warnings=none -prefs=build.warn_data_percentage=75 -verbose /Users/qihaoyan/Documents/Arduino/LEDCUBE/LEDCUBE.ino

if [ $? -ne 0 ] ; then exit 1 ; fi

/Applications/Arduino.app/Contents/Java/arduino-builder -compile -logger=machine -hardware /Applications/Arduino.app/Contents/Java/hardware -hardware /Users/qihaoyan/Library/Arduino15/packages -tools /Applications/Arduino.app/Contents/Java/tools-builder -tools /Applications/Arduino.app/Contents/Java/hardware/tools/avr -tools /Users/qihaoyan/Library/Arduino15/packages -built-in-libraries /Applications/Arduino.app/Contents/Java/libraries -libraries /Users/qihaoyan/Documents/Arduino/libraries -fqbn=MightyCore:avr:32:pinout=standard,BOD=2v7,LTO=Os,clock=16MHz_external -ide-version=10801 -build-path /var/folders/8h/j4dtqqy13bs6dsrb5txzqmyr0000gn/T/arduino_build_839600 -warnings=none -prefs=build.warn_data_percentage=75 -verbose /Users/qihaoyan/Documents/Arduino/LEDCUBE/LEDCUBE.ino

if [ $? -ne 0 ] ; then exit 1 ; fi

/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avrdude -C/Applications/Arduino.app/Contents/Java/hardware/tools/avr/etc/avrdude.conf -v -patmega32 -cusbasp -Pusb -Uflash:w:/var/folders/8h/j4dtqqy13bs6dsrb5txzqmyr0000gn/T/arduino_build_839600/LEDCUBE.ino.hex:i
