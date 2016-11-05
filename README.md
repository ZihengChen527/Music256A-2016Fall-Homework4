# `BokehExample` : Pretty audio-controlled textures!

This is an OpenFrameworks project that demonstrates how to draw a bunch of "[bokeh](https://photographylife.com/what-is-bokeh)"-style images, randomly colored/sized/positioned, with individual Bokeh brightness (i.e. color alpha value) controlled by an FFT bin magnitude. That is, each Bokeh is activated by a certain frequency in the incoming audio.

## To build

* Extract this directory and place it in your `$OF/apps/myapps/` directory, where `$OF` is the path to your OpenFrameworks directory. For example, this would end up in `/Users/tim/Desktop/of_v0.9.5_osx_release/apps/myApps/ofxBokehExample/` on my OSX machine.

* Download the [ofxFft](https://github.com/kylemcdonald/ofxFft/archive/master.zip) addon and unzip it into `$OF/addons/ofxFft/`. Note that it must have that exact directory name, *not* `ofxFft-master` or anything else.

* Build the program.
    * On OSX, open up `BokehExample.xcodeproj` and build the target for "*BokehExample Release > My Mac (64 bit)*" (or Debug, or 32-bit, etc.)
    * On Linux, you can type `make` from the project directory. Alternately, if you want to use the [QtCreator IDE](https://www.qt.io/ide/), you can open up `BokehExample.creator` and build.
    * Windows is untested, but you should be able to import the project into Visual Studio or QtCreator after you've followed the general OpenFrameworks installation directions.

* The compiled program should now be in your `ofxBokehExample/bin` directory.

## Further reading

* [OpenFrameworks](http://openframeworks.cc/)
* [OpenFrameworks API / Documentation](http://openframeworks.cc/documentation/)
* [OpenFrameworks getting started with the sound stream](http://openframeworks.cc/ofBook/chapters/sound.html#gettingstartedwiththesoundstream)
* [OpenFrameworks advanced graphics tutorial](http://openframeworks.cc/ofBook/chapters/advanced_graphics.html)
* [OpenFrameworks intro to vectors](http://openframeworks.cc/ofBook/chapters/stl_vector.html)