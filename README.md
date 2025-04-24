# MDP
![](https://raw.githubusercontent.com/zwartemees/MDP/a813d41da8f0cf49d667600f52c81ba8ea6d6028/site/assets/images/MDP_darkmode.svg)
MarkDown Present is a no nonsense CLI-tool to generate a presentation from markdown.
All functions and syntax are documented [here](https://github.com/zwartemees/MDP/blob/main/documentation/syntax.md).
## I-talent
My I-talent portfolio can be found under ``I-talent/portfolio_I-Talent_2425.md``. Follow the instructions under [install](#install) or [build](#build) to build from source.
> [!IMPORTANT]  
Don't separate the image folder from the markdown file. MDP won't present a file containing faulty links to local files .
## install 
Download the zip for your system and unzip it. You can find it [here](https://github.com/zwartemees/MDP/releases/tag/Release)
> [!IMPORTANT]  
Don't separate the site and templateSite directories from the binary.

## build
> [!NOTE]  
Cmake is required. The latest build was compiled on windows using Visual Studio 17 2022 as compiler and cmake version 3.31.1 and on WSL using cmake and gcc 

To build, clone the repo and run: 
````bash
cmake .
cmake --build .
````
> [!IMPORTANT]  
When moving the binary don't separate the ``site`` and ``templateSite`` directories from the binary.

## usage
> [!NOTE]
Use arrow keys or return to show the next or previous slide

To present, run:

MDP <path-to-file>

Other supported arguments:

- -v, --version
Show the version number.

- -t, --tab
Followed by the number of spaces for a tab. The default is 4.

- -r, --references
Show a reference page at the end of the slide show.
Otherwise, references appear when a link is clicked, but not during the presentation.
    
-----
## acknowledgements
Thanks to mongoose for the web server,  Iosevka for the font and catppuccin for the colorscheme.
