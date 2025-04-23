# MDP
![](./site/assets/images/MDP_logo.svg)
MarkDown Present is a no nonsense CLI-tool to generate a presentation from markdown.
## I-talent
## install 
Download the zip for your system and unzip it. 
> [!IMPORTANT]  
Don't separate the site and templateSite directories from the binary

## build
to build clone the repo and run 
````bash
cmake .
cmake --build .
````
> [!IMPORTANT]  
When moving the binary don't separate the site and templateSite directories from the binary

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
thanks to mongoose for the webserver,  Iosevka for the font and catppuccin for the colorscheme
