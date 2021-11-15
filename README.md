# DIY-RawSDL2PlatformerGame
This is a Simple SDL2-based Platformer Game, following part of [the tutorial from Youtube](https://www.youtube.com/watch?v=1KD4Ae0tX0g&list=PL-K0viiuJ2RctP5nlJlqmHGeh66-GOZR_&index=1&t=67s). Based on that, I added some additional stuff such as the type and number of enemies, lifebar, longer map, and various sprite resources.

**Original Version**
<center class="half">
  <img src="https://github.com/lujiazho/DIY-RawSDL2PlatformerGame/blob/main/display/orignal.gif" width="300"/>
</center>

**After Messed Up By Me**
<center class="half">
    <p float="left">
      <img src="https://github.com/lujiazho/DIY-RawSDL2PlatformerGame/blob/main/display/messup3.GIF.GIF" width="300"/>
      <img src="https://github.com/lujiazho/DIY-RawSDL2PlatformerGame/blob/main/display/messup2.GIF" width="300"/>
      <img src="https://github.com/lujiazho/DIY-RawSDL2PlatformerGame/blob/main/display/messup1.GIF" width="300"/>
    </p>
</center>

## Running
Before running it on **Visual Studio**(mine is 2019), unzip the (1)SDLtest/SDLtest/assets.zip (2)SDLtest/SDLtest/SDL-devel-1.2.15-VC.zip (3) SDLtest/SDLtest/Vendor.zip and (4) SDLtest/SDLtest/Debug.zip first. The Vendor.zip is used for reading map.tmx file.

Don't forget to configure the SDL and image library to your Visual Studio. If you don't know how to configure it, my advice is 'google it' because there are lots of tutorials out there.

```
# SDL2 image
SDLtest\SDLtest\SDL-devel-1.2.15-VC\SDL2_image-2.0.5\include
# SDL2
SDLtest\SDLtest\SDL-devel-1.2.15-VC\SDL-1.2.15\include
```

Notes: Don't get confused by the file name of SDL folder. I promise its SDL2 instead of SDL.

## Class Diagram
<img src="https://github.com/lujiazho/DIY-RawSDL2PlatformerGame/blob/main/display/class_diagram.png" width="900"/>

## Personal Reflection
When I developed this game, I have to follow the tutorial at first. After a while, I can add some additional functions but still don't exactly know how to properly or elegantly add that to this game. Because I have to consider expansibility, running efficiency, and the whole framework of this game. I found I've entered into a field of structure design or system design, which is really challenging but interesting. However, at the time of writing, I faced burdensome and challenging workload from graduate school, and I had to put more attention on other as interesting, challenging, and important things in school as GAME DEVELOPING.

So I put the pause button.
