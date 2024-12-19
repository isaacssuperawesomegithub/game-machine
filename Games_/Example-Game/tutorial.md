# TUTORIAL ON FORMATTING YOUR GAME FOLDER TO BE USED WITH THIS MENU

This assumes a couple of things:
1. You have already written and tested your code
2. You have compiled or otherwise made your code into an executable*
3. Your game folder has the following structure:

### *

If this is not true, please see Isaac.

- [Name of your game's folder] (1)
  - app_info.json (more on this later) (2)
  - [Your game's compiled executable] (3)
  - [The file your code is written in (.py, .cpp, etc file that is the main file for your game) ***OPTIONAL (SEE POINT 1)***] (3)
  - [Your game's icon] (4)
  - [A folder for other assets, classes, files, etc. for your game] (5)
 
For each part of this folder structure:

### 1

The folder should be whatever name you want your game's folder to be called. My personal reccomendation: make it your game's name.

So, if your game is called "Super Awesome Game", name the folder "Super Awesome Game"

### 2

app_info.json is **NOT** optional. Without this, the menu will not be able to detect your game, and therefore it will not be displayed.

An example of this file can be found in this directory. If needed, simply copy and paste the contents of the app_info.json file here into your own, and then replace the values with your own.

### 3

Your game's executable. This should be a file that can be executed ***without*** needing to install runtimes or other libraries.

To test this, send your file to a computer or virtual machine that does not have these things and attempt to run it. If it works as intended, you are good. If not, fix it.

### 4

This should be a file named `icon` with the extension of one of the following:

- `.png`
- `.svg`
- `.bmp`
- `.pic`
- `.jpg`

The icon will be loaded at a 1:1 aspect ratio, so keep this in mind when designing it.

### 5

This folder should contain the other files that your project needs. If you have custom sprites or other assets, put them in this folder.



## To get your game added:

Contact Isaac

## Other questions?

Ask Isaac
