# Sources
All sources I have or am using to complete this project.

## Texts:
### LearnOpenGL
For most work I'm doing.
https://learnopengl.com/book/book_pdf.pdf

### C Programming Language - 2nd Edition (OCR)
Regularly as a reference for things I have needed a refresher on.

## "Solutions" / Stackoverflow

### https://stackoverflow.com/questions/174531/how-to-read-the-content-of-a-file-to-a-string-in-c
My initial solution wasn't working. I found and adapted this to work with my project.

## AI Use
Here I will document all instances I have used AI, how and why, and their Commit ID

### Initial Commit
I have Used AI to create the CMakeLists.txt content, I have annotated where I have added/changed code.
> Why: I would like to learn CMake, I gave it a hour myself trying to get it to work and I did for building everything statically! However I want anyone to be able to build this without having to find the libraries for their system themselves, static linking the pre built binary won't work for that. I was struggling to get it my CMakeList to work with building GLFW from source and given that CMake specifically is out of scope for this Project/Assignment I used GLM 5.2 to create a template CMakeLists.txt for me and adapted it for my project.

### f632655061389a35b58de06bba68616068b8d382
I used AI to help find where I broke the mesh and buffer binding. This commit is all reccomended changes.
> Why: I spent just under an hour straight on the train with no internet trying to fix this. I went through the learnOpenGL PDF 3 times over tring to see what I did wrong. I wanted to continue working so as soon as I got reception I asked the Copilot if it could see anything wrong. Of course it was something simple I would have got myself with a bit more head smashing the keyboard.