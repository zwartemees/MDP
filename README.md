# MDP
![](https://raw.githubusercontent.com/zwartemees/MDP/a813d41da8f0cf49d667600f52c81ba8ea6d6028/site/assets/images/MDP_darkmode.svg)
MarkDown Present is a no nonsense CLI-tool to generate a presentation from markdown.
all functions and syntax are documented here.
## I-talent
My I-talent portfolio can be found under I-talent/portfolio_I-Talent_2425.md. Then follow the instructions under [install](#install) or [build](#build) to build from source.
> [!IMPORTANT]  
Don't separate the image folder from the markdown file. MDP won't present a file containing faulty links to local files .
## install 
Download the zip for your system and unzip it. you can find it [here](https://github.com/zwartemees/MDP/releases/tag/Release)
> [!IMPORTANT]  
Don't separate the site and templateSite directories from the binary.

## build
> [!NOTE]  
Cmake is required. latest build was only tested on windows using Visual Studio 17 2022 as compiler and cmake version 3.31.1

to build clone the repo and run 
````bash
cmake .
cmake --build .
````
> [!IMPORTANT]  
When moving the binary don't separate the site and templateSite directories from the binary.

## usage
````bash
To present run MDP <path-to-file>
 other supported arguments:
 -v/ --version
         to show the version number
-t/ --tab
        followed by the number of spaces one tab is.The default is 4.
-r/ --references
       To show a reference page at the end of the slide show. otherwise the refrences will show when a link is clicked but not when presenting
````
-----
## acknowledgements
Thanks to mongoose for the webserver,  Iosevka for the font and catppuccin for the colorscheme.
